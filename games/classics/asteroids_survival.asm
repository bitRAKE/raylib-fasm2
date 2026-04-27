; raylib-games classics: asteroids_survival, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 450
MAX_METEORS = 14
SPAWN_SAFE_R = 150

struct METEOR
	X dd ?
	Y dd ?
	DX dd ?
	DY dd ?
	Radius dd ?
	RadiusF dd ?
ends

section '.data' data readable writeable

GLOBSTR.here ; constant string payload

	align 4

gameOver db FALSE
pauseFlag db FALSE
gameStarted db FALSE
playerX dd 400
playerY dd 225
framesCounter dd 0
moveX dd 0
moveY dd 0
shipDirX dd 0
shipDirY dd -1

meteors METEOR
	rb sizeof.METEOR*(MAX_METEORS-1)

shipA RayLib.Vector2 x:0.0, y:0.0
shipB RayLib.Vector2 x:0.0, y:0.0
shipC RayLib.Vector2 x:0.0, y:0.0

macro StoreVector2i point*, xval*, yval*
	mov eax,xval
	cvtsi2ss xmm0,eax
	movss [point.x],xmm0
	mov eax,yval
	cvtsi2ss xmm0,eax
	movss [point.y],xmm0
end macro

section '.text' code readable executable

include 'common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: asteroids survival'
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
	mov dword [playerX],400
	mov dword [playerY],225
	mov dword [framesCounter],0
	mov dword [moveX],0
	mov dword [moveY],0
	mov dword [shipDirX],0
	mov dword [shipDirY],-1
	lea rbx,[meteors]
	lea rsi,[meteors+sizeof.METEOR*MAX_METEORS]
.init_loop:
	cmp rbx,rsi
	jae .done
.pick_position:
	GetRandomValue 0,SCREEN_WIDTH
	mov [rbx+METEOR.X],eax
	GetRandomValue 0,SCREEN_HEIGHT
	mov [rbx+METEOR.Y],eax
	mov eax,[rbx+METEOR.X]
	sub eax,[playerX]
	cmp eax,-SPAWN_SAFE_R
	jl .position_ok
	cmp eax,SPAWN_SAFE_R
	jg .position_ok
	mov eax,[rbx+METEOR.Y]
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
	mov [rbx+METEOR.DX],eax
	GetRandomValue -3,3
	cmp eax,0
	jne .dy_ok
	mov eax,2
.dy_ok:
	mov [rbx+METEOR.DY],eax
	GetRandomValue 16,34
	mov [rbx+METEOR.Radius],eax
	cvtsi2ss xmm0,eax
	movss [rbx+METEOR.RadiusF],xmm0
	add rbx,sizeof.METEOR
	jmp .init_loop
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

	mov dword [moveX],0
	mov dword [moveY],0
	IsKeyDown KEY_RIGHT
	test al,al
	jz .left
	add dword [playerX],5
	inc dword [moveX]
.left:
	IsKeyDown KEY_LEFT
	test al,al
	jz .down
	sub dword [playerX],5
	dec dword [moveX]
.down:
	IsKeyDown KEY_DOWN
	test al,al
	jz .up
	add dword [playerY],5
	inc dword [moveY]
.up:
	IsKeyDown KEY_UP
	test al,al
	jz .clamp
	sub dword [playerY],5
	dec dword [moveY]
.clamp:
	mov eax,[moveX]
	or eax,[moveY]
	jz .no_direction_change
	mov eax,[moveX]
	mov [shipDirX],eax
	mov eax,[moveY]
	mov [shipDirY],eax
.no_direction_change:
	ClampData playerX, 15, SCREEN_WIDTH-15
	ClampData playerY, 45, SCREEN_HEIGHT-15

	lea rbx,[meteors]
	lea rsi,[meteors+sizeof.METEOR*MAX_METEORS]
.meteor_loop:
	cmp rbx,rsi
	jae .done
	mov eax,[rbx+METEOR.DX]
	add [rbx+METEOR.X],eax
	mov eax,[rbx+METEOR.DY]
	add [rbx+METEOR.Y],eax
	cmp dword [rbx+METEOR.X],-40
	jge .right
	mov dword [rbx+METEOR.X],SCREEN_WIDTH+40
.right:
	cmp dword [rbx+METEOR.X],SCREEN_WIDTH+40
	jle .top
	mov dword [rbx+METEOR.X],-40
.top:
	cmp dword [rbx+METEOR.Y],20
	jge .bottom
	mov dword [rbx+METEOR.Y],SCREEN_HEIGHT+40
.bottom:
	cmp dword [rbx+METEOR.Y],SCREEN_HEIGHT+40
	jle .collision
	mov dword [rbx+METEOR.Y],20
.collision:
	mov eax,[playerX]
	sub eax,[rbx+METEOR.X]
	cmp eax,-32
	jl .next
	cmp eax,32
	jg .next
	mov eax,[playerY]
	sub eax,[rbx+METEOR.Y]
	cmp eax,-32
	jl .next
	cmp eax,32
	jg .next
	mov byte [gameOver],TRUE
.next:
	add rbx,sizeof.METEOR
	jmp .meteor_loop
.done:
	ret

endp

proc DrawGame uses rbx rsi
	BeginDrawing
	ClearBackground RAYWHITE
	cmp byte [gameStarted],TRUE
	je .help_done
	DrawText 'ARROWS dodge meteors  P pause  R restart', 20, 20, 20, DARKGRAY
.help_done:
	lea rbx,[meteors]
	lea rsi,[meteors+sizeof.METEOR*MAX_METEORS]
.draw_meteors:
	cmp rbx,rsi
	jae .draw_ship
	DrawCircle [rbx+METEOR.X], [rbx+METEOR.Y], float dword [rbx+METEOR.RadiusF], GRAY
	DrawCircleLines [rbx+METEOR.X], [rbx+METEOR.Y], float dword [rbx+METEOR.RadiusF], DARKGRAY
	add rbx,sizeof.METEOR
	jmp .draw_meteors
.draw_ship:
	mov r10d,18
	mov r11d,12
	mov ecx,14
	mov eax,[shipDirX]
	test eax,eax
	jz .shape_ready
	cmp dword [shipDirY],0
	je .shape_ready
	mov r10d,13
	mov r11d,9
	mov ecx,10
.shape_ready:
	mov eax,[shipDirX]
	imul eax,r10d
	add eax,[playerX]
	mov edx,[shipDirY]
	imul edx,r10d
	add edx,[playerY]
	StoreVector2i shipA, eax, edx

	mov r8d,[shipDirX]
	imul r8d,r11d
	mov eax,[playerX]
	sub eax,r8d
	mov r8d,eax
	mov r9d,[shipDirY]
	imul r9d,r11d
	mov edx,[playerY]
	sub edx,r9d
	mov r9d,edx

	mov eax,[shipDirY]
	neg eax
	imul eax,ecx
	add eax,r8d
	mov edx,[shipDirX]
	imul edx,ecx
	add edx,r9d
	StoreVector2i shipB, eax, edx

	mov eax,[shipDirY]
	imul eax,ecx
	add eax,r8d
	mov edx,[shipDirX]
	neg edx
	imul edx,ecx
	add edx,r9d
	StoreVector2i shipC, eax, edx

	DrawTriangle [shipA], [shipB], [shipC], MAROON
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
	DrawText 'CRASH - PRESS R', 310, 210, 20, MAROON
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
