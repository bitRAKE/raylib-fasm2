
; Text/font smoke test
;
; Stresses:
;   - GetFontDefault: returns Font (48B) via hidden dest
;   - DrawTextEx: 6 args including Font (48B auto-addr), Vector2 (8B
;     in-register), 2 floats, Color, plus a pointer
;   - Mixed reg-class routing (4 args go to rcx/rdx/r8/r9 + xmms,
;     2 spill to stack)

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

	; font = GetFontDefault();
	GetFontDefault		addr font

	; pos.x = 100.0f, pos.y = 200.0f
	mov	dword [pos.x], 100.0f
	mov	dword [pos.y], 200.0f

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	BeginDrawing
	ClearBackground		RAYWHITE

	; DrawTextEx(font, text, position, fontSize, spacing, tint)
	; - font: Font (48B)  -> `addr font` -> lea rcx, [font]
	; - text: const char* -> the bare label is its address (no addr/[])
	; - position: Vector2 (8B) — fits in r8 as raw bits, dereference
	;   with `[pos]` to get the contents loaded
	DrawTextEx		addr font, _msg, [pos], float dword 30.0, float dword 2.0, MAROON

	EndDrawing
	jmp	game_loop

  shutdown:
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title db 'Text smoke test', 0
  _msg   db 'rendered through GetFontDefault + DrawTextEx', 0

  font Font
  pos  Vector2

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
