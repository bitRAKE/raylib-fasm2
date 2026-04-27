; raylib [text] font return - expected projection gap.
;
; This example intentionally demonstrates a remaining API projection issue:
; GetFontDefault returns a Font aggregate. On Win64 this requires ABI handling
; for aggregate return/storage that the current generated wrappers do not model.
;
; Expected today: assembly fails at `GetFontDefault addr font`.

include 'raylib_pe64.inc'

section '.data' data readable writeable

title db 'raylib [text] font return challenge',0
message db 'GetFontDefault + DrawTextEx',0
font rb sizeof.RayLib.Font
pos:
	.x dd ?
	.y dd ?

section '.text' code readable executable

start:
	sub rsp,8

	InitWindow 800, 450, title
	SetTargetFPS 60

	GetFontDefault addr font

main_loop:
	WindowShouldClose
	test al,al
	jnz shutdown

	BeginDrawing
	ClearBackground RAYWHITE
	DrawTextEx addr font, message, [pos], float dword 30.0, float dword 2.0, MAROON
	EndDrawing
	jmp main_loop

shutdown:
	CloseWindow
	invoke ExitProcess,0

section '.idata' import data readable writeable

library raylib,'raylib.dll', \
	kernel32,'KERNEL32.DLL'
include 'raylib_imports_pe.inc'
import kernel32, \
	ExitProcess,'ExitProcess'
