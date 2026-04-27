; raylib-games classics: missile_commander, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 450
MAX_MISSILES = 18
MAX_INTERCEPTORS = 6
MAX_EXPLOSIONS = 8
BUILDINGS = 6
LAUNCHERS = 3
INTERCEPTOR_STEPS = 22

struct MISSILE
	X dd ?
	Y dd ?
	DY dd ?
	Active db ?
	rb 3
ends

struct INTERCEPTOR
	OriginX dd ?
	OriginY dd ?
	X dd ?
	Y dd ?
	TargetX dd ?
	TargetY dd ?
	DX dd ?
	DY dd ?
	Steps dd ?
	Active db ?
	rb 3
ends

struct EXPLOSION
	X dd ?
	Y dd ?
	Radius dd ?
	RadiusF dd ?
	Active db ?
	rb 3
ends

struct LAUNCHER
	X dd ?
	Active db ?
	rb 3
ends

section '.data' data readable writeable

GLOBSTR.here ; constant string payload

	align 4

gameOver db FALSE
pauseFlag db FALSE
gameStarted db FALSE
framesCounter dd 0
buildingsLeft dd BUILDINGS
launchersLeft dd LAUNCHERS
score dd 0

mousePos RayLib.Vector2 x:0.0, y:0.0
mouseX dd 0
mouseY dd 0

missiles MISSILE
	rb sizeof.MISSILE*(MAX_MISSILES-1)

interceptors INTERCEPTOR
	rb sizeof.INTERCEPTOR*(MAX_INTERCEPTORS-1)

explosions EXPLOSION
	rb sizeof.EXPLOSION*(MAX_EXPLOSIONS-1)

buildingActive db BUILDINGS dup ?
launchers LAUNCHER X:80, Active:FALSE
	LAUNCHER X:400, Active:FALSE
	LAUNCHER X:720, Active:FALSE

section '.text' code readable executable

include 'common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: missile commander'
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
	mov dword [framesCounter],0
	mov dword [buildingsLeft],BUILDINGS
	mov dword [launchersLeft],LAUNCHERS
	mov dword [score],0
	lea rbx,[missiles]
	lea rsi,[missiles+sizeof.MISSILE*MAX_MISSILES]
.clear_missiles:
	cmp rbx,rsi
	jae .clear_interceptors
	mov byte [rbx+MISSILE.Active],FALSE
	add rbx,sizeof.MISSILE
	jmp .clear_missiles
.clear_interceptors:
	lea rbx,[interceptors]
	lea rsi,[interceptors+sizeof.INTERCEPTOR*MAX_INTERCEPTORS]
.int_loop:
	cmp rbx,rsi
	jae .clear_explosions
	mov byte [rbx+INTERCEPTOR.Active],FALSE
	add rbx,sizeof.INTERCEPTOR
	jmp .int_loop
.clear_explosions:
	lea rbx,[explosions]
	lea rsi,[explosions+sizeof.EXPLOSION*MAX_EXPLOSIONS]
.expl_loop:
	cmp rbx,rsi
	jae .buildings
	mov byte [rbx+EXPLOSION.Active],FALSE
	add rbx,sizeof.EXPLOSION
	jmp .expl_loop
.buildings:
	xor ebx,ebx
.b_loop:
	cmp ebx,BUILDINGS
	jge .launchers
	mov byte [buildingActive+rbx],TRUE
	inc ebx
	jmp .b_loop
.launchers:
	lea rbx,[launchers]
	lea rsi,[launchers+sizeof.LAUNCHER*LAUNCHERS]
.l_loop:
	cmp rbx,rsi
	jae .done
	mov byte [rbx+LAUNCHER.Active],TRUE
	add rbx,sizeof.LAUNCHER
	jmp .l_loop
.done:
	ret
endp


proc LauncherForMouse uses rbx rsi
	; out eax origin x, edx TRUE/FALSE
	lea rbx,[launchers]
	cmp dword [mouseX],267
	jl .preferred
	add rbx,sizeof.LAUNCHER
	cmp dword [mouseX],533
	jle .preferred
	add rbx,sizeof.LAUNCHER
.preferred:
	cmp byte [rbx+LAUNCHER.Active],TRUE
	je .found
	lea rbx,[launchers]
	lea rsi,[launchers+sizeof.LAUNCHER*LAUNCHERS]
.search:
	cmp rbx,rsi
	jae .miss
	cmp byte [rbx+LAUNCHER.Active],TRUE
	je .found
	add rbx,sizeof.LAUNCHER
	jmp .search
.found:
	mov eax,[rbx+LAUNCHER.X]
	mov edx,TRUE
	ret
.miss:
	xor edx,edx
	ret
endp


proc SpawnMissile uses rbx rsi
	lea rbx,[missiles]
	lea rsi,[missiles+sizeof.MISSILE*MAX_MISSILES]
.loop:
	cmp rbx,rsi
	jae .done
	cmp byte [rbx+MISSILE.Active],FALSE
	jne .next
	mov byte [rbx+MISSILE.Active],TRUE
	GetRandomValue 20,780
	mov [rbx+MISSILE.X],eax
	mov dword [rbx+MISSILE.Y],45
	GetRandomValue 1,3
	mov [rbx+MISSILE.DY],eax
	jmp .done
.next:
	add rbx,sizeof.MISSILE
	jmp .loop
.done:
	ret
endp


proc SpawnExplosion uses rbx rsi
	; in eax=x, edx=y
	lea rbx,[explosions]
	lea rsi,[explosions+sizeof.EXPLOSION*MAX_EXPLOSIONS]
.loop:
	cmp rbx,rsi
	jae .done
	cmp byte [rbx+EXPLOSION.Active],FALSE
	jne .next
	mov byte [rbx+EXPLOSION.Active],TRUE
	mov [rbx+EXPLOSION.X],eax
	mov [rbx+EXPLOSION.Y],edx
	mov dword [rbx+EXPLOSION.Radius],4
	mov dword [rbx+EXPLOSION.RadiusF],4.0
	jmp .done
.next:
	add rbx,sizeof.EXPLOSION
	jmp .loop
.done:
	ret
endp


proc SpawnInterceptor uses rbx rsi
	lea rbx,[interceptors]
	lea rsi,[interceptors+sizeof.INTERCEPTOR*MAX_INTERCEPTORS]
.loop:
	cmp rbx,rsi
	jae .done
	cmp byte [rbx+INTERCEPTOR.Active],FALSE
	jne .next
	fastcall LauncherForMouse
	test edx,edx
	jz .done
	mov byte [rbx+INTERCEPTOR.Active],TRUE
	mov [rbx+INTERCEPTOR.OriginX],eax
	mov [rbx+INTERCEPTOR.X],eax
	mov dword [rbx+INTERCEPTOR.OriginY],395
	mov dword [rbx+INTERCEPTOR.Y],395
	mov eax,[mouseX]
	mov [rbx+INTERCEPTOR.TargetX],eax
	sub eax,[rbx+INTERCEPTOR.X]
	cdq
	mov ecx,INTERCEPTOR_STEPS
	idiv ecx
	mov [rbx+INTERCEPTOR.DX],eax
	mov eax,[mouseY]
	mov [rbx+INTERCEPTOR.TargetY],eax
	sub eax,[rbx+INTERCEPTOR.Y]
	cdq
	mov ecx,INTERCEPTOR_STEPS
	idiv ecx
	mov [rbx+INTERCEPTOR.DY],eax
	mov dword [rbx+INTERCEPTOR.Steps],0
	jmp .done
.next:
	add rbx,sizeof.INTERCEPTOR
	jmp .loop
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

	inc dword [framesCounter]
	cmp dword [framesCounter],35
	jl .mouse
	mov dword [framesCounter],0
	fastcall SpawnMissile

.mouse:
	IsMouseButtonPressed MOUSE_BUTTON_LEFT
	test al,al
	jz .move_interceptors
	GetMousePosition
	mov qword [mousePos],rax
	cvttss2si eax,dword [mousePos.x]
	mov [mouseX],eax
	cvttss2si eax,dword [mousePos.y]
	mov [mouseY],eax
	fastcall SpawnInterceptor

.move_interceptors:
	lea rbx,[interceptors]
	lea rsi,[interceptors+sizeof.INTERCEPTOR*MAX_INTERCEPTORS]
.int_move_loop:
	cmp rbx,rsi
	jae .move_missiles
	cmp byte [rbx+INTERCEPTOR.Active],FALSE
	je .int_next
	mov eax,[rbx+INTERCEPTOR.DX]
	add [rbx+INTERCEPTOR.X],eax
	mov eax,[rbx+INTERCEPTOR.DY]
	add [rbx+INTERCEPTOR.Y],eax
	inc dword [rbx+INTERCEPTOR.Steps]
	cmp dword [rbx+INTERCEPTOR.Steps],INTERCEPTOR_STEPS
	jl .int_next
	mov byte [rbx+INTERCEPTOR.Active],FALSE
	mov eax,[rbx+INTERCEPTOR.TargetX]
	mov edx,[rbx+INTERCEPTOR.TargetY]
	fastcall SpawnExplosion
.int_next:
	add rbx,sizeof.INTERCEPTOR
	jmp .int_move_loop

.move_missiles:
	lea rbx,[missiles]
	lea rsi,[missiles+sizeof.MISSILE*MAX_MISSILES]
.missile_loop:
	cmp rbx,rsi
	jae .move_explosions
	cmp byte [rbx+MISSILE.Active],FALSE
	je .missile_next
	mov eax,[rbx+MISSILE.DY]
	add [rbx+MISSILE.Y],eax
	cmp dword [rbx+MISSILE.Y],390
	jl .missile_next
	mov byte [rbx+MISSILE.Active],FALSE
	mov eax,[rbx+MISSILE.X]
	lea rdi,[launchers]
	lea r12,[launchers+sizeof.LAUNCHER*LAUNCHERS]
.launcher_hit:
	cmp rdi,r12
	jae .building_hit
	cmp byte [rdi+LAUNCHER.Active],FALSE
	je .launcher_next
	mov ecx,[rdi+LAUNCHER.X]
	sub ecx,35
	cmp eax,ecx
	jl .launcher_next
	mov ecx,[rdi+LAUNCHER.X]
	add ecx,35
	cmp eax,ecx
	jg .launcher_next
	mov byte [rdi+LAUNCHER.Active],FALSE
	dec dword [launchersLeft]
	cmp dword [launchersLeft],0
	jne .missile_next
	mov byte [gameOver],TRUE
	jmp .missile_next
.launcher_next:
	add rdi,sizeof.LAUNCHER
	jmp .launcher_hit
.building_hit:
	mov eax,[rbx+MISSILE.X]
	sub eax,110
	cmp eax,0
	jl .missile_next
	mov ecx,95
	xor edx,edx
	div ecx
	cmp eax,BUILDINGS
	jge .missile_next
	cmp byte [buildingActive+rax],FALSE
	je .missile_next
	mov byte [buildingActive+rax],FALSE
	dec dword [buildingsLeft]
	cmp dword [buildingsLeft],0
	jne .missile_next
	mov byte [gameOver],TRUE
.missile_next:
	add rbx,sizeof.MISSILE
	jmp .missile_loop

.move_explosions:
	lea rbx,[explosions]
	lea rsi,[explosions+sizeof.EXPLOSION*MAX_EXPLOSIONS]
.expl_loop:
	cmp rbx,rsi
	jae .hit_test
	cmp byte [rbx+EXPLOSION.Active],FALSE
	je .expl_next
	add dword [rbx+EXPLOSION.Radius],2
	cvtsi2ss xmm0,dword [rbx+EXPLOSION.Radius]
	movss [rbx+EXPLOSION.RadiusF],xmm0
	cmp dword [rbx+EXPLOSION.Radius],45
	jle .expl_next
	mov byte [rbx+EXPLOSION.Active],FALSE
.expl_next:
	add rbx,sizeof.EXPLOSION
	jmp .expl_loop

.hit_test:
	lea rbx,[explosions]
	lea rdi,[explosions+sizeof.EXPLOSION*MAX_EXPLOSIONS]
.outer:
	cmp rbx,rdi
	jae .done
	cmp byte [rbx+EXPLOSION.Active],FALSE
	je .outer_next
	lea rsi,[missiles]
	lea r12,[missiles+sizeof.MISSILE*MAX_MISSILES]
.inner:
	cmp rsi,r12
	jae .outer_next
	cmp byte [rsi+MISSILE.Active],FALSE
	je .inner_next
	mov eax,[rsi+MISSILE.X]
	sub eax,[rbx+EXPLOSION.X]
	mov edx,[rbx+EXPLOSION.Radius]
	neg edx
	cmp eax,edx
	jl .inner_next
	mov edx,[rbx+EXPLOSION.Radius]
	cmp eax,edx
	jg .inner_next
	mov eax,[rsi+MISSILE.Y]
	sub eax,[rbx+EXPLOSION.Y]
	mov edx,[rbx+EXPLOSION.Radius]
	neg edx
	cmp eax,edx
	jl .inner_next
	mov edx,[rbx+EXPLOSION.Radius]
	cmp eax,edx
	jg .inner_next
	mov byte [rsi+MISSILE.Active],FALSE
	add dword [score],100
	mov eax,[rsi+MISSILE.X]
	mov edx,[rsi+MISSILE.Y]
	fastcall SpawnExplosion
.inner_next:
	add rsi,sizeof.MISSILE
	jmp .inner
.outer_next:
	add rbx,sizeof.EXPLOSION
	jmp .outer
.done:
	ret

endp

proc DrawGame uses rbx rsi
	BeginDrawing
	ClearBackground RAYWHITE
	cmp byte [gameStarted],TRUE
	je .help_done
	DrawText 'LEFT CLICK intercept  P pause  R restart', 20, 20, 20, DARKGRAY
.help_done:
	TextFormat 'SCORE %04i', [score]
	DrawText rax, 20, 50, 20, GRAY
	lea rbx,[launchers]
	lea rsi,[launchers+sizeof.LAUNCHER*LAUNCHERS]
.draw_launchers:
	cmp rbx,rsi
	jae .draw_buildings_start
	cmp byte [rbx+LAUNCHER.Active],FALSE
	je .l_next
	mov eax,[rbx+LAUNCHER.X]
	sub eax,25
	DrawRectangle eax, 380, 50, 25, BLUE
.l_next:
	add rbx,sizeof.LAUNCHER
	jmp .draw_launchers
.draw_buildings_start:
	xor ebx,ebx
.draw_buildings:
	cmp ebx,BUILDINGS
	jge .draw_missiles
	cmp byte [buildingActive+rbx],FALSE
	je .b_next
	mov eax,ebx
	imul eax,95
	add eax,120
	DrawRectangle eax, 395, 50, 35, DARKGREEN
.b_next:
	inc ebx
	jmp .draw_buildings
.draw_missiles:
	lea rbx,[missiles]
	lea rsi,[missiles+sizeof.MISSILE*MAX_MISSILES]
.m_loop:
	cmp rbx,rsi
	jae .draw_interceptors
	cmp byte [rbx+MISSILE.Active],FALSE
	je .m_next
	DrawLine [rbx+MISSILE.X], 45, [rbx+MISSILE.X], [rbx+MISSILE.Y], RED
	DrawCircle [rbx+MISSILE.X], [rbx+MISSILE.Y], float dword 4.0, MAROON
.m_next:
	add rbx,sizeof.MISSILE
	jmp .m_loop
.draw_interceptors:
	lea rbx,[interceptors]
	lea rsi,[interceptors+sizeof.INTERCEPTOR*MAX_INTERCEPTORS]
.i_loop:
	cmp rbx,rsi
	jae .draw_explosions
	cmp byte [rbx+INTERCEPTOR.Active],FALSE
	je .i_next
	DrawLine [rbx+INTERCEPTOR.OriginX], [rbx+INTERCEPTOR.OriginY], [rbx+INTERCEPTOR.X], [rbx+INTERCEPTOR.Y], GREEN
	DrawCircle [rbx+INTERCEPTOR.X], [rbx+INTERCEPTOR.Y], float dword 3.0, BLUE
.i_next:
	add rbx,sizeof.INTERCEPTOR
	jmp .i_loop
.draw_explosions:
	lea rbx,[explosions]
	lea rsi,[explosions+sizeof.EXPLOSION*MAX_EXPLOSIONS]
.e_loop:
	cmp rbx,rsi
	jae .messages
	cmp byte [rbx+EXPLOSION.Active],FALSE
	je .e_next
	DrawCircleLines [rbx+EXPLOSION.X], [rbx+EXPLOSION.Y], float dword [rbx+EXPLOSION.RadiusF], ORANGE
.e_next:
	add rbx,sizeof.EXPLOSION
	jmp .e_loop
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
	DrawText 'CITIES LOST - PRESS R', 285, 210, 20, MAROON
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
