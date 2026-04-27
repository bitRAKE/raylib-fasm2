; raylib-games classics: arkanoid, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 450
BRICK_ROWS = 5
BRICKS_PER_LINE = 20
BRICK_COUNT = BRICK_ROWS*BRICKS_PER_LINE
BRICK_W = SCREEN_WIDTH/BRICKS_PER_LINE
BRICK_H = 40
BALL_R = 7
PADDLE_W = SCREEN_WIDTH/10
PADDLE_H = 20
PADDLE_Y = SCREEN_HEIGHT*7/8
PADDLE_TOP = PADDLE_Y-PADDLE_H/2
BALL_HOME_Y = PADDLE_Y-PADDLE_H/2-BALL_R
PLAYER_MAX_LIFE = 5

section '.data' data readable writeable

GLOBSTR.here ; constant string payload

	align 4

gameOver db FALSE
pauseFlag db FALSE
gameStarted db FALSE
victory db FALSE
ballActive db FALSE
paddleX dd SCREEN_WIDTH/2-PADDLE_W/2
ballX dd 400
ballY dd BALL_HOME_Y
ballDX dd 0
ballDY dd 0
bricksLeft dd BRICK_COUNT
playerLife dd PLAYER_MAX_LIFE
bricks db BRICK_COUNT dup ?

section '.text' code readable executable

include 'common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: arkanoid'
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

proc InitGame uses rbx
	mov byte [gameOver],FALSE
	mov byte [pauseFlag],FALSE
	mov byte [gameStarted],FALSE
	mov byte [victory],FALSE
	mov byte [ballActive],FALSE
	mov dword [paddleX],SCREEN_WIDTH/2-PADDLE_W/2
	mov dword [ballX],400
	mov dword [ballY],BALL_HOME_Y
	mov dword [ballDX],0
	mov dword [ballDY],0
	mov dword [bricksLeft],BRICK_COUNT
	mov dword [playerLife],PLAYER_MAX_LIFE
	xor ebx,ebx
.init_bricks:
	cmp ebx,BRICK_COUNT
	jge .done
	mov byte [bricks+rbx],TRUE
	inc ebx
	jmp .init_bricks
.done:
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
	cmp byte [victory],FALSE
	jne .done
	cmp byte [pauseFlag],FALSE
	jne .done

	IsKeyDown KEY_RIGHT
	test al,al
	jz .left
	add dword [paddleX],5
.left:
	IsKeyDown KEY_LEFT
	test al,al
	jz .clamp
	sub dword [paddleX],5
.clamp:
	ClampData paddleX, 0, SCREEN_WIDTH-PADDLE_W

	cmp byte [ballActive],TRUE
	je .move_ball
	mov eax,[paddleX]
	add eax,PADDLE_W/2
	mov [ballX],eax
	mov dword [ballY],BALL_HOME_Y
	IsKeyPressed KEY_SPACE
	test al,al
	jz .win_check
	mov byte [ballActive],TRUE
	mov dword [ballDX],0
	mov dword [ballDY],-5

.move_ball:
	mov eax,[ballDX]
	add [ballX],eax
	mov eax,[ballDY]
	add [ballY],eax

	cmp dword [ballX],BALL_R
	jge .right_wall
	neg dword [ballDX]
	mov dword [ballX],BALL_R
.right_wall:
	cmp dword [ballX],SCREEN_WIDTH-BALL_R
	jle .top_wall
	neg dword [ballDX]
	mov dword [ballX],SCREEN_WIDTH-BALL_R
.top_wall:
	cmp dword [ballY],BALL_R
	jge .bottom_check
	neg dword [ballDY]
	mov dword [ballY],BALL_R
.bottom_check:
	cmp dword [ballY],SCREEN_HEIGHT+BALL_R
	jle .paddle_check
	dec dword [playerLife]
	cmp dword [playerLife],0
	jg .reset_ball
	mov byte [gameOver],TRUE
	jmp .done
.reset_ball:
	mov byte [ballActive],FALSE
	mov dword [ballDX],0
	mov dword [ballDY],0
	jmp .done

.paddle_check:
	cmp dword [ballDY],0
	jle .brick_check
	mov eax,[ballY]
	add eax,BALL_R
	cmp eax,PADDLE_TOP
	jl .brick_check
	mov eax,[ballY]
	sub eax,BALL_R
	cmp eax,PADDLE_TOP+PADDLE_H
	jg .brick_check
	mov eax,[ballX]
	cmp eax,[paddleX]
	jl .brick_check
	mov edx,[paddleX]
	add edx,PADDLE_W
	cmp eax,edx
	jg .brick_check
	neg dword [ballDY]
	mov dword [ballY],BALL_HOME_Y
	mov eax,[ballX]
	mov edx,[paddleX]
	add edx,PADDLE_W/2
	sub eax,edx
	cdq
	mov ecx,8
	idiv ecx
	mov [ballDX],eax

.brick_check:
	xor ebx,ebx
.brick_loop:
	cmp ebx,BRICK_COUNT
	jge .win_check
	cmp byte [bricks+rbx],FALSE
	je .brick_next
	mov eax,ebx
	xor edx,edx
	mov ecx,BRICKS_PER_LINE
	div ecx
	; eax=row, edx=column
	mov r8d,edx
	imul r8d,BRICK_W
	mov r9d,eax
	imul r9d,BRICK_H
	add r9d,30
	mov eax,[ballX]
	cmp eax,r8d
	jl .brick_next
	mov edx,r8d
	add edx,BRICK_W
	cmp eax,edx
	jg .brick_next
	mov eax,[ballY]
	cmp eax,r9d
	jl .brick_next
	mov edx,r9d
	add edx,BRICK_H
	cmp eax,edx
	jg .brick_next
	mov byte [bricks+rbx],FALSE
	dec dword [bricksLeft]
	neg dword [ballDY]
	jmp .win_check
.brick_next:
	inc ebx
	jmp .brick_loop
.win_check:
	cmp dword [bricksLeft],0
	jne .done
	mov byte [victory],TRUE
.done:
	ret

endp

proc DrawGame uses rbx
	BeginDrawing
	ClearBackground RAYWHITE

	xor ebx,ebx
.draw_lives:
	cmp ebx,[playerLife]
	jge .draw_bricks_start
	mov eax,ebx
	imul eax,40
	add eax,20
	DrawRectangle eax, SCREEN_HEIGHT-30, 35, 10, LIGHTGRAY
	inc ebx
	jmp .draw_lives

.draw_bricks_start:
	xor ebx,ebx
.draw_bricks:
	cmp ebx,BRICK_COUNT
	jge .draw_player
	cmp byte [bricks+rbx],FALSE
	je .draw_next
	mov eax,ebx
	xor edx,edx
	mov ecx,BRICKS_PER_LINE
	div ecx
	mov r8d,edx
	imul r8d,BRICK_W
	mov r9d,eax
	imul r9d,BRICK_H
	add r9d,30
	add eax,edx
	test al,1
	jnz .draw_dark_brick
	DrawRectangle r8d, r9d, BRICK_W, BRICK_H, GRAY
	jmp .draw_next
.draw_dark_brick:
	DrawRectangle r8d, r9d, BRICK_W, BRICK_H, DARKGRAY
.draw_next:
	inc ebx
	jmp .draw_bricks

.draw_player:
	cmp byte [gameStarted],TRUE
	je .help_done
	DrawText 'LEFT/RIGHT move  SPACE launch  P pause  R restart', 20, 245, 20, DARKGRAY
.help_done:
	DrawRectangle [paddleX], PADDLE_TOP, PADDLE_W, PADDLE_H, BLACK
	DrawCircle [ballX], [ballY], float dword 7.0, MAROON
	cmp byte [gameStarted],TRUE
	je .start_prompt_done
	DrawText 'PRESS ANY KEY TO START', 285, 225, 20, GRAY
.start_prompt_done:
	cmp byte [pauseFlag],FALSE
	je .not_paused
	DrawText 'PAUSED', 360, 220, 20, GRAY
.not_paused:
	cmp byte [gameOver],FALSE
	je .victory_msg
	DrawText 'BALL LOST - PRESS R', 285, 220, 20, MAROON
.victory_msg:
	cmp byte [victory],FALSE
	je .end_draw
	DrawText 'BOARD CLEAR - PRESS R', 285, 220, 20, DARKGREEN
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
