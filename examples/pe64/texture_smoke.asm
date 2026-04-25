
; Texture round-trip: generate an Image, upload to a Texture, draw it.
;
; Stresses:
;   - GenImageColor: returns Image (24B) via hidden first-arg pointer
;   - LoadTextureFromImage: takes Image (24B) by value AND returns
;     Texture2D (20B) — both auto-addr
;   - DrawTexture: takes Texture2D (20B) by value
;   - UnloadImage / UnloadTexture: each takes one struct by value

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

	; Image img = GenImageColor(200, 200, BLUE);
	GenImageColor		addr img, 200, 200, BLUE

	; Texture2D tex = LoadTextureFromImage(img);
	LoadTextureFromImage	addr tex, addr img

	; UnloadImage(img);
	UnloadImage		addr img

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	BeginDrawing
	ClearBackground		RAYWHITE
	; DrawTexture(Texture2D, x, y, Color) — Texture is 20B, by-pointer
	DrawTexture		addr tex, 300, 125, WHITE
	DrawText		_msg, 200, 350, 20, DARKGRAY
	EndDrawing
	jmp	game_loop

  shutdown:
	UnloadTexture		addr tex
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title db 'Texture round-trip smoke test', 0
  _msg   db 'blue square = procedural Image -> Texture round trip', 0

  img Image
  tex Texture2D          ; the alias delegator wraps struct?.instantiate

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
