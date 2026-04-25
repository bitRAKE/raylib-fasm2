# fasmg ↔ Raylib projection — discovery notes

## Inputs

- API description: [`raylib/tools/rlparser/output/raylib_api.json`](https://github.com/raysan5/raylib/blob/master/parser/output/raylib_api.json)
  (under `RAYLIB_PATH/tools/rlparser/output/raylib_api.json` locally).
  - 57 defines (incl. 26 `COLOR` literals like `LIGHTGRAY` / `BLACK`, several `GUARD` macros, version ints/strings, `RLAPI`).
  - 67 structs (Vector2/3/4, Matrix, Color, Rectangle, Image, Texture, RenderTexture, NPatchInfo, GlyphInfo, Font, Camera2D/3D, Mesh, Shader, MaterialMap, Material, Transform, BoneInfo, Model, ModelAnimation, Ray, RayCollision, BoundingBox, Wave, AudioStream, Sound, Music, VrDeviceInfo, VrStereoConfig, FilePathList, AutomationEvent, AutomationEventList).
  - 6 type aliases (Quaternion=Vector4, Texture2D=Texture, …).
  - 21 enums totalling 600 named values (ConfigFlags, TraceLogLevel, KeyboardKey, MouseButton, MouseCursor, GamepadButton, GamepadAxis, MaterialMapIndex, ShaderLocationIndex, ShaderUniformDataType, ShaderAttributeDataType, PixelFormat, TextureFilter, TextureWrap, CubemapLayout, FontType, BlendMode, Gesture, CameraMode, CameraProjection, NPatchLayout).
  - 6 callbacks (TraceLogCallback, LoadFileDataCallback, …).
  - 202 functions.
- Sister files in the same directory: `raylib_api.txt` / `.lua` / `.xml`
  (same content, different formats).
- Header source: [`raylib/src/raylib.h`](https://github.com/raysan5/raylib/blob/master/src/raylib.h).

## fasm/fasmg/fasm2 essentials we'll lean on

The projection assembles with [fasm2][fasm2], a thin wrapper around
[fasmg][fasmg] that pre-includes a Win64 macro pack. Everything below
is straight fasmg semantics.

[fasm2]: https://github.com/tgrysztar/fasm2
[fasmg]: https://github.com/tgrysztar/fasmg

- `calminstruction NAME args` … `end calminstruction` defines a CALM macro. `*` makes an arg required, `&name&` slurps the rest of the line.
- `transform var, NAMESPACE` rewrites identifiers in `var`'s symbolic value as if they live in `NAMESPACE`. Result-flag tells whether anything changed; pair with `jyes`/`jno`.
- `arrange var, =literalToken plus var2 …` builds text. `=` keeps a name token literal, bare names are resolved to the symbolic value of a CALM variable.
- `assemble var` feeds the constructed text back into the standard pipeline.
- `call OTHERCALM, arg1, …` dispatches to another CALM, passing values directly (no preprocessing).
- `namespace name` … `end namespace` redirects the base namespace for symbol creation/lookup. Symbols of *different classes* may share names within one namespace (so a CALM `SetConfigFlags` and a data label `SetConfigFlags` coexist).
- `struct Foo` … `ends` declares a record; `instance Foo field:value, …` instantiates one.
- `library libname,'file.dll'` + `import libname, label,'ExportName',…` builds the `.idata` table; the `label` becomes a `qword` IAT slot.
- `proc64.inc` provides `invoke proc, args…` which expands to `fastcall [proc],args` (Win64 ABI: first 4 args in `rcx/rdx/r8/r9` or `xmm0..3` for floats, rest at `[rsp+8*(n-1)]`, 32-byte shadow space, dqword stack alignment).
- Two relevant output formats (via fasm2's `format.inc`):
  - `format PE64 GUI 5.0` / `format PE64 CONSOLE 5.0` → direct EXE with import table; no external linker needed.
  - `format MS64 COFF` → `.obj` for `link.exe` (uses `extrn`/`public`); pair with `raylib.lib` for static linking against the C build.

## The wrapper pattern (from the user's example)

```fasmg
namespace RayLib
    define ConfigFlags.FLAG_VSYNC_HINT       0x00000040
    …
end namespace

calminstruction SetConfigFlags flags*
    transform flags, RayLib.ConfigFlags
    call RLAPI, SetConfigFlags, flags
end calminstruction
```

Two things that work in our favor here:

1. The CALM `SetConfigFlags` and the imported data label `SetConfigFlags` share a name but differ in class — fasmg permits this. Inside the CALM body we re-emit `invoke SetConfigFlags, flags`, and that resolves to the data label.
2. `transform flags, RayLib.ConfigFlags` lets the user write the *short* enum names (`FLAG_VSYNC_HINT or FLAG_FULLSCREEN_MODE`) without polluting the global namespace.

## Project layout (as built)

See [README.md § Layout](README.md#layout) for the up-to-date tree;
the structure below is what we settled on early in the POC and the
generator still emits to it.

```
raylib-fasm2/
├── README.md
├── syntax_usage.md         practical reference for writing code
├── DISCOVERY.md            this file
├── PLAN.md                 implementation plan and status
├── build.cmd               assemble + link wrapper, three modes
├── gen.py                  JSON → .inc generator
├── infer_enums.py          AST-based typed-arg miner
├── inferred_enums.json     checked-in AST output
├── stress_test.py          assembles every wrapper at once
└── inc/
    ├── raylib.inc          master include
    ├── raylib_types.inc    struct definitions (with C-natural padding)
    ├── raylib_aliases.inc  type aliases + delegating CALMs
    ├── raylib_enums.inc    namespace RayLib { defines } + anchors
    ├── raylib_colors.inc   predefined Color constants (packed dwords)
    ├── raylib_dll_dispatch.inc   RLAPI for DLL mode (invoke via IAT)
    ├── raylib_obj_dispatch.inc   RLAPI for OBJ mode (fastcall direct)
    ├── raylib_imports.inc  PE64 import table
    ├── raylib_extrn.inc    COFF extrn declarations (gated by `if used`)
    └── raylib_api.inc      600 calminstruction wrappers
```

## How we recovered enum types from the source

The C signatures use bare `int`/`unsigned int` for enum-typed parameters
(`SetConfigFlags(unsigned int flags)`, `IsKeyPressed(int key)`), and the
trailing `// comment` hints are inconsistent. `infer_enums.py` solves
this by treating raylib's own examples and source as the ground truth:

1. Run `clang -Xclang -ast-dump=json -fsyntax-only` on every `.c` under
   `raylib/examples` and `raylib/src`. (rglfw.c is excluded; it doesn't
   call RLAPI functions and pulls in many platform headers.)
2. Walk each translation unit's AST, looking for `CallExpr` nodes whose
   callee is one of our 600 RLAPI functions.
3. For each argument expression, walk *only* through arithmetic/bitwise
   sub-nodes (ImplicitCastExpr, ParenExpr, UnaryOperator, BinaryOperator
   with `|`/`+`/`&`/etc.) until we hit a `DeclRefExpr` to an
   `EnumConstantDecl`. We deliberately do *not* recurse through:
     - ConditionalOperator (`x == GESTURE_TAP ? RED : LIGHTGRAY` would
       otherwise type the Color arg as Gesture).
     - BinaryOperator with comparison/logical opcodes.
     - CallExpr / MemberExpr / ArraySubscriptExpr / CompoundLiteralExpr.
4. Cross-reference the recovered enum-member name against the JSON's
   enum tables to identify the enum type.
5. Aggregate per `(function, argpos)`, requiring ≥ 50% agreement and at
   least one piece of evidence. Results land in `inferred_enums.json`.

Yields 30 high-confidence (function, arg) → enum pairs; manual overrides
catch the 9 typed pairs that examples don't cover (`IsKeyUp`,
`SetTraceLogLevel`, `GetPixelDataSize.format`, …). Final total:
**39 typed wrappers**.

## Win64 struct-return >8 bytes: hidden-dest first-arg

Functions like `Image LoadImage(const char*)` return a 24-byte struct.
Win64 ABI handles this by having the caller allocate space for the
result and pass `&space` as a hidden first parameter — all real args
shift by one. fasmg's `invoke` doesn't synthesize this hidden pointer,
so the wrapper has to.

The generator detects each function's return type, looks up the size in
the same table used for parameter routing, and if the return is a
struct > 8 bytes it prepends a `dest*` parameter to the wrapper:

```fasmg
calminstruction LoadImage dest*, fileName*
    local fname, args
    arrange fname, =LoadImage
    arrange args, =addr dest, fileName
    call RLAPI, fname, args
end calminstruction
```

User-facing convention: `LoadImage img, _filename` where `img Image`
was declared. 81 wrappers got this treatment; verified at runtime by
`examples/pe64/texture_smoke.asm` (GenImageColor → LoadTextureFromImage
→ DrawTexture → UnloadTexture round-trip prints `TEXTURE: [ID 3]
loaded successfully (200x200 | R8G8B8A8)`).

## Struct-alias as instance type: delegating CALM

`define Texture2D Texture` makes the alias usable in expressions and
field types, but fasmg does *not* follow `define` substitutions when
looking up an *instruction* name. So `tex Texture2D` (using the alias
as a struct constructor) silently fails to find a matching CALM and
the symbol `tex` is never created.

Fix: emit a labeled CALM per non-pointer alias that delegates to the
underlying struct's instantiator:

```fasmg
calminstruction (instance) Texture2D values&
    local sname
    arrange sname, =Texture
    call struct?.instantiate, instance, sname, values
end calminstruction
```

(Note: passing the bare identifier `Texture` as the second `call` arg
yields its label-value, which after `ends` is `sizeof Texture` — `ends`
publishes the struct as both a CALM constructor and a label. We need
the symbolic name, so we build it via `arrange sname, =Texture`.)

## Win64 struct-by-value: manual `addr` (no auto-injection)

Win64 ABI passes structs by value only when they're 1, 2, 4, or 8 bytes
— anything else goes as a pointer to caller-allocated storage. fasmg's
`invoke` rejects a 24-byte struct as a "value" argument; the caller
needs to take its address.

Earlier the generator silently auto-prepended `=addr` for struct args
> 8 bytes. That was tempting but bad: it meant the wrapper's emitted
code didn't match what the user typed, every call became a `lea`, and
behaviour diverged from the standard fasmg `invoke`/`fastcall` idiom
where `addr` is always explicit. So now wrappers are pure passthroughs:

```fasmg
calminstruction BeginMode2D camera*
    local fname, args
    arrange fname, =BeginMode2D
    arrange args, camera        ; whatever the user wrote, verbatim
    call RLAPI, fname, args
end calminstruction
```

User-side, the convention matches every other fasmg call site:

```fasmg
BeginMode2D     addr camera               ; 24 B  -> lea rcx, [camera]
DrawCircleV     [pos], float dword 50.0, RED   ; 8 B   -> mov r8, [pos]
ClearBackground RAYWHITE                  ; 4 B   -> mov ecx, imm
LoadImage       addr img, _filename       ; struct return + by-pointer
```

The same applies to the synthetic `dest*` first parameter we add for
struct-returns > 8 bytes: the user writes `addr img`, the wrapper
passes it through as-is.

## Single dispatch point: `RLAPI`

The wrappers all funnel through one CALM, `RLAPI`, instead of inlining
`invoke …` directly. Two flavours of `RLAPI` are emitted; `raylib.inc`
picks one based on a `define RAYLIB_MODE_OBJ` flag. This is what makes
the same wrapper code build either a self-contained PE64 EXE or a COFF
object linkable against `raylib.lib`:

```fasmg
; DLL mode — indirect call via IAT
calminstruction RLAPI fname*, args&
    local cmd
    match , args
    jyes _no_args
    arrange cmd, =invoke =RLAPI.fname, args
    assemble cmd
    exit
  _no_args:
    arrange cmd, =invoke =RLAPI.fname
    assemble cmd
end calminstruction

; OBJ mode — direct call resolved by linker (s/=invoke/=fastcall/)
```

Wrappers do `arrange fname, =SetConfigFlags` + `arrange args, p1, p2,
…` + `call RLAPI, fname, args`. Note: CALM `arrange` does *not* support
`#`-concatenation across token boundaries (probed; fails). Dot-adjacency
*does* work — `arrange cmd, =RLAPI.fname` produces `RLAPI.<value-of-fname>`.
That's why imports/extrns are exposed under the `RLAPI.<Func>` namespace
rather than as `_<Func>` — the dispatcher composes the dotted symbol name
at arrange-time.

For OBJ mode the `extrn` declarations are gated by `if used RLAPI.Func`
so a program that only references `InitWindow`/`CloseWindow` doesn't drag
all 600 symbols into the .obj. Verified against a prebuilt `raylib.lib`
from a [raylib release](https://github.com/raysan5/raylib/releases):
`lld-link` resolves only the referenced symbols and the .obj shrinks
from 21 KB to 442 B.

## `transform` semantics worth knowing

We rely on `transform var, RayLib.SomeEnum` in every typed wrapper to
swap short enum-member names (`FLAG_VSYNC_HINT`) for their numeric
values before assembly. Quirks:

- The result flag tracks **at-least-one-replaced**, not
  **all-resolved**. A compound expression like
  `FLAG_VSYNC_HINT or FLAG_NOPE` returns JYES with value
  `64 or FLAG_NOPE`; the typo only surfaces when the operand parser
  later chokes on `FLAG_NOPE`.
- JNO does **not** mean error — it also fires on pure-numeric values
  (`SetConfigFlags 0`), on user-defined aliases (`define MY_FLAGS …`),
  and on already-fully-qualified identifiers
  (`RayLib.ConfigFlags.FLAG_VSYNC_HINT`). So we can't blanket-`err` on
  JNO without rejecting all those legitimate cases.
- The two-pass pattern `transform val` (current scope) → loop while
  JYES → `transform val, NS` recovers user-defined aliases AND
  fully-qualified names. The wrappers in `raylib_api.inc` use this
  pattern.
- See `examples/typed_args_verify.asm` for a self-contained proof.

## Pitfalls discovered while building this

These are the things that ate time during the POC. Each is now handled by
the generator; documented here so future work isn't surprised again.

1. **Field name collisions with assembler/macro keywords.** A C struct field
   called `data` clashes with `pe.inc`'s `data?` macro and the struct macro
   tries to call it as an instruction. Same for `format` (built-in directive)
   and `frame` (proc64.inc macro). The generator suffixes those three with
   `_` (e.g. `Image.data_`) and notes the rename in a comment.

2. **Struct alias sizing.** `Font.texture` is `Texture2D`, which is an alias
   for `Texture` (20 bytes of `dd`). If the generator just falls back to
   `dq ?` for unknown alias names, the struct size and downstream offsets
   are wrong. We build an alias-to-struct map up-front from the JSON and
   resolve before deciding the directive.

3. **CALM wrapper vs import label name collision.** A `calminstruction
   InitWindow` plus an import label `InitWindow` cannot coexist cleanly:
   when the CALM body emits `invoke InitWindow, …`, the operand parser
   sees the same name and reports `out of scope`. Fix: the generator
   prefixes import labels with `_` (so `_InitWindow`) and the wrapper
   emits `invoke _InitWindow, …` internally. From the user's perspective
   the function name is unchanged.

4. **`transform … , <namespace>` silently does nothing without anchors.**
   Defining `RayLib.ConfigFlags.FLAG_VSYNC_HINT 64` does *not* implicitly
   create a `RayLib.ConfigFlags` symbol — the dotted name is just a
   parented identifier. If `transform val, RayLib.ConfigFlags` can't
   resolve `RayLib` and `ConfigFlags` to actual defined symbols, it skips
   replacement (no error, no warning) and the caller's `FLAG_*` token
   reaches the assembler unresolved. Fix is two `define X X` anchors —
   one for `RayLib` at top level, one for each enum inside the namespace.

5. **`stringify` destroys the symbolic value.** `transform` only operates
   on `VALTYPE_SYMBOLIC` values. If a wrapper does `stringify val` before
   `transform val, …` for any reason (logging, debug print), the transform
   silently no-ops. Always run `transform` first.

## Open questions / decisions

- **Typed-arg policy.** The C signatures don't carry enum types — `SetConfigFlags(unsigned int flags)` is just `unsigned int`. We need a hand-curated map { function-name + param-name → enum-namespace } to drive the `transform`. Initial list will cover the common cases (ConfigFlags, KeyboardKey, MouseButton, MouseCursor, GamepadButton/Axis, BlendMode, TraceLogLevel, CameraMode/Projection, PixelFormat, TextureFilter/Wrap, ShaderLocationIndex/UniformDataType/AttributeDataType, MaterialMapIndex, FontType, Gesture, CubemapLayout, NPatchLayout). Anything outside the table goes through unmodified.
- **Struct-by-value parameters.** Win64 ABI passes structs by value differently depending on size: 1/2/4/8-byte structs go in a register; larger ones are passed as a pointer to caller-allocated storage and the original integer slot becomes that pointer. The fasmg `invoke` macro doesn't do this lifting for us — for now, signatures that take structs (e.g. `DrawRectangleRec(Rectangle rec, Color color)`) need a thin wrapper that copies the struct to a temp on the stack and passes the pointer. Stub for v1, full support v2.
- **Variadic functions.** `TraceLog(int logLevel, const char *text, ...)` and `TextFormat(...)` — we'll skip variadic for v1; users can drop down to raw `invoke` if they need it.
- **Color literal**: `LIGHTGRAY` etc. are `(Color){200,200,200,255}` in C. In fasmg the practical equivalent is to either (a) emit a `Color LIGHTGRAY {…}` static instance, or (b) define them as packed `dd 0xFF C8 C8 C8` literals so they fit in a register. Win64 passes 32-bit-or-less structs by value in a register, so option (b) lets `DrawRectangle … , LIGHTGRAY` work directly.
