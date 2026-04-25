"""Generate a fasm2 source that calls every RLAPI wrapper exactly once
with type-appropriate placeholder arguments. Assembling it stresses the
projection and surfaces wrapper-emission bugs (wrong param counts,
malformed arrange patterns, name collisions) without us hand-translating
hundreds of examples.

Output: examples/build/stress/api_stress.asm — assemble with
        fasm2 api_stress.asm api_stress.obj
(MS64 COFF mode; we don't need to link or run, just assemble.)
"""
from __future__ import annotations
import json
import os
import re
from pathlib import Path

ROOT = Path(__file__).parent
RAYLIB_PATH = Path(os.environ.get("RAYLIB_PATH", ROOT.parent / "raylib"))
API = RAYLIB_PATH / "tools" / "rlparser" / "output" / "raylib_api.json"
OUT = ROOT / "examples" / "build" / "stress" / "api_stress.asm"

# Same description-quote fix as gen.py.
def load_api(path: Path) -> dict:
    text = path.read_text(encoding="utf-8")
    pat = re.compile(r'^(\s*"description":\s*)"(.*)"(,?\s*)$')
    fixed = []
    for line in text.splitlines():
        m = pat.match(line)
        if m:
            body = m.group(2).replace('\\"', '\x00').replace('"', '\\"').replace('\x00', '\\"')
            line = m.group(1) + '"' + body + '"' + m.group(3)
        fixed.append(line)
    return json.loads('\n'.join(fixed))

# Known-struct sizes for picking pass-by-value vs pass-by-pointer
# placeholders. Mirrors gen.py's logic.
STRUCT_SIZE = {
    "Vector2": 8, "Vector3": 12, "Vector4": 16, "Quaternion": 16,
    "Matrix": 64, "Color": 4, "Rectangle": 16, "Image": 24,
    "Texture": 20, "Texture2D": 20, "TextureCubemap": 20,
    "RenderTexture": 28, "RenderTexture2D": 28,
    "NPatchInfo": 36, "GlyphInfo": 32,
    "Font": 48,
    "Camera2D": 24, "Camera3D": 44, "Camera": 44,
    "Mesh": 96,  # forces by-pointer placeholder
    "Shader": 16, "MaterialMap": 28, "Material": 1056,
    "Transform": 40, "BoneInfo": 36,
    "Model": 96, "ModelAnimation": 96, "ModelSkeleton": 96, "ModelAnimPose": 96,
    "Ray": 24, "RayCollision": 32, "BoundingBox": 24,
    "Wave": 24, "AudioStream": 24, "Sound": 32, "Music": 56,
    "VrDeviceInfo": 64, "VrStereoConfig": 304,
    "FilePathList": 16, "AutomationEvent": 24, "AutomationEventList": 16,
}


def placeholder_for(c_type: str, struct_args_in_data: list[str]) -> str:
    t = c_type.strip()
    if t.endswith("*"):
        return "0"   # null pointer
    # Array (fixed-size buffer) — caller passes a pointer to one.
    m = re.match(r'^([\w\s\*]+?)\s*\[(\d+)\]$', t)
    if m:
        return "0"
    if t in {"int", "unsigned int", "long", "unsigned long",
             "short", "unsigned short", "char", "unsigned char",
             "signed char", "bool"}:
        return "0"
    if t in {"float", "double", "long long", "unsigned long long"}:
        # `float` prefix routes to SSE; `dword` for single-precision
        # (default for `float` would be qword/double under PE64).
        if t == "float":
            return "float dword 0.0"
        if t == "double":
            return "float qword 0.0"
        return "0"
    # struct types — pick by size
    sz = STRUCT_SIZE.get(t, 0)
    if sz in (1, 2, 4):
        return "0"           # treated as integer immediate
    if sz == 8:
        return "0"           # 8-byte struct → 0 in rcx
    if sz == 0:
        return "0"           # unknown struct, fallback
    # > 8 bytes: caller passes &copy. The wrapper does NOT auto-addr,
    # so we have to write `addr <label>` ourselves — same convention as
    # any fasmg invoke. Stash the label name so we can emit
    # `<label> <Type>` placeholders in the .data section.
    label = f"_ph_{t}"
    if label not in struct_args_in_data:
        struct_args_in_data.append(label)
    return f"addr {label}"


def main():
    api = load_api(API)
    OUT.parent.mkdir(parents=True, exist_ok=True)

    struct_phs: list[str] = []
    lines: list[str] = []
    skipped = 0

    for fn in api["functions"]:
        params = fn.get("params") or []
        # Skip variadic — placeholder for `...` is undefined.
        if any(p.get("type") == "..." or p.get("name") == "..." for p in params):
            skipped += 1
            lines.append(f"\t; skipped (variadic): {fn['name']}")
            continue
        head = [p for p in params if p.get("type") != "..." and p.get("name") != "..."]
        args = [placeholder_for(p["type"], struct_phs) for p in head]

        # If the return type is a struct > 8 bytes, gen.py prepended a
        # `dest*` first-arg slot — we have to provide a placeholder for
        # it. `placeholder_for` already prepends `addr` when the type is
        # >8B, so the resulting expression is e.g. `addr _ph_Image`.
        rt = fn.get("returnType", "void").strip()
        if rt and not rt.endswith("*") and rt not in {
            "void","int","unsigned int","float","double","char",
            "unsigned char","bool","short","unsigned short","long",
            "unsigned long","long long","unsigned long long",
        }:
            sz = STRUCT_SIZE.get(rt, 0)
            if sz > 8:
                args = [placeholder_for(rt, struct_phs)] + args

        if args:
            lines.append(f"\t{fn['name']:<32} {', '.join(args)}")
        else:
            lines.append(f"\t{fn['name']}")

    # Resolve type aliases to their underlying struct so the placeholder
    # data declarations actually match a `struct` definition (fasmg's
    # struct macro doesn't follow symbolic-link aliases when looking up
    # the instance type).
    aliases = {a["name"]: a["type"] for a in api["aliases"]
               if not a["name"].startswith("*")}

    # Build the .asm.
    body = "\n".join(lines)
    data_phs = "\n".join(
        f"  {ph} {aliases.get(ph[len('_ph_'):], ph[len('_ph_'):])}"
        for ph in struct_phs
    )

    src = f"""\
; AUTO-GENERATED by stress_test.py — calls every RLAPI wrapper exactly
; once with type-appropriate placeholder args. The goal isn't a
; runnable program; we just want fasmg to assemble it without errors,
; which proves all 600 wrappers are syntactically valid and that the
; struct-by-value pointer-passing works in every position.
;
; {len(api['functions'])} wrappers, {skipped} variadic skipped.
;
; Build:
;   fasmg api_stress.asm api_stress.obj
; (anything that assembles is a pass; .obj contents don't matter.)

format MS64 COFF
define RAYLIB_MODE_OBJ
include 'raylib.inc'
include 'raylib_extrn.inc'

section '.text' code readable executable
  public stress_main as 'stress_main'
  stress_main:
{body}
\tret

section '.data' data readable writeable
{data_phs}
"""
    OUT.write_text(src, encoding="utf-8")
    print(f"wrote {OUT} ({len(api['functions']) - skipped} calls, "
          f"{skipped} variadic skipped, {len(struct_phs)} struct placeholders)")


if __name__ == "__main__":
    main()
