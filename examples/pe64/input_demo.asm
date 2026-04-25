
; Simple input demo:
;   - opens a window, blue if SPACE held, red on ESC, gray otherwise.
;   - exercises the typed-arg `transform` machinery for KeyboardKey + ConfigFlags.
;
; Build:
;   build.cmd input_demo.asm
; Run:
;   .\input_demo.exe   (with raylib.dll alongside)

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	SetConfigFlags		FLAG_WINDOW_RESIZABLE or FLAG_VSYNC_HINT
	InitWindow		640, 400, _title

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	IsKeyDown		KEY_ESCAPE
	test	eax, eax
	jz	.not_esc
	mov	dword [bg_color], RED
	jmp	.draw

  .not_esc:
	IsKeyDown		KEY_SPACE
	test	eax, eax
	jz	.not_space
	mov	dword [bg_color], BLUE
	jmp	.draw

  .not_space:
	mov	dword [bg_color], DARKGRAY

  .draw:
	BeginDrawing
	ClearBackground		[bg_color]
	DrawText		_msg, 20, 20, 24, RAYWHITE
	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title  db 'Hold SPACE for blue, ESC quits', 0
  _msg    db 'fasmg + raylib: input demo', 0
  bg_color dd ?

section '.idata' import data readable writeable

  library raylib,'raylib.dll', \
	  kernel32,'KERNEL32.DLL'

  include 'raylib_imports.inc'

  import kernel32, ExitProcess,'ExitProcess'
