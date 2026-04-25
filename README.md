# raylib-fasm2

[fasm2][fasm2] projection of the [raylib][raylib] 6.0 C API: 600
function wrappers, 35 structs (with C-natural alignment), 21 enums, 26
predefined colors. Each wrapper runs `transform` against the relevant
enum namespace where applicable, so typos like
`SetConfigFlags FLAG_THIS_IS_FAKE` fail at *assemble* time rather than
silently at runtime.

I think this is the only assembly-language projection of the raylib API
in the wild — it slots in next to all the [official bindings][bindings].

[fasm2]: https://github.com/tgrysztar/fasm2
[fasmg]: https://github.com/tgrysztar/fasmg
[raylib]: https://github.com/raysan5/raylib
[bindings]: https://github.com/raysan5/raylib/blob/master/BINDINGS.md

## Getting started

1. Install [fasm2][fasm2] and set `FASM2_PATH` to its directory:

   ```cmd
   set "FASM2_PATH=C:\path\to\fasm2"
   ```

2. Download a raylib release from
   <https://github.com/raysan5/raylib/releases> and lay out the binaries
   into the matching directories at the repo root:

   ```
   bin64\raylib.dll       (PE64 + obj-dll modes)
   bin64\raylib.lib       (obj-dll mode — import library for the DLL)
   lib64\raylib.lib       (obj-static mode — fully-static archive)
   ```

   These directories are intentionally not committed; ship them in your
   release packages alongside the EXE.

3. Build any example:

   ```cmd
   build.cmd pe64       examples\pe64\core_basic_window.asm
   build.cmd obj-dll    examples\obj\obj_smoke.asm
   build.cmd obj-static examples\obj\obj_smoke.asm
   ```

   OBJ modes need a Visual Studio dev shell active (so `link.exe`,
   `kernel32.lib`, `ucrt.lib` etc. are findable).

4. For day-to-day code-writing reference (call-site recipes, struct
   declaration patterns, calling-convention cheat sheet, debugging) see
   [syntax_usage.md](syntax_usage.md).

## Layout

```
syntax_usage.md     practical reference: how to write code with this
DISCOVERY.md        notes from exploring the raylib JSON and fasm/fasmg manuals
PLAN.md             implementation plan and status
build.cmd           assemble + link wrapper, dispatches the three modes
gen.py              the generator: JSON + raylib.h + AST data → ./inc/*.inc
infer_enums.py      AST-based enum inference: walks every .c in raylib/
                    examples + raylib/src via clang, records which enum
                    each RLAPI argument actually receives at call sites.
                    Outputs `inferred_enums.json`.
inferred_enums.json AST-mined (function, argpos) → enum table (regen on
                    raylib version bump; checked in so users don't need
                    clang to regenerate the projection).
stress_test.py      generator that emits api_stress.asm — calls every
                    wrapper once with placeholder args; assembling it
                    proves all 600 wrappers are syntactically valid.
inc/
  raylib.inc                master include — pull this in and you're done
  raylib_types.inc          35 structs (with C-natural padding)
  raylib_aliases.inc        6 type aliases (Texture2D, Quaternion, …)
  raylib_enums.inc          21 enums under `namespace RayLib` w/ anchors
  raylib_colors.inc         LIGHTGRAY, RAYWHITE, … as packed dwords
  raylib_dll_dispatch.inc   RLAPI CALM that emits `invoke RLAPI.<Func>`
                            (DLL mode, indirect via IAT)
  raylib_obj_dispatch.inc   RLAPI CALM that emits `fastcall RLAPI.<Func>`
                            (OBJ mode, direct call resolved by linker)
  raylib_imports.inc        `import raylib, RLAPI.<Func>,'<Func>',…`
                            (DLL mode, place in user's `.idata`)
  raylib_extrn.inc          `extrn '<Func>' as RLAPI.<Func>` gated by
                            `if used`  (OBJ mode)
  raylib_api.inc            600 calminstruction wrappers; each does
                            `call RLAPI, fname, args` so the dispatcher
                            decides indirect-vs-direct
examples/
  pe64/                     PE64-direct sources (DLL imports)
  obj/                      MS64 COFF sources (linked with raylib.lib)
  typed_args_verify.asm     proves anchors + transform + jyes/jno work
  build/                    build outputs (one subdir per mode)
```

## Usage

### DLL mode (default — self-contained PE64 EXE, no linker)

```fasmg
format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable
  start:
        sub  rsp, 8
        InitWindow      800, 450, _title
        SetTargetFPS    60
  loop: WindowShouldClose
        test eax, eax
        jnz done
        BeginDrawing
        ClearBackground RAYWHITE
        DrawText        _msg, 190, 200, 20, LIGHTGRAY
        EndDrawing
        jmp loop
  done: CloseWindow
        invoke ExitProcess, 0

section '.data' data readable writeable
  _title db 'fasm2 + raylib', 0
  _msg   db 'Hello!', 0

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
```

```cmd
build.cmd pe64 examples\pe64\<your-program>.asm
```

The EXE lands in `examples\build\pe64\` with a copy of `raylib.dll`
alongside (when the release files are present in `bin64\`).

### OBJ mode (link with raylib.lib)

The source is mode-agnostic apart from the format and entry symbol:

```fasmg
format MS64 COFF
define RAYLIB_MODE_OBJ                   ; toggle BEFORE include
include 'raylib.inc'
include 'raylib_extrn.inc'

section '.text' code readable executable align 16
  public main as 'main'                  ; mainCRTStartup wants `main`
  main:
        sub  rsp, 8
        InitWindow 800, 450, _title
        ; …
        xor  eax, eax
        add  rsp, 8
        ret
```

```cmd
build.cmd obj-dll    examples\obj\<your-program>.asm   ; ~9 KB exe + raylib.dll
build.cmd obj-static examples\obj\<your-program>.asm   ; ~588 KB self-contained
```

The two link variants:
- `obj-dll` — links against `bin64\raylib.lib` (an import stub for
  `raylib.dll`). Resulting EXE needs `raylib.dll` alongside at runtime.
- `obj-static` — links against `lib64\raylib.lib` (a fully-static
  archive with raylib + GLFW + glad). Resulting EXE is self-contained,
  pulls in `user32 / gdi32 / shell32 / winmm / opengl32` + the dynamic
  CRT (`ucrt + msvcrt + vcruntime`) since raylib was built against the
  dynamic CRT.

Same wrappers, same enum validation, same `RAYWHITE`/`LIGHTGRAY`
constants — the only thing that differs across all three modes is what
`RLAPI` expands to.

## Regenerating the projection

You only need this if the upstream raylib API changes. Both scripts
look up the raylib source via the `RAYLIB_PATH` env var, defaulting to
`../raylib` (a sibling clone of <https://github.com/raysan5/raylib>).

```cmd
set "RAYLIB_PATH=C:\path\to\raylib"
python gen.py
```

For typed-arg inference, `gen.py` consumes the checked-in
`inferred_enums.json`. To rebuild that file:

```cmd
set "CLANG_PATH=C:\Program Files\LLVM\bin\clang.exe"   :: optional, default = `clang` from PATH
python infer_enums.py
```

`infer_enums.py` walks every `.c` under `raylib/examples` and
`raylib/src`, dumps each AST as JSON, locates every call to a public
RLAPI function, and for each argument follows the expression tree (only
through arithmetic/bitwise nodes — *not* through ternaries or
comparisons, to avoid being fooled by `lastGesture == GESTURE_X ? RED :
LIGHTGRAY`) until it hits an `EnumConstantDecl`. The enum-member name
is then cross-referenced against the JSON's enum tables to recover the
enum type. ~30 seconds across 224 files; the result is the most
accurate evidence we have because it comes from real raylib usage.

Why this beats parsing comments: the C signatures use plain `int` /
`unsigned int` for enum-typed parameters, and the trailing `// comment`
hints are inconsistent (sometimes `(view FLAGS)`, sometimes a list of
member names, sometimes nothing). Examples and source bodies always
pass the actual enum member, so they're authoritative.

To stress every wrapper at once (assembles a 598-call .obj):

```cmd
python stress_test.py
build.cmd obj-dll examples\build\stress\api_stress.asm
```

## What you can rely on

- Every public RLAPI function has a wrapper. Calling one looks like
  `InitWindow 800, 450, _title` (no parens, no return type — just
  arguments).
- 39 wrappers run `transform` against an inferred enum (`KeyboardKey`,
  `ConfigFlags`, `BlendMode`, `MouseButton`, …). 30 of those types come
  from clang AST evidence in raylib's own examples; 9 are filled in by
  manual overrides + comment/name heuristics for functions the examples
  don't exercise.
- The wrappers use a two-pass `transform` so user-defined aliases work:
    ```
    define MY_FLAGS FLAG_VSYNC_HINT or FLAG_FULLSCREEN_MODE
    SetConfigFlags MY_FLAGS    ; resolves to `64 or 2`
    ```
- Pass a wrong member name → `Error: symbol 'FLAG_NOPE' is undefined or
  out of scope.` at assemble time, *not* a silent bug at runtime.
- All 26 predefined colours are exposed as packed RGBA dwords. Win64
  ABI passes ≤ 8-byte structs by value in a register, so
  `ClearBackground RAYWHITE` produces
  `mov ecx, 0xFFF5F5F5; call [_ClearBackground]`.
- Struct layouts match C: padding inserted to natural alignment so
  `sizeof Image = 24`, `sizeof Music = 56`, etc., interoperating
  cleanly with the prebuilt raylib binaries.

## Caveats

For the full call-site convention reference (Color in a register,
Vector2 by `[…]`, big structs by `addr`, struct-return hidden-dest,
`float dword` vs `float qword`, etc.) see [syntax_usage.md](syntax_usage.md#3-argument-passing-cheat-sheet).

The one limit worth flagging in the README: **variadic functions**
(`TraceLog`, `TextFormat`) get a `rest&` slurp arg spliced verbatim
into the `invoke` line — no type-checking, no automatic float
promotion. Use the static-text form (`TraceLog LOG_INFO, _msg`) and
avoid runtime formatting; if you need `printf`-style formatting, drop
to a raw `invoke RLAPI.TraceLog, …` and hand-place each arg.
