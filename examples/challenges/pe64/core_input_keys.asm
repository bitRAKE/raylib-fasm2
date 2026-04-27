; raylib [core] input keys - projection challenge.
;
; Stresses:
;   - enum token reduction for IsKeyDown(KEY_*)
;   - Vector2 by-value as an 8-byte aggregate
;   - float argument routing
;
; Build:
;   .\_build.cmd examples\challenges\pe64\core_input_keys.asm build\core_input_keys.exe

include 'raylib_pe64.inc'

section '.data' data readable writeable

title db 'raylib [core] input keys',0
message db 'move the ball with arrow keys',0
ballPosition:
	.x dd ?
	.y dd ?
step dd 2.0f

section '.text' code readable executable

start:
	sub rsp,8

	InitWindow 800, 450, title
	SetTargetFPS 60

	mov dword [ballPosition.x], 400.0f
	mov dword [ballPosition.y], 225.0f

main_loop:
	WindowShouldClose
	test al,al
	jnz shutdown

	IsKeyDown KEY_RIGHT
	test al,al
	jz not_right
	movss xmm0,[ballPosition.x]
	addss xmm0,[step]
	movss [ballPosition.x],xmm0
not_right:

	IsKeyDown KEY_LEFT
	test al,al
	jz not_left
	movss xmm0,[ballPosition.x]
	subss xmm0,[step]
	movss [ballPosition.x],xmm0
not_left:

	IsKeyDown KEY_UP
	test al,al
	jz not_up
	movss xmm0,[ballPosition.y]
	subss xmm0,[step]
	movss [ballPosition.y],xmm0
not_up:

	IsKeyDown KEY_DOWN
	test al,al
	jz not_down
	movss xmm0,[ballPosition.y]
	addss xmm0,[step]
	movss [ballPosition.y],xmm0
not_down:

	BeginDrawing
	ClearBackground RAYWHITE
	DrawText message, 10, 10, 20, DARKGRAY
	DrawCircleV [ballPosition], float dword 50.0, MAROON
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
