; Direct PE x64 raylib support for fasm2.
; Selects `format PE64 GUI 5.0`, `entry start`, direct raylib.dll imports,
; and the x64 Windows calling convention.

include 'raylib_fasm2.inc'

if defined RAYLIB_DEBUG

; debug ABI compliance of RSP post ABI function call:
macro RLAPI function*, arguments&
	local dbgstr,skip
	repeat 1,L:__LINE__
		dbgstr equ __FILE__,'(',`L,'): ',`function,' ',`arguments
	end repeat

	RLAPI function, arguments ; forward to prior meaning
	test spl,$F
	jz skip
	int3 ; debugger break
	db dbgstr,10,0
skip:
end macro

end if
