; Direct PE x86 raylib support for fasm2.
; Selects `format PE GUI 4.0`, `entry start`, direct raylib.dll imports,
; and the x86 C calling convention.

define RAYLIB_TARGET_32
include 'raylib_fasm2.inc'
