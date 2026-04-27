; Small shared helpers for the fasmg/fasm2 raylib classics ports.

TRUE = 1
FALSE = 0

macro ClampData mem*, low*, high*
	local above_low, done
	cmp [mem], low
	jge above_low
	mov [mem], low
	jmp done
above_low:
	cmp [mem], high
	jle done
	mov [mem], high
done:
end macro

proc PointInBox x,y,left,top,right,bottom
	; x/y/left/top in ecx/edx/r8d/r9d, right/bottom on the call stack.
	cmp ecx,r8d
	jl .miss
	cmp ecx,dword [right]
	jg .miss
	cmp edx,r9d
	jl .miss
	cmp edx,dword [bottom]
	jg .miss
	mov eax,TRUE
	ret
.miss:
	xor eax,eax
	ret

endp

proc RectsOverlap x1,y1,w1,h1,x2,y2,w2,h2
	; x1/y1/w1/h1 in ecx/edx/r8d/r9d, second rect on the call stack.
	mov eax,ecx
	add eax,r8d
	cmp eax,dword [x2]
	jl .miss
	mov eax,dword [x2]
	add eax,dword [w2]
	cmp ecx,eax
	jg .miss
	mov eax,edx
	add eax,r9d
	cmp eax,dword [y2]
	jl .miss
	mov eax,dword [y2]
	add eax,dword [h2]
	cmp edx,eax
	jg .miss
	mov eax,TRUE
	ret
.miss:
	xor eax,eax
	ret

endp

proc CircleRectOverlap x,y,r,left,top,width,height
	; x/y/r/left in ecx/edx/r8d/r9d, rect top/width/height on the call stack.
	mov eax,ecx
	cmp eax,r9d
	jge .closest_x_above_left
	mov eax,r9d
	jmp .closest_y
.closest_x_above_left:
	mov r10d,r9d
	add r10d,dword [width]
	cmp eax,r10d
	jle .closest_y
	mov eax,r10d
.closest_y:
	sub ecx,eax
	imul ecx,ecx

	mov eax,edx
	cmp eax,dword [top]
	jge .closest_y_above_top
	mov eax,dword [top]
	jmp .distance
.closest_y_above_top:
	mov r10d,dword [top]
	add r10d,dword [height]
	cmp eax,r10d
	jle .distance
	mov eax,r10d
.distance:
	sub edx,eax
	imul edx,edx
	add ecx,edx
	mov eax,r8d
	imul eax,eax
	cmp ecx,eax
	jg .miss
	mov eax,TRUE
	ret
.miss:
	xor eax,eax
	ret

endp
