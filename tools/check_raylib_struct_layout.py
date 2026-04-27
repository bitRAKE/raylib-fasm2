#!/usr/bin/env python3
from __future__ import annotations

import os
import subprocess
import tempfile
from pathlib import Path

from generate_raylib_fasmg import INPUT, SOURCE_ROOT, alias_maps, compute_struct_layouts, parse_api


def clang_path() -> str:
    return os.environ.get("CLANG", r"C:\Program Files\LLVM\bin\clang.exe")


def assert_source(api: dict, arch: int) -> str:
    aliases, pointer_aliases = alias_maps(api)
    layouts = compute_struct_layouts(api, arch, aliases, pointer_aliases)
    lines = ['#include <stddef.h>', '#include "raylib.h"', ""]

    for struct in api["structs"]:
        name = struct["name"]
        layout = layouts[name]
        lines.append(f'_Static_assert(sizeof({name}) == {layout["size"]}, "sizeof {name}");')
        for entry in layout["entries"]:
            if entry["kind"] != "field":
                continue
            field = entry["field"]["name"]
            lines.append(f'_Static_assert(offsetof({name}, {field}) == {entry["offset"]}, "offsetof {name}.{field}");')
        lines.append("")

    return "\n".join(lines)


def check_target(api: dict, arch: int, target: str) -> None:
    path = Path(tempfile.gettempdir()) / f"raylib_layout_assert_{arch}.c"
    path.write_text(assert_source(api, arch), encoding="ascii", newline="\n")
    cmd = [
        clang_path(),
        f"--target={target}",
        "-std=c11",
        "-I",
        str(SOURCE_ROOT),
        "-fsyntax-only",
        str(path),
    ]
    result = subprocess.run(cmd, text=True, capture_output=True)
    if result.returncode:
        print(result.stdout, end="")
        print(result.stderr, end="")
        raise SystemExit(result.returncode)
    print(f"{target}: C layout matches generated projection")


def main() -> None:
    api = parse_api(INPUT)
    check_target(api, 64, "x86_64-pc-windows-msvc")
    check_target(api, 32, "i686-pc-windows-msvc")


if __name__ == "__main__":
    main()
