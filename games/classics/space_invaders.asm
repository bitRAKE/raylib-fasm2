; raylib-games classics: space_invaders, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 450
PLAYER_W = 20
PLAYER_H = 20
ENEMY_W = 10
ENEMY_H = 10
SHOOT_W = 10
SHOOT_H = 5
NUM_SHOOTS = 50
NUM_MAX_ENEMIES = 50
FIRST_WAVE = 10
SECOND_WAVE = 20
THIRD_WAVE = 50
FIRST = 0
SECOND = 1
THIRD = 2

struct ENEMY
	X dd ?
	Y dd ?
	Active db ?
	rb 3
ends

struct SHOT
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
victory db FALSE
smooth db FALSE
playerX dd 20
playerY dd 50
shootRate dd 0
wave dd FIRST
activeEnemies dd FIRST_WAVE
enemiesKill dd 0
score dd 0
alpha dd 0.0
alphaStep dd 0.02
alphaOne dd 1.0
alphaZero dd 0.0
waveFadeColor dd ?

enemies ENEMY
	rb sizeof.ENEMY*(NUM_MAX_ENEMIES-1)

shots SHOT
	rb sizeof.SHOT*(NUM_SHOOTS-1)

section '.text' code readable executable

include 'common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: space invaders'
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

proc ResetEnemy uses rbx
	; rbx points at the enemy
	GetRandomValue SCREEN_WIDTH, SCREEN_WIDTH+1000
	mov [rbx+ENEMY.X],eax
	GetRandomValue 0, SCREEN_HEIGHT-ENEMY_H
	mov [rbx+ENEMY.Y],eax
	ret

endp

proc InitGame uses rbx rsi
	mov byte [gameOver],FALSE
	mov byte [pauseFlag],FALSE
	mov byte [gameStarted],FALSE
	mov byte [victory],FALSE
	mov byte [smooth],FALSE
	mov dword [playerX],20
	mov dword [playerY],50
	mov dword [shootRate],0
	mov dword [wave],FIRST
	mov dword [activeEnemies],FIRST_WAVE
	mov dword [enemiesKill],0
	mov dword [score],0
	mov dword [alpha],0.0
	lea rbx,[enemies]
	lea rsi,[enemies+sizeof.ENEMY*NUM_MAX_ENEMIES]
.enemy_loop:
	cmp rbx,rsi
	jae .shoots
	mov byte [rbx+ENEMY.Active],TRUE
	fastcall ResetEnemy
	add rbx,sizeof.ENEMY
	jmp .enemy_loop
.shoots:
	lea rbx,[shots]
	lea rsi,[shots+sizeof.SHOT*NUM_SHOOTS]
.shoot_loop:
	cmp rbx,rsi
	jae .done
	mov byte [rbx+SHOT.Active],FALSE
	add rbx,sizeof.SHOT
	jmp .shoot_loop
.done:
	ret

endp

proc SpawnShoot uses rbx rsi
	lea rbx,[shots]
	lea rsi,[shots+sizeof.SHOT*NUM_SHOOTS]
.loop:
	cmp rbx,rsi
	jae .done
	cmp byte [rbx+SHOT.Active],FALSE
	jne .next
	mov byte [rbx+SHOT.Active],TRUE
	mov eax,[playerX]
	mov [rbx+SHOT.X],eax
	mov eax,[playerY]
	add eax,PLAYER_H/4
	mov [rbx+SHOT.Y],eax
	jmp .done
.next:
	add rbx,sizeof.SHOT
	jmp .loop
.done:
	ret

endp

proc UpdateWave
	cmp byte [smooth],FALSE
	jne .fade_out
	movss xmm0,[alpha]
	addss xmm0,[alphaStep]
	movss [alpha],xmm0
	comiss xmm0,[alphaOne]
	jb .wave_check
	mov byte [smooth],TRUE
	jmp .wave_check
.fade_out:
	movss xmm0,[alpha]
	subss xmm0,[alphaStep]
	maxss xmm0,[alphaZero]
	movss [alpha],xmm0
.wave_check:
	mov eax,[enemiesKill]
	cmp eax,[activeEnemies]
	jne .done
	cmp dword [wave],THIRD
	jne .advance
	mov byte [victory],TRUE
	jmp .done
.advance:
	mov dword [enemiesKill],0
	cmp dword [wave],FIRST
	jne .third
	mov dword [wave],SECOND
	mov dword [activeEnemies],SECOND_WAVE
	mov byte [smooth],FALSE
	mov dword [alpha],0.0
	jmp .done
.third:
	mov dword [wave],THIRD
	mov dword [activeEnemies],THIRD_WAVE
	mov byte [smooth],FALSE
	mov dword [alpha],0.0
.done:
	ret

endp

proc UpdateGame uses rbx rsi rdi r12
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

	fastcall UpdateWave
	cmp byte [victory],FALSE
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
	ClampData playerX, 0, SCREEN_WIDTH-PLAYER_W
	ClampData playerY, 0, SCREEN_HEIGHT-PLAYER_H

	mov eax,[activeEnemies]
	imul eax,sizeof.ENEMY
	lea rsi,[enemies+rax]
	lea rbx,[enemies]
.player_collision:
	cmp rbx,rsi
	jae .enemy_tick
	cmp byte [rbx+ENEMY.Active],FALSE
	je .player_next
	fastcall RectsOverlap, [playerX], [playerY], PLAYER_W, PLAYER_H, [rbx+ENEMY.X], [rbx+ENEMY.Y], ENEMY_W, ENEMY_H
	test eax,eax
	jz .player_next
	mov byte [gameOver],TRUE
	jmp .done
.player_next:
	add rbx,sizeof.ENEMY
	jmp .player_collision

.enemy_tick:
	mov eax,[activeEnemies]
	imul eax,sizeof.ENEMY
	lea rsi,[enemies+rax]
	lea rbx,[enemies]
.enemy_loop:
	cmp rbx,rsi
	jae .shoot_input
	cmp byte [rbx+ENEMY.Active],FALSE
	je .enemy_next
	sub dword [rbx+ENEMY.X],5
	cmp dword [rbx+ENEMY.X],0
	jge .enemy_next
	fastcall ResetEnemy
.enemy_next:
	add rbx,sizeof.ENEMY
	jmp .enemy_loop

.shoot_input:
	IsKeyDown KEY_SPACE
	test al,al
	jz .move_shoots
	add dword [shootRate],5
	cmp dword [shootRate],20
	jl .move_shoots
	mov dword [shootRate],0
	fastcall SpawnShoot

.move_shoots:
	lea rdi,[shots]
	lea rsi,[shots+sizeof.SHOT*NUM_SHOOTS]
.shoot_loop:
	cmp rdi,rsi
	jae .done
	cmp byte [rdi+SHOT.Active],FALSE
	je .shoot_next
	add dword [rdi+SHOT.X],7
	mov eax,[rdi+SHOT.X]
	add eax,SHOOT_W
	cmp eax,SCREEN_WIDTH
	jl .shot_collision
	mov byte [rdi+SHOT.Active],FALSE
	mov dword [shootRate],0
	jmp .shoot_next

.shot_collision:
	mov eax,[activeEnemies]
	imul eax,sizeof.ENEMY
	lea r12,[enemies+rax]
	lea rbx,[enemies]
.shot_enemy_loop:
	cmp rbx,r12
	jae .shoot_next
	cmp byte [rbx+ENEMY.Active],FALSE
	je .shot_enemy_next
	fastcall RectsOverlap, [rdi+SHOT.X], [rdi+SHOT.Y], SHOOT_W, SHOOT_H, [rbx+ENEMY.X], [rbx+ENEMY.Y], ENEMY_W, ENEMY_H
	test eax,eax
	jz .shot_enemy_next
	mov byte [rdi+SHOT.Active],FALSE
	mov dword [shootRate],0
	fastcall ResetEnemy
	inc dword [enemiesKill]
	add dword [score],100
	jmp .shoot_next
.shot_enemy_next:
	add rbx,sizeof.ENEMY
	jmp .shot_enemy_loop
.shoot_next:
	add rdi,sizeof.SHOT
	jmp .shoot_loop
.done:
	ret

endp

proc DrawGame uses rbx rsi
	BeginDrawing
	ClearBackground RAYWHITE
	cmp byte [gameStarted],TRUE
	je .help_done
	DrawText 'ARROWS move  HOLD SPACE shoot  P pause  R restart', 20, 20, 20, DARKGRAY
.help_done:
	TextFormat '%04i', [score]
	DrawText rax, 20, 50, 40, GRAY

	DrawRectangle [playerX], [playerY], PLAYER_W, PLAYER_H, BLACK
	Fade BLACK, float dword [alpha]
	mov [waveFadeColor],eax
	cmp dword [wave],FIRST
	jne .wave_second
	MeasureText 'FIRST WAVE', 40
	sar eax,1
	mov ecx,SCREEN_WIDTH/2
	sub ecx,eax
	DrawText 'FIRST WAVE', ecx, SCREEN_HEIGHT/2-40, 40, [waveFadeColor]
	jmp .draw_enemies_start
.wave_second:
	cmp dword [wave],SECOND
	jne .wave_third
	MeasureText 'SECOND WAVE', 40
	sar eax,1
	mov ecx,SCREEN_WIDTH/2
	sub ecx,eax
	DrawText 'SECOND WAVE', ecx, SCREEN_HEIGHT/2-40, 40, [waveFadeColor]
	jmp .draw_enemies_start
.wave_third:
	MeasureText 'THIRD WAVE', 40
	sar eax,1
	mov ecx,SCREEN_WIDTH/2
	sub ecx,eax
	DrawText 'THIRD WAVE', ecx, SCREEN_HEIGHT/2-40, 40, [waveFadeColor]

.draw_enemies_start:
	mov eax,[activeEnemies]
	imul eax,sizeof.ENEMY
	lea rsi,[enemies+rax]
	lea rbx,[enemies]
.draw_enemies:
	cmp rbx,rsi
	jae .draw_shoots_start
	cmp byte [rbx+ENEMY.Active],FALSE
	je .enemy_draw_next
	DrawRectangle [rbx+ENEMY.X], [rbx+ENEMY.Y], ENEMY_W, ENEMY_H, GRAY
.enemy_draw_next:
	add rbx,sizeof.ENEMY
	jmp .draw_enemies

.draw_shoots_start:
	lea rbx,[shots]
	lea rsi,[shots+sizeof.SHOT*NUM_SHOOTS]
.draw_shoots:
	cmp rbx,rsi
	jae .score
	cmp byte [rbx+SHOT.Active],FALSE
	je .shoot_draw_next
	DrawRectangle [rbx+SHOT.X], [rbx+SHOT.Y], SHOOT_W, SHOOT_H, MAROON
.shoot_draw_next:
	add rbx,sizeof.SHOT
	jmp .draw_shoots

.score:
	cmp byte [gameStarted],TRUE
	je .start_prompt_done
	DrawText 'PRESS ANY KEY TO START', 285, 225, 20, GRAY
.start_prompt_done:
	cmp byte [pauseFlag],FALSE
	je .not_paused
	DrawText 'PAUSED', 360, 210, 20, GRAY
.not_paused:
	cmp byte [gameOver],FALSE
	je .victory_msg
	DrawText 'INVADED - PRESS R', 300, 210, 20, MAROON
.victory_msg:
	cmp byte [victory],FALSE
	je .end_draw
	DrawText 'VICTORY - PRESS R', 300, 210, 20, DARKGREEN
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
