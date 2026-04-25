; raylib type aliases — generated
;
; Each non-pointer alias gets:
;   1. A `define` so expressions referring to the alias resolve
;      to the underlying struct name (e.g. in field types).
;   2. A labeled CALM `(instance) AliasName values&` that
;      delegates to the underlying struct's instantiator. fasmg
;      doesn't follow `define` substitutions when looking up an
;      *instruction* name, so without this CALM the line
;      `tex Texture2D` would fail to recognize Texture2D as a
;      struct constructor.

define Quaternion Vector4
calminstruction (instance) Quaternion values&
	local sname
	arrange sname, =Vector4
	call struct?.instantiate, instance, sname, values
end calminstruction

define Texture2D Texture
calminstruction (instance) Texture2D values&
	local sname
	arrange sname, =Texture
	call struct?.instantiate, instance, sname, values
end calminstruction

define TextureCubemap Texture
calminstruction (instance) TextureCubemap values&
	local sname
	arrange sname, =Texture
	call struct?.instantiate, instance, sname, values
end calminstruction

define RenderTexture2D RenderTexture
calminstruction (instance) RenderTexture2D values&
	local sname
	arrange sname, =RenderTexture
	call struct?.instantiate, instance, sname, values
end calminstruction

define Camera Camera3D
calminstruction (instance) Camera values&
	local sname
	arrange sname, =Camera3D
	call struct?.instantiate, instance, sname, values
end calminstruction

; Anim pose, an array of Transform[]
struct ModelAnimPose
  ptr dq ?
ends
