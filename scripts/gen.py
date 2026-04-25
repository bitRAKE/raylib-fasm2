"""Generate fasmg projection of the raylib C API.

Reads the JSON description (`raylib_api.json`) for the API's structural
shape and parses `raylib.h` for the trailing `// comment` of each RLAPI
declaration so we can infer which integer parameters are *actually*
typed against an enum (`int key` → KeyboardKey, etc.). The C signatures
themselves erase that information; the docstrings retain it.

Outputs (under ./inc):
    raylib_types.inc       struct definitions
    raylib_aliases.inc     `define` aliases
    raylib_enums.inc       enum members under `namespace RayLib`
    raylib_colors.inc      26 predefined colors as packed dwords
    raylib_imports.inc     `import raylib, _Func,'Func', …`
    raylib_api.inc         calminstruction wrapper per function
    raylib.inc             master include

Usage:
    python gen.py [--api PATH/TO/raylib_api.json] [--header PATH/TO/raylib.h]
"""
from __future__ import annotations

import argparse
import json
import os
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

REPO_ROOT = Path(__file__).parent
RAYLIB_PATH = Path(os.environ.get("RAYLIB_PATH",
                                  REPO_ROOT.parent / "raylib"))
DEFAULT_API = RAYLIB_PATH / "tools" / "rlparser" / "output" / "raylib_api.json"
DEFAULT_HEADER = RAYLIB_PATH / "src" / "raylib.h"
OUT = REPO_ROOT / "inc"

IMPORT_PREFIX = "_"  # data-label prefix to keep CALM wrappers from colliding
                     # with their import-table doppelgängers.

# ---------------------------------------------------------------------------
# JSON loading (the upstream file occasionally has unescaped " inside
# description strings — we sanitize line-by-line).
# ---------------------------------------------------------------------------

def load_api(path: Path) -> dict:
    text = path.read_text(encoding="utf-8")
    fixed = []
    pat = re.compile(r'^(\s*"description":\s*)"(.*)"(,?\s*)$')
    for line in text.splitlines():
        m = pat.match(line)
        if m:
            prefix, body, suffix = m.group(1), m.group(2), m.group(3)
            body_fixed = body.replace('\\"', '\x00').replace('"', '\\"').replace('\x00', '\\"')
            line = prefix + '"' + body_fixed + '"' + suffix
        fixed.append(line)
    return json.loads('\n'.join(fixed))

# ---------------------------------------------------------------------------
# raylib.h parser. Captures the trailing comment for each RLAPI declaration.
# ---------------------------------------------------------------------------

# Greedy on the body so functions whose declaration is split across multiple
# lines still match (none in 6.0, but cheap insurance).
DECL_RE = re.compile(
    r"^RLAPI\s+(?P<ret>[^;]+?[\s\*])(?P<name>[A-Za-z_]\w*)\s*"
    r"\((?P<params>[^)]*)\)\s*;\s*(?://\s*(?P<doc>.*))?$"
)

def parse_header(path: Path) -> dict[str, str]:
    """Return {function_name: trailing_comment} from raylib.h declarations."""
    text = path.read_text(encoding="utf-8")
    out: dict[str, str] = {}
    for line in text.splitlines():
        m = DECL_RE.match(line.strip())
        if not m:
            continue
        out[m.group("name")] = (m.group("doc") or "").strip()
    return out

# ---------------------------------------------------------------------------
# Enum inference: derive {(function, param) -> enum-name} via three sources,
# in order of trust:
#   1. Comment hint — uppercase tokens in the trailing // comment that are
#      members of exactly one enum. This catches `LOG_INFO`/`KEY_ESCAPE`-style
#      mentions and is the most reliable signal.
#   2. Param-name heuristics — when a parameter is unambiguously named (`key`,
#      `axis`, `cursor`, `logLevel`, …).
#   3. Manual overrides — the few cases neither catches (`int mode` for
#      BeginBlendMode, `int mode` for UpdateCamera, etc.).
# ---------------------------------------------------------------------------

# Param name → preferred enum, plus optional context predicates. Each rule is
# (param_name, predicate, enum). predicate is a callable taking the function
# dict from the JSON; return True to apply. These act as a *fallback* when
# the AST inference (loaded from inferred_enums.json) finds no evidence —
# typically because raylib's own examples never call the function.
def _no_gamepad(fn): return all("gamepad" not in p["name"].lower() for p in fn.get("params", []))
def _has_gamepad(fn): return any("gamepad" in p["name"].lower() for p in fn.get("params", []))

PARAM_NAME_RULES: list[tuple[str, callable, str]] = [
    ("key",       lambda fn: True,     "KeyboardKey"),
    ("logLevel",  lambda fn: True,     "TraceLogLevel"),
    ("axis",      lambda fn: True,     "GamepadAxis"),
    ("cursor",    lambda fn: True,     "MouseCursor"),
    ("button",    _has_gamepad,        "GamepadButton"),
    ("button",    _no_gamepad,         "MouseButton"),
    ("gesture",   lambda fn: True,     "Gesture"),
    ("uniformType", lambda fn: True,   "ShaderUniformDataType"),
]

# Inferred-enums JSON: produced by `infer_enums.py`, which walks every .c
# file in raylib/examples + raylib/src via clang's AST and records the
# enum-constant values that flow into each RLAPI argument position.
INFERRED_ENUMS_JSON = Path(__file__).parent / "inferred_enums.json"


def load_inferred() -> dict[tuple[str, int], tuple[str, int]]:
    """Return {(function_name, argpos): (enum_name, evidence_count)}."""
    if not INFERRED_ENUMS_JSON.exists():
        return {}
    raw = json.loads(INFERRED_ENUMS_JSON.read_text(encoding="utf-8"))
    out: dict[tuple[str, int], tuple[str, int]] = {}
    for r in raw:
        out[(r["function"], r["argpos"])] = (r["enum"], r["evidence_count"])
    return out

# Cases that need a hand: same param name across functions but different enum.
MANUAL_OVERRIDES: dict[tuple[str, str], str] = {
    # function, param  ->  enum
    ("BeginBlendMode",  "mode"):  "BlendMode",
    ("UpdateCamera",    "mode"):  "CameraMode",

    ("SetGesturesEnabled", "flags"): "Gesture",
    ("IsGestureDetected",  "gesture"): "Gesture",

    ("SetTextureFilter",   "filter"): "TextureFilter",
    ("SetTextureWrap",     "wrap"):   "TextureWrap",

    ("LoadTextureCubemap", "layout"): "CubemapLayout",
    ("DrawTextureNPatch",  "nPatchInfo"): None,  # struct, no transform

    ("LoadFontEx",          "type"): "FontType",
    ("LoadFontData",        "type"): "FontType",
    ("ImageFormat",         "newFormat"): "PixelFormat",
    ("LoadImageFromMemory", "fileType"): None,
    ("LoadImageRaw",        "format"): "PixelFormat",
    ("GetPixelColor",       "format"): "PixelFormat",
    ("SetPixelColor",       "format"): "PixelFormat",
    ("GetPixelDataSize",    "format"): "PixelFormat",

    # Window flag-bag: every Set/Clear/IsWindowState takes ConfigFlags.
    # Intentional: reinforces in case the comment scan misses (the comment for
    # Set/ClearWindowState doesn't mention any FLAG_* constant).
    ("SetWindowState",   "flags"): "ConfigFlags",
    ("ClearWindowState", "flags"): "ConfigFlags",
    ("IsWindowState",    "flag"):  "ConfigFlags",
    ("SetConfigFlags",   "flags"): "ConfigFlags",
}

INT_PARAM_TYPES = {"int", "unsigned int", "unsigned short", "short", "unsigned char"}

# Comment-based inference fires only for parameter names that *plausibly* hold
# an enum value. Restricting this list stops things like `SetWindowMinSize(int
# width, int height) // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)`
# from incorrectly typing `width` and `height` as ConfigFlags.
ENUM_CANDIDATE_NAMES = {
    "flag", "flags", "mode", "type", "format", "key", "button", "axis",
    "cursor", "level", "logLevel", "filter", "wrap", "gesture", "layout",
    "uniformType", "attribType", "locIndex", "newFormat", "fileType",
    "shaderType", "blendMode",
}


def build_typed_args(api: dict, comments: dict[str, str]) -> dict[str, dict[str, str]]:
    """Decide, per (function, parameter), which enum (if any) the arg is
    typed against. Source priority:
      1. AST evidence (inferred_enums.json from `_infer_enums.py`) — rock
         solid because it's recovered from real call sites in raylib's
         examples/src.
      2. Manual override map for known typed pairs that examples don't
         exercise (e.g. `IsKeyUp`).
      3. Comment-token heuristic (legacy fallback) — only fires when the
         param name is enum-y and the function's trailing // comment
         mentions a unique enum's members.
      4. Param-name heuristic (`key` → KeyboardKey, etc.).
    """
    member_to_enums: dict[str, set[str]] = defaultdict(set)
    for e in api["enums"]:
        for m in e["values"]:
            member_to_enums[m["name"]].add(e["name"])

    inferred = load_inferred()
    typed: dict[str, dict[str, str]] = {}
    n_ast = n_override = n_comment = n_rule = 0
    skipped_ambiguous: list[tuple[str, str]] = []

    for fn in api["functions"]:
        fname = fn["name"]
        comment = comments.get(fname, "")
        per_fn: dict[str, str] = {}
        params = fn.get("params") or []

        for argpos, p in enumerate(params):
            ptype, pname = p["type"], p["name"]
            if ptype not in INT_PARAM_TYPES:
                continue

            # 1 — AST evidence first (highest trust).
            ast_hit = inferred.get((fname, argpos))
            if ast_hit:
                per_fn[pname] = ast_hit[0]
                n_ast += 1
                continue

            # 2 — manual override (incl. explicit None to opt out).
            key = (fname, pname)
            if key in MANUAL_OVERRIDES:
                enum = MANUAL_OVERRIDES[key]
                if enum is not None:
                    per_fn[pname] = enum
                    n_override += 1
                continue

            # 3 — comment scan (only for enum-y param names).
            if pname in ENUM_CANDIDATE_NAMES:
                tokens = re.findall(r"[A-Z][A-Z0-9_]{2,}", comment)
                tally: Counter[str] = Counter()
                for t in tokens:
                    for enum in member_to_enums.get(t, ()):
                        tally[enum] += 1
                if tally:
                    top, ntop = tally.most_common(1)[0]
                    if ntop > 0 and (len(tally) == 1 or ntop > tally.most_common(2)[1][1]):
                        per_fn[pname] = top
                        n_comment += 1
                        continue

            # 4 — param-name heuristic.
            for rname, pred, enum in PARAM_NAME_RULES:
                if pname == rname and pred(fn):
                    per_fn[pname] = enum
                    n_rule += 1
                    break
            else:
                if pname in {"flags", "flag", "mode", "type", "format",
                             "filter", "wrap", "layout"}:
                    skipped_ambiguous.append(key)

        if per_fn:
            typed[fname] = per_fn

    print(f"  typed-args: ast={n_ast}, override={n_override}, "
          f"comment={n_comment}, rule={n_rule}; "
          f"unmapped-but-suspicious={len(skipped_ambiguous)}")
    if skipped_ambiguous[:5]:
        for fn, p in skipped_ambiguous[:5]:
            print(f"    (todo: {fn}({p}))")
    return typed

# ---------------------------------------------------------------------------
# Type mapping for struct fields.
# ---------------------------------------------------------------------------

PRIM = {
    "char":               "db ?",
    "unsigned char":      "db ?",
    "signed char":        "db ?",
    "bool":               "db ?",
    "short":              "dw ?",
    "unsigned short":     "dw ?",
    "int":                "dd ?",
    "unsigned int":       "dd ?",
    "long":               "dd ?",
    "unsigned long":      "dd ?",
    "float":              "dd ?",
    "double":             "dq ?",
    "long long":          "dq ?",
    "unsigned long long": "dq ?",
}

PRIM_SIZE = {
    "char": 1, "unsigned char": 1, "signed char": 1, "bool": 1,
    "short": 2, "unsigned short": 2,
    "int": 4, "unsigned int": 4, "long": 4, "unsigned long": 4, "float": 4,
    "double": 8, "long long": 8, "unsigned long long": 8,
}


def c_type_size(c_type: str) -> int | None:
    """Best-effort byte size for a C type (None if unknown). Used to
    decide which struct-by-value args need to be passed as pointers under
    the Win64 ABI."""
    t = c_type.strip()
    if t.endswith("*"):
        return 8
    m = ARR_RE.match(t)
    if m:
        inner, n = m.group(1).strip(), int(m.group(2))
        inner = _alias_to_struct.get(inner, inner)
        s = PRIM_SIZE.get(inner) or _struct_size.get(inner)
        return s * n if s is not None else None
    if t in PRIM_SIZE:
        return PRIM_SIZE[t]
    resolved = _alias_to_struct.get(t, t)
    return _struct_size.get(resolved)


def c_type_alignment(c_type: str) -> int:
    """Natural alignment for a C type under the Microsoft x64 ABI:
    primitive type → its size; pointer → 8; array of T → alignment of T;
    struct → max alignment over its fields (already computed)."""
    t = c_type.strip()
    if t.endswith("*"):
        return 8
    m = ARR_RE.match(t)
    if m:
        return c_type_alignment(m.group(1).strip())
    if t in PRIM_SIZE:
        return PRIM_SIZE[t]
    resolved = _alias_to_struct.get(t, t)
    return _struct_alignment.get(resolved, 8)

_known_structs: set[str] = set()

# Computed struct sizes in bytes — used to decide when a struct arg is too
# big to be passed by value in a Win64 GP register (only sizes 1, 2, 4, 8
# qualify; everything else is passed by pointer to caller-allocated copy).
_struct_size: dict[str, int] = {}

# Per-struct natural alignment (max field alignment), used both to insert
# padding before fields that need it inside a parent struct, and to round
# the struct's total size up to its alignment boundary.
_struct_alignment: dict[str, int] = {}

# Type aliases resolved to their underlying struct name (Texture2D -> Texture).
_alias_to_struct: dict[str, str] = {}

ARR_RE = re.compile(r'^([\w\s\*]+?)\s*\[(\d+)\]$')

# Field names that collide with fasmg directives or with macros pulled in by
# the Win64 framework (pe.inc, proc64.inc).
RESERVED_FIELDS = {"data", "format", "frame"}


def field_name(c_name: str) -> str:
    if c_name in RESERVED_FIELDS:
        return c_name + "_"
    return c_name


def field_directive(c_type: str) -> str:
    t = c_type.strip()
    if t.endswith("*"):
        return "dq ?"
    m = ARR_RE.match(t)
    if m:
        inner, n = m.group(1).strip(), int(m.group(2))
        # Resolve struct aliases (Texture2D → Texture).
        inner = _alias_to_struct.get(inner, inner)
        if inner in PRIM:
            unit = PRIM[inner].split()[0]
            return f"{unit} {','.join(['?']*n)}"
        if inner in _known_structs:
            return f"rb {n}*sizeof.{inner}"
        return f"rb {n}"
    if t in PRIM:
        return PRIM[t]
    # Resolve struct aliases (Texture2D → Texture) before embedding.
    resolved = _alias_to_struct.get(t, t)
    if resolved in _known_structs:
        return resolved
    return "dq ?"  # unknown alias: fall back to a 64-bit slot


def emit_struct(s: dict, out: list[str]) -> None:
    """Emit a fasmg `struct` definition that matches the C compiler's
    layout: each field is preceded by `rb N` padding to reach its
    natural alignment, and the struct's total size is rounded up to its
    own alignment so arrays of it pack correctly. raylib's structs
    aren't `__attribute__((packed))`, so this is the only layout that
    interoperates with the prebuilt `raylib.dll` / `raylib.lib`.
    """
    name = s["name"]
    if s.get("description"):
        out.append(f"; {s['description']}")
    out.append(f"struct {name}")

    field_names = [field_name(f["name"]) for f in s["fields"]]
    pad_w = max(len(n) for n in field_names) if field_names else 0

    offset = 0
    struct_align = 1
    pad_index = 0          # serial counter for unique pad-field labels

    for f in s["fields"]:
        sz = c_type_size(f["type"])
        align = c_type_alignment(f["type"])
        # Align the current offset up to this field's boundary.
        gap = (-offset) % align
        if gap > 0:
            out.append(f"  {'_pad' + str(pad_index):<{pad_w}}  rb {gap}")
            pad_index += 1
            offset += gap
        directive = field_directive(f["type"])
        renamed = field_name(f["name"])
        note = ""
        if renamed != f["name"]:
            note = f"  ; renamed from `{f['name']}`"
        desc = f"  ; {f['description']}" if f.get("description") else ""
        out.append(f"  {renamed:<{pad_w}}  {directive}{desc}{note}")
        if sz is None:
            offset = None
            break
        offset += sz
        if align > struct_align:
            struct_align = align

    if offset is not None:
        # Trailing padding so `sizeof Foo` is a multiple of the alignment.
        gap = (-offset) % struct_align
        if gap > 0:
            out.append(f"  {'_pad' + str(pad_index):<{pad_w}}  rb {gap}")
            offset += gap
        _struct_size[name] = offset
        _struct_alignment[name] = struct_align

    out.append("ends")
    out.append("")
    _known_structs.add(name)


def build_alias_map(api: dict) -> None:
    for a in api["aliases"]:
        if a["name"].startswith("*"):
            # Pointer-alias (e.g. `*ModelAnimPose -> Transform`). The alias
            # name represents "pointer to Transform". For sizing purposes
            # it occupies a single pointer slot (8 bytes on x64) with
            # 8-byte alignment.
            stripped = a["name"].lstrip("*")
            _struct_size[stripped] = 8
            _struct_alignment[stripped] = 8
            continue
        _alias_to_struct[a["name"]] = a["type"]


def write_types(api: dict) -> None:
    out: list[str] = []
    out.append("; raylib structs — generated; do not edit by hand")
    out.append(";")
    out.append("; A handful of C field names collide with fasmg directives or with")
    out.append("; macros pulled in by the Win64 framework (pe.inc, proc64.inc).")
    out.append("; Affected fields are renamed with a trailing underscore:")
    for n in sorted(RESERVED_FIELDS):
        out.append(f";   {n} -> {n}_")
    out.append("")
    for s in api["structs"]:
        emit_struct(s, out)
    (OUT / "raylib_types.inc").write_text("\n".join(out), encoding="utf-8")
    print(f"wrote inc/raylib_types.inc ({len(api['structs'])} structs)")


def write_aliases(api: dict) -> None:
    out: list[str] = [
        "; raylib type aliases — generated",
        ";",
        "; Each non-pointer alias gets:",
        ";   1. A `define` so expressions referring to the alias resolve",
        ";      to the underlying struct name (e.g. in field types).",
        ";   2. A labeled CALM `(instance) AliasName values&` that",
        ";      delegates to the underlying struct's instantiator. fasmg",
        ";      doesn't follow `define` substitutions when looking up an",
        ";      *instruction* name, so without this CALM the line",
        ";      `tex Texture2D` would fail to recognize Texture2D as a",
        ";      struct constructor.",
        "",
    ]
    for a in api["aliases"]:
        if a["name"].startswith("*"):
            # `*ModelAnimPose` etc. — array-of-Transform views. Expose as a
            # 64-bit slot for now; the consumer treats it as a pointer.
            name = a["name"].lstrip("*")
            out.append(f"; {a.get('description','')}")
            out.append(f"struct {name}")
            out.append(f"  ptr dq ?")
            out.append(f"ends")
            out.append("")
            continue
        out.append(f"define {a['name']} {a['type']}")
        # Build the underlying struct name as a symbolic value, then call
        # struct?.instantiate. Passing the bare identifier `Texture`
        # would yield its label-value (sizeof Texture, since `ends`
        # publishes the struct as a label too); we need the symbolic name.
        out.append(f"calminstruction (instance) {a['name']} values&")
        out.append(f"\tlocal sname")
        out.append(f"\tarrange sname, ={a['type']}")
        out.append(f"\tcall struct?.instantiate, instance, sname, values")
        out.append(f"end calminstruction")
        out.append("")
    (OUT / "raylib_aliases.inc").write_text("\n".join(out), encoding="utf-8")
    print(f"wrote inc/raylib_aliases.inc ({len(api['aliases'])} aliases)")


def write_enums(api: dict) -> None:
    out: list[str] = [
        "; raylib enums — generated",
        ";",
        "; Members live under `RayLib.<EnumName>.<MEMBER>`. Wrappers `transform`",
        "; their typed parameters against `RayLib.<EnumName>` so callers can",
        "; write the *short* name (KEY_ESCAPE, FLAG_VSYNC_HINT) without",
        "; polluting the global namespace.",
        ";",
        "; The `define <Name> <Name>` anchors are required — fasmg's `transform`",
        "; with a namespace argument needs the namespace path to resolve to a",
        "; real symbol, not just a parent of `define X.Y` children. Without these",
        "; anchors `transform val, RayLib.ConfigFlags` silently does nothing.",
        "",
        "define RayLib RayLib",
        "",
        "namespace RayLib",
        "",
    ]
    for e in api["enums"]:
        if e.get("description"):
            out.append(f"  ; {e['description']}")
        out.append(f"  define {e['name']} {e['name']}")
        members = e["values"]
        pad = max(len(m["name"]) for m in members) if members else 0
        for m in members:
            comment = f"  ; {m['description']}" if m.get("description") else ""
            out.append(
                f"  define {e['name']}.{m['name']:<{pad}}  {m['value']}{comment}"
            )
        out.append("")
    out.append("end namespace ; RayLib")
    (OUT / "raylib_enums.inc").write_text("\n".join(out), encoding="utf-8")
    nval = sum(len(e["values"]) for e in api["enums"])
    print(f"wrote inc/raylib_enums.inc ({len(api['enums'])} enums, {nval} values)")


def write_colors(api: dict) -> None:
    out: list[str] = [
        "; raylib predefined colors — generated",
        "",
        "; Each color is a packed RGBA dword. Win64 ABI puts struct-by-value",
        "; <= 8 bytes in a register, so passing one of these as a Color arg",
        "; produces the right machine code without any wrapping.",
        "",
        "; If you need a Color *instance* (e.g. to take its address), declare",
        "; one yourself in your data section:",
        ";     myColor Color r:200, g:200, b:200, a:255",
        "",
    ]
    color_defs = [d for d in api["defines"] if d["type"] == "COLOR"]
    rgba = re.compile(r"\{\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\}")
    for d in color_defs:
        m = rgba.search(d["value"])
        if not m:
            continue
        r, g, b, a = (int(x) for x in m.groups())
        packed = (a << 24) | (b << 16) | (g << 8) | r
        out.append(
            f"define {d['name']} 0x{packed:08X}  ; {d['description']} "
            f"({r},{g},{b},{a})"
        )
    (OUT / "raylib_colors.inc").write_text("\n".join(out), encoding="utf-8")
    print(f"wrote inc/raylib_colors.inc ({len(color_defs)} colors)")


def write_imports(api: dict) -> None:
    """Two linkage flavors:

    - `raylib_imports.inc` (DLL mode, default): emits an `import raylib,
      RLAPI.Func, 'Func', …` block for the user's `.idata` section.
      Combined with `raylib_dll_dispatch.inc` (the RLAPI dispatcher in
      DLL mode), this produces a self-contained PE64 EXE with no
      external linker step.

    - `raylib_extrn.inc` (OBJ mode): emits `extrn 'Func' as RLAPI.Func`
      declarations. Combined with `raylib_obj_dispatch.inc` (the RLAPI
      dispatcher in OBJ mode), this lets fasmg emit a COFF object that
      `link.exe` can resolve against `raylib.lib`.
    """
    names = [f["name"] for f in api["functions"]]

    # ---- DLL: import table ------------------------------------------------
    out: list[str] = [
        "; raylib import table — DLL mode, generated",
        ";",
        "; Place inside an `.idata` section like so:",
        ";   section '.idata' import data readable writeable",
        ";     library raylib, 'raylib.dll'",
        ";     include 'raylib_imports.inc'",
        ";",
        "; Labels are emitted under the `RLAPI.` namespace so the dispatcher",
        "; (raylib_dll_dispatch.inc) can do `invoke RLAPI.<FuncName>`",
        "; without colliding with the same-named wrapper CALMs.",
        "",
        "import raylib, \\",
    ]
    for i, n in enumerate(names):
        is_last = i == len(names) - 1
        out.append(f"\tRLAPI.{n},'{n}'" + ("" if is_last else ", \\"))
    (OUT / "raylib_imports.inc").write_text("\n".join(out), encoding="utf-8")
    print(f"wrote inc/raylib_imports.inc ({len(names)} imports, DLL mode)")

    # ---- OBJ: extrn declarations (gated by `if used`) ---------------------
    # Without the gate, every one of the 600 RLAPI symbols gets an
    # entry in the COFF symbol table and the linker tries to resolve all
    # of them against raylib.lib — failing on any function the user's
    # specific raylib.lib version doesn't have. The `if used …` guard
    # makes fasmg only emit symbols the program actually references.
    out = [
        "; raylib extrn declarations — OBJ mode, generated",
        ";",
        "; Place anywhere in the source after `format MS64 COFF`:",
        ";   include 'raylib_extrn.inc'",
        ";",
        "; The external symbol is `Func` (raylib.lib's actual export); we",
        "; alias it to `RLAPI.Func` so the dispatcher can address it the",
        "; same way it would in DLL mode. Each declaration is gated by",
        "; `if used RLAPI.Func` so only referenced symbols make it into",
        "; the .obj — important when raylib.lib's API surface is a",
        "; subset of what this projection covers.",
        "",
    ]
    for n in names:
        out.append(f"if used RLAPI.{n}")
        out.append(f"\textrn '{n}' as RLAPI.{n}")
        out.append(f"end if")
    (OUT / "raylib_extrn.inc").write_text("\n".join(out), encoding="utf-8")
    print(f"wrote inc/raylib_extrn.inc ({len(names)} extrn declarations, OBJ mode)")


# ---------------------------------------------------------------------------
# RLAPI dispatcher CALMs (one per linkage flavor).
# ---------------------------------------------------------------------------

DLL_DISPATCH = """
; raylib_dll_dispatch.inc — DLL-mode RLAPI dispatcher (generated)
;
; The wrappers in raylib_api.inc all funnel through `call RLAPI, fname,
; args`. In DLL mode `RLAPI.<FuncName>` is the IAT slot built by
; raylib_imports.inc (a 64-bit pointer to the function), and we use
; `invoke` (which expands to `mov rax,[RLAPI.Func]; call rax`).

calminstruction RLAPI fname*, args&
\tlocal cmd
\tmatch , args
\tjyes _no_args
\tarrange cmd, =invoke =RLAPI.fname, args
\tassemble cmd
\texit
    _no_args:
\tarrange cmd, =invoke =RLAPI.fname
\tassemble cmd
end calminstruction
"""

OBJ_DISPATCH = """
; raylib_obj_dispatch.inc — OBJ-mode RLAPI dispatcher (generated)
;
; In COFF/OBJ mode the linker resolves the symbol so we use a *direct*
; call (`fastcall` macro from proc64.inc, which expands to `call proc`,
; not `call [proc]`). The extrn declarations in raylib_extrn.inc make
; `RLAPI.<FuncName>` link to raylib.lib's `<FuncName>` symbol.

calminstruction RLAPI fname*, args&
\tlocal cmd
\tmatch , args
\tjyes _no_args
\tarrange cmd, =fastcall =RLAPI.fname, args
\tassemble cmd
\texit
    _no_args:
\tarrange cmd, =fastcall =RLAPI.fname
\tassemble cmd
end calminstruction
"""


def write_dispatchers() -> None:
    (OUT / "raylib_dll_dispatch.inc").write_text(DLL_DISPATCH.lstrip(), encoding="utf-8")
    (OUT / "raylib_obj_dispatch.inc").write_text(OBJ_DISPATCH.lstrip(), encoding="utf-8")
    print("wrote inc/raylib_dll_dispatch.inc, inc/raylib_obj_dispatch.inc")

# ---------------------------------------------------------------------------
# Per-function CALM wrapper.
# ---------------------------------------------------------------------------

def emit_wrapper(fn: dict, out: list[str], typed_args: dict[str, dict[str, str]]) -> None:
    """Emit a CALM wrapper that funnels through `call RLAPI, fname, args`.

    The wrapper:
      1. Validates parameter count via the `*` (required) markers.
      2. For each typed parameter, runs a two-pass `transform`: first an
         unbound pass (current scope) so user `define` aliases expand,
         then a namespace-bound pass to resolve short enum names. Loop
         so chained aliases keep unfolding.
      3. For functions whose return type is a struct > 8 bytes, the
         Win64 ABI passes a hidden destination pointer as the first
         argument. The wrapper exposes that as an explicit `dest*` param
         so the caller writes `LoadImage addr img, _filename` (where
         `img Image` was declared in their data section); the wrapper
         passes `dest` straight through to fastcall — the `addr` keyword
         is the user's responsibility, matching the convention for any
         other struct-by-pointer arg.
      4. Builds an `args` symbolic value out of the parameter substitutions
         (with literal commas), then does `call RLAPI, fname, args`. The
         RLAPI dispatcher (loaded from raylib_dll_dispatch.inc or
         raylib_obj_dispatch.inc) decides indirect-via-IAT vs direct-call
         based on the build mode.
    """
    name = fn["name"]
    params = fn.get("params") or []
    desc = fn.get("description", "")
    typed = typed_args.get(name, {})

    is_variadic = any(p.get("type") == "..." or p.get("name") == "..." for p in params)
    head_params = [p for p in params if p.get("type") != "..." and p.get("name") != "..."]

    # Does this function return a struct > 8 bytes? If so, prepend a
    # hidden `dest*` parameter and route it via `=addr dest` as the first
    # argument to invoke.
    ret_type = fn.get("returnType", "void").strip()
    needs_hidden_dest = False
    if ret_type and not ret_type.endswith("*") and ret_type not in PRIM:
        sz = c_type_size(ret_type)
        if sz is not None and sz > 8:
            needs_hidden_dest = True

    if desc:
        out.append(f"; {desc}")
        if needs_hidden_dest:
            out.append(f"; (returns {ret_type} via hidden first-arg pointer — pass `dest` as the destination buffer)")

    # Signature.
    if not params and not needs_hidden_dest:
        out.append(f"calminstruction {name}")
    else:
        sig_parts: list[str] = []
        if needs_hidden_dest:
            sig_parts.append("dest*")
        sig_parts.extend(f"{p['name']}*" for p in head_params)
        if is_variadic:
            sig_parts.append("rest&")
        out.append(f"calminstruction {name} {', '.join(sig_parts)}")

    # Typed-arg validation. CALM labels are local to the `calminstruction`
    # they appear in, so we can use the short name `reduce` (or
    # `reduce_<param>` when more than one typed param needs its own loop)
    # without fear of colliding across wrappers.
    typed_here = [p for p in head_params if p["name"] in typed]
    for p in typed_here:
        pn = p["name"]
        label = "reduce" if len(typed_here) == 1 else f"reduce_{pn}"
        out.append(f"    {label}:")
        out.append(f"\ttransform {pn}")
        out.append(f"\tjyes {label}")
        out.append(f"\ttransform {pn}, RayLib.{typed[pn]}")

    # Build the function-name symbolic var.
    out.append(f"\tlocal fname, args")
    out.append(f"\tarrange fname, ={name}")

    # Build the args symbolic var (comma-separated parameter substitutions).
    # The wrapper does *not* synthesize `addr` for any parameter — what
    # you type is what fasmg's `invoke`/`fastcall` macro sees, including
    # for the hidden destination buffer (`dest*`). This matches the
    # convention used elsewhere in fasmg/fasm code:
    #
    #     BeginMode2D    addr camera          ; pass &camera (lea rcx, [camera])
    #     DrawCircleV    [pos], …             ; load 8-byte struct
    #     ClearBackground RAYWHITE            ; immediate value
    #     LoadImage      addr img, _filename  ; user explicitly takes &img
    #
    # Auto-injection of `=addr` was tempting but produces a `lea`
    # whether the user expected one or not, and made the wrapper's
    # behaviour diverge from what the user typed.
    chunks: list[str] = []
    if needs_hidden_dest:
        chunks.append("dest")
    chunks.extend(p["name"] for p in head_params)
    if is_variadic:
        chunks.append("rest")

    if chunks:
        out.append(f"\tarrange args, {', '.join(chunks)}")
    else:
        out.append(f"\tarrange args,")

    out.append(f"\tcall RLAPI, fname, args")
    out.append(f"end calminstruction")
    out.append("")


def write_api(api: dict, typed_args: dict[str, dict[str, str]]) -> None:
    out: list[str] = [
        "; raylib calminstruction wrappers — generated",
        ";",
        "; Each wrapper:",
        ";   1. Validates parameter count via the `*` (required) marker.",
        ";   2. Applies `transform` to typed parameters so callers can use",
        ";      short enum names (KEY_ESCAPE, FLAG_VSYNC_HINT, …) and so",
        ";      misspellings or wrong-enum mixing fail at assemble time.",
        ";   3. Assembles `invoke _Func, args…`, where `_Func` is the import-",
        ";      table label produced from raylib_imports.inc.",
        "",
    ]
    typed_count = sum(len(v) for v in typed_args.values())
    print(f"  emitting {typed_count} typed-arg transform calls "
          f"across {len(typed_args)} functions")
    for f in api["functions"]:
        emit_wrapper(f, out, typed_args)
    (OUT / "raylib_api.inc").write_text("\n".join(out), encoding="utf-8")
    print(f"wrote inc/raylib_api.inc ({len(api['functions'])} wrappers)")


# ---------------------------------------------------------------------------
# Master include.
# ---------------------------------------------------------------------------

MASTER = """
; raylib.inc — top-level fasmg projection of the raylib C API.
;
; Two linkage modes:
;
;   DLL mode (default): user's program is a self-contained PE64 EXE
;       that imports raylib.dll at runtime. No external linker step.
;       The RLAPI dispatcher uses indirect calls through an IAT we
;       build via `library raylib, 'raylib.dll'` + `include
;       'raylib_imports.inc'`.
;
;   OBJ mode: opt in with `define RAYLIB_MODE_OBJ` BEFORE this include.
;       Writes a COFF object that link.exe resolves against
;       raylib.lib (either an import library for raylib.dll or a static
;       library). The RLAPI dispatcher uses direct calls; symbols are
;       declared via `include 'raylib_extrn.inc'`.
;
; Example (DLL):
;
;     format PE64 GUI 5.0
;     entry start
;     include 'raylib.inc'
;
;     section '.text' code readable executable
;       start:
;         sub  rsp, 8
;         InitWindow 800, 450, _title
;         …
;
;     section '.idata' import data readable writeable
;       library raylib, 'raylib.dll', kernel32, 'KERNEL32.DLL'
;       include 'raylib_imports.inc'
;       import kernel32, ExitProcess, 'ExitProcess'
;
; Example (OBJ — link with raylib.lib + kernel32.lib):
;
;     format MS64 COFF
;     define RAYLIB_MODE_OBJ
;     include 'raylib.inc'
;     extrn 'ExitProcess' as ExitProcess
;     include 'raylib_extrn.inc'
;
;     section '.text' code readable executable
;       public start
;       start:
;         sub  rsp, 8
;         InitWindow 800, 450, _title
;         …

include 'win64a.inc'

include 'raylib_types.inc'
include 'raylib_aliases.inc'
include 'raylib_enums.inc'
include 'raylib_colors.inc'

; Pick a dispatcher based on the build mode flag.
if defined RAYLIB_MODE_OBJ
\tinclude 'raylib_obj_dispatch.inc'
else
\tinclude 'raylib_dll_dispatch.inc'
end if

include 'raylib_api.inc'
"""


def write_master() -> None:
    (OUT / "raylib.inc").write_text(MASTER.lstrip(), encoding="utf-8")
    print("wrote inc/raylib.inc")


# ---------------------------------------------------------------------------

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--api", type=Path, default=DEFAULT_API)
    ap.add_argument("--header", type=Path, default=DEFAULT_HEADER)
    args = ap.parse_args()

    api = load_api(args.api)
    comments = parse_header(args.header)
    print(f"parsed {len(comments)} RLAPI declarations from raylib.h")
    typed_args = build_typed_args(api, comments)

    OUT.mkdir(exist_ok=True)
    build_alias_map(api)
    write_types(api)
    write_aliases(api)
    write_enums(api)
    write_colors(api)
    write_imports(api)
    write_dispatchers()
    write_api(api, typed_args)
    write_master()
    return 0


if __name__ == "__main__":
    sys.exit(main())
