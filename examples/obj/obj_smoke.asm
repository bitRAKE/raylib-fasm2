
; OBJ-mode sample: assembles to a COFF object that link.exe resolves
; against either the raylib import library (bin64\raylib.lib + raylib.dll
; alongside the EXE) or the fully-static library (lib64\raylib.lib —
; pulls in opengl/glfw/stdlib).
;
; The entry symbol is `main` (not `start`) so MSVC's `mainCRTStartup`
; brings up the C runtime before raylib gets any chance to call malloc /
; strstr / printf — without that init, raylib.lib's stubs segfault.
;
; Build (assemble + link via build_obj.cmd which sets VS env):
;   build_obj.cmd obj_smoke.asm dll       -> link against bin64\raylib.lib
;   build_obj.cmd obj_smoke.asm static    -> link against lib64\raylib.lib

format MS64 COFF

define RAYLIB_MODE_OBJ                  ; toggle BEFORE include
include 'raylib.inc'

include 'raylib_extrn.inc'

section '.text' code readable executable align 16

  public main as 'main'
  main:                                 ; int main(int argc, char **argv)
	sub	rsp, 8                  ; align stack for ABI

	SetTargetFPS		60
	InitWindow		800, 450, _title

  frame_loop:
	WindowShouldClose
	test	eax, eax
	jnz	done

	BeginDrawing
	ClearBackground		RAYWHITE
	DrawText		_msg, 200, 200, 24, DARKGRAY
	EndDrawing

	jmp	frame_loop

  done:
	CloseWindow
	xor	eax, eax                ; return 0
	add	rsp, 8
	ret

section '.rdata' data readable align 1

  _title db 'fasmg + raylib (OBJ mode)', 0
  _msg   db 'linked from .obj!', 0
