
; raylib [core] example - input keys
; ported from raylib/examples/core/core_input_keys.c
;
; Tests:
;   - IsKeyDown(KEY_*) typed-arg path
;   - DrawCircleV(Vector2 by value, float, Color) — exercises 8-byte
;     struct-by-value calling convention on Win64

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

	; ballPosition = (400.0f, 225.0f)
	mov	dword [ballPosition.x], 400.0f
	mov	dword [ballPosition.y], 225.0f

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	IsKeyDown		KEY_RIGHT
	test	eax, eax
	jz	.not_right
	movss	xmm0, [ballPosition.x]
	addss	xmm0, [c_step]
	movss	[ballPosition.x], xmm0
  .not_right:

	IsKeyDown		KEY_LEFT
	test	eax, eax
	jz	.not_left
	movss	xmm0, [ballPosition.x]
	subss	xmm0, [c_step]
	movss	[ballPosition.x], xmm0
  .not_left:

	IsKeyDown		KEY_UP
	test	eax, eax
	jz	.not_up
	movss	xmm0, [ballPosition.y]
	subss	xmm0, [c_step]
	movss	[ballPosition.y], xmm0
  .not_up:

	IsKeyDown		KEY_DOWN
	test	eax, eax
	jz	.not_down
	movss	xmm0, [ballPosition.y]
	addss	xmm0, [c_step]
	movss	[ballPosition.y], xmm0
  .not_down:

	BeginDrawing
	ClearBackground		RAYWHITE
	DrawText		_msg, 10, 10, 20, DARKGRAY
	; DrawCircleV(Vector2 center, float radius, Color color)
	; Vector2 is 8 bytes -> passed in rcx (as raw bits)
	; radius is float    -> xmm1 (slot 1)
	; color is 4 bytes   -> r8d
	; The fasmg `invoke` macro needs floats marked with the `float`
	; keyword so it knows to use xmm registers; the explicit `dword`
	; pins it to single-precision (default for `float` is qword/double
	; under PE64).
	DrawCircleV		[ballPosition], float dword 50.0, MAROON
	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title db 'raylib [core] example - input keys', 0
  _msg   db 'move the ball with arrow keys', 0

  ballPosition Vector2

  c_step dd 2.0f    ; 2 px / frame

section '.idata' import data readable writeable

  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
