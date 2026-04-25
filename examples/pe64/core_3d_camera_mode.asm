
; raylib [core] example - 3d camera mode
; Port of raylib/examples/core/core_3d_camera_mode.c
;
; Stresses:
;   - Camera3D (44 bytes) by-value via auto-addr
;   - Vector3 (12 bytes) by-value via auto-addr
;   - DrawCube has 5 args: Vector3 + 3 floats + Color (mixed
;     int/float/struct register routing)
;   - DrawGrid has int + float
;   - CameraProjection enum (camera.projection field)
;   - DrawFPS — no args

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

	; camera = { position:(0,10,10), target:(0,0,0), up:(0,1,0),
	;            fovy:45, projection:CAMERA_PERSPECTIVE }
	mov	dword [camera.position.x], 0.0f
	mov	dword [camera.position.y], 10.0f
	mov	dword [camera.position.z], 10.0f
	mov	dword [camera.target.x],   0.0f
	mov	dword [camera.target.y],   0.0f
	mov	dword [camera.target.z],   0.0f
	mov	dword [camera.up.x],       0.0f
	mov	dword [camera.up.y],       1.0f
	mov	dword [camera.up.z],       0.0f
	mov	dword [camera.fovy],       45.0f
	mov	dword [camera.projection], RayLib.CameraProjection.CAMERA_PERSPECTIVE

	; cubePosition = (0, 0, 0)
	mov	dword [cubePosition.x], 0.0f
	mov	dword [cubePosition.y], 0.0f
	mov	dword [cubePosition.z], 0.0f

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	BeginDrawing
	ClearBackground		RAYWHITE

	BeginMode3D		addr camera
	; DrawCube(Vector3 pos, float w, float h, float l, Color color)
	;   pos via `addr` (12B → lea rcx, [pos]),
	;   w/h/l in xmm1/xmm2/xmm3 (single-precision),
	;   color (4B) on stack at [rsp+32]
	DrawCube		addr cubePosition, float dword 2.0f, float dword 2.0f, float dword 2.0f, RED
	DrawCubeWires		addr cubePosition, float dword 2.0f, float dword 2.0f, float dword 2.0f, MAROON
	DrawGrid		10, float dword 1.0f
	EndMode3D

	DrawText		_msg, 10, 40, 20, DARKGRAY
	DrawFPS			10, 10
	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title db 'raylib [core] example - 3d camera mode', 0
  _msg   db 'Welcome to the third dimension!', 0

  camera       Camera3D
  cubePosition Vector3

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
