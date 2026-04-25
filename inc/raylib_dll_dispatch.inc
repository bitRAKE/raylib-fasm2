; raylib_dll_dispatch.inc — DLL-mode RLAPI dispatcher (generated)
;
; The wrappers in raylib_api.inc all funnel through `call RLAPI, fname,
; args`. In DLL mode `RLAPI.<FuncName>` is the IAT slot built by
; raylib_imports.inc (a 64-bit pointer to the function), and we use
; `invoke` (which expands to `mov rax,[RLAPI.Func]; call rax`).

calminstruction RLAPI fname*, args&
	local cmd
	match , args
	jyes _no_args
	arrange cmd, =invoke =RLAPI.fname, args
	assemble cmd
	exit
    _no_args:
	arrange cmd, =invoke =RLAPI.fname
	assemble cmd
end calminstruction
