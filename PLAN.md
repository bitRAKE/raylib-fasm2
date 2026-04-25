# Implementation plan

## Status

**Phase 1 — DONE.** All three linkage modes verified end-to-end with
raylib 6.0:

- `examples/build/pe64/`            DLL-direct, ~2 KB EXE + raylib.dll
- `examples/build/obj-dll/`         OBJ + bin64\raylib.lib, ~9 KB EXE + raylib.dll
- `examples/build/obj-static/`      OBJ + lib64\raylib.lib, ~588 KB self-contained EXE

Hand-translated examples currently passing (`examples/pe64/`):
core_basic_window, core_basic_screen_manager, core_input_keys,
core_input_mouse, core_2d_camera, core_3d_camera_mode, core_3d_picking,
core_world_screen, cube_grid, input_demo, shapes_basic_shapes,
shader_smoke, audio_sound_smoke (with embedded coin.wav payload),
text_smoke, texture_smoke. Plus typed_args_verify.asm (proves the
transform pipeline works on the real generated `raylib.inc`) and
obj_smoke.asm under `examples/obj/`.

**Stress test.** `stress_test.py` generates `api_stress.asm` that calls
all 598 non-variadic wrappers exactly once with type-appropriate
placeholder args; assembles cleanly under MS64 COFF. Confirms every
wrapper is syntactically valid and that the auto-`addr` path works in
every argument position for every distinct struct type.

Enum validation works at assemble time: `SetConfigFlags FLAG_THIS_IS_FAKE`
produces `Error: symbol 'FLAG_THIS_IS_FAKE' is undefined or out of scope`,
while `SetConfigFlags FLAG_FULLSCREEN_MODE or FLAG_VSYNC_HINT` is replaced
with `2 or 64` and assembles.

**Typed-arg coverage.** 39 wrappers carry `transform`. Source priority:
- 30 from clang AST evidence (`infer_enums.py` walks raylib/examples +
  raylib/src, watches what enum constants flow into each argument
  position at every call site).
- 4 from `MANUAL_OVERRIDES` for typed pairs the examples don't exercise
  (`GetPixelColor`, `SetPixelColor`, `GetPixelDataSize`, `LoadFontData`).
- 1 from comment-token scan, 4 from param-name fallback rules
  (`IsKeyUp.key`, `IsMouseButtonUp.button`, etc.).

**Wrapper shape.** Each typed wrapper uses a two-pass transform and then
funnels through a single `RLAPI` dispatcher CALM:

```
calminstruction SetConfigFlags flags*
    _SetConfigFlags_flags_loop:
        transform flags                    ; current scope: user aliases
        jyes _SetConfigFlags_flags_loop
        transform flags, RayLib.ConfigFlags ; namespace: short enum names
        local fname, args
        arrange fname, =SetConfigFlags
        arrange args, flags
        call RLAPI, fname, args
end calminstruction
```

Verified by `examples/typed_args_verify.asm`.

**Linkage modes.** The `RLAPI` dispatcher comes in two flavours,
selected by a `define RAYLIB_MODE_OBJ` flag before `include 'raylib.inc'`:

- *DLL mode* (default): `RLAPI` emits `invoke RLAPI.<Func>` which expands
  to `mov rax, [RLAPI.Func]; call rax` against the IAT slot built from
  `raylib_imports.inc` (`import raylib, RLAPI.Func, 'Func', …`). Result
  is a self-contained PE64 EXE that loads raylib.dll at runtime, no
  external linker step.
- *OBJ mode*: `RLAPI` emits `fastcall RLAPI.<Func>` which expands to
  `call RLAPI.Func` — a direct call that the linker resolves against
  raylib.lib. Symbols are declared via `raylib_extrn.inc`
  (`extrn 'Func' as RLAPI.Func`, gated by `if used` so only referenced
  symbols make it into the .obj). Verified to link cleanly against the
  prebuilt `raylib.lib` from a [raylib release](https://github.com/raysan5/raylib/releases);
  runtime needs MSVC's standard Win32/UCRT libs alongside.

## Phase 1 — POC (this pass)

**Goal:** generate a working `raylib.inc` set that builds a tiny demo (window + colored rectangle + close) as a PE64 EXE that dynamically links to `raylib.dll`.

1. `gen.py` reads `raylib_api.json` and emits:
   - `raylib_types.inc`: every struct as fasmg `struct … ends`.
   - `raylib_aliases.inc`: each alias as `define Alias Target`.
   - `raylib_enums.inc`: every enum as `define EnumName.MEMBER value` inside `namespace RayLib`. Also emits an `EnumName.__transform var` CALM that the API wrappers can `call`. (Optional convenience.)
   - `raylib_colors.inc`: 26 predefined colors as both packed-DWORD constants and full `Color` struct instances.
   - `raylib_imports.inc`: `library raylib,'raylib.dll'` + `import raylib, FuncA,'FuncA', FuncB,'FuncB', …` for every RLAPI function.
   - `raylib_api.inc`: a `calminstruction` wrapper per function. The wrapper:
     - Names parameters and marks them required (`*`).
     - Calls `transform paramN, RayLib.SomeEnum` for params on the curated typed-arg list.
     - Builds and assembles `invoke FuncName, p1, p2, …`.
2. `raylib.inc` master:
   - Includes `'win64a.inc'` so that `proc`, `invoke`, `frame`, `endf` are available.
   - Includes the generated files in order: types → aliases → enums → colors → api.
   - Picks the dispatcher (`raylib_dll_dispatch.inc` vs `raylib_obj_dispatch.inc`) based on a `RAYLIB_MODE_OBJ` define before the include.
3. `examples\pe64\core_basic_window.asm`: minimal raylib hello-world. Demonstrates init, frame loop, draw, close.
4. `build.cmd`: invokes [fasm2](https://github.com/tgrysztar/fasm2)'s `fasm2.cmd` (which wraps fasmg) with the right include path; dispatches PE64 / obj-dll / obj-static modes.
5. Manual verification: assemble the .asm, drop a copy of `raylib.dll` next to the .exe, and confirm a window appears.

## Phase 2 — coverage and ergonomics (later)

- Curate the typed-arg map to cover all 21 enums where they apply.
- Implement struct-by-value lift in a `passstruct` CALM helper for Image/Color/Rectangle/etc. when used as args.
- Add a `format MS64 COFF` mode + `raylib_extrn.inc` so the projection can also feed `link.exe` against `raylib.lib`.
- Variadic helpers for `TraceLog` / `TextFormat`.
- Callback registration (`SetTraceLogCallback`, etc.) — needs `proc` definitions matching Win64 ABI.

## Typed-arg map (initial)

Hand-curated `(function, param) -> enum-namespace` pairs the generator will inject `transform` calls for:

| Function                         | Param     | Enum                      |
|----------------------------------|-----------|---------------------------|
| SetConfigFlags                   | flags     | ConfigFlags               |
| SetWindowState                   | flags     | ConfigFlags               |
| ClearWindowState                 | flags     | ConfigFlags               |
| IsWindowState                    | flag      | ConfigFlags               |
| SetTraceLogLevel                 | logLevel  | TraceLogLevel             |
| TraceLog                         | logLevel  | TraceLogLevel             |
| IsKeyPressed / IsKeyDown / …     | key       | KeyboardKey               |
| GetKeyPressed (no arg)           | —         | —                         |
| IsMouseButtonPressed / …         | button    | MouseButton               |
| SetMouseCursor                   | cursor    | MouseCursor               |
| IsGamepadButtonPressed / …       | button    | GamepadButton             |
| GetGamepadAxisMovement           | axis      | GamepadAxis               |
| BeginBlendMode                   | mode      | BlendMode                 |
| SetGesturesEnabled               | flags     | Gesture                   |
| LoadTextureCubemap               | layout    | CubemapLayout             |
| GenTextureMipmaps / Set*Filter   | filter    | TextureFilter             |
| Set*Wrap                         | wrap      | TextureWrap               |
| SetCameraMode (legacy)           | mode      | CameraMode                |
| Camera3D.projection field        | —         | CameraProjection (struct) |
| LoadFontEx etc.                  | type      | FontType                  |
| DrawTextureNPatch                | layout    | NPatchLayout (in struct)  |
| GetShaderLocation*               | uniformType | ShaderUniformDataType   |
| SetShaderValueV                  | uniformType | ShaderUniformDataType   |

Anything not in the table: param passes through verbatim (still works for ints/pointers/etc.).
