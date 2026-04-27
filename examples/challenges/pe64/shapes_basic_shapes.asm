; raylib [shapes] basic shapes - projection challenge.
;
; Stresses:
;   - repeated small structs by value
;   - mixed int/float/struct arguments
;   - stack spill after multiple register arguments
;
; Build:
;   .\_build.cmd examples\challenges\pe64\shapes_basic_shapes.asm build\shapes_basic_shapes.exe

include 'raylib_pe64.inc'

section '.data' data readable writeable

title db 'raylib [shapes] basic shapes',0
message db 'projection challenge: shapes and by-value structs',0
rotation dd ?
step dd 0.2f
circle:
	.x dd ?
	.y dd ?
t1:
	.x dd ?
	.y dd ?
t2:
	.x dd ?
	.y dd ?
t3:
	.x dd ?
	.y dd ?
poly:
	.x dd ?
	.y dd ?

section '.text' code readable executable

start:
	sub rsp,8

	InitWindow 800, 450, title
	SetTargetFPS 60

	mov dword [rotation], 0.0f
	mov dword [circle.x], 160.0f
	mov dword [circle.y], 220.0f
	mov dword [t1.x], 600.0f
	mov dword [t1.y], 80.0f
	mov dword [t2.x], 540.0f
	mov dword [t2.y], 150.0f
	mov dword [t3.x], 660.0f
	mov dword [t3.y], 150.0f
	mov dword [poly.x], 600.0f
	mov dword [poly.y], 330.0f

main_loop:
	WindowShouldClose
	test al,al
	jnz shutdown

	movss xmm0,[rotation]
	addss xmm0,[step]
	movss [rotation],xmm0

	BeginDrawing
	ClearBackground RAYWHITE
	DrawText message, 20, 20, 20, DARKGRAY
	DrawLine 18, 42, 782, 42, BLACK

	DrawCircle 160, 120, float dword 35.0, DARKBLUE
	DrawCircleGradient [circle], float dword 60.0, GREEN, SKYBLUE
	DrawCircleLines 160, 340, float dword 80.0, DARKBLUE
	DrawEllipse 160, 120, float dword 25.0, float dword 20.0, YELLOW
	DrawRectangle 340, 100, 120, 60, RED
	DrawRectangleGradientH 310, 170, 180, 130, MAROON, GOLD
	DrawRectangleLines 360, 320, 80, 60, ORANGE
	DrawTriangle [t1], [t2], [t3], VIOLET
	DrawPoly [poly], 6, float dword 80.0, float dword [rotation], BROWN

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
