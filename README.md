# fasmg raylib projection

Generated from raylib `tools/rlparser/output/raylib_api.xml`.

Generated include outputs:

- `include/raylib.inc`: constants, enums, structs, aliases, callback pointer aliases, and 600 CALM wrappers.
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
cmd /c "call _local.cmd && python tools\check_raylib_struct_layout.py"
```

The project-local fasm2 support-layer includes are `include/raylib_pe64.inc`, `include/raylib_pe32.inc`, `include/raylib_coff64.inc`, and `include/raylib_coff32.inc`. Select one by filename; it selects the output format, architecture, Raylib linkage layer, and calling convention. Following raylib calls are the same in every mode. Set fasm2's include search path to include `include` and any shared example directory you include from.
