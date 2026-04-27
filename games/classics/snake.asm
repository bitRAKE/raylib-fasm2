; raylib-games classics: snake, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 450
SNAKE_LENGTH = 256
SQUARE_SIZE = 20
MOVE_TICKS = 7

struct SNAKE_SEGMENT
	X dd ?
	Y dd ?
ends


section '.data' data readable writeable

GLOBSTR.here ; constant string payload

	align 4
gameOver db FALSE
pauseFlag db FALSE
gameStarted db FALSE
framesCounter dd 0
score dd 0
snakeLength dd 4
dirX dd SQUARE_SIZE
dirY dd 0
foodX dd 400
foodY dd 220

snake SNAKE_SEGMENT
	rb sizeof.SNAKE_SEGMENT*(SNAKE_LENGTH-1)


section '.text' code readable executable

include 'common.inc'

fastcall.frame = 0 ; setting fastcall.frame to non-negative value makes fastcall/invoke use it to track maximum necessary stack space (aligned to a multiple of 16 bytes), and not allocate it automatically.

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: snake'
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


proc InitGame
	mov byte [gameOver],FALSE
	mov byte [pauseFlag],FALSE
	mov byte [gameStarted],FALSE
	mov dword [framesCounter],0
	mov dword [score],0
	mov dword [snakeLength],4
	mov dword [dirX],SQUARE_SIZE
	mov dword [dirY],0

	mov dword [snake.X],200
	mov dword [snake.Y],220
	mov dword [snake+1*sizeof.SNAKE_SEGMENT+SNAKE_SEGMENT.X],180
	mov dword [snake+1*sizeof.SNAKE_SEGMENT+SNAKE_SEGMENT.Y],220
	mov dword [snake+2*sizeof.SNAKE_SEGMENT+SNAKE_SEGMENT.X],160
	mov dword [snake+2*sizeof.SNAKE_SEGMENT+SNAKE_SEGMENT.Y],220
	mov dword [snake+3*sizeof.SNAKE_SEGMENT+SNAKE_SEGMENT.X],140
	mov dword [snake+3*sizeof.SNAKE_SEGMENT+SNAKE_SEGMENT.Y],220

	fastcall PlaceFood
	ret
endp


proc PlaceFood
	GetRandomValue 1,38
	imul eax,SQUARE_SIZE
	mov [foodX],eax
	GetRandomValue 1,20
	imul eax,SQUARE_SIZE
	mov [foodY],eax
	ret
endp


proc UpdateGame uses rbx
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

	IsKeyPressed KEY_RIGHT
	test al,al
	jz .try_left
	cmp dword [dirX],-SQUARE_SIZE
	je .try_left
	mov dword [dirX],SQUARE_SIZE
	mov dword [dirY],0
.try_left:
	IsKeyPressed KEY_LEFT
	test al,al
	jz .try_up
	cmp dword [dirX],SQUARE_SIZE
	je .try_up
	mov dword [dirX],-SQUARE_SIZE
	mov dword [dirY],0
.try_up:
	IsKeyPressed KEY_UP
	test al,al
	jz .try_down
	cmp dword [dirY],SQUARE_SIZE
	je .try_down
	mov dword [dirX],0
	mov dword [dirY],-SQUARE_SIZE
.try_down:
	IsKeyPressed KEY_DOWN
	test al,al
	jz .keys_done
	cmp dword [dirY],-SQUARE_SIZE
	je .keys_done
	mov dword [dirX],0
	mov dword [dirY],SQUARE_SIZE
.keys_done:

	inc dword [framesCounter]
	cmp dword [framesCounter],MOVE_TICKS
	jl .done
	mov dword [framesCounter],0

	mov ebx,[snakeLength]
	dec ebx
.tail_loop:
	cmp ebx,0
	jle .tail_done
	mov eax,ebx
	imul eax,sizeof.SNAKE_SEGMENT
	lea rdx,[snake+rax]
	mov eax,[rdx-sizeof.SNAKE_SEGMENT+SNAKE_SEGMENT.X]
	mov [rdx+SNAKE_SEGMENT.X],eax
	mov eax,[rdx-sizeof.SNAKE_SEGMENT+SNAKE_SEGMENT.Y]
	mov [rdx+SNAKE_SEGMENT.Y],eax
	dec ebx
	jmp .tail_loop
.tail_done:

	mov eax,[dirX]
	add [snake.X],eax
	mov eax,[dirY]
	add [snake.Y],eax

	mov eax,[snake.X]
	cmp eax,0
	jl .set_game_over
	cmp eax,SCREEN_WIDTH-SQUARE_SIZE
	jg .set_game_over
	mov eax,[snake.Y]
	cmp eax,0
	jl .set_game_over
	cmp eax,SCREEN_HEIGHT-SQUARE_SIZE
	jg .set_game_over

	mov ebx,1
	lea rdx,[snake+sizeof.SNAKE_SEGMENT]
.self_loop:
	cmp ebx,[snakeLength]
	jge .self_done
	mov eax,[snake.X]
	cmp eax,[rdx+SNAKE_SEGMENT.X]
	jne .self_next
	mov eax,[snake.Y]
	cmp eax,[rdx+SNAKE_SEGMENT.Y]
	je .set_game_over
.self_next:
	add rdx,sizeof.SNAKE_SEGMENT
	inc ebx
	jmp .self_loop
.self_done:
	mov eax,[snake.X]
	cmp eax,[foodX]
	jne .done
	mov eax,[snake.Y]
	cmp eax,[foodY]
	jne .done
	cmp dword [snakeLength],SNAKE_LENGTH
	jge .skip_grow
	mov ebx,[snakeLength]
	mov eax,ebx
	imul eax,sizeof.SNAKE_SEGMENT
	lea rdx,[snake+rax]
	mov eax,[rdx-sizeof.SNAKE_SEGMENT+SNAKE_SEGMENT.X]
	mov [rdx+SNAKE_SEGMENT.X],eax
	mov eax,[rdx-sizeof.SNAKE_SEGMENT+SNAKE_SEGMENT.Y]
	mov [rdx+SNAKE_SEGMENT.Y],eax
	inc dword [snakeLength]
.skip_grow:
	inc dword [score]
	fastcall PlaceFood
	jmp .done

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
	DrawText 'ARROWS move  P pause  R restart', 20, 20, 20, DARKGRAY
.help_done:

	DrawRectangle [foodX], [foodY], SQUARE_SIZE-2, SQUARE_SIZE-2, MAROON

	xor ebx,ebx
	lea rsi,[snake]
.draw_snake:
	cmp ebx,[snakeLength]
	jge .draw_done
	cmp ebx,0
	jne .body
	DrawRectangle [rsi+SNAKE_SEGMENT.X], [rsi+SNAKE_SEGMENT.Y], SQUARE_SIZE-2, SQUARE_SIZE-2, DARKGREEN
	jmp .next
.body:
	DrawRectangle [rsi+SNAKE_SEGMENT.X], [rsi+SNAKE_SEGMENT.Y], SQUARE_SIZE-2, SQUARE_SIZE-2, GREEN
.next:
	add rsi,sizeof.SNAKE_SEGMENT
	inc ebx
	jmp .draw_snake
.draw_done:
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

library raylib,'raylib.dll',\
	kernel32,'KERNEL32.DLL'

include 'raylib_imports_pe.inc'

import kernel32,\
	ExitProcess,'ExitProcess'
