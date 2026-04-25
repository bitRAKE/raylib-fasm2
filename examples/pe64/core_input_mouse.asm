
; raylib [core] input mouse — port
;
; Tests struct *return* (Vector2 from GetMousePosition, 8 bytes — fits
; in rax under Win64 ABI). Also: chained IsMouseButtonPressed enum
; checks via the wrapper-level transform.

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

	mov	dword [ballPosition.x], -100.0f
	mov	dword [ballPosition.y], -100.0f
	mov	dword [ballColor], DARKBLUE

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	IsKeyPressed		KEY_H
	test	eax, eax
	jz	.no_h
	IsCursorHidden
	test	eax, eax
	jz	.was_visible
	ShowCursor
	jmp	.h_done
  .was_visible:
	HideCursor
  .h_done:
  .no_h:

	; ballPosition = GetMousePosition()  -- Vector2 (8 bytes) returned in rax
	GetMousePosition
	mov	qword [ballPosition], rax

	; Cascade of IsMouseButtonPressed -> ballColor = …
	IsMouseButtonPressed	MOUSE_BUTTON_LEFT
	test	eax, eax
	jz	.try_mid
	mov	dword [ballColor], MAROON
	jmp	.color_done
  .try_mid:
	IsMouseButtonPressed	MOUSE_BUTTON_MIDDLE
	test	eax, eax
	jz	.try_right
	mov	dword [ballColor], LIME
	jmp	.color_done
  .try_right:
	IsMouseButtonPressed	MOUSE_BUTTON_RIGHT
	test	eax, eax
	jz	.color_done
	mov	dword [ballColor], DARKBLUE
  .color_done:

	BeginDrawing
	ClearBackground		RAYWHITE
	DrawCircleV		[ballPosition], float dword 40.0, [ballColor]
	DrawText		_msg1, 10, 10, 20, DARKGRAY
	DrawText		_msg2, 10, 30, 20, DARKGRAY
	IsCursorHidden
	test	eax, eax
	jz	.show_visible
	DrawText		_hidden, 20, 60, 20, RED
	jmp	.text_done
  .show_visible:
	DrawText		_visible, 20, 60, 20, LIME
  .text_done:
	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title    db 'raylib [core] example - input mouse', 0
  _msg1     db 'move ball with mouse and click button to change color', 0
  _msg2     db 'Press H to toggle cursor visibility', 0
  _hidden   db 'CURSOR HIDDEN', 0
  _visible  db 'CURSOR VISIBLE', 0

  ballPosition Vector2
  ballColor    dd ?

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
