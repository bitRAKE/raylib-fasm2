# Projection Challenge Examples

These examples are ports from earlier raylib/fasmg experiments. They are
intended to expose areas where the API projection and ABI layer need more
precision.

Buildable direct PE64 examples:

```bat
.\_build.cmd examples\challenges\pe64\core_input_keys.asm build\core_input_keys.exe
.\_build.cmd examples\challenges\pe64\core_input_mouse.asm build\core_input_mouse.exe
.\_build.cmd examples\challenges\pe64\shapes_basic_shapes.asm build\shapes_basic_shapes.exe
```

Expected failure:

```bat
.\_build.cmd examples\challenges\pe64\text_font_return.asm build\text_font_return.exe
```

`text_font_return.asm` documents the current aggregate-return gap for functions
such as `GetFontDefault`.

Observed projection issues while porting:

- Namespaced struct declarations such as `ballPosition RayLib.Vector2` were not
  usable as `[ballPosition]` arguments under the current fasm2 call parser, so
  these examples use explicit storage labels for `Vector2` values.
- Data labels passed through `fastcall` argument parsing need to be defined
  before use in these examples.
- Aggregate returns, for example `Font GetFontDefault(void)`, need explicit ABI
  support. The generated wrapper has no destination parameter and therefore
  rejects `GetFontDefault addr font`.
