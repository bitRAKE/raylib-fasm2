; Compile/runtime smoke for aggregate-sensitive raylib calls used by the
; classics ports. This is intentionally small and direct PE x64 only.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 640
SCREEN_HEIGHT = 360

section '.data' data readable writeable

GLOBSTR.here ; constant string payload

	align 4

mousePos RayLib.Vector2 x:0.0, y:0.0
panel RayLib.Rectangle x:120.0, y:110.0, width:210.0, height:90.0
probe RayLib.Rectangle x:220.0, y:145.0, width:120.0, height:70.0
camera RayLib.Camera2D
customColor RayLib.Color r:80, g:150, b:210, a:255
fadeColor dd ?

section '.text' code readable executable

include '..\common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'raylib aggregate smoke'
	fastcall InitGame
	SetTargetFPS 60

.frame:
	WindowShouldClose
	test al,al
	jnz .close

	fastcall UpdateDrawFrame
	jmp .frame

.close:
	fastcall UnloadGame
	CloseWindow
	invoke ExitProcess,0
.space := fastcall.frame

proc InitGame
	mov dword [camera.offset+RayLib.Vector2.x],0.0
	mov dword [camera.offset+RayLib.Vector2.y],0.0
	mov dword [camera.target+RayLib.Vector2.x],0.0
	mov dword [camera.target+RayLib.Vector2.y],0.0
	mov dword [camera.rotation],0.0
	mov dword [camera.zoom],1.0
	Fade [customColor], float dword 0.55
	mov [fadeColor],eax
	ret

endp

proc UpdateDrawFrame
	GetMousePosition
	mov [mousePos],rax

	BeginDrawing
	ClearBackground RAYWHITE
	DrawText 'aggregate smoke: Rectangle, Vector2, Camera2D, TextFormat, Fade', 20, 15, 18, DARKGRAY
	TextFormat 'score %i', 42
	DrawText rax, 20, 42, 18, GRAY

	BeginMode2D addr camera
	DrawRectangleRec addr panel, [fadeColor]
	CheckCollisionRecs addr panel, addr probe
	test al,al
	jz .no_hit
	DrawRectangleRec addr probe, GREEN
	jmp .after_probe
.no_hit:
	DrawRectangleRec addr probe, RED
.after_probe:
	DrawCircleV [mousePos], float dword 8.0, BLUE
	EndMode2D

	EndDrawing
	ret

endp

proc UnloadGame
	ret

endp
section '.idata' import data readable writeable

library raylib,'raylib.dll', \
	kernel32,'KERNEL32.DLL'

include 'raylib_imports_pe.inc'

import kernel32, \
	ExitProcess,'ExitProcess'
