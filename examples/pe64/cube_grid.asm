
; 3D grid of cubes — stresses multiple Vector3 by-value args in
; sequence and a tight inner loop driving raylib draws.
;
; Stresses:
;   - DrawCubeV(Vector3 pos, Vector3 size, Color tint)
;     -> two consecutive 12-byte struct args (auto-addr both)
;   - GetTime() returns double
;   - SSE math driving cube positions per frame

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

	; camera = perspective at (10, 10, 10) looking at origin
	mov	dword [camera.position.x], 10.0f
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

	; cube size = (0.8, 0.8, 0.8)
	mov	dword [cubeSize.x], 0.8f
	mov	dword [cubeSize.y], 0.8f
	mov	dword [cubeSize.z], 0.8f

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	BeginDrawing
	ClearBackground		RAYWHITE

	BeginMode3D		addr camera

	; Draw a 5x5 grid of cubes on the XZ plane.
	xor	r12d, r12d            ; ix = 0
  .row:
	cmp	r12d, 5
	jge	.grid_done
	xor	r13d, r13d            ; iz = 0
  .col:
	cmp	r13d, 5
	jge	.row_next

	; cubePos.x = (ix - 2) * 1.0
	mov	eax, r12d
	sub	eax, 2
	cvtsi2ss xmm0, eax
	movss	[cubePos.x], xmm0
	mov	dword [cubePos.y], 0.0f
	; cubePos.z = (iz - 2) * 1.0
	mov	eax, r13d
	sub	eax, 2
	cvtsi2ss xmm0, eax
	movss	[cubePos.z], xmm0

	; tint cycles: skyblue/maroon/gold/lime/violet by (ix+iz) mod 5
	mov	eax, r12d
	add	eax, r13d
	xor	edx, edx
	mov	ecx, 5
	div	ecx                   ; edx = (ix+iz) % 5
	mov	eax, dword [colors + rdx*4]
	mov	[currentTint], eax

	DrawCubeV		addr cubePos, addr cubeSize, [currentTint]

	inc	r13d
	jmp	.col
  .row_next:
	inc	r12d
	jmp	.row
  .grid_done:

	DrawGrid		10, float dword 1.0f
	EndMode3D

	DrawText		_msg, 10, 10, 20, DARKGRAY
	DrawFPS			10, 30
	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title  db '3D cube grid — DrawCubeV test', 0
  _msg    db '5x5 grid of cubes with cycling tints', 0

  camera   Camera3D
  cubeSize Vector3
  cubePos  Vector3

  currentTint dd ?
  colors      dd SKYBLUE, MAROON, GOLD, LIME, VIOLET

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
