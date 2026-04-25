
; raylib [core] example - basic screen manager
; Port of raylib/examples/core/core_basic_screen_manager.c
;
; The C version uses two `switch (currentScreen) { … }` blocks. We
; collapse each to a single indirect jump through a per-table base —
; one cmp/jne for index-bounds, one `jmp [tab + idx*8]`. State
; transitions are direct stores into [currentScreen].

format PE64 GUI 5.0
entry start

include 'raylib.inc'

LOGO     = 0
TITLE    = 1
GAMEPLAY = 2
ENDING   = 3
N_SCREENS = 4

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	; --- update phase: jmp [update_tbl + screen*8] ---
	mov	eax, [currentScreen]
	cmp	eax, N_SCREENS
	jae	update_done
	jmp	qword [update_tbl + rax*8]

  update_logo:
	inc	dword [framesCounter]
	cmp	dword [framesCounter], 120
	jle	update_done
	mov	dword [currentScreen], TITLE
	jmp	update_done

  update_title:
	IsKeyPressed		KEY_ENTER
	test	eax, eax
	jnz	.title_advance
	IsGestureDetected	GESTURE_TAP
	test	eax, eax
	jz	update_done
  .title_advance:
	mov	dword [currentScreen], GAMEPLAY
	jmp	update_done

  update_gameplay:
	IsKeyPressed		KEY_ENTER
	test	eax, eax
	jnz	.gameplay_advance
	IsGestureDetected	GESTURE_TAP
	test	eax, eax
	jz	update_done
  .gameplay_advance:
	mov	dword [currentScreen], ENDING
	jmp	update_done

  update_ending:
	IsKeyPressed		KEY_ENTER
	test	eax, eax
	jnz	.ending_advance
	IsGestureDetected	GESTURE_TAP
	test	eax, eax
	jz	update_done
  .ending_advance:
	mov	dword [currentScreen], TITLE

  update_done:

	; --- draw phase: jmp [draw_tbl + screen*8] ---
	BeginDrawing
	ClearBackground		RAYWHITE

	mov	eax, [currentScreen]
	cmp	eax, N_SCREENS
	jae	draw_done
	jmp	qword [draw_tbl + rax*8]

  draw_logo:
	DrawText		_logo_top, 20, 20, 40, LIGHTGRAY
	DrawText		_logo_sub, 290, 220, 20, GRAY
	jmp	draw_done

  draw_title:
	DrawRectangle		0, 0, 800, 450, GREEN
	DrawText		_title_top, 20, 20, 40, DARKGREEN
	DrawText		_title_sub, 120, 220, 20, DARKGREEN
	jmp	draw_done

  draw_gameplay:
	DrawRectangle		0, 0, 800, 450, PURPLE
	DrawText		_play_top, 20, 20, 40, MAROON
	DrawText		_play_sub, 130, 220, 20, MAROON
	jmp	draw_done

  draw_ending:
	DrawRectangle		0, 0, 800, 450, BLUE
	DrawText		_end_top, 20, 20, 40, DARKBLUE
	DrawText		_end_sub, 120, 220, 20, DARKBLUE

  draw_done:
	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title      db 'raylib [core] example - basic screen manager', 0
  _logo_top   db 'LOGO SCREEN', 0
  _logo_sub   db 'WAIT for 2 SECONDS...', 0
  _title_top  db 'TITLE SCREEN', 0
  _title_sub  db 'PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN', 0
  _play_top   db 'GAMEPLAY SCREEN', 0
  _play_sub   db 'PRESS ENTER or TAP to JUMP to ENDING SCREEN', 0
  _end_top    db 'ENDING SCREEN', 0
  _end_sub    db 'PRESS ENTER or TAP to RETURN to TITLE SCREEN', 0

  currentScreen dd LOGO
  framesCounter dd 0

  update_tbl dq update_logo, update_title, update_gameplay, update_ending
  draw_tbl   dq draw_logo,   draw_title,   draw_gameplay,   draw_ending

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
