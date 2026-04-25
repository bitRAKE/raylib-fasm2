
; Minimal raylib-with-fasmg sample: open a window, draw text, close on ESC
;
; Build:
;   fasmg -i "INCLUDE = '../inc'" core_basic_window.asm core_basic_window.exe
; Run:
;   place raylib.dll next to the .exe and double-click

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8			; align stack to 16 bytes for the ABI

	InitWindow		800, 450, _title
	SetTargetFPS		60

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	BeginDrawing
	ClearBackground		RAYWHITE
	DrawText		_msg, 190, 200, 20, LIGHTGRAY
	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title db 'fasmg + raylib', 0
  _msg   db 'Congrats! You created your first fasmg+raylib window', 0

section '.idata' import data readable writeable

  library raylib,'raylib.dll', \
	  kernel32,'KERNEL32.DLL'

  include 'raylib_imports.inc'    ; emits `import raylib, RLAPI.<Func>,…`

  import kernel32, ExitProcess,'ExitProcess'
