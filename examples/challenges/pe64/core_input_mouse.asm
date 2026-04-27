; raylib [core] input mouse - projection challenge.
;
; Stresses:
;   - Vector2 return from GetMousePosition
;   - MouseButton enum token reduction
;   - color from memory operand
;
; Build:
;   .\_build.cmd examples\challenges\pe64\core_input_mouse.asm build\core_input_mouse.exe

include 'raylib_pe64.inc'

section '.data' data readable writeable

title db 'raylib [core] input mouse',0
message db 'move ball with mouse, click to change color',0
ballPosition:
	.x dd ?
	.y dd ?
ballColor dd ?

section '.text' code readable executable

start:
	sub rsp,8

	InitWindow 800, 450, title
	SetTargetFPS 60

	mov dword [ballPosition.x], -100.0f
	mov dword [ballPosition.y], -100.0f
	mov dword [ballColor], RayLib.DARKBLUE

main_loop:
	WindowShouldClose
	test al,al
	jnz shutdown

	GetMousePosition
	mov qword [ballPosition],rax

	IsMouseButtonPressed MOUSE_BUTTON_LEFT
	test al,al
	jz try_middle
	mov dword [ballColor], RayLib.MAROON
	jmp color_done
try_middle:
	IsMouseButtonPressed MOUSE_BUTTON_MIDDLE
	test al,al
	jz try_right
	mov dword [ballColor], RayLib.LIME
	jmp color_done
try_right:
	IsMouseButtonPressed MOUSE_BUTTON_RIGHT
	test al,al
	jz color_done
	mov dword [ballColor], RayLib.DARKBLUE
color_done:

	BeginDrawing
	ClearBackground RAYWHITE
	DrawCircleV [ballPosition], float dword 40.0, [ballColor]
	DrawText message, 10, 10, 20, DARKGRAY
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
