; raylib-games classics: platformer, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

TILE_SIZE = 16
TILE_MAP_WIDTH = 20
TILE_MAP_HEIGHT = 12
TILE_COUNT = TILE_MAP_WIDTH*TILE_MAP_HEIGHT
SCREEN_SCALE = 2
SCREEN_WIDTH = TILE_SIZE*TILE_MAP_WIDTH*SCREEN_SCALE
SCREEN_HEIGHT = TILE_SIZE*TILE_MAP_HEIGHT*SCREEN_SCALE
EMPTY = -1
BLOCK = 0
COINS = 10
PLAYER_W = 8
PLAYER_H = 16
PLAYER_MAX_VX_FP = 400
PLAYER_ACC_FP = 30
PLAYER_DCC_FP = 29
PLAYER_GRAVITY_FP = 93
PLAYER_JUMP_FP = -1680
PLAYER_JUMP_RELEASE_FP = -336
PLAYER_MAX_VY_FP = 1680

section '.data' data readable writeable

GLOBSTR.here ; constant string payload

	align 4

pauseFlag db FALSE
gameStarted db FALSE
winFlag db FALSE
grounded db FALSE
jumping db FALSE
playerX dd TILE_SIZE*TILE_MAP_WIDTH/2
playerY dd TILE_MAP_HEIGHT*TILE_SIZE-16-1
playerXF dd TILE_SIZE*TILE_MAP_WIDTH/2*256
playerYF dd (TILE_MAP_HEIGHT*TILE_SIZE-16-1)*256
velXF dd 0
velYF dd 0
moveDX dd 0
score dd 0
scorePtr dq 0

camera RayLib.Camera2D

tiles db TILE_COUNT dup ?

coinX dd 1*TILE_SIZE+6, 3*TILE_SIZE+6, 4*TILE_SIZE+6, 5*TILE_SIZE+6, 8*TILE_SIZE+6
	dd 9*TILE_SIZE+6, 10*TILE_SIZE+6, 13*TILE_SIZE+6, 14*TILE_SIZE+6, 15*TILE_SIZE+6
coinY dd 7*TILE_SIZE+6, 5*TILE_SIZE+6, 5*TILE_SIZE+6, 5*TILE_SIZE+6, 3*TILE_SIZE+6
	dd 3*TILE_SIZE+6, 3*TILE_SIZE+6, 4*TILE_SIZE+6, 4*TILE_SIZE+6, 4*TILE_SIZE+6
coinActive db COINS dup ?

section '.text' code readable executable

include 'common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	SetConfigFlags FLAG_VSYNC_HINT
	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: platformer'
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

proc MapInit uses rbx rsi
	xor ebx,ebx
.row:
	cmp ebx,TILE_MAP_HEIGHT
	jge .manual
	xor esi,esi
.column:
	cmp esi,TILE_MAP_WIDTH
	jge .next_row
	mov eax,ebx
	imul eax,TILE_MAP_WIDTH
	add eax,esi
	mov byte [tiles+rax],EMPTY
	cmp ebx,0
	je .set_block
	cmp ebx,TILE_MAP_HEIGHT-1
	je .set_block
	cmp esi,0
	je .set_block
	cmp esi,TILE_MAP_WIDTH-1
	jne .next_column
.set_block:
	mov byte [tiles+rax],BLOCK
.next_column:
	inc esi
	jmp .column
.next_row:
	inc ebx
	jmp .row
.manual:
	mov byte [tiles+3+8*TILE_MAP_WIDTH],BLOCK
	mov byte [tiles+4+8*TILE_MAP_WIDTH],BLOCK
	mov byte [tiles+5+8*TILE_MAP_WIDTH],BLOCK
	mov byte [tiles+8+6*TILE_MAP_WIDTH],BLOCK
	mov byte [tiles+9+6*TILE_MAP_WIDTH],BLOCK
	mov byte [tiles+10+6*TILE_MAP_WIDTH],BLOCK
	mov byte [tiles+13+7*TILE_MAP_WIDTH],BLOCK
	mov byte [tiles+14+7*TILE_MAP_WIDTH],BLOCK
	mov byte [tiles+15+7*TILE_MAP_WIDTH],BLOCK
	mov byte [tiles+1+10*TILE_MAP_WIDTH],BLOCK
	ret

endp

proc InitGame uses rbx
	mov byte [pauseFlag],FALSE
	mov byte [gameStarted],FALSE
	mov byte [winFlag],FALSE
	mov byte [grounded],FALSE
	mov byte [jumping],FALSE
	mov dword [playerX],TILE_SIZE*TILE_MAP_WIDTH/2
	mov dword [playerY],TILE_MAP_HEIGHT*TILE_SIZE-16-1
	mov dword [playerXF],TILE_SIZE*TILE_MAP_WIDTH/2*256
	mov dword [playerYF],(TILE_MAP_HEIGHT*TILE_SIZE-16-1)*256
	mov dword [velXF],0
	mov dword [velYF],0
	mov dword [moveDX],0
	mov dword [score],0
	mov dword [camera.offset+RayLib.Vector2.x],0.0
	mov dword [camera.offset+RayLib.Vector2.y],0.0
	mov dword [camera.target+RayLib.Vector2.x],0.0
	mov dword [camera.target+RayLib.Vector2.y],0.0
	mov dword [camera.rotation],0.0
	mov dword [camera.zoom],2.0
	fastcall MapInit
	xor ebx,ebx
.coins:
	cmp ebx,COINS
	jge .done
	mov byte [coinActive+rbx],TRUE
	inc ebx
	jmp .coins
.done:
	ret

endp

proc MapSolidAt x,y
	cmp ecx,0
	jl .solid
	cmp edx,0
	jl .solid
	cmp ecx,TILE_MAP_WIDTH*TILE_SIZE
	jge .solid
	cmp edx,TILE_MAP_HEIGHT*TILE_SIZE
	jge .solid
	mov eax,edx
	sar eax,4
	imul eax,TILE_MAP_WIDTH
	mov r8d,ecx
	sar r8d,4
	add eax,r8d
	cmp byte [tiles+rax],EMPTY
	jne .solid
	xor eax,eax
	ret
.solid:
	mov eax,TRUE
	ret

endp

proc PlayerCollides uses rbx rsi
	; ecx = player bottom-center x, edx = player bottom-center y.
	mov ebx,ecx
	mov esi,edx

	mov ecx,ebx
	sub ecx,PLAYER_W/2
	mov edx,esi
	sub edx,PLAYER_H-1
	fastcall MapSolidAt, ecx, edx
	test al,al
	jnz .hit

	mov ecx,ebx
	add ecx,PLAYER_W/2-1
	mov edx,esi
	sub edx,PLAYER_H-1
	fastcall MapSolidAt, ecx, edx
	test al,al
	jnz .hit

	mov ecx,ebx
	sub ecx,PLAYER_W/2
	mov edx,esi
	fastcall MapSolidAt, ecx, edx
	test al,al
	jnz .hit

	mov ecx,ebx
	add ecx,PLAYER_W/2-1
	mov edx,esi
	fastcall MapSolidAt, ecx, edx
	test al,al
	jnz .hit

	xor eax,eax
	ret
.hit:
	mov eax,TRUE
	ret

endp

proc UpdateGame uses rbx rsi rdi
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
	cmp byte [pauseFlag],FALSE
	jne .done
	cmp byte [winFlag],FALSE
	jne .done

	mov byte [grounded],FALSE
	mov edi,[playerY]
	inc edi
	fastcall PlayerCollides, [playerX], edi
	test al,al
	jz .ground_check_done
	mov byte [grounded],TRUE
.ground_check_done:

	mov dword [moveDX],0
	IsKeyDown KEY_RIGHT
	test al,al
	jnz .move_right
	IsKeyDown KEY_D
	test al,al
	jz .left
.move_right:
	inc dword [moveDX]
.left:
	IsKeyDown KEY_LEFT
	test al,al
	jnz .move_left
	IsKeyDown KEY_A
	test al,al
	jz .move_calc
.move_left:
	dec dword [moveDX]
.move_calc:
	cmp dword [moveDX],0
	je .decelerate
	mov eax,[moveDX]
	imul eax,PLAYER_ACC_FP
	add [velXF],eax
	ClampData velXF, -PLAYER_MAX_VX_FP, PLAYER_MAX_VX_FP
	jmp .jump_press
.decelerate:
	cmp dword [velXF],0
	jg .decel_positive
	jl .decel_negative
	jmp .jump_press
.decel_positive:
	sub dword [velXF],PLAYER_DCC_FP
	cmp dword [velXF],0
	jge .jump_press
	mov dword [velXF],0
	jmp .jump_press
.decel_negative:
	add dword [velXF],PLAYER_DCC_FP
	cmp dword [velXF],0
	jle .jump_press
	mov dword [velXF],0

.jump_press:
	xor edi,edi
	IsKeyPressed KEY_SPACE
	test al,al
	jnz .jump_pressed
	IsKeyPressed KEY_UP
	test al,al
	jnz .jump_pressed
	IsKeyPressed KEY_W
	test al,al
	jz .jump_press_done
.jump_pressed:
	inc edi
.jump_press_done:
	cmp byte [grounded],TRUE
	jne .jump_release
	test edi,edi
	jz .jump_release
	mov dword [velYF],PLAYER_JUMP_FP
	mov byte [jumping],TRUE
	mov byte [grounded],FALSE

.jump_release:
	xor edi,edi
	IsKeyDown KEY_SPACE
	test al,al
	jnz .jump_held
	IsKeyDown KEY_UP
	test al,al
	jnz .jump_held
	IsKeyDown KEY_W
	test al,al
	jz .jump_held_done
.jump_held:
	inc edi
.jump_held_done:
	cmp byte [jumping],TRUE
	jne .gravity
	test edi,edi
	jnz .gravity
	cmp dword [velYF],PLAYER_JUMP_RELEASE_FP
	jge .gravity
	mov dword [velYF],PLAYER_JUMP_RELEASE_FP
	mov byte [jumping],FALSE

.gravity:
	add dword [velYF],PLAYER_GRAVITY_FP
	cmp dword [velYF],PLAYER_MAX_VY_FP
	jle .move_x_prepare
	mov dword [velYF],PLAYER_MAX_VY_FP

.move_x_prepare:
	mov eax,[velXF]
	add [playerXF],eax
	mov edi,[playerXF]
	sar edi,8
	sub edi,[playerX]
	test edi,edi
	jz .move_y_prepare
	mov esi,1
	cmp edi,0
	jge .step_x_count
	neg edi
	mov esi,-1
.step_x_count:
	mov ebx,edi
.step_x:
	cmp ebx,0
	je .move_y_prepare
	mov edi,[playerX]
	add edi,esi
	fastcall PlayerCollides, edi, [playerY]
	test al,al
	jz .move_x
	mov dword [velXF],0
	mov eax,[playerX]
	shl eax,8
	mov [playerXF],eax
	jmp .move_y_prepare
.move_x:
	mov [playerX],edi
	dec ebx
	jmp .step_x

.move_y_prepare:
	mov eax,[velYF]
	add [playerYF],eax
	mov edi,[playerYF]
	sar edi,8
	sub edi,[playerY]
	test edi,edi
	jz .coin_check
	mov byte [grounded],FALSE
	mov esi,1
	cmp edi,0
	jge .step_y_count
	neg edi
	mov esi,-1
.step_y_count:
	mov ebx,edi
.step_y:
	cmp ebx,0
	je .coin_check
	mov edi,[playerY]
	add edi,esi
	fastcall PlayerCollides, [playerX], edi
	test al,al
	jz .move_y
	mov dword [velYF],0
	mov eax,[playerY]
	shl eax,8
	mov [playerYF],eax
	cmp esi,0
	jle .coin_check
	mov byte [grounded],TRUE
	mov byte [jumping],FALSE
	jmp .coin_check
.move_y:
	mov [playerY],edi
	dec ebx
	jmp .step_y

.coin_check:
	xor ebx,ebx
.coin_loop:
	cmp ebx,COINS
	jge .win_check
	cmp byte [coinActive+rbx],FALSE
	je .coin_next
	mov ecx,[playerX]
	sub ecx,PLAYER_W/2
	mov edx,[playerY]
	sub edx,PLAYER_H-1
	fastcall RectsOverlap, ecx, edx, PLAYER_W, PLAYER_H, [coinX+rbx*4], [coinY+rbx*4], 4, 4
	test al,al
	jz .coin_next
	mov byte [coinActive+rbx],FALSE
	inc dword [score]
.coin_next:
	inc ebx
	jmp .coin_loop
.win_check:
	cmp dword [score],COINS
	jne .done
	mov byte [winFlag],TRUE
.done:
	ret

endp

proc DrawMap uses rbx
	xor ebx,ebx
.loop:
	cmp ebx,TILE_COUNT
	jge .done
	cmp byte [tiles+rbx],EMPTY
	je .next
	mov eax,ebx
	xor edx,edx
	mov ecx,TILE_MAP_WIDTH
	div ecx
	; eax = row, edx = column
	mov r8d,edx
	imul r8d,TILE_SIZE
	mov r9d,eax
	imul r9d,TILE_SIZE
	DrawRectangle r8d, r9d, TILE_SIZE, TILE_SIZE, GRAY
.next:
	inc ebx
	jmp .loop
.done:
	ret

endp

proc DrawCoins uses rbx
	xor ebx,ebx
.loop:
	cmp ebx,COINS
	jge .done
	cmp byte [coinActive+rbx],FALSE
	je .next
	DrawRectangle [coinX+rbx*4], [coinY+rbx*4], 4, 4, GOLD
.next:
	inc ebx
	jmp .loop
.done:
	ret

endp

proc DrawPlayer
	mov ecx,[playerX]
	sub ecx,PLAYER_W/2
	mov edx,[playerY]
	sub edx,PLAYER_H-1
	DrawRectangle ecx, edx, PLAYER_W, PLAYER_H, RED
	ret

endp

proc DrawGame
	BeginDrawing
	ClearBackground RAYWHITE

	BeginMode2D addr camera
	fastcall DrawMap
	fastcall DrawCoins
	fastcall DrawPlayer
	EndMode2D

	TextFormat 'SCORE: %i', [score]
	mov [scorePtr],rax
	MeasureText rax, 40
	sar eax,1
	mov ecx,SCREEN_WIDTH/2
	sub ecx,eax
	DrawText [scorePtr], ecx, 50, 40, BLACK

	cmp byte [gameStarted],TRUE
	je .help_done
	DrawText 'A/D or arrows move  SPACE/W/UP jump  P pause  R restart', 20, SCREEN_HEIGHT-28, 18, DARKGRAY
.help_done:

	cmp byte [gameStarted],TRUE
	je .start_prompt_done
	DrawText 'PRESS ANY KEY TO START', 205, 185, 20, GRAY
.start_prompt_done:
	cmp byte [pauseFlag],FALSE
	je .not_paused
	DrawText 'PAUSED', 285, 170, 20, GRAY
.not_paused:
	cmp byte [winFlag],FALSE
	je .end_draw
	DrawText 'ALL COINS - PRESS R', 230, 170, 20, DARKGREEN
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
