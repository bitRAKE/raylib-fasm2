; raylib-games classics: gorilas, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 450
MAX_BUILDINGS = 15
MAX_CRATERS = 200
MAX_PLAYERS = 2
PLAYER_SIZE = 40
BALL_R = 10
CRATER_R = 30
BALL_GRAVITY_FP = 42 ; 9.81/60 in 8.8 fixed point

struct BUILDING
	X dd ?
	Y dd ?
	W dd ?
	H dd ?
	Color dd ?
ends

struct PLAYER
	X dd ?
	Y dd ?
	AimX dd ?
	AimY dd ?
	PrevX dd ?
	PrevY dd ?
	Alive db ?
	rb 3
ends

struct CRATER
	X dd ?
	Y dd ?
ends

section '.data' data readable writeable

GLOBSTR.here ; constant string payload

	align 4

gameOver db FALSE
pauseFlag db FALSE
gameStarted db FALSE
playerTurn dd 0
winner dd -1
ballActive db FALSE
ballX dd 0
ballY dd 0
ballXF dd 0
ballYF dd 0
ballVXF dd 0
ballVYF dd 0

mousePos RayLib.Vector2 x:0.0, y:0.0
mouseX dd 0
mouseY dd 0
hitLeft dd 0
hitTop dd 0

buildings BUILDING
	rb sizeof.BUILDING*(MAX_BUILDINGS-1)

players PLAYER
	rb sizeof.PLAYER*(MAX_PLAYERS-1)

craterCount dd 0
craterNext dd 0
craters CRATER
	rb sizeof.CRATER*(MAX_CRATERS-1)

aimA RayLib.Vector2 x:0.0, y:0.0
aimB RayLib.Vector2 x:0.0, y:0.0
aimC RayLib.Vector2 x:0.0, y:0.0

macro StoreVector2xy point*
	cvtsi2ss xmm0,eax
	movss [point.x],xmm0
	cvtsi2ss xmm0,edx
	movss [point.y],xmm0
end macro

section '.text' code readable executable

include 'common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: gorilas'
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

proc InitBuildings uses rbx rsi rdi
	lea rbx,[buildings]
	xor esi,esi
	xor edi,edi
.loop:
	cmp esi,MAX_BUILDINGS
	jge .done
	mov [rbx+BUILDING.X],edi
	GetRandomValue 66,100
	mov [rbx+BUILDING.W],eax
	add edi,eax

	GetRandomValue 20,60
	imul eax,SCREEN_HEIGHT
	xor edx,edx
	mov ecx,100
	div ecx
	mov [rbx+BUILDING.H],eax
	mov edx,SCREEN_HEIGHT
	sub edx,eax
	mov [rbx+BUILDING.Y],edx

	GetRandomValue 120,200
	mov ecx,eax
	shl ecx,8
	or ecx,eax
	mov edx,eax
	shl edx,16
	or ecx,edx
	or ecx,0FF000000h
	mov [rbx+BUILDING.Color],ecx

	add rbx,sizeof.BUILDING
	inc esi
	jmp .loop
.done:
	ret

endp

proc PlacePlayer uses rbx rsi rdi
	; rcx = PLAYER pointer, edx = requested x position.
	mov rbx,rcx
	mov edi,edx
	lea rsi,[buildings]
	mov ecx,MAX_BUILDINGS
.find:
	mov eax,[rsi+BUILDING.X]
	add eax,[rsi+BUILDING.W]
	cmp edi,eax
	jl .found
	add rsi,sizeof.BUILDING
	loop .find
	sub rsi,sizeof.BUILDING
.found:
	mov eax,[rsi+BUILDING.W]
	sar eax,1
	add eax,[rsi+BUILDING.X]
	mov [rbx+PLAYER.X],eax
	mov [rbx+PLAYER.AimX],eax
	mov [rbx+PLAYER.PrevX],eax
	mov eax,[rsi+BUILDING.Y]
	sub eax,PLAYER_SIZE/2
	mov [rbx+PLAYER.Y],eax
	mov [rbx+PLAYER.AimY],eax
	mov [rbx+PLAYER.PrevY],eax
	mov byte [rbx+PLAYER.Alive],TRUE
	ret

endp

proc InitPlayers
	GetRandomValue SCREEN_WIDTH*5/100, SCREEN_WIDTH*20/100
	lea rcx,[players]
	mov edx,eax
	fastcall PlacePlayer, rcx, edx

	GetRandomValue SCREEN_WIDTH*5/100, SCREEN_WIDTH*20/100
	mov edx,SCREEN_WIDTH
	sub edx,eax
	lea rcx,[players+sizeof.PLAYER]
	fastcall PlacePlayer, rcx, edx
	ret

endp

proc InitGame
	mov byte [gameOver],FALSE
	mov byte [pauseFlag],FALSE
	mov byte [gameStarted],FALSE
	mov byte [ballActive],FALSE
	mov dword [playerTurn],0
	mov dword [winner],-1
	mov dword [craterCount],0
	mov dword [craterNext],0
	fastcall InitBuildings
	fastcall InitPlayers
	ret

endp

proc AddCrater uses rbx
	; in eax x, edx y.
	mov ebx,[craterNext]
	imul ebx,sizeof.CRATER
	lea rbx,[craters+rbx]
	mov [rbx+CRATER.X],eax
	mov [rbx+CRATER.Y],edx
	mov ebx,[craterNext]
	inc ebx
	cmp ebx,MAX_CRATERS
	jl .next_ok
	xor ebx,ebx
.next_ok:
	mov [craterNext],ebx
	cmp dword [craterCount],MAX_CRATERS
	jge .done
	inc dword [craterCount]
.done:
	ret

endp

proc BallInsideCrater uses rbx rsi
	xor ebx,ebx
	lea rsi,[craters]
.loop:
	cmp ebx,[craterCount]
	jge .miss
	mov eax,[ballX]
	sub eax,[rsi+CRATER.X]
	imul eax,eax
	mov edx,[ballY]
	sub edx,[rsi+CRATER.Y]
	imul edx,edx
	add eax,edx
	cmp eax,(CRATER_R-BALL_R)*(CRATER_R-BALL_R)
	jle .hit
	add rsi,sizeof.CRATER
	inc ebx
	jmp .loop
.hit:
	mov eax,TRUE
	ret
.miss:
	xor eax,eax
	ret

endp

proc EndTurn
	mov byte [ballActive],FALSE
	cmp byte [players+PLAYER.Alive],FALSE
	jne .check_player2
	mov dword [winner],1
	jmp .over
.check_player2:
	cmp byte [players+sizeof.PLAYER+PLAYER.Alive],FALSE
	jne .next_turn
	mov dword [winner],0
	jmp .over
.next_turn:
	xor dword [playerTurn],1
	ret
.over:
	mov byte [gameOver],TRUE
	ret

endp

proc UpdateAim uses rbx
	mov eax,[playerTurn]
	imul eax,sizeof.PLAYER
	lea rbx,[players+rax]

	GetMousePosition
	mov qword [mousePos],rax
	cvttss2si eax,dword [mousePos.x]
	mov [mouseX],eax
	cvttss2si eax,dword [mousePos.y]
	mov [mouseY],eax

	mov eax,[rbx+PLAYER.X]
	mov [rbx+PLAYER.AimX],eax
	mov eax,[rbx+PLAYER.Y]
	mov [rbx+PLAYER.AimY],eax

	mov eax,[mouseY]
	cmp eax,[rbx+PLAYER.Y]
	jg .done
	cmp dword [playerTurn],0
	jne .right_player
	mov eax,[mouseX]
	cmp eax,[rbx+PLAYER.X]
	jl .done
	jmp .valid_aim
.right_player:
	mov eax,[mouseX]
	cmp eax,[rbx+PLAYER.X]
	jg .done

.valid_aim:
	mov eax,[mouseX]
	mov [rbx+PLAYER.AimX],eax
	mov eax,[mouseY]
	mov [rbx+PLAYER.AimY],eax

	IsMouseButtonPressed MOUSE_BUTTON_LEFT
	test al,al
	jz .done

	mov eax,[rbx+PLAYER.AimX]
	mov [rbx+PLAYER.PrevX],eax
	mov eax,[rbx+PLAYER.AimY]
	mov [rbx+PLAYER.PrevY],eax

	mov eax,[rbx+PLAYER.X]
	mov [ballX],eax
	shl eax,8
	mov [ballXF],eax
	mov eax,[rbx+PLAYER.Y]
	mov [ballY],eax
	shl eax,8
	mov [ballYF],eax

	mov eax,[rbx+PLAYER.PrevX]
	sub eax,[rbx+PLAYER.X]
	imul eax,256
	cdq
	mov ecx,20
	idiv ecx
	mov [ballVXF],eax

	mov eax,[rbx+PLAYER.PrevY]
	sub eax,[rbx+PLAYER.Y]
	imul eax,256
	cdq
	mov ecx,20
	idiv ecx
	mov [ballVYF],eax

	mov byte [ballActive],TRUE
.done:
	ret

endp

proc UpdateBall uses rbx rsi
	mov eax,[ballVXF]
	add [ballXF],eax
	mov eax,[ballVYF]
	add [ballYF],eax
	add dword [ballVYF],BALL_GRAVITY_FP
	mov eax,[ballXF]
	sar eax,8
	mov [ballX],eax
	mov eax,[ballYF]
	sar eax,8
	mov [ballY],eax

	cmp dword [ballX],-BALL_R
	jl .end_turn
	cmp dword [ballX],SCREEN_WIDTH+BALL_R
	jg .end_turn
	cmp dword [ballY],SCREEN_HEIGHT+BALL_R
	jg .end_turn

	lea rbx,[players]
	xor esi,esi
.player_loop:
	cmp esi,MAX_PLAYERS
	jge .building_start
	cmp esi,[playerTurn]
	je .player_next
	cmp byte [rbx+PLAYER.Alive],FALSE
	je .player_next
	mov eax,[rbx+PLAYER.X]
	sub eax,PLAYER_SIZE/2
	mov [hitLeft],eax
	mov eax,[rbx+PLAYER.Y]
	sub eax,PLAYER_SIZE/2
	mov [hitTop],eax
	fastcall CircleRectOverlap, [ballX], [ballY], BALL_R, [hitLeft], [hitTop], PLAYER_SIZE, PLAYER_SIZE
	test al,al
	jz .player_next
	mov byte [rbx+PLAYER.Alive],FALSE
	fastcall EndTurn
	ret
.player_next:
	add rbx,sizeof.PLAYER
	inc esi
	jmp .player_loop

.building_start:
	lea rbx,[buildings]
	xor esi,esi
.building_loop:
	cmp esi,MAX_BUILDINGS
	jge .done
	fastcall CircleRectOverlap, [ballX], [ballY], BALL_R, [rbx+BUILDING.X], [rbx+BUILDING.Y], [rbx+BUILDING.W], [rbx+BUILDING.H]
	test al,al
	jz .building_next
	fastcall BallInsideCrater
	test al,al
	jnz .building_next
	mov eax,[ballX]
	mov edx,[ballY]
	add edx,BALL_R
	fastcall AddCrater
.end_turn:
	fastcall EndTurn
	ret
.building_next:
	add rbx,sizeof.BUILDING
	inc esi
	jmp .building_loop
.done:
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

	cmp byte [ballActive],FALSE
	jne .move_ball
	fastcall UpdateAim
	jmp .done
.move_ball:
	fastcall UpdateBall
.done:
	ret

endp

proc DrawAimForPlayer uses rbx rdi
	; rcx = PLAYER pointer, edx = current color.
	mov rbx,rcx
	mov edi,edx

	cmp dword [playerTurn],0
	jne .right_shape
	mov eax,[rbx+PLAYER.X]
	sub eax,PLAYER_SIZE/4
	mov edx,[rbx+PLAYER.Y]
	sub edx,PLAYER_SIZE/4
	StoreVector2xy aimA
	mov eax,[rbx+PLAYER.X]
	add eax,PLAYER_SIZE/4
	mov edx,[rbx+PLAYER.Y]
	add edx,PLAYER_SIZE/4
	StoreVector2xy aimB
	jmp .previous
.right_shape:
	mov eax,[rbx+PLAYER.X]
	sub eax,PLAYER_SIZE/4
	mov edx,[rbx+PLAYER.Y]
	add edx,PLAYER_SIZE/4
	StoreVector2xy aimA
	mov eax,[rbx+PLAYER.X]
	add eax,PLAYER_SIZE/4
	mov edx,[rbx+PLAYER.Y]
	sub edx,PLAYER_SIZE/4
	StoreVector2xy aimB
.previous:
	mov eax,[rbx+PLAYER.PrevX]
	mov edx,[rbx+PLAYER.PrevY]
	StoreVector2xy aimC
	DrawTriangle [aimA], [aimB], [aimC], GRAY
	mov eax,[rbx+PLAYER.AimX]
	mov edx,[rbx+PLAYER.AimY]
	StoreVector2xy aimC
	DrawTriangle [aimA], [aimB], [aimC], edi
	ret

endp

proc DrawGame uses rbx rsi
	BeginDrawing
	ClearBackground RAYWHITE
	cmp byte [gameStarted],TRUE
	je .help_done
	DrawText 'LEFT CLICK throw  P pause  R restart', 20, 20, 20, DARKGRAY
.help_done:

	lea rbx,[buildings]
	xor esi,esi
.build_loop:
	cmp esi,MAX_BUILDINGS
	jge .craters
	DrawRectangle [rbx+BUILDING.X], [rbx+BUILDING.Y], [rbx+BUILDING.W], [rbx+BUILDING.H], [rbx+BUILDING.Color]
	add rbx,sizeof.BUILDING
	inc esi
	jmp .build_loop

.craters:
	xor esi,esi
	lea rbx,[craters]
.crater_loop:
	cmp esi,[craterCount]
	jge .players
	DrawCircle [rbx+CRATER.X], [rbx+CRATER.Y], float dword 30.0, RAYWHITE
	add rbx,sizeof.CRATER
	inc esi
	jmp .crater_loop

.players:
	lea rbx,[players]
	cmp byte [rbx+PLAYER.Alive],FALSE
	je .player2
	mov ecx,[rbx+PLAYER.X]
	sub ecx,PLAYER_SIZE/2
	mov edx,[rbx+PLAYER.Y]
	sub edx,PLAYER_SIZE/2
	DrawRectangle ecx, edx, PLAYER_SIZE, PLAYER_SIZE, BLUE
.player2:
	lea rbx,[players+sizeof.PLAYER]
	cmp byte [rbx+PLAYER.Alive],FALSE
	je .aim
	mov ecx,[rbx+PLAYER.X]
	sub ecx,PLAYER_SIZE/2
	mov edx,[rbx+PLAYER.Y]
	sub edx,PLAYER_SIZE/2
	DrawRectangle ecx, edx, PLAYER_SIZE, PLAYER_SIZE, RED

.aim:
	cmp byte [ballActive],TRUE
	je .draw_ball
	cmp byte [gameStarted],TRUE
	jne .messages
	mov eax,[playerTurn]
	imul eax,sizeof.PLAYER
	lea rcx,[players+rax]
	mov edx,RayLib.DARKBLUE
	cmp dword [playerTurn],0
	je .draw_aim
	mov edx,RayLib.MAROON
.draw_aim:
	fastcall DrawAimForPlayer, rcx, edx

.draw_ball:
	cmp byte [ballActive],FALSE
	je .messages
	DrawCircle [ballX], [ballY], float dword 10.0, MAROON

.messages:
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
	cmp dword [winner],0
	jne .red_winner
	DrawText 'BLUE WINS - PRESS R', 290, 210, 20, BLUE
	jmp .end_draw
.red_winner:
	cmp dword [winner],1
	jne .hit_message
	DrawText 'RED WINS - PRESS R', 300, 210, 20, MAROON
	jmp .end_draw
.hit_message:
	DrawText 'HIT - PRESS R', 330, 210, 20, MAROON
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
