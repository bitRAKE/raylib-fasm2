; MS COFF x64 dynamic response-file build with relaxed linker policy.
; This source emits the object and the linker response file consumed by
; ..\_build_link.cmd.
;
; Run from an x64 MSVC developer shell:
;   _build_link.cmd examples\_dynamic64_lax.asm

include 'raylib_coff64.inc'

section '.text' code readable executable align 16

extrn exit
public WinMain as 'WinMain'

; setting fastcall.frame to non-negative value makes fastcall/invoke use it to track maximum necessary
; stack space (aligned to a multiple of 16 bytes), and not allocate it automatically
fastcall.frame = 0

WinMain:
	enter .frame,0

	InitWindow 800, 450, title
	SetTargetFPS 60

.loop:
	WindowShouldClose
	test al,al
	jnz .close_window

	BeginDrawing
	ClearBackground RAYWHITE
	DrawText message, 190, 200, 20, LIGHTGRAY
	EndDrawing
	jmp .loop

.close_window:
	CloseWindow
	fastcall exit, 0

.frame := fastcall.frame ; maximum necessary stack space


section '.data' data readable writeable align 1

title db 'fasmg raylib',0
message db 'COFF x64 dynamic, relaxed linker options',0


; We configure the linker from here by generating a response file:
;===============================================================================
virtual as "response"
	db '/NOLOGO',10 ; don't show linker version header

; Keep the dynamic build ordinary:
; - no /FIXED or custom image base
; - no zero-sized stack/heap reserves
; - no disabled ASLR, CFG, CET, or relocation behavior
; - no /NODEFAULTLIB unless debugging CRT selection

	db '/ENTRY:WinMain',10
	db '/SUBSYSTEM:WINDOWS,6.02',10

; Optional linker diagnostics:
;	db '/VERBOSE',10
;	db '/TIME+',10

; Dynamic Raylib import library. Use the restored MS release by default; switch
; to Release.DLL.LLVM.Size when testing the LLVM distribution DLL.
	db 'x64\Release.DLL\raylib.lib',10
;	db 'x64\Release.DLL.LLVM.Size\raylib.lib',10

; The app calls CRT exit directly. The Raylib DLL carries its own platform
; dependencies, but these are harmless and keep the response easy to adapt
; between static/dynamic experiments.
	db 'kernel32.lib',10
	db 'user32.lib',10
	db 'gdi32.lib',10
	db 'shell32.lib',10
	db 'winmm.lib',10
	db 'msvcrt.lib',10
	db 'vcruntime.lib',10
	db 'ucrt.lib',10
	db 'opengl32.lib',10

; The first object file defines the EXE name, unless /OUT: is used:
; (We process this file's name ...)
	__BASE__ = __SOURCE__ bswap lengthof __SOURCE__
	while '.' <> __BASE__ and 0xFF
		__BASE__ = __BASE__ shr 8
	end while
	__BASE__ = __BASE__ bswap lengthof __BASE__
	db __BASE__,'obj',10
end virtual
