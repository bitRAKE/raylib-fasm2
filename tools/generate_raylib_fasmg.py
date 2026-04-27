#!/usr/bin/env python3
from __future__ import annotations

import html
import os
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RAYLIB_REPO = Path(os.environ.get("RAYLIB_REPO", ROOT.parent / "raylib"))
INPUT = Path(os.environ.get("RAYLIB_API_XML", RAYLIB_REPO / "tools" / "rlparser" / "output" / "raylib_api.xml"))
SOURCE_ROOT = Path(os.environ.get("RAYLIB_SOURCE_ROOT", RAYLIB_REPO / "src"))
OUT = ROOT / "include"


CALM_WORDS = {
    "arrange", "assemble", "call", "check", "compute", "define", "display",
    "element", "emit", "end", "err", "exit", "init", "initsym", "jump",
    "jyes", "jno", "local", "match", "publish", "take", "transform",
}

FASM2_FIELD_WORDS = {
    "align", "as", "at", "data", "db", "dd", "display", "dq", "dw",
    "end", "extrn", "file", "format", "frame", "from", "include", "label", "local",
    "macro", "namespace", "public", "rb", "rd", "repeat", "rq", "rw",
    "section", "struc", "struct", "type", "virtual",
}

ENUM_PARAM_HINTS = {
    "flags": "ConfigFlags",
    "logLevel": "TraceLogLevel",
    "key": "KeyboardKey",
    "button": "MouseButton",
    "cursor": "MouseCursor",
    "gamepadButton": "GamepadButton",
    "axis": "GamepadAxis",
    "mapType": "MaterialMapIndex",
    "shaderLoc": "ShaderLocationIndex",
    "uniformType": "ShaderUniformDataType",
    "attribType": "ShaderAttributeDataType",
    "pixelFormat": "PixelFormat",
    "format": "PixelFormat",
    "filter": "TextureFilter",
    "wrap": "TextureWrap",
    "layout": "CubemapLayout",
    "fontType": "FontType",
    "blendMode": "BlendMode",
    "gesture": "Gesture",
    "mode": "CameraMode",
    "projection": "CameraProjection",
}

FUNCTION_ENUM_HINTS = {
    ("SetWindowState", "flags"): "ConfigFlags",
    ("ClearWindowState", "flags"): "ConfigFlags",
    ("IsWindowState", "flag"): "ConfigFlags",
    ("SetTraceLogLevel", "logLevel"): "TraceLogLevel",
    ("IsKeyPressed", "key"): "KeyboardKey",
    ("IsKeyPressedRepeat", "key"): "KeyboardKey",
    ("IsKeyDown", "key"): "KeyboardKey",
    ("IsKeyReleased", "key"): "KeyboardKey",
    ("IsKeyUp", "key"): "KeyboardKey",
    ("SetExitKey", "key"): "KeyboardKey",
    ("IsMouseButtonPressed", "button"): "MouseButton",
    ("IsMouseButtonDown", "button"): "MouseButton",
    ("IsMouseButtonReleased", "button"): "MouseButton",
    ("IsMouseButtonUp", "button"): "MouseButton",
    ("SetMouseCursor", "cursor"): "MouseCursor",
    ("IsGamepadButtonPressed", "button"): "GamepadButton",
    ("IsGamepadButtonDown", "button"): "GamepadButton",
    ("IsGamepadButtonReleased", "button"): "GamepadButton",
    ("IsGamepadButtonUp", "button"): "GamepadButton",
    ("GetGamepadAxisMovement", "axis"): "GamepadAxis",
    ("SetTextureFilter", "filter"): "TextureFilter",
    ("SetTextureWrap", "wrap"): "TextureWrap",
    ("DrawTextureNPatch", "layout"): "NPatchLayout",
    ("BeginBlendMode", "mode"): "BlendMode",
    ("SetGesturesEnabled", "flags"): "Gesture",
    ("IsGestureDetected", "gesture"): "Gesture",
    ("UpdateCamera", "mode"): "CameraMode",
    ("LoadFontData", "type"): "FontType",
}

SCALAR_ENUM_CARRIERS = {"int", "unsigned int"}


def attr(line: str, name: str) -> str:
    if name == "desc":
        m = re.search(r'\sdesc="(.*)"\s*/?>\s*$', line)
    else:
        m = re.search(rf'\s{name}="([^"]*)"', line)
    if not m:
        return ""
    return html.unescape(m.group(1)).replace("\t", " ").replace("\n", " ").strip()


def parse_api(path: Path) -> dict:
    api = {k: [] for k in ("defines", "aliases", "enums", "structs", "callbacks", "functions")}
    current = None
    section = None

    for raw in path.read_text(encoding="cp1252").splitlines():
        line = raw.strip()
        if line.startswith("<Define "):
            api["defines"].append({k: attr(line, k) for k in ("name", "type", "value", "desc")})
        elif line.startswith("<Alias "):
            api["aliases"].append({k: attr(line, k) for k in ("type", "name", "desc")})
        elif line.startswith("<Enum "):
            current = {"name": attr(line, "name"), "desc": attr(line, "desc"), "values": []}
            section = "enums"
        elif line.startswith("</Enum>"):
            api["enums"].append(current)
            current = section = None
        elif line.startswith("<Value ") and section == "enums":
            current["values"].append({k: attr(line, k) for k in ("name", "integer", "desc")})
        elif line.startswith("<Struct "):
            current = {"name": attr(line, "name"), "desc": attr(line, "desc"), "fields": []}
            section = "structs"
        elif line.startswith("</Struct>"):
            api["structs"].append(current)
            current = section = None
        elif line.startswith("<Field ") and section == "structs":
            current["fields"].append({k: attr(line, k) for k in ("type", "name", "desc")})
        elif line.startswith("<Callback "):
            current = {"name": attr(line, "name"), "retType": attr(line, "retType"), "desc": attr(line, "desc"), "params": []}
            section = "callbacks"
        elif line.startswith("</Callback>"):
            api["callbacks"].append(current)
            current = section = None
        elif line.startswith("<Function "):
            current = {"name": attr(line, "name"), "retType": attr(line, "retType"), "desc": attr(line, "desc"), "params": []}
            section = "functions"
        elif line.startswith("</Function>"):
            api["functions"].append(current)
            current = section = None
        elif line.startswith("<Param ") and section in {"callbacks", "functions"}:
            current["params"].append({k: attr(line, k) for k in ("type", "name", "desc")})

    return api


def fas_comment(text: str) -> str:
    return text.replace("\r", " ").replace("\n", " ").replace(";", ",").strip()


def ident(name: str) -> str:
    name = re.sub(r"\W+", "_", name).strip("_")
    if not name:
        name = "arg"
    if name in CALM_WORDS:
        name += "_"
    return name


def value_text(value: str) -> str:
    value = str(value)
    if re.fullmatch(r"-?\d+", value):
        n = int(value)
        return f"-0x{-n:X}" if n < 0 else f"0x{n:X}"
    return value


def c_base_type(ctype: str) -> str:
    t = ctype.replace("const ", "").replace("volatile ", "").strip()
    t = re.sub(r"\s+", " ", t)
    return re.sub(r"\s*\*+\s*$", "", t).strip()


def is_scalar_enum_carrier(ctype: str) -> bool:
    return not is_pointer(ctype) and c_base_type(ctype) in SCALAR_ENUM_CARRIERS


def is_pointer(ctype: str) -> bool:
    return "*" in ctype or ctype in {"va_list"}


def align_up(value: int, alignment: int) -> int:
    return (value + alignment - 1) // alignment * alignment


def alias_maps(api: dict) -> tuple[dict[str, str], set[str]]:
    aliases: dict[str, str] = {}
    pointer_aliases: set[str] = set()
    for alias in api["aliases"]:
        atype = alias["type"].strip()
        if atype.startswith("*"):
            pointer_aliases.add(atype[1:].strip())
        else:
            aliases[atype] = alias["name"].strip()
    return aliases, pointer_aliases


def resolve_alias(base: str, aliases: dict[str, str]) -> str:
    seen: set[str] = set()
    while base in aliases and base not in seen:
        seen.add(base)
        base = aliases[base]
    return base


def field_symbol_name(field: dict) -> str:
    name = ident(field["name"])
    return "." + name if name in FASM2_FIELD_WORDS else name


def primitive_type_info(base: str) -> dict | None:
    if base in {"bool", "unsigned char", "char"}:
        return {"kind": "scalar", "size": 1, "align": 1, "directive": "db"}
    if base in {"short", "unsigned short"}:
        return {"kind": "scalar", "size": 2, "align": 2, "directive": "dw"}
    if base in {"int", "unsigned int", "float", "long", "unsigned long"}:
        return {"kind": "scalar", "size": 4, "align": 4, "directive": "dd"}
    if base in {"double", "long long", "unsigned long long"}:
        return {"kind": "scalar", "size": 8, "align": 8, "directive": "dq"}
    return None


def ctype_info(
    ctype: str,
    arch: int,
    layouts: dict[str, dict],
    struct_names: set[str],
    aliases: dict[str, str],
    pointer_aliases: set[str],
) -> dict:
    ctype = ctype.strip()
    array = re.fullmatch(r"(.+)\[(\d+)\]", ctype)
    if array:
        elem = ctype_info(array.group(1).strip(), arch, layouts, struct_names, aliases, pointer_aliases)
        count = int(array.group(2))
        return {"kind": "array", "size": elem["size"] * count, "align": elem["align"], "count": count, "elem": elem}

    ptr_size = 4 if arch == 32 else 8
    base = c_base_type(ctype)
    if is_pointer(ctype) or base in pointer_aliases:
        return {"kind": "pointer", "size": ptr_size, "align": ptr_size, "directive": "dd" if arch == 32 else "dq"}

    base = resolve_alias(base, aliases)
    primitive = primitive_type_info(base)
    if primitive:
        return primitive

    if base in layouts:
        return {"kind": "struct", "size": layouts[base]["size"], "align": layouts[base]["align"], "base": base}
    if base in struct_names:
        raise ValueError(f"struct {base} used before its layout is known")

    return {
        "kind": "unknown",
        "size": ptr_size,
        "align": ptr_size,
        "directive": "dd" if arch == 32 else "dq",
        "ctype": ctype,
    }


def field_decl(field: dict, info: dict) -> str:
    fname = field_symbol_name(field)
    if info["kind"] == "array":
        elem = info["elem"]
        count = info["count"]
        if elem["kind"] == "scalar":
            return f"{fname} {elem['directive']} {count} dup ?"
        if elem["kind"] == "pointer":
            return f"{fname} {elem['directive']} {count} dup ?"
        if elem["kind"] == "struct":
            return f"{fname} rb {count}*sizeof.RayLib.{elem['base']}"
        return f"{fname} rb {info['size']} ; {fas_comment(field['type'])}"
    if info["kind"] == "scalar":
        return f"{fname} {info['directive']} ?"
    if info["kind"] == "pointer":
        return f"{fname} {info['directive']} ?"
    if info["kind"] == "struct":
        return f"{fname} RayLib.{info['base']}"
    return f"{fname} {info['directive']} ? ; {fas_comment(info.get('ctype', field['type']))}"


def compute_struct_layouts(api: dict, arch: int, aliases: dict[str, str], pointer_aliases: set[str]) -> dict[str, dict]:
    struct_names = {s["name"] for s in api["structs"]}
    layouts: dict[str, dict] = {}
    for struct in api["structs"]:
        offset = 0
        max_align = 1
        pad_index = 0
        entries: list[dict] = []
        for field in struct["fields"]:
            info = ctype_info(field["type"], arch, layouts, struct_names, aliases, pointer_aliases)
            aligned = align_up(offset, info["align"])
            if aligned > offset:
                entries.append({"kind": "pad", "name": f"_pad{pad_index}", "size": aligned - offset})
                pad_index += 1
                offset = aligned
            entries.append({"kind": "field", "field": field, "offset": offset, "info": info, "decl": field_decl(field, info)})
            offset += info["size"]
            max_align = max(max_align, info["align"])
        size = align_up(offset, max_align)
        if size > offset:
            entries.append({"kind": "pad", "name": f"_pad{pad_index}", "size": size - offset})
        layouts[struct["name"]] = {"size": size, "align": max_align, "entries": entries}
    return layouts


def enum_constant_map(api: dict) -> dict[str, str]:
    return {value["name"]: enum["name"] for enum in api["enums"] for value in enum["values"]}


def strip_c_strings(text: str) -> str:
    return re.sub(r'"(?:\\.|[^"\\])*"', '""', text)


def function_body(text: str, name: str) -> tuple[str, str] | None:
    pattern = re.compile(rf"(?m)^[A-Za-z_][\w\s\*\(\)]*?\b{re.escape(name)}\s*\([^;{{}}]*\)\s*\{{")
    match = pattern.search(text)
    if not match:
        return None
    open_brace = text.find("{", match.start())
    depth = 0
    for i in range(open_brace, len(text)):
        ch = text[i]
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                context_start = max(0, text.rfind("\n", 0, match.start() - 1))
                for _ in range(6):
                    prev = text.rfind("\n", 0, context_start)
                    if prev < 0:
                        context_start = 0
                        break
                    context_start = prev
                return text[context_start:match.start()], text[open_brace + 1:i]
    return None


def enum_votes_from_text(text: str, constants: dict[str, str]) -> dict[str, int]:
    votes: dict[str, int] = {}
    for token in re.findall(r"\b[A-Z][A-Z0-9_]*\b", text):
        enum = constants.get(token)
        if enum:
            votes[enum] = votes.get(enum, 0) + 1
    return votes


def semantically_matches_enum(function: str, param: str, enum: str) -> bool:
    key = (function, param)
    if FUNCTION_ENUM_HINTS.get(key) == enum:
        return True
    if ENUM_PARAM_HINTS.get(param) == enum:
        return True

    f = function.lower()
    p = param.lower()
    if enum == "ConfigFlags":
        return p in {"flag", "flags"} and ("window" in f or "config" in f)
    if enum == "TraceLogLevel":
        return p in {"loglevel", "logtype"} or "log" in p
    if enum == "KeyboardKey":
        return p == "key"
    if enum == "MouseButton":
        return p == "button" and "mouse" in f
    if enum == "MouseCursor":
        return p == "cursor"
    if enum == "GamepadButton":
        return p == "button" and "gamepad" in f
    if enum == "GamepadAxis":
        return p == "axis"
    if enum == "MaterialMapIndex":
        return p in {"maptype", "mapindex"}
    if enum == "ShaderLocationIndex":
        return p in {"locindex", "shaderloc"}
    if enum == "ShaderUniformDataType":
        return p in {"uniformtype", "type"} and "shader" in f
    if enum == "ShaderAttributeDataType":
        return p in {"attribtype", "type"} and "shader" in f
    if enum == "PixelFormat":
        return p in {"format", "newformat", "pixelformat"}
    if enum == "TextureFilter":
        return p == "filter" and "texture" in f
    if enum == "TextureWrap":
        return p == "wrap"
    if enum == "CubemapLayout":
        return p == "layout" and "cubemap" in f
    if enum == "FontType":
        return p in {"type", "fonttype"} and ("font" in f or "glyph" in f)
    if enum == "BlendMode":
        return p == "mode" and "blend" in f
    if enum == "Gesture":
        return p in {"gesture", "flags"} and "gesture" in f
    if enum == "CameraMode":
        return p == "mode" and "camera" in f
    if enum == "CameraProjection":
        return p == "projection"
    if enum == "NPatchLayout":
        return p == "layout" and "npatch" in f
    return False


def source_enum_inference(api: dict) -> tuple[dict[tuple[str, str], tuple[str, str]], list[str]]:
    constants = enum_constant_map(api)
    enum_names = {e["name"] for e in api["enums"]}
    source_files = list(SOURCE_ROOT.glob("*.c")) + list(SOURCE_ROOT.glob("*.h")) + list((SOURCE_ROOT / "platforms").glob("*.c"))
    source_texts = [(p, p.read_text(encoding="utf-8", errors="ignore")) for p in source_files if p.exists()]
    inferred: dict[tuple[str, str], tuple[str, str]] = {}
    report: list[str] = [
        "# Enum Parameter Inference",
        "",
        "Generated from raylib public parser output plus source inspection.",
        "",
    ]

    for func in api["functions"]:
        params = [p for p in func.get("params", []) if is_scalar_enum_carrier(p["type"])]
        if not params:
            continue
        for path, text in source_texts:
            body_info = function_body(text, func["name"])
            if not body_info:
                continue
            leading_comment, body = body_info
            body_no_strings = strip_c_strings(body)
            comment_votes = enum_votes_from_text(leading_comment, {name: name for name in enum_names})
            for param in params:
                pname = re.escape(param["name"])
                evidence = ""
                votes: dict[str, int] = {}

                for switch in re.finditer(rf"switch\s*\(\s*{pname}\s*\)", body_no_strings):
                    segment = body_no_strings[switch.start():switch.start() + 3500]
                    votes = enum_votes_from_text(segment, constants)
                    evidence = f"{path.name}: switch({param['name']})"
                    break

                if not votes:
                    window_votes: dict[str, int] = {}
                    for const, enum in constants.items():
                        pattern = rf"({pname}[^\n;]{{0,100}}\b{re.escape(const)}\b|\b{re.escape(const)}\b[^\n;]{{0,100}}{pname})"
                        if semantically_matches_enum(func["name"], param["name"], enum) and re.search(pattern, body_no_strings):
                            window_votes[enum] = window_votes.get(enum, 0) + 1
                    if window_votes:
                        votes = window_votes
                        evidence = f"{path.name}: parameter/constant expression"

                if not votes and len(params) == 1 and comment_votes:
                    votes = {enum: count for enum, count in comment_votes.items() if semantically_matches_enum(func["name"], param["name"], enum)}
                    evidence = f"{path.name}: function comment names enum"

                if votes:
                    enum, count = max(votes.items(), key=lambda item: item[1])
                    if count > 0:
                        inferred[(func["name"], param["name"])] = (enum, evidence)
                        report.append(f"- `{func['name']}({param['name']})` -> `RayLib.{enum}` ({evidence})")
            break

    if len(report) == 4:
        report.append("No enum-typed parameters were inferred from source bodies.")
    return inferred, report


def function_enum_type(function: str, param: dict, enum_names: set[str], inferred: dict[tuple[str, str], tuple[str, str]] | None = None) -> str | None:
    if not is_scalar_enum_carrier(param["type"]):
        return None
    if inferred and (function, param["name"]) in inferred:
        return inferred[(function, param["name"])][0]
    base = c_base_type(param["type"])
    if base in enum_names:
        return base
    key = (function, param["name"])
    if key in FUNCTION_ENUM_HINTS:
        return FUNCTION_ENUM_HINTS[key]
    hint = ENUM_PARAM_HINTS.get(param["name"])
    if hint in enum_names:
        return hint
    return None


def function_transform_namespace(function: str, param: dict, enum_names: set[str], inferred: dict[tuple[str, str], tuple[str, str]], aliases: dict[str, str]) -> str | None:
    enum_type = function_enum_type(function, param, enum_names, inferred)
    if enum_type:
        return f"RayLib.{enum_type}"
    if not is_pointer(param["type"]):
        base = c_base_type(param["type"])
        base = aliases.get(base, base)
        if base == "Color":
            return "RayLib"
    return None


def emit_structs(lines: list[str], api: dict, layouts: dict[str, dict], heading: str) -> None:
    lines += [f"; Structs ({heading})", ""]
    for struct in api["structs"]:
        if struct["desc"]:
            lines.append(f"; {fas_comment(struct['desc'])}")
        layout = layouts[struct["name"]]
        lines.append(f"struct RayLib.{struct['name']}")
        for entry in layout["entries"]:
            if entry["kind"] == "pad":
                lines.append(f"\t{entry['name']} rb {entry['size']}")
                continue
            field = entry["field"]
            desc = fas_comment(field["desc"])
            lines.append(f"\t{entry['decl']}" + (f" ; {desc}" if desc else ""))
        lines.append("ends")
        lines.append("")


def emit_main(api: dict, inferred: dict[tuple[str, str], tuple[str, str]]) -> str:
    enum_names = {e["name"] for e in api["enums"]}
    aliases, pointer_aliases = alias_maps(api)
    callback_names = {c["name"] for c in api["callbacks"]}
    layouts32 = compute_struct_layouts(api, 32, aliases, pointer_aliases)
    layouts64 = compute_struct_layouts(api, 64, aliases, pointer_aliases)

    lines = [
        "; Auto-generated from raylib_api.xml by tools/generate_raylib_fasmg.py",
        "; Source: raylib tools/rlparser/output/raylib_api.xml",
        "; Raylib API version: 6.0 projection for fasmg",
        "",
        "define RayLib",
        "namespace RayLib",
        "",
        "; Compile-time constants",
    ]

    for define in api["defines"]:
        name, typ, val = define["name"], define["type"], define["value"]
        if "(" in name or typ in {"GUARD", "MACRO"} or not val:
            continue
        if typ == "STRING":
            val = f"'{val}'"
        elif typ == "COLOR":
            nums = re.findall(r"\d+", val)
            if len(nums) == 4:
                val = "0x%02X%02X%02X%02X" % tuple(map(int, reversed(nums)))
            else:
                continue
        elif typ == "FLOAT_MATH":
            continue
        elif typ in {"INT", "FLOAT", "UNKNOWN"}:
            val = value_text(val)
        else:
            continue
        desc = fas_comment(define["desc"])
        suffix = f" ; {desc}" if desc else ""
        lines.append(f"define {ident(name):<34} {val}{suffix}")

    lines += ["", "; Enums"]
    for enum in api["enums"]:
        if enum["desc"]:
            lines.append(f"; {fas_comment(enum['desc'])}")
        lines.append(f"define {enum['name']} {enum['name']}")
        for value in enum["values"]:
            desc = fas_comment(value["desc"])
            suffix = f" ; {desc}" if desc else ""
            lines.append(f"define {enum['name']}.{value['name']:<38} {value_text(value['integer'])}{suffix}")
        lines.append("")

    lines += [
        "; Structs",
        "end namespace",
        "",
        "; Raylib public headers use ordinary C structs, not pragma-packed structs.",
        "; fasm2 struct definitions are textual, so ABI padding is emitted explicitly.",
        "if defined RAYLIB_TARGET_32",
        "",
    ]

    emit_structs(lines, api, layouts32, "Win32 C ABI layout")
    lines += ["else", ""]
    emit_structs(lines, api, layouts64, "Win64 C ABI layout")
    lines += ["end if", ""]

    lines += ["namespace RayLib", "", "; Type aliases"]
    for alias in api["aliases"]:
        lines.append(f"define {ident(alias['type']):<24} {alias['name']} ; {fas_comment(alias['desc'])}")
    if callback_names:
        lines += ["if defined RAYLIB_TARGET_32"]
        for cb in sorted(callback_names):
            lines.append(f"define {cb:<24} dword ; callback pointer")
        lines += ["else"]
        for cb in sorted(callback_names):
            lines.append(f"define {cb:<24} qword ; callback pointer")
        lines += ["end if"]

    lines += ["", "end namespace", ""]

    for func in api["functions"]:
        params = func.get("params", [])
        names = [ident(p["name"]) for p in params]
        signature = ", ".join(f"{n}*" for n in names)
        if func["desc"]:
            lines.append(f"; {fas_comment(func['desc'])}")
        if params:
            proto_parts = []
            for p in params:
                enum_type = function_enum_type(func["name"], p, enum_names, inferred)
                proto_parts.append(f"{enum_type or p['type']} {p['name']}")
            proto = ", ".join(proto_parts)
            lines.append(f"; {func['retType']} {func['name']}({proto})")
            lines.append(f"calminstruction {func['name']} {signature}")
        else:
            lines.append(f"; {func['retType']} {func['name']}(void)")
            lines.append(f"calminstruction {func['name']}")
        lines.append("\tlocal line")
        for p, n in zip(params, names):
            namespace = function_transform_namespace(func["name"], p, enum_names, inferred, aliases)
            if namespace:
                lines.append(f"\ttransform {n}, {namespace}")
        if names:
            lines.append(f"\tarrange line, =RLAPI ={func['name']}, {','.join(names)}")
        else:
            lines.append(f"\tarrange line, =RLAPI ={func['name']}")
        lines.append("\tassemble line")
        lines.append("end calminstruction")
        lines.append("")

    return "\n".join(lines)


def emit_extrn(api: dict, bits: int) -> str:
    decorated = bits == 32
    pointer_type = "dword" if bits == 32 else "qword"
    lines = [
        "; Auto-generated from raylib_api.xml by tools/generate_raylib_fasmg.py",
        f"; Optional COFF/MS x{bits} extern projection.",
        "; Include after a fasmg COFF format include that provides the extrn macro.",
        "; Wrappers in raylib.inc intentionally call RLAPI so users can choose this map,",
        "; an import-table map, or any other ABI bridge.",
        "",
        "namespace RayLib.API",
    ]
    for func in api["functions"]:
        symbol = "_" + func["name"] if decorated else func["name"]
        lines.append(f"\textrn '{symbol}' as {func['name']}:{pointer_type}")
    lines.append("end namespace")
    lines.append("")
    return "\n".join(lines)


def emit_pe_imports(api: dict) -> str:
    lines = [
        "; Auto-generated from raylib_api.xml by tools/generate_raylib_fasmg.py",
        "; Optional direct PE import projection.",
        "; Use in a PE .idata section after: library raylib,'raylib.dll'",
        "; Labels are placed under RayLib.API to avoid colliding with wrapper names.",
        "",
        "import raylib, \\",
    ]
    entries = [f"\tRayLib.API.{func['name']},'{func['name']}'" for func in api["functions"]]
    for index, entry in enumerate(entries):
        suffix = ", \\" if index + 1 < len(entries) else ""
        lines.append(entry + suffix)
    lines.append("")
    return "\n".join(lines)


def emit_readme(api: dict) -> str:
    return f"""# fasmg raylib projection

Generated from raylib `tools/rlparser/output/raylib_api.xml`.

Generated include outputs:

- `include/raylib.inc`: constants, enums, structs, aliases, callback pointer aliases, and {len(api["functions"])} CALM wrappers.
- `include/raylib_extrn_coff32.inc`: optional x86 COFF/MS external labels under `RayLib.API`.
- `include/raylib_extrn_coff64.inc`: optional x64 COFF/MS external labels under `RayLib.API`.
- `include/raylib_imports_pe.inc`: optional direct PE import table entries under `RayLib.API`.
- `include/enum_inference.md`: source-backed enum-parameter inference notes.

Every wrapper is a `calminstruction` and routes through `RLAPI`:

```fasmg
calminstruction SetConfigFlags flags*
        transform flags, RayLib.ConfigFlags
        arrange line, =RLAPI =SetConfigFlags, flags
        assemble line
end calminstruction
```

Define `RLAPI` before calling wrappers. A COFF/x64 bridge can qualify the function name into `RayLib.API` and then assemble a `fastcall`:

```fasmg
calminstruction RLAPI function*, arguments&
        local line
        match , arguments
        jyes noargs
        arrange line, =fastcall =RayLib=.=API.function, arguments
        assemble line
        exit
    noargs:
        arrange line, =fastcall =RayLib=.=API.function
        assemble line
end calminstruction
```

The generated parameter transforms are intentionally conservative and non-validating. They reduce known enum tokens such as `FLAG_VSYNC_HINT` through anchored enum namespaces like `RayLib.ConfigFlags`, and reduce color constants such as `RAYWHITE` through `RayLib` for parameters typed as `Color`. Registers, memory operands, computed values, and other runtime values pass through to the selected ABI bridge. The projection does not define naked enum or color aliases globally; use names like `RayLib.ConfigFlags.FLAG_VSYNC_HINT` and `RayLib.RAYWHITE` outside typed function arguments.

Raylib `bool` returns are left in `al` as returned by the C ABI. The wrappers do not promote them to `BOOL` or clear the upper bits of `eax`; test `al` when consuming a boolean return.

Raylib's public headers declare ordinary C structs; they do not use `#pragma pack` or packed attributes. The generated structures therefore use explicit padding for the selected Windows ABI. `raylib_pe32.inc` and `raylib_coff32.inc` select the Win32 layouts, while the x64 includes select the Win64 layouts. Nested Raylib struct fields use typed fasm2 fields, for example `position RayLib.Vector3`. Arrays of nested structs still use raw storage such as `projection rb 2*sizeof.RayLib.Matrix`, because `RayLib.Matrix 2 dup ?` does not instantiate as an array field with the current fasm2 `struct` macro.

Verify the generated struct layout against the C compiler with:

```cmd
cmd /c "call _local.cmd && python tools\\check_raylib_struct_layout.py"
```

The project-local fasm2 support-layer includes are `include/raylib_pe64.inc`, `include/raylib_pe32.inc`, `include/raylib_coff64.inc`, and `include/raylib_coff32.inc`. Select one by filename; it selects the output format, architecture, Raylib linkage layer, and calling convention. Following raylib calls are the same in every mode. Set fasm2's include search path to include `include` and any shared example directory you include from.
"""


def main() -> None:
    api = parse_api(INPUT)
    inferred, report = source_enum_inference(api)
    OUT.mkdir(exist_ok=True)
    (OUT / "raylib.inc").write_text(emit_main(api, inferred), encoding="utf-8", newline="\n")
    (OUT / "raylib_extrn_coff32.inc").write_text(emit_extrn(api, 32), encoding="utf-8", newline="\n")
    (OUT / "raylib_extrn_coff64.inc").write_text(emit_extrn(api, 64), encoding="utf-8", newline="\n")
    (OUT / "raylib_extrn_coff.inc").write_text(emit_extrn(api, 64), encoding="utf-8", newline="\n")
    (OUT / "raylib_imports_pe.inc").write_text(emit_pe_imports(api), encoding="utf-8", newline="\n")
    (OUT / "enum_inference.md").write_text("\n".join(report) + "\n", encoding="utf-8", newline="\n")
    (ROOT / "README.md").write_text(emit_readme(api), encoding="utf-8", newline="\n")
    print(
        f"generated defines={len(api['defines'])} aliases={len(api['aliases'])} "
        f"enums={len(api['enums'])} structs={len(api['structs'])} "
        f"callbacks={len(api['callbacks'])} functions={len(api['functions'])} "
        f"source_enum_params={len(inferred)}"
    )


if __name__ == "__main__":
    main()
