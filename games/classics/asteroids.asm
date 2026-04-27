; raylib-games classics: asteroids, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 450
INITIAL_METEORS = 4
MAX_METEORS = 28
MAX_SHOOTS = 10
SPAWN_SAFE_R = 150
BIG_METEOR_R = 40
SMALL_METEOR_R = 10

struct METEOR
	X dd ?
	Y dd ?
	DX dd ?
	DY dd ?
	Radius dd ?
	RadiusF dd ?
	Active db ?
	rb 3
ends

struct SHOOT
	X dd ?
	Y dd ?
	DX dd ?
	DY dd ?
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
playerX dd 400
playerY dd 225
playerXF dd 400.0
playerYF dd 225.0
playerAngle dd 0
playerAccel dd 0
angleRad dd 0.0
sinAngle dd 0.0
cosAngle dd 1.0
meteorsLeft dd INITIAL_METEORS
splitRadius dd 0
splitCount dd 0

meteors METEOR
	rb sizeof.METEOR*(MAX_METEORS-1)

shoots SHOOT
	rb sizeof.SHOOT*(MAX_SHOOTS-1)

shipA RayLib.Vector2 x:0.0, y:0.0
shipB RayLib.Vector2 x:0.0, y:0.0
shipC RayLib.Vector2 x:0.0, y:0.0
shipAX dd 0
shipAY dd 0
shipBX dd 0
shipBY dd 0
shipCX dd 0
shipCY dd 0

degToRad dd 0.01745329252
playerSpeed dd 6.0
shotSpeed dd 9.0
shipHeight dd 27.0
shipBaseHalf dd 10.0
accelScale dd 256.0

section '.text' code readable executable

include 'common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: asteroids'
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

proc InitGame uses rbx rdi
	mov byte [gameOver],FALSE
	mov byte [pauseFlag],FALSE
	mov byte [gameStarted],FALSE
	mov byte [victory],FALSE
	mov dword [playerX],400
	mov dword [playerY],225
	mov dword [playerXF],400.0
	mov dword [playerYF],225.0
	mov dword [playerAngle],0
	mov dword [playerAccel],0
	mov dword [sinAngle],0.0
	mov dword [cosAngle],1.0
	mov dword [meteorsLeft],INITIAL_METEORS
	lea rdi,[meteors]
	xor ebx,ebx
.init_meteors:
	cmp ebx,MAX_METEORS
	jge .clear_shoots
	cmp ebx,INITIAL_METEORS
	jl .active_meteor
	mov byte [rdi+METEOR.Active],FALSE
	add rdi,sizeof.METEOR
	inc ebx
	jmp .init_meteors
.active_meteor:
	mov byte [rdi+METEOR.Active],TRUE
.pick_position:
	GetRandomValue 0,SCREEN_WIDTH
	mov [rdi+METEOR.X],eax
	GetRandomValue 50,SCREEN_HEIGHT
	mov [rdi+METEOR.Y],eax
	mov eax,[rdi+METEOR.X]
	sub eax,[playerX]
	cmp eax,-SPAWN_SAFE_R
	jl .position_ok
	cmp eax,SPAWN_SAFE_R
	jg .position_ok
	mov eax,[rdi+METEOR.Y]
	sub eax,[playerY]
	cmp eax,-SPAWN_SAFE_R
	jl .position_ok
	cmp eax,SPAWN_SAFE_R
	jg .position_ok
	jmp .pick_position
.position_ok:
	GetRandomValue -3,3
	cmp eax,0
	jne .dx_ok
	mov eax,2
.dx_ok:
	mov [rdi+METEOR.DX],eax
	GetRandomValue -3,3
	cmp eax,0
	jne .dy_ok
	mov eax,2
.dy_ok:
	mov [rdi+METEOR.DY],eax
	mov eax,BIG_METEOR_R
	mov [rdi+METEOR.Radius],eax
	cvtsi2ss xmm0,eax
	movss [rdi+METEOR.RadiusF],xmm0
	add rdi,sizeof.METEOR
	inc ebx
	jmp .init_meteors
.clear_shoots:
	lea rdi,[shoots]
	xor ebx,ebx
.shoot_loop:
	cmp ebx,MAX_SHOOTS
	jge .done
	mov byte [rdi+SHOOT.Active],FALSE
	add rdi,sizeof.SHOOT
	inc ebx
	jmp .shoot_loop
.done:
	ret

endp

proc SplitMeteor uses rbx rsi rdi
	; source meteor index is in esi; original has already been deactivated.
	mov eax,esi
	imul eax,sizeof.METEOR
	lea rsi,[meteors+rax]
	mov eax,[rsi+METEOR.Radius]
	cmp eax,SMALL_METEOR_R
	jle .done
	shr eax,1
	mov [splitRadius],eax
	mov dword [splitCount],0
	lea rdi,[meteors]
	xor ebx,ebx
.find_slot:
	cmp dword [splitCount],2
	jge .done
	cmp ebx,MAX_METEORS
	jge .done
	cmp byte [rdi+METEOR.Active],FALSE
	jne .next
	mov byte [rdi+METEOR.Active],TRUE
	mov eax,[rsi+METEOR.X]
	mov [rdi+METEOR.X],eax
	mov eax,[rsi+METEOR.Y]
	mov [rdi+METEOR.Y],eax
	mov eax,[splitRadius]
	mov [rdi+METEOR.Radius],eax
	cvtsi2ss xmm0,eax
	movss [rdi+METEOR.RadiusF],xmm0
	GetRandomValue -3,3
	cmp eax,0
	jne .dx_ok
	mov eax,2
	cmp dword [splitCount],0
	jne .dx_ok
	neg eax
.dx_ok:
	mov [rdi+METEOR.DX],eax
	GetRandomValue -3,3
	cmp eax,0
	jne .dy_ok
	mov eax,2
.dy_ok:
	mov [rdi+METEOR.DY],eax
	inc dword [splitCount]
	inc dword [meteorsLeft]
.next:
	add rdi,sizeof.METEOR
	inc ebx
	jmp .find_slot
.done:
	ret

endp

proc UpdatePlayerTrig
	fild dword [playerAngle]
	fmul dword [degToRad]
	fst dword [angleRad]
	fsin
	fstp dword [sinAngle]
	fld dword [angleRad]
	fcos
	fstp dword [cosAngle]
	ret

endp

proc SyncPlayerInts
	fld dword [playerXF]
	fistp dword [playerX]
	fld dword [playerYF]
	fistp dword [playerY]
	ret

endp

proc MovePlayerByTrig
	fild dword [playerAccel]
	fmul dword [playerSpeed]
	fdiv dword [accelScale]
	fmul dword [sinAngle]
	fadd dword [playerXF]
	fstp dword [playerXF]

	fild dword [playerAccel]
	fmul dword [playerSpeed]
	fdiv dword [accelScale]
	fmul dword [cosAngle]
	fchs
	fadd dword [playerYF]
	fstp dword [playerYF]

	fastcall SyncPlayerInts
	ret

endp

proc BuildShipVectors
	fld dword [sinAngle]
	fmul dword [shipHeight]
	fadd dword [playerXF]
	fstp dword [shipA.x]
	fld dword [cosAngle]
	fmul dword [shipHeight]
	fchs
	fadd dword [playerYF]
	fstp dword [shipA.y]

	fld dword [cosAngle]
	fmul dword [shipBaseHalf]
	fchs
	fadd dword [playerXF]
	fstp dword [shipB.x]
	fld dword [sinAngle]
	fmul dword [shipBaseHalf]
	fchs
	fadd dword [playerYF]
	fstp dword [shipB.y]

	fld dword [cosAngle]
	fmul dword [shipBaseHalf]
	fadd dword [playerXF]
	fstp dword [shipC.x]
	fld dword [sinAngle]
	fmul dword [shipBaseHalf]
	fadd dword [playerYF]
	fstp dword [shipC.y]
	ret

endp

proc SyncShipInts
	fld dword [shipA.x]
	fistp dword [shipAX]
	fld dword [shipA.y]
	fistp dword [shipAY]
	fld dword [shipB.x]
	fistp dword [shipBX]
	fld dword [shipB.y]
	fistp dword [shipBY]
	fld dword [shipC.x]
	fistp dword [shipCX]
	fld dword [shipC.y]
	fistp dword [shipCY]
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
	cmp byte [gameOver],FALSE
	jne .done
	cmp byte [victory],FALSE
	jne .done
	cmp byte [pauseFlag],FALSE
	jne .done

	IsKeyDown KEY_LEFT
	test al,al
	jz .right_key
	sub dword [playerAngle],5
	cmp dword [playerAngle],0
	jge .right_key
	add dword [playerAngle],360
.right_key:
	IsKeyDown KEY_RIGHT
	test al,al
	jz .trig
	add dword [playerAngle],5
	cmp dword [playerAngle],360
	jl .trig
	sub dword [playerAngle],360

.trig:
	fastcall UpdatePlayerTrig
	IsKeyDown KEY_UP
	test al,al
	jz .coast
	add dword [playerAccel],10
	cmp dword [playerAccel],256
	jle .move_player
	mov dword [playerAccel],256
	jmp .move_player
.coast:
	sub dword [playerAccel],5
	cmp dword [playerAccel],0
	jge .down_key
	mov dword [playerAccel],0
.down_key:
	IsKeyDown KEY_DOWN
	test al,al
	jz .move_player
	sub dword [playerAccel],10
	cmp dword [playerAccel],0
	jge .move_player
	mov dword [playerAccel],0
.move_player:
	fastcall MovePlayerByTrig
	cmp dword [playerX],SCREEN_WIDTH+40
	jle .wrap_left
	mov dword [playerX],-40
	mov dword [playerXF],-40.0
.wrap_left:
	cmp dword [playerX],-40
	jge .wrap_bottom
	mov dword [playerX],SCREEN_WIDTH+40
	mov dword [playerXF],SCREEN_WIDTH+40.0
.wrap_bottom:
	cmp dword [playerY],SCREEN_HEIGHT+40
	jle .wrap_top
	mov dword [playerY],-40
	mov dword [playerYF],-40.0
.wrap_top:
	cmp dword [playerY],-40
	jge .shoot_input
	mov dword [playerY],SCREEN_HEIGHT+40
	mov dword [playerYF],SCREEN_HEIGHT+40.0

.shoot_input:
	IsKeyPressed KEY_SPACE
	test al,al
	jz .move_shoots
	lea rdi,[shoots]
	xor ebx,ebx
.spawn_loop:
	cmp ebx,MAX_SHOOTS
	jge .move_shoots
	cmp byte [rdi+SHOOT.Active],FALSE
	jne .spawn_next
	mov byte [rdi+SHOOT.Active],TRUE
	fld dword [sinAngle]
	fmul dword [shipHeight]
	fadd dword [playerXF]
	fistp dword [rdi+SHOOT.X]
	fld dword [cosAngle]
	fmul dword [shipHeight]
	fchs
	fadd dword [playerYF]
	fistp dword [rdi+SHOOT.Y]
	fld dword [sinAngle]
	fmul dword [shotSpeed]
	fistp dword [rdi+SHOOT.DX]
	fld dword [cosAngle]
	fmul dword [shotSpeed]
	fchs
	fistp dword [rdi+SHOOT.DY]
	jmp .move_shoots
.spawn_next:
	add rdi,sizeof.SHOOT
	inc ebx
	jmp .spawn_loop

.move_shoots:
	lea rdi,[shoots]
	xor ebx,ebx
.shoot_loop:
	cmp ebx,MAX_SHOOTS
	jge .move_meteors
	cmp byte [rdi+SHOOT.Active],FALSE
	je .shoot_next
	mov eax,[rdi+SHOOT.DX]
	add [rdi+SHOOT.X],eax
	mov eax,[rdi+SHOOT.DY]
	add [rdi+SHOOT.Y],eax
	cmp dword [rdi+SHOOT.X],-10
	jl .kill_shoot
	cmp dword [rdi+SHOOT.X],SCREEN_WIDTH+10
	jg .kill_shoot
	cmp dword [rdi+SHOOT.Y],20
	jl .kill_shoot
	cmp dword [rdi+SHOOT.Y],SCREEN_HEIGHT+10
	jle .shoot_next
.kill_shoot:
	mov byte [rdi+SHOOT.Active],FALSE
.shoot_next:
	add rdi,sizeof.SHOOT
	inc ebx
	jmp .shoot_loop

.move_meteors:
	lea rdi,[meteors]
	xor ebx,ebx
.meteor_loop:
	cmp ebx,MAX_METEORS
	jge .collision_shoots
	cmp byte [rdi+METEOR.Active],FALSE
	je .meteor_next
	mov eax,[rdi+METEOR.DX]
	add [rdi+METEOR.X],eax
	mov eax,[rdi+METEOR.DY]
	add [rdi+METEOR.Y],eax
	cmp dword [rdi+METEOR.X],-40
	jge .right
	mov dword [rdi+METEOR.X],SCREEN_WIDTH+40
.right:
	cmp dword [rdi+METEOR.X],SCREEN_WIDTH+40
	jle .top
	mov dword [rdi+METEOR.X],-40
.top:
	cmp dword [rdi+METEOR.Y],30
	jge .bottom
	mov dword [rdi+METEOR.Y],SCREEN_HEIGHT+40
.bottom:
	cmp dword [rdi+METEOR.Y],SCREEN_HEIGHT+40
	jle .player_collision
	mov dword [rdi+METEOR.Y],30
.player_collision:
	mov eax,[playerX]
	sub eax,[rdi+METEOR.X]
	cmp eax,-30
	jl .meteor_next
	cmp eax,30
	jg .meteor_next
	mov eax,[playerY]
	sub eax,[rdi+METEOR.Y]
	cmp eax,-30
	jl .meteor_next
	cmp eax,30
	jg .meteor_next
	mov byte [gameOver],TRUE
.meteor_next:
	add rdi,sizeof.METEOR
	inc ebx
	jmp .meteor_loop

.collision_shoots:
	lea rdi,[shoots]
	xor ebx,ebx
.outer:
	cmp ebx,MAX_SHOOTS
	jge .done
	cmp byte [rdi+SHOOT.Active],FALSE
	je .outer_next
	lea rdx,[meteors]
	xor esi,esi
.inner:
	cmp esi,MAX_METEORS
	jge .outer_next
	cmp byte [rdx+METEOR.Active],FALSE
	je .inner_next
	mov eax,[rdi+SHOOT.X]
	sub eax,[rdx+METEOR.X]
	cmp eax,-28
	jl .inner_next
	cmp eax,28
	jg .inner_next
	mov eax,[rdi+SHOOT.Y]
	sub eax,[rdx+METEOR.Y]
	cmp eax,-28
	jl .inner_next
	cmp eax,28
	jg .inner_next
	mov byte [rdi+SHOOT.Active],FALSE
	mov byte [rdx+METEOR.Active],FALSE
	dec dword [meteorsLeft]
	fastcall SplitMeteor
	cmp dword [meteorsLeft],0
	jne .outer_next
	mov byte [victory],TRUE
	jmp .done
.inner_next:
	add rdx,sizeof.METEOR
	inc esi
	jmp .inner
.outer_next:
	add rdi,sizeof.SHOOT
	inc ebx
	jmp .outer
.done:
	ret

endp

proc DrawGame uses rbx rdi
	BeginDrawing
	ClearBackground RAYWHITE
	cmp byte [gameStarted],TRUE
	je .help_done
	DrawText 'ARROWS move  SPACE shoot  P pause  R restart', 20, 20, 20, DARKGRAY
.help_done:
	lea rdi,[meteors]
	xor ebx,ebx
.draw_meteors:
	cmp ebx,MAX_METEORS
	jge .draw_shoots
	cmp byte [rdi+METEOR.Active],FALSE
	je .meteor_next
	DrawCircle [rdi+METEOR.X], [rdi+METEOR.Y], float dword [rdi+METEOR.RadiusF], GRAY
	DrawCircleLines [rdi+METEOR.X], [rdi+METEOR.Y], float dword [rdi+METEOR.RadiusF], DARKGRAY
.meteor_next:
	add rdi,sizeof.METEOR
	inc ebx
	jmp .draw_meteors
.draw_shoots:
	lea rdi,[shoots]
	xor ebx,ebx
.draw_shoot_loop:
	cmp ebx,MAX_SHOOTS
	jge .draw_player
	cmp byte [rdi+SHOOT.Active],FALSE
	je .shoot_next_draw
	DrawCircle [rdi+SHOOT.X], [rdi+SHOOT.Y], float dword 3.0, MAROON
.shoot_next_draw:
	add rdi,sizeof.SHOOT
	inc ebx
	jmp .draw_shoot_loop
.draw_player:
	fastcall UpdatePlayerTrig
	fastcall BuildShipVectors
	DrawTriangle [shipA], [shipC], [shipB], MAROON
	fastcall SyncShipInts
	DrawLine [shipAX], [shipAY], [shipBX], [shipBY], DARKBLUE
	DrawLine [shipBX], [shipBY], [shipCX], [shipCY], DARKBLUE
	DrawLine [shipCX], [shipCY], [shipAX], [shipAY], DARKBLUE
	DrawCircle [playerX], [playerY], float dword 3.0, MAROON
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
	DrawText 'CRASH - PRESS R', 310, 210, 20, MAROON
.victory_msg:
	cmp byte [victory],FALSE
	je .end_draw
	DrawText 'FIELD CLEAR - PRESS R', 290, 210, 20, DARKGREEN
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
