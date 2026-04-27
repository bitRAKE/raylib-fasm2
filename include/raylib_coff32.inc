; MS COFF x86 raylib support for fasm2.
; Selects `format MS COFF`, link-time raylib symbols, and the x86 C calling
; convention.

define RAYLIB_TARGET_32
define RAYLIB_LINK_COFF
include 'raylib_fasm2.inc'
