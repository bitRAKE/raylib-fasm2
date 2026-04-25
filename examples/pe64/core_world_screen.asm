
; raylib [core] example - world screen
; Port of raylib/examples/core/core_world_screen.c
;
; Stresses:
;   - GetWorldToScreen: Vector2 (8B) return in rax, Vector3 (12B)
;     by-addr first arg, Camera (44B) by-addr second arg
;   - MeasureText: int return used to centre a text
;   - 3D + 2D overlay: world-space cube + screen-space text label
;     pinned to its projected position
;   - TextFormat skipped — we use a static label instead since
;     variadic printf formatting isn't yet supported

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

	; Camera at (10,10,10) looking at origin
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

	; cubePosition = (0,0,0); labelOrigin = (0, 2.5, 0)
	mov	dword [cubePosition.x], 0.0f
	mov	dword [cubePosition.y], 0.0f
	mov	dword [cubePosition.z], 0.0f
	mov	dword [labelOrigin.x],  0.0f
	mov	dword [labelOrigin.y],  2.5f
	mov	dword [labelOrigin.z],  0.0f

	DisableCursor

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	UpdateCamera		addr camera, CAMERA_THIRD_PERSON

	; cubeScreenPosition = GetWorldToScreen(labelOrigin, camera)
	GetWorldToScreen	addr labelOrigin, addr camera
	mov	qword [cubeScreenPos], rax

	BeginDrawing
	ClearBackground		RAYWHITE

	BeginMode3D		addr camera
	DrawCube		addr cubePosition, float dword 2.0f, float dword 2.0f, float dword 2.0f, RED
	DrawCubeWires		addr cubePosition, float dword 2.0f, float dword 2.0f, float dword 2.0f, MAROON
	DrawGrid		10, float dword 1.0f
	EndMode3D

	; centre the label text horizontally on the cube's screen pos:
	;   x = (int)cubeScreenPos.x - MeasureText(label, 20)/2
	;   y = (int)cubeScreenPos.y
	MeasureText		_label_text, 20
	sar	eax, 1                       ; eax = MeasureText / 2
	mov	r12d, eax                    ; r12d = half-width in px

	cvttss2si eax, dword [cubeScreenPos.x]
	sub	eax, r12d
	mov	r13d, eax                    ; r13d = label x

	cvttss2si eax, dword [cubeScreenPos.y]
	mov	r14d, eax                    ; r14d = label y

	DrawText		_label_text, r13d, r14d, 20, BLACK

	DrawText		_help1, 10, 10, 20, LIME
	DrawText		_help2, 10, 40, 20, GRAY

	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title       db 'raylib [core] example - world screen', 0
  _label_text  db 'Enemy: 100/100', 0
  _help1       db 'Cube screen-space label tracks its world position', 0
  _help2       db 'Text 2d should be always on top of the cube', 0

  camera         Camera3D
  cubePosition   Vector3
  labelOrigin    Vector3
  cubeScreenPos  Vector2

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
