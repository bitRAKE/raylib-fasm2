; fasm2/fasmg raylib backend selector implementation.
;
; Prefer the public support-layer includes:
;
;   raylib_pe64.inc
;   raylib_pe32.inc
;   raylib_coff64.inc
;   raylib_coff32.inc
;
; They select the same backend flags used here without requiring user code to
; define them manually. This file remains as the shared implementation layer.
;
; The user-facing raylib calls are identical in both modes:
;
;   InitWindow 800, 450, title
;   ClearBackground RAYWHITE
;
; Include path requirements when using fasm2.cmd:
;
;   set "include=%cd%\include;%include%"

if defined RAYLIB_TARGET_32
	include 'win32a.inc'
else
	include 'win64a.inc'
end if

if defined RAYLIB_LINK_COFF
	if defined RAYLIB_TARGET_32
		format MS COFF
	else
		format MS64 COFF
	end if
else
	if defined RAYLIB_TARGET_32
		format PE GUI 4.0
	else
		format PE64 GUI 5.0
	end if
	entry start
end if

if defined RAYLIB_LINK_COFF

	if defined RAYLIB_TARGET_32
		include 'raylib_extrn_coff32.inc'
		calminstruction RLAPI function*, arguments&
			local line
			match , arguments
			jyes noargs
			arrange line, =ccall =RayLib=.=API.function, arguments
			assemble line
			exit
		noargs:
			arrange line, =ccall =RayLib=.=API.function
			assemble line
		end calminstruction
	else
		include 'raylib_extrn_coff64.inc'
		calminstruction RLAPI function*, arguments&
			local line
			match , arguments
			jyes noargs
			arrange line, =fastcall =RayLib=.=API.function, arguments
			assemble line
			exit
		noargs:
			arrange line, =fastcall =RayLib=.=API.function
			assemble line
		end calminstruction
	end if

else

	if defined RAYLIB_TARGET_32
		calminstruction RLAPI function*, arguments&
			local line
			match , arguments
			jyes noargs
			arrange line, =ccall [=RayLib=.=API.function], arguments
			assemble line
			exit
		noargs:
			arrange line, =ccall [=RayLib=.=API.function]
			assemble line
		end calminstruction
	else
		calminstruction RLAPI function*, arguments&
			local line
			match , arguments
			jyes noargs
			arrange line, =fastcall [=RayLib=.=API.function], arguments
			assemble line
			exit
		noargs:
			arrange line, =fastcall [=RayLib=.=API.function]
			assemble line
		end calminstruction
	end if

end if

include 'raylib.inc'


; Using the static RSP frees up the RBP register.
; (No downside because dynamic local space isn't being implemented.)
prologue@proc	equ static_rsp_prologue
epilogue@proc	equ static_rsp_epilogue
close@proc	equ static_rsp_close procname


include 'globstr.inc' ; general constant string support
GLOBSTR.reuse := 1

if defined RAYLIB_TARGET_32
	; For 32-bit case it would be the "stdcall?.push_string" macro, provided here for completness:
	macro stdcall?.push_string value&
		local data
		data GLOBSTR value,0
		push data
	end macro
else
	; Replacing the "fastcall?.inline_string" macro changes how the string arguments to "fastcall" and "invoke" are handled:
	macro fastcall?.inline_string var
		local data
		data GLOBSTR var,0
		redefine var data
	end macro
end if


