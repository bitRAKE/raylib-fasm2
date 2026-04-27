; raylib-games classics: pang, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 450
MAX_BALLS = 10
MAX_POINTS = 16

struct BALL
	X dd ?
	Y dd ?
	DX dd ?
	DY dd ?
	Radius dd ?
	RadiusF dd ?
	Active db ?
	rb 3
ends

struct POINT_LABEL
	X dd ?
	Y dd ?
	Value dd ?
	TTL dd ?
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
playerX dd 380
lineActive db FALSE
lineY dd 390
ballsLeft dd 2
score dd 0

balls BALL
	rb sizeof.BALL*(MAX_BALLS-1)

points POINT_LABEL
	rb sizeof.POINT_LABEL*(MAX_POINTS-1)

section '.text' code readable executable

include 'common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: pang'
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

proc SetBallUpVelocity ball
	mov eax,[rcx+BALL.Radius]
	cmp eax,30
	jge .big
	cmp eax,18
	jge .medium
	mov dword [rcx+BALL.DY],-14
	ret
.medium:
	mov dword [rcx+BALL.DY],-16
	ret
.big:
	mov dword [rcx+BALL.DY],-19
	ret

endp

proc AddPointLabel uses rbx rsi
	; rcx = source BALL pointer, edx = score value.
	lea rbx,[points]
	lea rsi,[points+sizeof.POINT_LABEL*MAX_POINTS]
.find:
	cmp rbx,rsi
	jae .done
	cmp byte [rbx+POINT_LABEL.Active],FALSE
	je .store
	add rbx,sizeof.POINT_LABEL
	jmp .find
.store:
	mov byte [rbx+POINT_LABEL.Active],TRUE
	mov eax,[rcx+BALL.X]
	mov [rbx+POINT_LABEL.X],eax
	mov eax,[rcx+BALL.Y]
	mov [rbx+POINT_LABEL.Y],eax
	mov [rbx+POINT_LABEL.Value],edx
	mov dword [rbx+POINT_LABEL.TTL],45
.done:
	ret

endp

proc InitGame uses rbx rsi
	mov byte [gameOver],FALSE
	mov byte [pauseFlag],FALSE
	mov byte [gameStarted],FALSE
	mov byte [victory],FALSE
	mov byte [lineActive],FALSE
	mov dword [playerX],380
	mov dword [ballsLeft],2
	mov dword [score],0
	lea rbx,[balls]
	lea rsi,[balls+sizeof.BALL*MAX_BALLS]
.clear:
	cmp rbx,rsi
	jae .first
	mov byte [rbx+BALL.Active],FALSE
	add rbx,sizeof.BALL
	jmp .clear
.first:
	lea rbx,[points]
	lea rsi,[points+sizeof.POINT_LABEL*MAX_POINTS]
.clear_points:
	cmp rbx,rsi
	jae .balls
	mov byte [rbx+POINT_LABEL.Active],FALSE
	add rbx,sizeof.POINT_LABEL
	jmp .clear_points
.balls:
	mov byte [balls+BALL.Active],TRUE
	mov dword [balls+BALL.X],420
	mov dword [balls+BALL.Y],160
	mov dword [balls+BALL.DX],3
	mov dword [balls+BALL.DY],0
	mov dword [balls+BALL.Radius],36
	mov dword [balls+BALL.RadiusF],36.0
	mov byte [balls+sizeof.BALL+BALL.Active],TRUE
	mov dword [balls+sizeof.BALL+BALL.X],220
	mov dword [balls+sizeof.BALL+BALL.Y],140
	mov dword [balls+sizeof.BALL+BALL.DX],-3
	mov dword [balls+sizeof.BALL+BALL.DY],0
	mov dword [balls+sizeof.BALL+BALL.Radius],36
	mov dword [balls+sizeof.BALL+BALL.RadiusF],36.0
	ret

endp

proc SpawnSplit uses rbx rsi rdi
	; rbx points at the source ball, deactivates or splits into first free slot
	mov eax,[rbx+BALL.Radius]
	cmp eax,18
	jg .score_big
	cmp eax,9
	jg .score_medium
	mov edx,50
	jmp .score_done
.score_big:
	mov edx,200
	jmp .score_done
.score_medium:
	mov edx,100
.score_done:
	add [score],edx
	fastcall AddPointLabel, rbx, edx
	mov eax,[rbx+BALL.Radius]
	cmp eax,10
	jge .split
	mov byte [rbx+BALL.Active],FALSE
	dec dword [ballsLeft]
	jmp .done
.split:
	shr eax,1
	mov [rbx+BALL.Radius],eax
	cvtsi2ss xmm0,eax
	movss [rbx+BALL.RadiusF],xmm0
	neg dword [rbx+BALL.DX]
	fastcall SetBallUpVelocity, rbx
	lea rdi,[balls]
	lea rsi,[balls+sizeof.BALL*MAX_BALLS]
.find:
	cmp rdi,rsi
	jae .done
	cmp byte [rdi+BALL.Active],FALSE
	jne .next
	mov byte [rdi+BALL.Active],TRUE
	mov eax,[rbx+BALL.X]
	mov [rdi+BALL.X],eax
	mov eax,[rbx+BALL.Y]
	mov [rdi+BALL.Y],eax
	mov eax,[rbx+BALL.Radius]
	mov [rdi+BALL.Radius],eax
	cvtsi2ss xmm0,eax
	movss [rdi+BALL.RadiusF],xmm0
	mov eax,[rbx+BALL.DX]
	neg eax
	mov [rdi+BALL.DX],eax
	fastcall SetBallUpVelocity, rdi
	inc dword [ballsLeft]
	jmp .done
.next:
	add rdi,sizeof.BALL
	jmp .find
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
	cmp byte [victory],FALSE
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
	jz .clamp
	sub dword [playerX],5
.clamp:
	ClampData playerX, 0, SCREEN_WIDTH-40

	cmp byte [lineActive],FALSE
	jne .move_line
	IsKeyPressed KEY_SPACE
	test al,al
	jz .move_balls
	mov byte [lineActive],TRUE
	mov dword [lineY],390
	jmp .move_balls
.move_line:
	sub dword [lineY],14
	cmp dword [lineY],45
	jg .move_balls
	mov byte [lineActive],FALSE

.move_balls:
	lea rbx,[balls]
	lea rsi,[balls+sizeof.BALL*MAX_BALLS]
.ball_loop:
	cmp rbx,rsi
	jae .line_hits
	cmp byte [rbx+BALL.Active],FALSE
	je .next_ball
	mov eax,[rbx+BALL.DX]
	add [rbx+BALL.X],eax
	mov eax,[rbx+BALL.DY]
	add [rbx+BALL.Y],eax
	inc dword [rbx+BALL.DY]
	cmp dword [rbx+BALL.X],20
	jge .right
	neg dword [rbx+BALL.DX]
.right:
	cmp dword [rbx+BALL.X],SCREEN_WIDTH-20
	jle .floor
	neg dword [rbx+BALL.DX]
.floor:
	cmp dword [rbx+BALL.Y],380
	jl .player_hit
	mov dword [rbx+BALL.Y],380
	fastcall SetBallUpVelocity, rbx
.player_hit:
	fastcall CircleRectOverlap, [rbx+BALL.X], [rbx+BALL.Y], [rbx+BALL.Radius], [playerX], 400, 40, 20
	test al,al
	jz .next_ball
	mov byte [gameOver],TRUE
.next_ball:
	add rbx,sizeof.BALL
	jmp .ball_loop

.line_hits:
	cmp byte [lineActive],FALSE
	je .win_check
	lea rbx,[balls]
	lea rsi,[balls+sizeof.BALL*MAX_BALLS]
.hit_loop:
	cmp rbx,rsi
	jae .win_check
	cmp byte [rbx+BALL.Active],FALSE
	je .hit_next
	mov eax,[playerX]
	add eax,20
	sub eax,[rbx+BALL.X]
	mov edx,[rbx+BALL.Radius]
	neg edx
	cmp eax,edx
	jl .hit_next
	cmp eax,[rbx+BALL.Radius]
	jg .hit_next
	mov eax,[lineY]
	mov edx,[rbx+BALL.Y]
	add edx,[rbx+BALL.Radius]
	cmp eax,edx
	jg .hit_next
	mov byte [lineActive],FALSE
	fastcall SpawnSplit
	jmp .win_check
.hit_next:
	add rbx,sizeof.BALL
	jmp .hit_loop
.win_check:
	lea rbx,[points]
	lea rsi,[points+sizeof.POINT_LABEL*MAX_POINTS]
.point_loop:
	cmp rbx,rsi
	jae .win_count
	cmp byte [rbx+POINT_LABEL.Active],FALSE
	je .point_next
	sub dword [rbx+POINT_LABEL.Y],2
	dec dword [rbx+POINT_LABEL.TTL]
	jnz .point_next
	mov byte [rbx+POINT_LABEL.Active],FALSE
.point_next:
	add rbx,sizeof.POINT_LABEL
	jmp .point_loop
.win_count:
	cmp dword [ballsLeft],0
	jne .done
	mov byte [victory],TRUE
.done:
	ret

endp

proc DrawGame uses rbx rsi
	BeginDrawing
	ClearBackground RAYWHITE
	cmp byte [gameStarted],TRUE
	je .help_done
	DrawText 'LEFT/RIGHT move  SPACE shoot  P pause  R restart', 20, 20, 20, DARKGRAY
.help_done:
	DrawRectangle [playerX], 400, 40, 20, BLUE
	cmp byte [lineActive],FALSE
	je .balls
	mov eax,[playerX]
	add eax,20
	DrawLine eax, 400, eax, [lineY], MAROON
.balls:
	lea rbx,[balls]
	lea rsi,[balls+sizeof.BALL*MAX_BALLS]
.draw_loop:
	cmp rbx,rsi
	jae .messages
	cmp byte [rbx+BALL.Active],FALSE
	je .draw_next
	DrawCircle [rbx+BALL.X], [rbx+BALL.Y], float dword [rbx+BALL.RadiusF], ORANGE
	DrawCircleLines [rbx+BALL.X], [rbx+BALL.Y], float dword [rbx+BALL.RadiusF], MAROON
.draw_next:
	add rbx,sizeof.BALL
	jmp .draw_loop
.messages:
	lea rbx,[points]
	lea rsi,[points+sizeof.POINT_LABEL*MAX_POINTS]
.point_draw_loop:
	cmp rbx,rsi
	jae .score
	cmp byte [rbx+POINT_LABEL.Active],FALSE
	je .point_draw_next
	TextFormat '+%02i', [rbx+POINT_LABEL.Value]
	DrawText rax, [rbx+POINT_LABEL.X], [rbx+POINT_LABEL.Y], 20, BLUE
.point_draw_next:
	add rbx,sizeof.POINT_LABEL
	jmp .point_draw_loop
.score:
	TextFormat 'SCORE: %i', [score]
	DrawText rax, 10, 45, 20, LIGHTGRAY
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
	DrawText 'HIT - PRESS R', 330, 210, 20, MAROON
.victory_msg:
	cmp byte [victory],FALSE
	je .end_draw
	DrawText 'CLEAR - PRESS R', 330, 210, 20, DARKGREEN
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
