
; raylib [core] example - 3d picking (subset)
; Adapted from raylib/examples/core/core_3d_picking.c
;
; Stresses:
;   - GetScreenToWorldRay: Ray (24B) return via hidden dest, Vector2
;     by-value, Camera (44B) by addr
;   - GetMousePosition: Vector2 (8B) return in rax — spill to memory
;     before passing as a 8B by-value arg to the next call
;   - GetRayCollisionBox: BoundingBox (24B) by-value addr, Ray addr,
;     RayCollision return (>8B hidden dest)
;   - UpdateCamera: Camera*, CameraMode enum (typed-arg)
;   - DrawRay: Ray (24B) by addr
;
; Click left to recompute the pick ray; the line shown is from camera
; through the cursor at the moment of the click.

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	; Right-click toggles cursor lock
	IsMouseButtonPressed	MOUSE_BUTTON_RIGHT
	test	eax, eax
	jz	.no_toggle
	IsCursorHidden
	test	eax, eax
	jz	.cursor_visible
	EnableCursor
	jmp	.no_toggle
  .cursor_visible:
	DisableCursor
  .no_toggle:

	; If cursor is hidden -> first-person camera
	IsCursorHidden
	test	eax, eax
	jz	.skip_update_cam
	UpdateCamera		addr camera, CAMERA_FIRST_PERSON
  .skip_update_cam:

	; Left-click -> recompute pick ray, run BB collision
	IsMouseButtonPressed	MOUSE_BUTTON_LEFT
	test	eax, eax
	jz	.no_pick

	; Vector2 mp = GetMousePosition();
	GetMousePosition
	mov	qword [mousePos], rax            ; spill the 8-byte Vector2

	; ray = GetScreenToWorldRay(mp, camera)
	GetScreenToWorldRay	addr ray, [mousePos], addr camera

	; collision = GetRayCollisionBox(ray, box)
	GetRayCollisionBox	addr collision, addr ray, addr box

  .no_pick:

	BeginDrawing
	ClearBackground		RAYWHITE

	BeginMode3D		addr camera

	; collision.hit (first byte of RayCollision = bool)
	movzx	eax, byte [collision.hit]
	test	eax, eax
	jz	.draw_unselected

	DrawCubeV		addr cubePosition, addr cubeSize, RED
	; CubeWires uses 3 floats, not Vector3
	DrawCubeWires		addr cubePosition, float dword 2.0f, float dword 2.0f, float dword 2.0f, MAROON
	DrawCubeWires		addr cubePosition, float dword 2.2f, float dword 2.2f, float dword 2.2f, GREEN
	jmp	.cube_drawn

  .draw_unselected:
	DrawCubeV		addr cubePosition, addr cubeSize, GRAY
	DrawCubeWires		addr cubePosition, float dword 2.0f, float dword 2.0f, float dword 2.0f, DARKGRAY

  .cube_drawn:
	DrawRay			addr ray, MAROON
	DrawGrid		10, float dword 1.0f
	EndMode3D

	DrawText		_msg1, 240, 10, 20, DARKGRAY
	DrawText		_msg2, 10, 430, 10, GRAY
	DrawFPS			10, 10

	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title  db 'raylib [core] example - 3d picking', 0
  _msg1   db 'Try clicking on the box with your mouse!', 0
  _msg2   db 'Right click mouse to toggle camera controls', 0

  ; baked initial values — no init code needed at runtime
  camera Camera3D                                                     \
                position:<10.0,10.0,10.0>, target:<0.0,0.0,0.0>,      \
                up:<0.0,1.0,0.0>, fovy:45.0,                           \
                projection:RayLib.CameraProjection.CAMERA_PERSPECTIVE
  cubePosition Vector3 0.0, 1.0, 0.0
  cubeSize     Vector3 2.0, 2.0, 2.0
  box          BoundingBox min:<-1.0, 0.0, -1.0>, max:<1.0, 2.0, 1.0>

  ray          Ray
  collision    RayCollision
  mousePos     Vector2

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
