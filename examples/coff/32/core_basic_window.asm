; Minimal MS COFF x86 object-only sample.
;
; Assemble only:
;   set "include=%cd%\include;%include%"
;   %FASM2_PATH%\fasm2.cmd examples\coff\32\core_basic_window.asm build\core_basic_window32.obj
;
; Prefer response-file sources with _build_link.cmd for full
; assemble-and-link flows.

include 'raylib_coff32.inc'

section '.text' code readable executable align 16

public main as '_main'
main:
	InitWindow 800, 450, title
	SetTargetFPS 60

main_loop:
	WindowShouldClose
	test al,al
	jnz close_window

	BeginDrawing
	ClearBackground RAYWHITE
	DrawText message, 190, 200, 20, LIGHTGRAY
	EndDrawing
	jmp main_loop

close_window:
	CloseWindow
	xor eax,eax
	ret

section '.data' data readable writeable align 1

title db 'fasmg raylib MS COFF x86',0
message db 'MS COFF x86: linked with raylib.lib',0
