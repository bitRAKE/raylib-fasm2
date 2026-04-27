; raylib-games classics: gold_fever, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 450
PLAYER_SIZE = 24
ENEMY_SIZE = 28
POINT_SIZE = 16
PLAYER_R = 20
ENEMY_R = 20
POINT_R = 10
HOME_SIZE = 50
CHASE_R = 150

section '.data' data readable writeable

GLOBSTR.here ; constant string payload

	align 4

gameOver db FALSE
pauseFlag db FALSE
gameStarted db FALSE
follow db FALSE
pointActive db TRUE
homeSave db FALSE
enemyMoveRight db TRUE
playerX dd 50
playerY dd 50
enemyX dd 680
enemyY dd 220
enemyStep dd 3
enemyStepBonus db FALSE
pointX dd 400
pointY dd 220
homeX dd 30
homeY dd 195
score dd 0
hiScore dd 0

section '.text' code readable executable

include 'common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: gold fever'
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
	mov dword [playerX],50
	mov dword [playerY],50
	mov dword [enemyX],680
	mov dword [enemyY],220
	mov dword [enemyStep],3
	mov byte [enemyStepBonus],FALSE
	mov dword [score],0
	mov byte [follow],FALSE
	mov byte [pointActive],TRUE
	mov byte [homeSave],FALSE
	mov byte [enemyMoveRight],TRUE
	fastcall PlacePoint
	GetRandomValue 0,SCREEN_WIDTH-HOME_SIZE
	mov [homeX],eax
	GetRandomValue 0,SCREEN_HEIGHT-HOME_SIZE
	mov [homeY],eax
	ret

endp

proc PlacePoint
	GetRandomValue POINT_R,SCREEN_WIDTH-POINT_R
	mov [pointX],eax
	GetRandomValue POINT_R,SCREEN_HEIGHT-POINT_R
	mov [pointY],eax
	ret

endp

proc UpdateGame
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

	IsKeyDown KEY_RIGHT
	test al,al
	jz .left
	add dword [playerX],5
.left:
	IsKeyDown KEY_LEFT
	test al,al
	jz .down
	sub dword [playerX],5
.down:
	IsKeyDown KEY_DOWN
	test al,al
	jz .up
	add dword [playerY],5
.up:
	IsKeyDown KEY_UP
	test al,al
	jz .clamp
	sub dword [playerY],5
.clamp:
	ClampData playerX, PLAYER_R, SCREEN_WIDTH-PLAYER_R
	ClampData playerY, PLAYER_R, SCREEN_HEIGHT-PLAYER_R

	cmp byte [follow],TRUE
	je .enemy_chase
	mov eax,[playerX]
	sub eax,[enemyX]
	cmp eax,-CHASE_R
	jl .enemy_patrol
	cmp eax,CHASE_R
	jg .enemy_patrol
	mov eax,[playerY]
	sub eax,[enemyY]
	cmp eax,-CHASE_R
	jl .enemy_patrol
	cmp eax,CHASE_R
	jg .enemy_patrol
.enemy_chase:
	cmp byte [homeSave],TRUE
	je .enemy_patrol
	mov eax,[playerX]
	cmp [enemyX],eax
	jge .enemy_left
	mov edx,[enemyStep]
	add [enemyX],edx
	jmp .enemy_y
.enemy_left:
	jle .enemy_y
	mov edx,[enemyStep]
	sub [enemyX],edx
.enemy_y:
	mov eax,[playerY]
	cmp [enemyY],eax
	jge .enemy_up
	mov edx,[enemyStep]
	add [enemyY],edx
	jmp .enemy_bounds
.enemy_up:
	jle .enemy_bounds
	mov edx,[enemyStep]
	sub [enemyY],edx
	jmp .enemy_bounds

.enemy_patrol:
	cmp byte [enemyMoveRight],TRUE
	jne .patrol_left
	mov eax,[enemyStep]
	add [enemyX],eax
	jmp .enemy_bounds
.patrol_left:
	mov eax,[enemyStep]
	sub [enemyX],eax

.enemy_bounds:
	cmp dword [enemyX],ENEMY_R
	jg .enemy_right_bound
	mov dword [enemyX],ENEMY_R
	mov byte [enemyMoveRight],TRUE
.enemy_right_bound:
	cmp dword [enemyX],SCREEN_WIDTH-ENEMY_R
	jl .enemy_top_bound
	mov dword [enemyX],SCREEN_WIDTH-ENEMY_R
	mov byte [enemyMoveRight],FALSE
.enemy_top_bound:
	ClampData enemyY, ENEMY_R, SCREEN_HEIGHT-ENEMY_R

.collision:
	cmp byte [homeSave],TRUE
	je .point_check
	mov eax,[playerX]
	sub eax,[enemyX]
	cmp eax,-32
	jl .point_check
	cmp eax,32
	jg .point_check
	mov eax,[playerY]
	sub eax,[enemyY]
	cmp eax,-32
	jl .point_check
	cmp eax,32
	jg .point_check
	mov byte [gameOver],TRUE
	mov eax,[score]
	cmp [hiScore],eax
	jge .done
	mov [hiScore],eax
	jmp .done

.point_check:
	cmp byte [pointActive],TRUE
	jne .home_check
	mov eax,[playerX]
	sub eax,[pointX]
	cmp eax,-30
	jl .home_check
	cmp eax,30
	jg .home_check
	mov eax,[playerY]
	sub eax,[pointY]
	cmp eax,-30
	jl .home_check
	cmp eax,30
	jg .home_check
	mov byte [follow],TRUE
	mov byte [pointActive],FALSE

.home_check:
	mov byte [homeSave],FALSE
	mov eax,[playerX]
	cmp eax,[homeX]
	jl .done
	mov edx,[homeX]
	add edx,HOME_SIZE
	cmp eax,edx
	jg .done
	mov eax,[playerY]
	cmp eax,[homeY]
	jl .done
	mov edx,[homeY]
	add edx,HOME_SIZE
	cmp eax,edx
	jg .done
	mov byte [homeSave],TRUE
	mov byte [follow],FALSE
	cmp byte [pointActive],TRUE
	je .done
	add dword [score],100
	mov byte [pointActive],TRUE
	xor byte [enemyStepBonus],1
	cmp byte [enemyStepBonus],FALSE
	jne .point_again
	inc dword [enemyStep]
.point_again:
	fastcall PlacePoint
.done:
	ret

endp

proc DrawGame
	BeginDrawing
	ClearBackground RAYWHITE
	cmp byte [follow],FALSE
	je .no_follow_flash
	DrawRectangle 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RED
	DrawRectangle 10, 10, SCREEN_WIDTH-20, SCREEN_HEIGHT-20, RAYWHITE
.no_follow_flash:
	cmp byte [gameStarted],TRUE
	je .help_done
	DrawText 'ARROWS collect gold  P pause  R restart', 20, 20, 20, DARKGRAY
.help_done:
	DrawRectangleLines [homeX], [homeY], HOME_SIZE, HOME_SIZE, BLUE
	DrawCircleLines [enemyX], [enemyY], float dword 150.0, RED
	DrawCircle [enemyX], [enemyY], float dword 20.0, MAROON
	DrawCircle [playerX], [playerY], float dword 20.0, GRAY
	cmp byte [pointActive],FALSE
	je .skip_point
	DrawCircle [pointX], [pointY], float dword 10.0, GOLD
.skip_point:
	TextFormat 'SCORE: %04i', [score]
	DrawText rax, 20, 50, 20, GRAY
	TextFormat 'HI-SCORE: %04i', [hiScore]
	DrawText rax, 300, 50, 20, GRAY
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
	DrawText 'CAUGHT - PRESS R', 300, 210, 20, MAROON
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
