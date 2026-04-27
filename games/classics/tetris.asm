; raylib-games classics: tetris, fasmg/fasm2 PE64 port.

include 'raylib_pe64.inc'

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 450
GRID_W = 12
GRID_H = 20
CELL = 20
GRID_COUNT = GRID_W*GRID_H
GRID_EMPTY = 0
GRID_FULL = 1
GRID_FADING = 2
GRID_BLOCK = 3
FADING_TIME = 33

section '.data' data readable writeable

GLOBSTR.here ; constant string payload

	align 4

gameOver db FALSE
pauseFlag db FALSE
gameStarted db FALSE
lineToDelete db FALSE
pieceX dd 5
pieceY dd 0
pieceKind dd 0
nextKind dd 0
pieceRot dd 0
testX dd 0
testY dd 0
testRot dd 0
dropCounter dd 0
dropSpeed dd 28
linesCleared dd 0
level dd 1
fadeLineCounter dd 0
fadingColor dd ?
grid db GRID_COUNT dup ?

pieceMasks dw \
	00F0h, 2222h, 00F0h, 2222h, \
	0066h, 0066h, 0066h, 0066h, \
	0072h, 0262h, 0270h, 0232h, \
	0036h, 0462h, 0036h, 0462h, \
	0063h, 0264h, 0063h, 0264h, \
	0071h, 0226h, 0470h, 0322h, \
	0074h, 0622h, 0170h, 0223h

section '.text' code readable executable

include 'common.inc'

fastcall.frame = 0 ; track maximum call space and reserve it once in start

start:
	sub rsp,.space+8

	InitWindow SCREEN_WIDTH, SCREEN_HEIGHT, 'classic game: tetris'
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

proc GridIndex
	; in eax=x, edx=y, out eax=index
	imul edx,GRID_W
	add eax,edx
	ret

endp

proc GetPieceMask
	; in eax=kind, ecx=rotation, out eax=16-bit 4x4 mask
	and ecx,3
	imul eax,4
	add eax,ecx
	movzx eax,word [pieceMasks+rax*2]
	ret

endp

proc InitGame uses rbx
	mov byte [gameOver],FALSE
	mov byte [pauseFlag],FALSE
	mov byte [gameStarted],FALSE
	mov byte [lineToDelete],FALSE
	mov dword [dropCounter],0
	mov dword [linesCleared],0
	mov dword [level],1
	mov dword [dropSpeed],28
	mov dword [fadeLineCounter],0
	mov dword [fadingColor],RayLib.GRAY
	xor ebx,ebx
.clear:
	cmp ebx,GRID_COUNT
	jge .spawn
	mov eax,ebx
	xor edx,edx
	mov ecx,GRID_W
	div ecx
	cmp eax,GRID_H-1
	je .set_block
	cmp edx,0
	je .set_block
	cmp edx,GRID_W-1
	je .set_block
	mov byte [grid+rbx],GRID_EMPTY
	jmp .next_cell
.set_block:
	mov byte [grid+rbx],GRID_BLOCK
.next_cell:
	inc ebx
	jmp .clear
.spawn:
	GetRandomValue 0,6
	mov [nextKind],eax
	fastcall SpawnPiece
	ret

endp

proc SpawnPiece
	mov dword [pieceX],4
	mov dword [pieceY],0
	mov dword [pieceRot],0
	mov eax,[nextKind]
	mov [pieceKind],eax
	GetRandomValue 0,6
	mov [nextKind],eax
	mov eax,[pieceX]
	mov [testX],eax
	mov eax,[pieceY]
	mov [testY],eax
	mov eax,[pieceRot]
	mov [testRot],eax
	fastcall CanPlace
	test eax,eax
	jnz .done
	mov byte [gameOver],TRUE
.done:
	ret

endp

proc UpdateLevel
	mov eax,[linesCleared]
	xor edx,edx
	mov ecx,5
	div ecx
	inc eax
	mov [level],eax
	dec eax
	imul eax,3
	mov ecx,28
	sub ecx,eax
	cmp ecx,6
	jge .store
	mov ecx,6
.store:
	mov [dropSpeed],ecx
	ret

endp

proc CanPlace uses rbx rsi rdi
	mov eax,[pieceKind]
	mov ecx,[testRot]
	fastcall GetPieceMask
	mov ebx,eax
	xor esi,esi
.loop:
	cmp esi,16
	jge .yes
	bt ebx,esi
	jnc .next
	mov eax,esi
	and eax,3
	add eax,[testX]
	cmp eax,0
	jl .no
	cmp eax,GRID_W
	jge .no
	mov edi,eax
	mov eax,esi
	shr eax,2
	add eax,[testY]
	cmp eax,0
	jl .no
	cmp eax,GRID_H
	jge .no
	mov edx,eax
	mov eax,edi
	fastcall GridIndex
	cmp byte [grid+rax],GRID_EMPTY
	jne .no
.next:
	inc esi
	jmp .loop
.yes:
	mov eax,TRUE
	ret
.no:
	xor eax,eax
	ret

endp

proc CanMoveDown
	mov eax,[pieceX]
	mov [testX],eax
	mov eax,[pieceY]
	inc eax
	mov [testY],eax
	mov eax,[pieceRot]
	mov [testRot],eax
	fastcall CanPlace
	ret

endp

proc CanMoveSide
	; in ecx delta, out eax bool
	mov eax,[pieceX]
	add eax,ecx
	mov [testX],eax
	mov eax,[pieceY]
	mov [testY],eax
	mov eax,[pieceX]
	mov eax,[pieceRot]
	mov [testRot],eax
	fastcall CanPlace
	ret

endp

proc CanRotate
	mov eax,[pieceX]
	mov [testX],eax
	mov eax,[pieceY]
	mov [testY],eax
	mov eax,[pieceRot]
	inc eax
	and eax,3
	mov [testRot],eax
	fastcall CanPlace
	ret

endp

proc PlacePiece uses rbx rsi rdi
	mov eax,[pieceKind]
	mov ecx,[pieceRot]
	fastcall GetPieceMask
	mov ebx,eax
	xor esi,esi
.loop:
	cmp esi,16
	jge .placed
	bt ebx,esi
	jnc .next
	mov eax,esi
	and eax,3
	add eax,[pieceX]
	mov edi,eax
	mov eax,esi
	shr eax,2
	add eax,[pieceY]
	mov edx,eax
	mov eax,edi
	fastcall GridIndex
	mov byte [grid+rax],GRID_FULL
.next:
	inc esi
	jmp .loop
.placed:
	fastcall CheckCompletion
	cmp byte [lineToDelete],FALSE
	jne .done
	fastcall SpawnPiece
.done:
	ret

endp

proc DrawPiece uses rbx rsi rdi
	mov eax,[pieceKind]
	mov ecx,[pieceRot]
	fastcall GetPieceMask
	mov ebx,eax
	xor esi,esi
.loop:
	cmp esi,16
	jge .done
	bt ebx,esi
	jnc .next
	mov eax,esi
	and eax,3
	add eax,[pieceX]
	imul eax,CELL
	add eax,280
	mov edi,eax
	mov eax,esi
	shr eax,2
	add eax,[pieceY]
	imul eax,CELL
	add eax,30
	DrawRectangle edi, eax, CELL-1, CELL-1, SKYBLUE
.next:
	inc esi
	jmp .loop
.done:
	ret

endp

proc CheckCompletion uses rbx rsi rdi
	mov byte [lineToDelete],FALSE
	mov ebx,GRID_H-2
.row_loop:
	cmp ebx,0
	jl .done
	mov esi,1
	mov edi,TRUE
.check_cols:
	cmp esi,GRID_W-1
	jge .row_full
	mov eax,esi
	mov edx,ebx
	fastcall GridIndex
	cmp byte [grid+rax],GRID_FULL
	je .col_next
	mov edi,FALSE
.col_next:
	inc esi
	jmp .check_cols
.row_full:
	cmp edi,TRUE
	jne .prev_row
	mov byte [lineToDelete],TRUE
	mov esi,1
.fade_cols:
	cmp esi,GRID_W-1
	jge .prev_row
	mov eax,esi
	mov edx,ebx
	fastcall GridIndex
	mov byte [grid+rax],GRID_FADING
	inc esi
	jmp .fade_cols
.prev_row:
	dec ebx
	jmp .row_loop
.done:
	ret

endp

proc DeleteCompleteLines uses rbx rsi rdi
	mov ebx,GRID_H-2
.row_loop:
	cmp ebx,0
	jl .done
	mov esi,1
	mov edi,FALSE
.find_fading:
	cmp esi,GRID_W-1
	jge .row_done
	mov eax,esi
	mov edx,ebx
	fastcall GridIndex
	cmp byte [grid+rax],GRID_FADING
	jne .find_next
	mov edi,TRUE
	jmp .row_done
.find_next:
	inc esi
	jmp .find_fading
.row_done:
	cmp edi,TRUE
	jne .prev_row
	inc dword [linesCleared]
	fastcall UpdateLevel
	mov edx,ebx
.shift_rows:
	cmp edx,0
	jle .clear_top
	mov esi,1
.shift_cols:
	cmp esi,GRID_W-1
	jge .shift_next_row
	mov eax,esi
	push rdx
	fastcall GridIndex
	mov ecx,eax
	pop rdx
	dec edx
	mov eax,esi
	push rcx
	push rdx
	fastcall GridIndex
	pop rdx
	pop rcx
	mov al,[grid+rax]
	mov [grid+rcx],al
	inc edx
	inc esi
	jmp .shift_cols
.shift_next_row:
	dec edx
	jmp .shift_rows
.clear_top:
	mov esi,1
.top_cols:
	cmp esi,GRID_W-1
	jge .row_loop
	mov byte [grid+rsi],GRID_EMPTY
	inc esi
	jmp .top_cols
.prev_row:
	dec ebx
	jmp .row_loop
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
	cmp byte [lineToDelete],FALSE
	je .piece_update

	inc dword [fadeLineCounter]
	mov eax,[fadeLineCounter]
	and eax,7
	cmp eax,4
	jge .fade_gray
	mov dword [fadingColor],RayLib.MAROON
	jmp .fade_color_done
.fade_gray:
	mov dword [fadingColor],RayLib.GRAY
.fade_color_done:
	cmp dword [fadeLineCounter],FADING_TIME
	jl .done
	fastcall DeleteCompleteLines
	mov dword [fadeLineCounter],0
	mov byte [lineToDelete],FALSE
	fastcall SpawnPiece
	jmp .done

.piece_update:
	IsKeyPressed KEY_LEFT
	test al,al
	jz .right
	mov ecx,-1
	fastcall CanMoveSide
	test eax,eax
	jz .right
	dec dword [pieceX]
.right:
	IsKeyPressed KEY_RIGHT
	test al,al
	jz .rotate
	mov ecx,1
	fastcall CanMoveSide
	test eax,eax
	jz .rotate
	inc dword [pieceX]
.rotate:
	IsKeyPressed KEY_UP
	test al,al
	jz .manual_down
	fastcall CanRotate
	test eax,eax
	jz .manual_down
	inc dword [pieceRot]
	and dword [pieceRot],3
.manual_down:
	IsKeyDown KEY_DOWN
	test al,al
	jz .gravity
	add dword [dropCounter],6
.gravity:
	inc dword [dropCounter]
	mov eax,[dropCounter]
	cmp eax,[dropSpeed]
	jl .done
	mov dword [dropCounter],0
	fastcall CanMoveDown
	test eax,eax
	jz .place
	inc dword [pieceY]
	jmp .done
.place:
	fastcall PlacePiece
.done:
	ret

endp

proc DrawNextPiece uses rbx rsi rdi
	mov eax,[nextKind]
	xor ecx,ecx
	fastcall GetPieceMask
	mov ebx,eax
	xor esi,esi
.loop:
	cmp esi,16
	jge .done
	bt ebx,esi
	jnc .next
	mov eax,esi
	and eax,3
	imul eax,CELL
	add eax,555
	mov edi,eax
	mov eax,esi
	shr eax,2
	imul eax,CELL
	add eax,135
	DrawRectangle edi, eax, CELL-1, CELL-1, SKYBLUE
.next:
	inc esi
	jmp .loop
.done:
	ret

endp

proc DrawGame uses rbx
	BeginDrawing
	ClearBackground RAYWHITE
	cmp byte [gameStarted],TRUE
	je .help_done
	DrawText 'LEFT/RIGHT move  UP rotate  DOWN drop  P pause  R restart', 20, 20, 20, DARKGRAY
.help_done:
	xor ebx,ebx
.draw_loop:
	cmp ebx,GRID_COUNT
	jge .draw_piece
	cmp byte [grid+rbx],GRID_EMPTY
	je .next
	mov eax,ebx
	xor edx,edx
	mov ecx,GRID_W
	div ecx
	; eax=row, edx=col
	mov r8d,edx
	imul r8d,CELL
	add r8d,280
	mov r9d,eax
	imul r9d,CELL
	add r9d,30
	cmp byte [grid+rbx],GRID_FADING
	jne .draw_full
	DrawRectangle r8d, r9d, CELL-1, CELL-1, [fadingColor]
	jmp .next
.draw_full:
	cmp byte [grid+rbx],GRID_BLOCK
	jne .draw_locked
	DrawRectangle r8d, r9d, CELL-1, CELL-1, LIGHTGRAY
	jmp .next
.draw_locked:
	DrawRectangle r8d, r9d, CELL-1, CELL-1, DARKBLUE
.next:
	inc ebx
	jmp .draw_loop
.draw_piece:
	cmp byte [lineToDelete],FALSE
	jne .after_piece
	fastcall DrawPiece
.after_piece:
	DrawRectangleLines 280, 30, GRID_W*CELL, GRID_H*CELL, GRAY
	TextFormat 'LINES: %04i', [linesCleared]
	DrawText rax, 550, 80, 20, GRAY
	TextFormat 'LEVEL: %02i', [level]
	DrawText rax, 550, 105, 20, GRAY
	DrawText 'NEXT', 550, 135, 20, GRAY
	fastcall DrawNextPiece
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
	DrawText 'STACKED OUT - PRESS R', 285, 210, 20, MAROON
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
