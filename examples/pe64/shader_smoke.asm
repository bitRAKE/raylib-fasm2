
; Shader API smoke test
;
; Stresses:
;   - LoadShader: returns Shader (16B) via hidden dest, two char* args
;     (NULL allowed -> raylib uses the default vertex/fragment shader)
;   - GetShaderLocation(Shader, char*): Shader by-value (16B addr)
;   - SetShaderValue(Shader, locIndex, void*, uniformType): typed
;     enum arg ShaderUniformDataType
;   - BeginShaderMode/EndShaderMode/IsShaderValid/UnloadShader (Shader addr)

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	SetTargetFPS		60

	; Shader shader = LoadShader(NULL, NULL);  -> uses default shader
	LoadShader		addr shader, 0, 0

	; int loc = GetShaderLocation(shader, "tint");
	GetShaderLocation	addr shader, _uniform_name
	mov	[tintLoc], eax

	; tintColor = (1.0, 1.0, 1.0, 1.0) — Vector4 fields are x/y/z/w
	; establish initial data w/o code

	; SetShaderValue(shader, tintLoc, &tintColor, SHADER_UNIFORM_VEC4)
	; -- typed enum arg fires `transform` against ShaderUniformDataType
	SetShaderValue		addr shader, [tintLoc], addr tintColor, SHADER_UNIFORM_VEC4

	; IsShaderValid(shader)
	IsShaderValid		addr shader
	mov	[isValid], eax

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	BeginDrawing
	ClearBackground		RAYWHITE

	BeginShaderMode		addr shader
	DrawRectangle		200, 100, 400, 250, BLUE
	EndShaderMode

	DrawText		_msg, 10, 10, 20, DARKGRAY

	; show the resolved location index next to the message
	cmp	dword [isValid], 0
	je	.invalid
	DrawText		_valid, 10, 40, 20, DARKGREEN
	jmp	.shown
  .invalid:
	DrawText		_invalid, 10, 40, 20, MAROON
  .shown:

	EndDrawing
	jmp	game_loop

  shutdown:
	UnloadShader		addr shader
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  tintColor Vector4 1.0,1.0,1.0,1.0

  _title         db 'Shader API smoke test', 0
  _msg           db 'default shader + SHADER_UNIFORM_VEC4 transform path', 0
  _valid         db 'IsShaderValid -> true', 0
  _invalid       db 'IsShaderValid -> false', 0
  _uniform_name  db 'tint', 0

  shader    Shader
  tintLoc   dd ?
  isValid   dd ?


section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
