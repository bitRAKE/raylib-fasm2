# fasmg raylib examples

These examples demonstrate the fasm2 backend layer used by the generated raylib projection:

- `include/raylib_pe64.inc`, `include/raylib_pe32.inc`, `include/raylib_coff64.inc`, and `include/raylib_coff32.inc` select the Raylib support layer by filename.
- `_build_link.cmd` plus response-file examples such as `examples/_static64.asm` cover COFF builds where the source controls the linker response.
- `_build.cmd` plus `examples/pe/` covers direct dynamic PE executables and copies `raylib.dll` beside the output when needed.
- `examples/challenges/` contains larger ports that stress the projection and document known gaps.

The six demonstrated Windows cases are:

| Case | Example | Raylib resolution |
| --- | --- | --- |
| direct PE x64 | `examples/pe/64/core_basic_window.asm` | direct `raylib.dll` import table |
| direct PE x86 | `examples/pe/32/core_basic_window.asm` | direct `raylib.dll` import table |
| COFF x64 dynamic | `examples/_dynamic64_lax.asm` | link with `x64\Release.DLL\raylib.lib` |
| COFF x64 static | `examples/_static64.asm` | link with `x64\Release\raylib.lib` |
| COFF x86 dynamic | response-file source using `raylib_coff32.inc` | link with `Win32\Release.DLL\raylib.lib` |
| COFF x86 static | response-file source using `raylib_coff32.inc` | link with `Win32\Release\raylib.lib` |

Set fasm2's include path before assembling:

```bat
set "include=%cd%\include;%include%"
```

Set external dependency paths for the helper scripts:

```bat
set "FASM2_PATH=..\fasm2"
set "RAYLIB_ROOT=..\raylib-build"
set "RAYLIB_LIBPATH=..\raylib-build"
set "RAYLIB_LINKER=C:\Program Files\LLVM\bin\lld-link.exe"
```

`RAYLIB_ROOT` is used by `_build.cmd` to find `raylib.dll`; `RAYLIB_LIBPATH`
is used by `_build_link.cmd` as the linker `/LIBPATH` root. `RAYLIB_LINKER`
is optional; when unset, `_build_link.cmd` prefers `lld-link.exe` on `PATH`
and falls back to `link.exe`.

For local development, create `_local.cmd` at the repo root. It is gitignored
and is called automatically by `_build.cmd` and `_build_link.cmd` when present:

```bat
set "FASM2_PATH=..\fasm2"
set "RAYLIB_ROOT=..\raylib-build"
set "RAYLIB_LIBPATH=..\raylib-build"
set "RAYLIB_LINKER=C:\Program Files\LLVM\bin\lld-link.exe"
```

## COFF Response-File Build

`_build_link.cmd` assembles the requested source with fasm2 and then invokes
the selected COFF linker with the response file emitted by that source. Run it
from a matching MSVC developer shell so the Windows SDK and CRT libraries are
available:

```bat
.\_build_link.cmd examples\_static64.asm
```

`examples/_static64.asm` keeps the aggressive static-link response policy.
`examples/_dynamic64_lax.asm` is the relaxed x64 dynamic variant: it links the
Raylib DLL import library and leaves normal linker defaults such as relocations,
ASLR, stack/heap reserves, and default library behavior intact.

## Direct PE, x64

```bat
.\_build.cmd examples\pe\64\core_basic_window.asm build\core_basic_window64.exe
```

This is the direct dynamic EXE path: no linker step, direct PE import table, and
an x64 `raylib.dll` copied beside the executable when it is not already there.

## Direct PE, x86

```bat
.\_build.cmd examples\pe\32\core_basic_window.asm build32\core_basic_window32.exe
```

This is the direct dynamic EXE path for x86: no linker step, direct PE import
table, and an x86 `raylib.dll` copied beside the executable when it is not
already there.

## Include Selection

Use the include that matches the output format and architecture:

```asm
include 'raylib_pe64.inc'

include 'raylib_pe32.inc'

include 'raylib_coff64.inc'

include 'raylib_coff32.inc'
```

Each support include selects the output format, architecture, Raylib linkage layer, and calling convention. After the include, Raylib calls are the same in every mode.
