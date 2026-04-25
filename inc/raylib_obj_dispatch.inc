; raylib_obj_dispatch.inc — OBJ-mode RLAPI dispatcher (generated)
;
; In COFF/OBJ mode the linker resolves the symbol so we use a *direct*
; call (`fastcall` macro from proc64.inc, which expands to `call proc`,
; not `call [proc]`). The extrn declarations in raylib_extrn.inc make
; `RLAPI.<FuncName>` link to raylib.lib's `<FuncName>` symbol.

calminstruction RLAPI fname*, args&
	local cmd
	match , args
	jyes _no_args
	arrange cmd, =fastcall =RLAPI.fname, args
	assemble cmd
	exit
    _no_args:
	arrange cmd, =fastcall =RLAPI.fname
	assemble cmd
end calminstruction
