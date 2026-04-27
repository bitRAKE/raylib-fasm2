; Direct PE x64 executable build that imports raylib.dll.
;
; Build and copy raylib.dll if needed:
;   .\_build.cmd examples\pe\64\core_basic_window.asm build\core_basic_window64.exe

include 'raylib_pe64.inc'

section '.text' code readable executable

start:
	sub rsp,8

	InitWindow 800, 450, title
	SetTargetFPS 60

main_loop:
	WindowShouldClose
	test al,al
	jnz close_window

	BeginDrawing
	ClearBackground RAYWHITE
	DrawText message, 190, 200, 20, LIGHTGRAY
	EndDrawing
	jmp main_loop

close_window:
	CloseWindow
	invoke ExitProcess,0

section '.data' data readable writeable

title db 'fasmg raylib PE x64',0
message db 'direct PE x64: imports raylib.dll',0

section '.idata' import data readable writeable

library raylib,'raylib.dll', \
	kernel32,'KERNEL32.DLL'
include 'raylib_imports_pe.inc'
import kernel32, \
	ExitProcess,'ExitProcess'
