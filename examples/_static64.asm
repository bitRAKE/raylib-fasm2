; MS COFF x64 response-file build. This source emits the object and the linker
; response file consumed by ..\_build_link.cmd.
;
; Run from an x64 MSVC developer shell:
;   _build_link.cmd examples\_static64.asm

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
message db 'same raylib calls, selected backend',0


; We configure the linker from here by generating a response file:
;===============================================================================
virtual as "response"
	db '/NOLOGO',10 ; don't show linker version header

; Use to debug build process:
;	db '/VERBOSE',10
;	db '/TIME+',10

; Create unique binary using image version and checksum:
	db '/RELEASE',10 ; set program checksum in header
	repeat 1,T:__TIME__ shr 16,t:__TIME__ and 0xFFFF
		db '/VERSION:',`T,'.',`t,10
	end repeat

; Use default expected entry-point:
	db '/ENTRY:WinMain',10
	db '/SUBSYSTEM:WINDOWS,6.02',10
	db '/NOCOFFGRPINFO',10	; no debug info, undocumented
;	db '/MERGE:.rdata=.text',10 ; reduce executable size

; Unless /OUT: is used, the linker policy creates a default name:
;	lld-link.exe:	first binary
;	MS link.exe:	first object file

	__BASE__ = __SOURCE__ bswap lengthof __SOURCE__
	while '.' <> __BASE__ and 0xFF
		__BASE__ = __BASE__ shr 8
	end while
	__BASE__ = __BASE__ bswap lengthof __BASE__
	db __BASE__,'obj',10

; Select type of build:
;	db 'Win32\Release.DLL\raylib.lib',10
;	db 'x64\Release.DLL\raylib.lib',10
;	db 'Win32\Release\raylib.lib',10
;	db 'x64\Release\raylib.lib',10 ; static 64-bit

	db 'x64\Release.LLVM.Size\raylib.lib',10 ; static 64-bit

; Dynamic dependencies:
	db 'kernel32.lib',10
	db 'user32.lib',10
	db 'gdi32.lib',10
	db 'shell32.lib',10
	db 'winmm.lib',10

; Additional static dependencies:
	db 'msvcrt.lib',10 ; requires WinMain entry-point, security checks
	db 'vcruntime.lib',10
	db 'ucrt.lib',10
	db 'opengl32.lib',10

end virtual





