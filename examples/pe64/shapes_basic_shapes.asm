
; raylib [shapes] example - basic shapes
; Port of raylib/examples/shapes/shapes_basic_shapes.c (subset)
;
; Stresses:
;   - Many shape primitives in one frame
;   - Multiple Vector2 (8B) by-value via `[label]`
;   - DrawTriangle with three Vector2 in a row
;   - DrawPoly with mixed int + float + struct
;   - SSE accumulator drives a per-frame rotation

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

	mov	[rotation], 0.0

	; static Vector2 instances for shapes that take them by value
	mov	[v_circle.x], 160.0
	mov	[v_circle.y], 220.0

	mov	[v_t1.x], 600.0
	mov	[v_t1.y],  80.0
	mov	[v_t2.x], 540.0
	mov	[v_t2.y], 150.0
	mov	[v_t3.x], 660.0
	mov	[v_t3.y], 150.0

	mov	[v_poly.x], 600.0
	mov	[v_poly.y], 330.0

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	movss	xmm0, [rotation]
	addss	xmm0, [c_step]
	movss	[rotation], xmm0

	BeginDrawing
	ClearBackground		RAYWHITE
	DrawText		_msg, 20, 20, 20, DARKGRAY
	DrawLine		18, 42, 782, 42, BLACK

	; circle / ellipse cluster on the left
	DrawCircle		160, 120, float dword 35.0, DARKBLUE
	DrawCircleGradient	[v_circle], float dword 60.0, GREEN, SKYBLUE
	DrawCircleLines		160, 340, float dword 80.0, DARKBLUE
	DrawEllipse		160, 120, float dword 25.0, float dword 20.0, YELLOW
	DrawEllipseLines	160, 120, float dword 30.0, float dword 25.0, YELLOW

	; rectangle cluster in the middle
	DrawRectangle		340, 100, 120, 60, RED
	DrawRectangleGradientH	310, 170, 180, 130, MAROON, GOLD
	DrawRectangleLines	360, 320, 80, 60, ORANGE

	; triangles on the right
	DrawTriangle		[v_t1], [v_t2], [v_t3], VIOLET

	; rotating regular polygon at bottom-right
	DrawPoly		[v_poly], 6, float dword 80.0, float dword [rotation], BROWN

	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title db 'raylib [shapes] example - basic shapes', 0
  _msg   db 'some basic shapes available on raylib', 0

  rotation dd ?
  c_step   dd 0.2

  v_circle Vector2
  v_t1     Vector2
  v_t2     Vector2
  v_t3     Vector2
  v_poly   Vector2

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
