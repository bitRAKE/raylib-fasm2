; raylib-games classics: floppy, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 450
MAX_TUBES = 100
FLOPPY_RADIUS = 24
TUBE_WIDTH = 80
TUBE_HEIGHT = 255
TUBE_BOTTOM_BASE = 600-TUBE_HEIGHT
BIRD_X = 80
FLOPPY_HIT_RADIUS = FLOPPY_RADIUS-3

struct TUBE
	X dd ?
	Y dd ?
	Active db ?
	rb 3
ends

section '.data' data readable writeable

GLOBSTR.here ; constant string payload

	align 4
gameOver db FALSE
pauseFlag db FALSE
gameStarted db FALSE
superFx db FALSE
birdY dd SCREEN_HEIGHT/2-FLOPPY_RADIUS
tubeSpeed dd 2
score dd 0
hiScore dd 0
tubeBottomY dd 0

tubes TUBE
	rb sizeof.TUBE*(MAX_TUBES-1)

section '.text' code readable executable
include 'common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: floppy'
	fastcall InitGame
	SetTargetFPS 60
.frame:
	WindowShouldClose
	test al,al
	jnz .close

	fastcall UpdateDrawFrame
	jmp .frame
.close:
	fastcall UnloadGame
	CloseWindow
	invoke ExitProcess,0
.space := fastcall.frame


proc InitGame uses rbx rsi
	mov byte [gameOver],FALSE
	mov byte [pauseFlag],FALSE
	mov byte [gameStarted],FALSE
	mov byte [superFx],FALSE
	mov dword [birdY],SCREEN_HEIGHT/2-FLOPPY_RADIUS
	mov dword [tubeSpeed],2
	mov dword [score],0
	xor esi,esi
	lea rbx,[tubes]
.init_tubes:
	cmp esi,MAX_TUBES
	jge .done
	mov eax,esi
	imul eax,280
	add eax,400
	mov [rbx+TUBE.X],eax
	GetRandomValue 0,120
	neg eax
	mov [rbx+TUBE.Y],eax
	mov byte [rbx+TUBE.Active],TRUE
	add rbx,sizeof.TUBE
	inc esi
	jmp .init_tubes
.done:
	ret
endp


proc UpdateGame uses rbx rsi
	cmp byte [gameStarted],TRUE
	je .game_started
	GetKeyPressed
	test eax,eax
	jz .done
	mov byte [gameStarted],TRUE
	ret
.game_started:
	IsKeyPressed KEY_R
	test al,al
	jz .no_restart
	fastcall InitGame
	ret
.no_restart:
	IsKeyPressed KEY_P
	test al,al
	jz .pause_done
	xor byte [pauseFlag],1
.pause_done:
	cmp byte [gameOver],FALSE
	jne .done
	cmp byte [pauseFlag],FALSE
	jne .done

	IsKeyDown KEY_SPACE
	test al,al
	jnz .flap
	IsKeyDown KEY_UP
	test al,al
	jz .fall
.flap:
	sub dword [birdY],3
	jmp .move_tubes
.fall:
	add dword [birdY],1
.move_tubes:
	lea rbx,[tubes]
	lea rsi,[tubes+sizeof.TUBE*MAX_TUBES]
.tube_loop:
	cmp rbx,rsi
	jae .done
	mov eax,[tubeSpeed]
	sub [rbx+TUBE.X],eax
	mov eax,[rbx+TUBE.X]
	cmp eax,BIRD_X
	jge .tube_overlap
	cmp byte [rbx+TUBE.Active],TRUE
	jne .tube_overlap
	mov byte [rbx+TUBE.Active],FALSE
	add dword [score],100
	mov byte [superFx],TRUE
	mov eax,[score]
	cmp [hiScore],eax
	jge .tube_overlap
	mov [hiScore],eax
.tube_overlap:
	fastcall CircleRectOverlap, BIRD_X, [birdY], FLOPPY_HIT_RADIUS, [rbx+TUBE.X], [rbx+TUBE.Y], TUBE_WIDTH, TUBE_HEIGHT
	test al,al
	jnz .set_game_over
	mov edx,[rbx+TUBE.Y]
	add edx,TUBE_BOTTOM_BASE
	mov [tubeBottomY],edx
	fastcall CircleRectOverlap, BIRD_X, [birdY], FLOPPY_HIT_RADIUS, [rbx+TUBE.X], [tubeBottomY], TUBE_WIDTH, TUBE_HEIGHT
	test al,al
	jnz .set_game_over
.next:
	add rbx,sizeof.TUBE
	jmp .tube_loop
.set_game_over:
	mov byte [gameOver],TRUE
.done:
	ret
endp


proc DrawGame uses rbx rsi
	BeginDrawing
	ClearBackground RAYWHITE
	cmp byte [gameStarted],TRUE
	je .help_done
	DrawText 'SPACE/UP flap  P pause  R restart', 20, 20, 20, DARKGRAY
.help_done:
	lea rbx,[tubes]
	lea rsi,[tubes+sizeof.TUBE*MAX_TUBES]
.draw_tubes:
	cmp rbx,rsi
	jae .draw_bird
	DrawRectangle [rbx+TUBE.X], [rbx+TUBE.Y], TUBE_WIDTH, TUBE_HEIGHT, GRAY
	mov eax,[rbx+TUBE.Y]
	add eax,TUBE_BOTTOM_BASE
	DrawRectangle [rbx+TUBE.X], eax, TUBE_WIDTH, TUBE_HEIGHT, GRAY
	add rbx,sizeof.TUBE
	jmp .draw_tubes
.draw_bird:
	DrawCircle BIRD_X, [birdY], float dword 24.0, DARKGRAY
	cmp byte [superFx],FALSE
	je .score
	DrawRectangle 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE
	mov byte [superFx],FALSE
.score:
	TextFormat '%04i', [score]
	DrawText rax, 20, 50, 40, GRAY
	TextFormat 'HI-SCORE: %04i', [hiScore]
	DrawText rax, 20, 95, 20, LIGHTGRAY
	cmp byte [gameStarted],TRUE
	je .start_prompt_done
	DrawText 'PRESS ANY KEY TO START', 285, 225, 20, GRAY
.start_prompt_done:
	cmp byte [pauseFlag],FALSE
	je .not_paused
	DrawText 'PAUSED', 360, 210, 20, GRAY
.not_paused:
	cmp byte [gameOver],FALSE
	je .end_draw
	DrawText 'GAME OVER - PRESS R', 285, 210, 20, MAROON
.end_draw:
	EndDrawing
	ret
endp


proc UnloadGame
	ret
endp


proc UpdateDrawFrame
	fastcall UpdateGame
	fastcall DrawGame
	ret
endp


section '.idata' import data readable writeable

library raylib,'raylib.dll', \
	kernel32,'KERNEL32.DLL'

include 'raylib_imports_pe.inc'

import kernel32, \
	ExitProcess,'ExitProcess'
