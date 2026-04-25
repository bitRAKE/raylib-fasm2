; raylib.inc — top-level fasmg projection of the raylib C API.
;
; Two linkage modes:
;
;   DLL mode (default): user's program is a self-contained PE64 EXE
;       that imports raylib.dll at runtime. No external linker step.
;       The RLAPI dispatcher uses indirect calls through an IAT we
;       build via `library raylib, 'raylib.dll'` + `include
;       'raylib_imports.inc'`.
;
;   OBJ mode: opt in with `define RAYLIB_MODE_OBJ` BEFORE this include.
;       Writes a COFF object that link.exe resolves against
;       raylib.lib (either an import library for raylib.dll or a static
;       library). The RLAPI dispatcher uses direct calls; symbols are
;       declared via `include 'raylib_extrn.inc'`.
;
; Example (DLL):
;
;     format PE64 GUI 5.0
;     entry start
;     include 'raylib.inc'
;
;     section '.text' code readable executable
;       start:
;         sub  rsp, 8
;         InitWindow 800, 450, _title
;         …
;
;     section '.idata' import data readable writeable
;       library raylib, 'raylib.dll', kernel32, 'KERNEL32.DLL'
;       include 'raylib_imports.inc'
;       import kernel32, ExitProcess, 'ExitProcess'
;
; Example (OBJ — link with raylib.lib + kernel32.lib):
;
;     format MS64 COFF
;     define RAYLIB_MODE_OBJ
;     include 'raylib.inc'
;     extrn 'ExitProcess' as ExitProcess
;     include 'raylib_extrn.inc'
;
;     section '.text' code readable executable
;       public start
;       start:
;         sub  rsp, 8
;         InitWindow 800, 450, _title
;         …

include 'win64a.inc'

include 'raylib_types.inc'
include 'raylib_aliases.inc'
include 'raylib_enums.inc'
include 'raylib_colors.inc'

; Pick a dispatcher based on the build mode flag.
if defined RAYLIB_MODE_OBJ
	include 'raylib_obj_dispatch.inc'
else
	include 'raylib_dll_dispatch.inc'
end if

include 'raylib_api.inc'
