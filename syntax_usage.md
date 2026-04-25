# `syntax_usage.md` — writing fasm2 code against the raylib projection

This file is the practical companion to the README. The README explains
what the projection *is*; this one tells you what to *type* when you sit
down to write a program. It assumes you've already cloned the repo, set
`FASM2_PATH` to your [fasm2](https://github.com/tgrysztar/fasm2)
install, and dropped a [raylib release](https://github.com/raysan5/raylib/releases)'s
`bin64\` files into the repo's `bin64\` directory (see [README §
Getting started](README.md#getting-started)).

If you only read one section, read **§3 "Argument-passing cheat sheet"**.

---

## 1. Hello, window

The minimum viable program. Save as `examples/pe64/hello.asm`, then
`build.cmd pe64 examples\pe64\hello.asm`:

```fasmg
format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable
  start:
        sub  rsp, 8                     ; stack alignment for the ABI
        InitWindow      800, 450, _title
        SetTargetFPS    60
  loop: WindowShouldClose
        test eax, eax
        jnz  done
        BeginDrawing
        ClearBackground RAYWHITE
        DrawText        _msg, 240, 200, 20, DARKGRAY
        EndDrawing
        jmp  loop
  done: CloseWindow
        invoke ExitProcess, 0

section '.data' data readable writeable
  _title db 'hello fasmg + raylib', 0
  _msg   db 'press ESC to quit', 0

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
```

Three things to notice:
- No parens, no return-type, no semicolons. `InitWindow 800, 450, _title`
  is one line of x86 assembly that fasmg will lower to a real `call`.
- The string label `_title` IS its address — strings work as `char *`
  args without `addr` or `[…]`.
- ESC closes the window because raylib intercepts it; that's why the
  loop exits when `WindowShouldClose` returns non-zero.

---

## 2. The shape of a wrapper call

Every wrapper boils down to:

```
WrapperName arg1, arg2, …
```

Behind the scenes this expands (in DLL mode) to:

```
invoke RLAPI.WrapperName, arg1, arg2, …
```

…which in turn lowers to fasmg's standard Win64 fastcall sequence
(`mov rcx, …; mov rdx, …; …; call qword [RLAPI.WrapperName]`).

The wrapper does **not** rewrite your arguments. Whatever you type
between the commas is what fasmg's `fastcall` sees. So the rules below
are just "what does fasmg's invoke want for an arg of type X?" — they
are not raylib-specific, just Win64 + fastcall.

The two exceptions:

1. **Typed-arg `transform`** — for 39 specific (function, parameter)
   pairs the wrapper substitutes short enum-member names for their
   numeric values *before* invoke sees them. See §6.
2. **Hidden destination for struct returns > 8 B** — for 81 functions
   the wrapper exposes an extra `dest*` first parameter that
   corresponds to Win64's hidden return-pointer. See §7.

---

## 3. Argument-passing cheat sheet

| Argument shape | What you type | What invoke emits |
|---|---|---|
| `int`, `unsigned int`, `bool` (1/2/4 B integers) | `42`, `0`, `MOUSE_BUTTON_LEFT` | `mov ecx, imm` |
| `float` (single-precision) | `float dword 50.0` | `movss xmm1, …` |
| `double` (double-precision) | `float qword 1.5` | `movsd xmm1, …` |
| `const char *` (string) | `_label` (the bare label IS its address) | `mov rdx, _label` |
| Pointer to anything | `_label` (or `addr buf` if buf is a struct instance) | `mov r8, …` |
| Color (struct, 4 B) | `RAYWHITE`, `0xFF0000FF` | `mov ecx, imm` |
| Vector2 (struct, 8 B) | `[pos]` (memory load — note brackets) | `mov r8, [pos]` |
| Any struct > 8 B (Vector3, Camera2D, Image, …) | `addr camera` | `lea rcx, [camera]` |
| Hidden-dest first arg (struct return > 8 B) | `addr img` | `lea rcx, [img]` |

The two `[…]` vs `addr` cases are the ones to memorize:
- 8-byte struct → `[name]`. fasmg loads its 8 bytes into a register.
- bigger struct → `addr name`. fasmg passes a pointer.
- 4-byte struct (just Color) → bare value, since Color literals are
  packed dwords.

---

## 4. Declaring struct instances

Two equivalent ways. Use whichever reads better in context.

### 4a. By field, with `field:value, …`

```fasmg
camera Camera2D offset:<400.0, 225.0>,        \
                target:<420.0, 300.0>,        \
                rotation:0.0,                  \
                zoom:1.0
```

Nested struct fields are written with `<…>` literal syntax. Useful
when only some fields matter; unspecified fields are zero.

### 4b. Positional

```fasmg
cubePosition Vector3 0.0, 1.0, 0.0
cubeSize     Vector3 2.0, 2.0, 2.0
box          BoundingBox min:<-1.0, 0.0, -1.0>, max:<1.0, 2.0, 1.0>
```

### 4c. Uninitialized

```fasmg
ray       Ray
collision RayCollision
mousePos  Vector2
```

### 4d. Type aliases work as constructor names

`Texture2D`, `Quaternion`, `RenderTexture2D`, `Camera`, `TextureCubemap`
are all aliases. The generator emits a labeled CALM per alias that
delegates to the underlying struct's instantiator, so:

```fasmg
tex Texture2D                  ; same as `tex Texture`
q   Quaternion x:0, y:0, z:0, w:1.0
```

works without surprise.

### 4e. Field renames you'll see in `inc/raylib_types.inc`

Three C field names collide with fasmg directives or `pe.inc`/`proc64.inc`
macros. The generator suffixes them with `_`:

| C field | fasmg field | structs affected |
|---|---|---|
| `data` | `data_` | `Image.data_`, `Wave.data_` |
| `format` | `format_` | `Image.format_`, `Texture.format_` |
| `frame` | `frame_` | `AutomationEvent.frame_` |

So `image.data_` and `image.format_` are the offsets you'd reach for.

---

## 5. Floats — pin the size

`float` is fasmg's marker that the arg goes through XMM. Without an
explicit size it defaults to qword (double). raylib uses single-precision
floats almost everywhere, so the canonical form is:

```fasmg
DrawCircleV     [pos], float dword 50.0, MAROON      ; single-precision
SomeDouble                  float qword 1.0          ; explicit double
```

For *constants* in the data section the `f` suffix and the `dword` size
are both inferred — fasm2-style floats:

```fasmg
c_step    dd 2.0      ; 2.0 single-precision (no `f` needed in fasm2)
c_pi      dd 3.14159
c_full    dq 6.28318  ; double-precision (qword)
```

For `mov` instructions that write a float-bit-pattern into memory:

```fasmg
mov [camera.fovy],  45.0       ; assembler picks the dword form
mov [player.x],    400.0
```

The `dword` size hint is needed only when context is ambiguous.

---

## 6. Enum-typed parameters: the `transform` pipeline

39 wrapper parameters are typed against a `RayLib.<EnumName>` namespace.
Calling one of those wrappers expands `transform` twice — once over the
caller's current scope (resolves user `define`s) and once over the
namespace (resolves short enum-member names):

```fasmg
SetConfigFlags   FLAG_VSYNC_HINT or FLAG_FULLSCREEN_MODE   ; -> 64 or 2
IsKeyDown        KEY_RIGHT                                  ; -> 262
SetMouseCursor   MOUSE_CURSOR_POINTING_HAND
SetShaderValue   addr shader, [tintLoc], addr tintColor, SHADER_UNIFORM_VEC4
```

User-defined aliases work transparently because the unbound `transform`
pass picks them up before the namespace pass:

```fasmg
define MY_FLAGS  FLAG_VSYNC_HINT or FLAG_FULLSCREEN_MODE
SetConfigFlags   MY_FLAGS                  ; -> 64 or 2
```

Numeric literals just pass through; nothing for `transform` to swap:

```fasmg
SetConfigFlags   0                         ; -> mov ecx, 0
SetConfigFlags   0x40                      ; -> mov ecx, 0x40
```

Typos error at *assemble* time, not at runtime:

```
> SetConfigFlags FLAG_NOPE
Error: symbol 'FLAG_NOPE' is undefined or out of scope.
```

For the full list of typed (function, param) pairs, see
`inferred_enums.json` plus the `MANUAL_OVERRIDES` map in `gen.py`.

To check what a given wrapper expects, search `inc/raylib_api.inc` for
`calminstruction <Func> ` — any `transform <param>, RayLib.…` line is a
typed arg.

---

## 7. Struct returns

### 7a. Small (≤ 8 bytes) — read `rax`

`Vector2` (8 B), `Color` (4 B), and any int/float return arrive in `rax`
or `xmm0` per the ABI. Spill into memory if you need to keep the value:

```fasmg
GetMousePosition                 ; Vector2 in rax
mov  qword [pos], rax            ; spill the 8 bytes

GetFrameTime                     ; float in xmm0
movss [delta], xmm0
```

### 7b. Large (> 8 bytes) — pass `addr dest` as the first arg

For 81 functions the wrapper exposes a synthetic `dest*` parameter
ahead of the C-level args. Pre-allocate the buffer in `.data`, then
pass `addr` to it:

```fasmg
img Image                         ; in .data, uninitialized
tex Texture2D                     ; alias OK as instance type

; in .text:
GenImageColor        addr img, 200, 200, BLUE   ; img receives the Image
LoadTextureFromImage addr tex, addr img         ; tex receives the Texture2D
DrawTexture          addr tex, 100, 100, WHITE
UnloadImage          addr img
UnloadTexture        addr tex
```

To know whether a given wrapper has the synthetic `dest`, look at its
description comment in `inc/raylib_api.inc` — for those functions the
generator includes:

```
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
```

---

## 8. Embedding binary resources

raylib functions ending in `FromMemory` accept a pointer + size pair, so
you don't need to read from disk at all. Use fasmg's `file` directive
to incbin the resource into your `.data` section:

```fasmg
section '.data' data readable writeable
  _wav_ext db '.wav', 0

  coin_data: file 'coin.wav'
  coin_size = $ - coin_data       ; assemble-time length

  wave Wave
  fx   Sound

section '.text' code readable executable
  start:
        InitAudioDevice
        LoadWaveFromMemory  addr wave, _wav_ext, coin_data, coin_size
        LoadSoundFromWave   addr fx,   addr wave
        UnloadWave          addr wave
        ; …
        PlaySound           addr fx
```

Same pattern works for `LoadImageFromMemory`, `LoadFontFromMemory`,
`LoadModelFromMemory` (where supported), etc. The `file` payload becomes
part of the EXE; no resource directory needed at run time.

`coin.wav` lives next to the .asm so it travels with the source. fasmg
looks for `file '…'` arguments relative to the source file's directory.

---

## 9. Common debugging recipes

### "nothing happens" / "wrapper doesn't fire"

You probably typed the wrapper name as if it were a C call:

```fasmg
InitWindow(800, 450, _title)     ; WRONG — fasmg sees this as `InitWindow` then `(800, …)`
```

Drop the parens. Wrappers are line-leader instructions:

```fasmg
InitWindow 800, 450, _title       ; right
```

### `Custom error: invalid argument [camera].`

You passed `[camera]` to a wrapper for a struct > 8 bytes. Use `addr`:

```fasmg
BeginMode2D  [camera]            ; WRONG
BeginMode2D  addr camera         ; right
```

### `Error: symbol 'XYZ' is undefined or out of scope.` on a typed arg

Either you typo'd the enum-member name or passed an enum-member of the
wrong enum. The wrapper applied `transform` and the symbol didn't
resolve. Check it lives in the namespace fasmg expects:

```fasmg
SetMouseCursor MOUSE_CURSOR_POINTING_HAND     ; OK
SetMouseCursor KEY_A                          ; FAIL — KEY_A isn't in MouseCursor
```

To verify the namespace, grep:

```
grep "MOUSE_CURSOR_" inc/raylib_enums.inc
```

### `Error: failed to write the output file.`

A previous build's EXE is still running. Close it (or
`taskkill /F /IM yourprog.exe`) and retry.

### Wrapper assembled but raylib crashes / misbehaves

Most often: passed `addr` where you should have passed `[…]`, or vice
versa. The wrapper is a passthrough — it can't distinguish. Re-check
§3's cheat sheet against the C signature.

### Want to see what your call expanded to

Add `-d FASMG_DEBUG=1` to your build and re-assemble; fasmg prints the
expanded text. Or temporarily replace the wrapper call with raw
`invoke RLAPI.<Func>, …` to bypass our layer and see if it's the
wrapper or the underlying invoke that's wrong.

---

## 10. Extending: add a new typed-arg mapping

If you find an `int` parameter that should be typed against an enum:

1. Open `gen.py`, find `MANUAL_OVERRIDES`.
2. Add an entry: `("FunctionName", "paramName"): "EnumName"`.
3. Re-run `python gen.py`.

Or, if the type is something the AST scan should have caught but didn't
(because no example exercises it), add the function to a new test
program in `examples/pe64/` so `infer_enums.py` picks it up next time.

To add a brand-new enum (raylib added one in a new version):

1. Re-run `infer_enums.py` (it'll pick up new members from the JSON +
   raylib.h automatically).
2. The generator will emit `define <NewEnum> <NewEnum>` anchors and
   member defines under `namespace RayLib`.
3. Wrappers using the new enum get the typed-arg loop automatically if
   the AST or override table maps to it.

---

## 11. Three build flavours, when to pick which

| Mode | Command | Output | Use when |
|---|---|---|---|
| PE64 direct | `build.cmd pe64 src.asm` | `~2 KB` exe + `raylib.dll` alongside | Quick iteration, no MSVC needed |
| OBJ → DLL | `build.cmd obj-dll src.asm` | `~9 KB` exe + `raylib.dll` alongside | You want MSVC's CRT (`mainCRTStartup`, full stdlib) but still ship raylib as a DLL |
| OBJ → static | `build.cmd obj-static src.asm` | `~588 KB` self-contained exe | Single-file distribution, no raylib.dll required |

The OBJ modes need the VS dev shell envs in scope (`LIB`, `INCLUDE`).
The PE64 mode needs nothing besides fasmg.

---

## 12. Known gaps

- **Variadic functions** (`TraceLog`, `TextFormat`). The wrapper splices
  whatever you pass after the format string straight into invoke — no
  type-checking, no automatic float promotion. For a typed `TraceLog`
  call use the static-text form (`TraceLog LOG_INFO, _msg`) and avoid
  formatting; if you need formatting, drop to raw `invoke
  RLAPI.TraceLog, …` and hand-place each arg.
- **Callbacks** (`SetTraceLogCallback`, `SetLoadFileDataCallback`).
  Pass a function pointer with the right Win64 prologue/epilogue.
  No wrapper sugar yet for the callee side.
- **`FilePathList` returned by `LoadDroppedFiles` / `LoadDirectoryFiles`**
  works in raylib 6.0 (no padding gap), but earlier raylib releases had
  a `capacity` field that the JSON dropped — if you upgrade to a future
  version that re-adds it, regenerate the projection.
- **No 32-bit target.** The dispatcher and ABI handling are Win64-only.
  `bin32/`/`lib32/` are present in the release tree but no build
  tooling targets them yet.

---

## 13. Where to look next

- [README.md](README.md) — high-level orientation, layout map.
- [DISCOVERY.md](DISCOVERY.md) — exploration notes; the *why* behind
  every odd choice in `gen.py`.
- [PLAN.md](PLAN.md) — implementation status + AST stats.
- [examples/pe64/](examples/pe64/) — 15 working ports that double as
  recipes (start with `core_basic_window.asm`, then `core_2d_camera.asm`
  for the camera follow pattern, then `core_3d_picking.asm` for the
  Vector2-spill + multi-struct-arg case).
- [examples/typed_args_verify.asm](examples/typed_args_verify.asm) — a
  self-contained proof of the `transform` pipeline; run it to see the
  JYES/JNO behaviour table.
- [inc/raylib_api.inc](inc/raylib_api.inc) — the wrappers themselves.
  600 of them; grep is your friend.
- [inc/raylib_enums.inc](inc/raylib_enums.inc) — every enum member
  available to typed-arg wrappers.
