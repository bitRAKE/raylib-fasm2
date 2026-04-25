
; raylib [core] example - 2d camera
; Port of raylib/examples/core/core_2d_camera.c (subset)
;
; Stresses:
;   - Camera2D (24B) by-value via `addr` for BeginMode2D, plus direct
;     field access for camera.target / camera.rotation / camera.zoom
;     each frame
;   - Per-frame SSE math (rotation clamp, log/exp via runtime calls
;     skipped here — we use a simpler linear zoom instead)
;   - Input-driven mutation of player Rectangle and camera state
;
; Differences from the C version:
;   - No buildings array (one Rectangle "player" only — keeps the asm
;     readable; the camera transform path is the part we want to test)
;   - Mouse-wheel zoom is linear instead of `expf(logf(z) + dz*0.1f)`
;     so we don't have to call libc

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

	; player = { 400, 280, 40, 40 }
	mov	dword [player.x],      400.0f
	mov	dword [player.y],      280.0f
	mov	dword [player.width],   40.0f
	mov	dword [player.height],  40.0f

	; camera = { offset:(400, 225), target:(420, 300), rotation:0, zoom:1 }
	mov	dword [camera.offset.x], 400.0f
	mov	dword [camera.offset.y], 225.0f
	mov	dword [camera.target.x], 420.0f
	mov	dword [camera.target.y], 300.0f
	mov	dword [camera.rotation], 0.0f
	mov	dword [camera.zoom],     1.0f

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	; --- update player ---
	IsKeyDown		KEY_RIGHT
	test	eax, eax
	jz	.not_right
	movss	xmm0, [player.x]
	addss	xmm0, [c_2_0]
	movss	[player.x], xmm0
  .not_right:

	IsKeyDown		KEY_LEFT
	test	eax, eax
	jz	.not_left
	movss	xmm0, [player.x]
	subss	xmm0, [c_2_0]
	movss	[player.x], xmm0
  .not_left:

	; camera.target = player.x + 20, player.y + 20
	movss	xmm0, [player.x]
	addss	xmm0, [c_20_0]
	movss	[camera.target.x], xmm0
	movss	xmm0, [player.y]
	addss	xmm0, [c_20_0]
	movss	[camera.target.y], xmm0

	; --- camera rotation: A decreases, S increases, clamp to [-40, 40] ---
	IsKeyDown		KEY_A
	test	eax, eax
	jz	.not_a
	movss	xmm0, [camera.rotation]
	subss	xmm0, [c_1_0]
	movss	[camera.rotation], xmm0
  .not_a:

	IsKeyDown		KEY_S
	test	eax, eax
	jz	.not_s
	movss	xmm0, [camera.rotation]
	addss	xmm0, [c_1_0]
	movss	[camera.rotation], xmm0
  .not_s:

	movss	xmm0, [camera.rotation]
	movss	xmm1, [c_40_0]
	ucomiss	xmm0, xmm1
	jbe	.not_too_high
	movss	[camera.rotation], xmm1
  .not_too_high:
	movss	xmm0, [camera.rotation]
	movss	xmm1, [c_neg_40_0]
	ucomiss	xmm0, xmm1
	jae	.not_too_low
	movss	[camera.rotation], xmm1
  .not_too_low:

	; --- camera zoom: mouse wheel moves it linearly, clamp [0.1, 3.0] ---
	GetMouseWheelMove                       ; returns float in xmm0
	mulss	xmm0, [c_0_1]                   ; scale wheel delta
	addss	xmm0, [camera.zoom]
	movss	[camera.zoom], xmm0

	movss	xmm0, [camera.zoom]
	movss	xmm1, [c_3_0]
	ucomiss	xmm0, xmm1
	jbe	.zoom_in_range
	movss	[camera.zoom], xmm1
  .zoom_in_range:
	movss	xmm0, [camera.zoom]
	movss	xmm1, [c_0_1]
	ucomiss	xmm0, xmm1
	jae	.zoom_above_min
	movss	[camera.zoom], xmm1
  .zoom_above_min:

	; R resets rotation + zoom
	IsKeyPressed		KEY_R
	test	eax, eax
	jz	.no_reset
	mov	dword [camera.rotation], 0.0f
	mov	dword [camera.zoom],     1.0f
  .no_reset:

	; --- draw ---
	BeginDrawing
	ClearBackground		RAYWHITE

	BeginMode2D		addr camera
	; ground line
	DrawRectangle		-6000, 320, 13000, 8000, DARKGRAY
	; player square
	DrawRectangleRec	addr player, RED
	EndMode2D

	DrawText		_msg1, 20, 20, 10, BLACK
	DrawText		_msg2, 40, 40, 10, DARKGRAY
	DrawText		_msg3, 40, 60, 10, DARKGRAY
	DrawText		_msg4, 40, 80, 10, DARKGRAY
	DrawFPS			700, 10
	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title db 'raylib [core] example - 2d camera', 0
  _msg1  db 'Free 2D camera controls:', 0
  _msg2  db '- Right/Left to move player', 0
  _msg3  db '- Mouse Wheel to Zoom in-out', 0
  _msg4  db '- A / S to Rotate, R to reset', 0

  player Rectangle
  camera Camera2D

  c_2_0     dd 2.0f
  c_20_0    dd 20.0f
  c_1_0     dd 1.0f
  c_40_0    dd 40.0f
  c_neg_40_0 dd -40.0f
  c_3_0     dd 3.0f
  c_0_1     dd 0.1f

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
