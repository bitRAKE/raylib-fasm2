; MS COFF x64 raylib support for fasm2.
; Selects `format MS64 COFF`, link-time raylib symbols, and the x64 Windows
; calling convention.

define RAYLIB_LINK_COFF
include 'raylib_fasm2.inc'
