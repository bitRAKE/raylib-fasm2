# MS COFF Raylib Examples

The preferred COFF path is now response-file driven:

```bat
.\_build_link.cmd examples\_static64.asm
.\_build_link.cmd examples\_dynamic64_lax.asm
```

The assembly source emits both the COFF object and a linker response file. The
script assembles with fasm2 and then invokes the selected COFF linker with that
response file. Set `RAYLIB_LINKER` to force a linker, for example
`C:\Program Files\LLVM\bin\lld-link.exe`; otherwise the script prefers
`lld-link.exe` on `PATH` and falls back to `link.exe`.

Select the Raylib linkage by choosing one library line in the response block:

- `Win32\Release.DLL\raylib.lib`: dynamic x86
- `x64\Release.DLL\raylib.lib`: dynamic x64
- `Win32\Release\raylib.lib`: static x86
- `x64\Release\raylib.lib`: static x64

`examples/_static64.asm` demonstrates the aggressive static-link response.
`examples/_dynamic64_lax.asm` demonstrates a relaxed dynamic EXE response that
keeps ordinary linker defaults and links against `raylib.dll` through the import
library.
