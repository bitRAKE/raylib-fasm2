; raylib enums — generated
;
; Members live under `RayLib.<EnumName>.<MEMBER>`. Wrappers `transform`
; their typed parameters against `RayLib.<EnumName>` so callers can
; write the *short* name (KEY_ESCAPE, FLAG_VSYNC_HINT) without
; polluting the global namespace.
;
; The `define <Name> <Name>` anchors are required — fasmg's `transform`
; with a namespace argument needs the namespace path to resolve to a
; real symbol, not just a parent of `define X.Y` children. Without these
; anchors `transform val, RayLib.ConfigFlags` silently does nothing.

define RayLib RayLib

namespace RayLib

  ; System/Window config flags
  define ConfigFlags ConfigFlags
  define ConfigFlags.FLAG_VSYNC_HINT                64  ; Set to try enabling V-Sync on GPU
  define ConfigFlags.FLAG_FULLSCREEN_MODE           2  ; Set to run program in fullscreen
  define ConfigFlags.FLAG_WINDOW_RESIZABLE          4  ; Set to allow resizable window
  define ConfigFlags.FLAG_WINDOW_UNDECORATED        8  ; Set to disable window decoration (frame and buttons)
  define ConfigFlags.FLAG_WINDOW_HIDDEN             128  ; Set to hide window
  define ConfigFlags.FLAG_WINDOW_MINIMIZED          512  ; Set to minimize window (iconify)
  define ConfigFlags.FLAG_WINDOW_MAXIMIZED          1024  ; Set to maximize window (expanded to monitor)
  define ConfigFlags.FLAG_WINDOW_UNFOCUSED          2048  ; Set to window non focused
  define ConfigFlags.FLAG_WINDOW_TOPMOST            4096  ; Set to window always on top
  define ConfigFlags.FLAG_WINDOW_ALWAYS_RUN         256  ; Set to allow windows running while minimized
  define ConfigFlags.FLAG_WINDOW_TRANSPARENT        16  ; Set to allow transparent framebuffer
  define ConfigFlags.FLAG_WINDOW_HIGHDPI            8192  ; Set to support HighDPI
  define ConfigFlags.FLAG_WINDOW_MOUSE_PASSTHROUGH  16384  ; Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
  define ConfigFlags.FLAG_BORDERLESS_WINDOWED_MODE  32768  ; Set to run program in borderless windowed mode
  define ConfigFlags.FLAG_MSAA_4X_HINT              32  ; Set to try enabling MSAA 4X
  define ConfigFlags.FLAG_INTERLACED_HINT           65536  ; Set to try enabling interlaced video format (for V3D)

  ; Trace log level
  define TraceLogLevel TraceLogLevel
  define TraceLogLevel.LOG_ALL      0  ; Display all logs
  define TraceLogLevel.LOG_TRACE    1  ; Trace logging, intended for internal use only
  define TraceLogLevel.LOG_DEBUG    2  ; Debug logging, used for internal debugging, it should be disabled on release builds
  define TraceLogLevel.LOG_INFO     3  ; Info logging, used for program execution info
  define TraceLogLevel.LOG_WARNING  4  ; Warning logging, used on recoverable failures
  define TraceLogLevel.LOG_ERROR    5  ; Error logging, used on unrecoverable failures
  define TraceLogLevel.LOG_FATAL    6  ; Fatal logging, used to abort program: exit(EXIT_FAILURE)
  define TraceLogLevel.LOG_NONE     7  ; Disable logging

  ; Keyboard keys (US keyboard layout)
  define KeyboardKey KeyboardKey
  define KeyboardKey.KEY_NULL           0  ; Key: NULL, used for no key pressed
  define KeyboardKey.KEY_APOSTROPHE     39  ; Key: '
  define KeyboardKey.KEY_COMMA          44  ; Key: ,
  define KeyboardKey.KEY_MINUS          45  ; Key: -
  define KeyboardKey.KEY_PERIOD         46  ; Key: .
  define KeyboardKey.KEY_SLASH          47  ; Key: /
  define KeyboardKey.KEY_ZERO           48  ; Key: 0
  define KeyboardKey.KEY_ONE            49  ; Key: 1
  define KeyboardKey.KEY_TWO            50  ; Key: 2
  define KeyboardKey.KEY_THREE          51  ; Key: 3
  define KeyboardKey.KEY_FOUR           52  ; Key: 4
  define KeyboardKey.KEY_FIVE           53  ; Key: 5
  define KeyboardKey.KEY_SIX            54  ; Key: 6
  define KeyboardKey.KEY_SEVEN          55  ; Key: 7
  define KeyboardKey.KEY_EIGHT          56  ; Key: 8
  define KeyboardKey.KEY_NINE           57  ; Key: 9
  define KeyboardKey.KEY_SEMICOLON      59  ; Key: ;
  define KeyboardKey.KEY_EQUAL          61  ; Key: =
  define KeyboardKey.KEY_A              65  ; Key: A | a
  define KeyboardKey.KEY_B              66  ; Key: B | b
  define KeyboardKey.KEY_C              67  ; Key: C | c
  define KeyboardKey.KEY_D              68  ; Key: D | d
  define KeyboardKey.KEY_E              69  ; Key: E | e
  define KeyboardKey.KEY_F              70  ; Key: F | f
  define KeyboardKey.KEY_G              71  ; Key: G | g
  define KeyboardKey.KEY_H              72  ; Key: H | h
  define KeyboardKey.KEY_I              73  ; Key: I | i
  define KeyboardKey.KEY_J              74  ; Key: J | j
  define KeyboardKey.KEY_K              75  ; Key: K | k
  define KeyboardKey.KEY_L              76  ; Key: L | l
  define KeyboardKey.KEY_M              77  ; Key: M | m
  define KeyboardKey.KEY_N              78  ; Key: N | n
  define KeyboardKey.KEY_O              79  ; Key: O | o
  define KeyboardKey.KEY_P              80  ; Key: P | p
  define KeyboardKey.KEY_Q              81  ; Key: Q | q
  define KeyboardKey.KEY_R              82  ; Key: R | r
  define KeyboardKey.KEY_S              83  ; Key: S | s
  define KeyboardKey.KEY_T              84  ; Key: T | t
  define KeyboardKey.KEY_U              85  ; Key: U | u
  define KeyboardKey.KEY_V              86  ; Key: V | v
  define KeyboardKey.KEY_W              87  ; Key: W | w
  define KeyboardKey.KEY_X              88  ; Key: X | x
  define KeyboardKey.KEY_Y              89  ; Key: Y | y
  define KeyboardKey.KEY_Z              90  ; Key: Z | z
  define KeyboardKey.KEY_LEFT_BRACKET   91  ; Key: [
  define KeyboardKey.KEY_BACKSLASH      92  ; Key: '\'
  define KeyboardKey.KEY_RIGHT_BRACKET  93  ; Key: ]
  define KeyboardKey.KEY_GRAVE          96  ; Key: `
  define KeyboardKey.KEY_SPACE          32  ; Key: Space
  define KeyboardKey.KEY_ESCAPE         256  ; Key: Esc
  define KeyboardKey.KEY_ENTER          257  ; Key: Enter
  define KeyboardKey.KEY_TAB            258  ; Key: Tab
  define KeyboardKey.KEY_BACKSPACE      259  ; Key: Backspace
  define KeyboardKey.KEY_INSERT         260  ; Key: Ins
  define KeyboardKey.KEY_DELETE         261  ; Key: Del
  define KeyboardKey.KEY_RIGHT          262  ; Key: Cursor right
  define KeyboardKey.KEY_LEFT           263  ; Key: Cursor left
  define KeyboardKey.KEY_DOWN           264  ; Key: Cursor down
  define KeyboardKey.KEY_UP             265  ; Key: Cursor up
  define KeyboardKey.KEY_PAGE_UP        266  ; Key: Page up
  define KeyboardKey.KEY_PAGE_DOWN      267  ; Key: Page down
  define KeyboardKey.KEY_HOME           268  ; Key: Home
  define KeyboardKey.KEY_END            269  ; Key: End
  define KeyboardKey.KEY_CAPS_LOCK      280  ; Key: Caps lock
  define KeyboardKey.KEY_SCROLL_LOCK    281  ; Key: Scroll down
  define KeyboardKey.KEY_NUM_LOCK       282  ; Key: Num lock
  define KeyboardKey.KEY_PRINT_SCREEN   283  ; Key: Print screen
  define KeyboardKey.KEY_PAUSE          284  ; Key: Pause
  define KeyboardKey.KEY_F1             290  ; Key: F1
  define KeyboardKey.KEY_F2             291  ; Key: F2
  define KeyboardKey.KEY_F3             292  ; Key: F3
  define KeyboardKey.KEY_F4             293  ; Key: F4
  define KeyboardKey.KEY_F5             294  ; Key: F5
  define KeyboardKey.KEY_F6             295  ; Key: F6
  define KeyboardKey.KEY_F7             296  ; Key: F7
  define KeyboardKey.KEY_F8             297  ; Key: F8
  define KeyboardKey.KEY_F9             298  ; Key: F9
  define KeyboardKey.KEY_F10            299  ; Key: F10
  define KeyboardKey.KEY_F11            300  ; Key: F11
  define KeyboardKey.KEY_F12            301  ; Key: F12
  define KeyboardKey.KEY_LEFT_SHIFT     340  ; Key: Shift left
  define KeyboardKey.KEY_LEFT_CONTROL   341  ; Key: Control left
  define KeyboardKey.KEY_LEFT_ALT       342  ; Key: Alt left
  define KeyboardKey.KEY_LEFT_SUPER     343  ; Key: Super left
  define KeyboardKey.KEY_RIGHT_SHIFT    344  ; Key: Shift right
  define KeyboardKey.KEY_RIGHT_CONTROL  345  ; Key: Control right
  define KeyboardKey.KEY_RIGHT_ALT      346  ; Key: Alt right
  define KeyboardKey.KEY_RIGHT_SUPER    347  ; Key: Super right
  define KeyboardKey.KEY_KB_MENU        348  ; Key: KB menu
  define KeyboardKey.KEY_KP_0           320  ; Key: Keypad 0
  define KeyboardKey.KEY_KP_1           321  ; Key: Keypad 1
  define KeyboardKey.KEY_KP_2           322  ; Key: Keypad 2
  define KeyboardKey.KEY_KP_3           323  ; Key: Keypad 3
  define KeyboardKey.KEY_KP_4           324  ; Key: Keypad 4
  define KeyboardKey.KEY_KP_5           325  ; Key: Keypad 5
  define KeyboardKey.KEY_KP_6           326  ; Key: Keypad 6
  define KeyboardKey.KEY_KP_7           327  ; Key: Keypad 7
  define KeyboardKey.KEY_KP_8           328  ; Key: Keypad 8
  define KeyboardKey.KEY_KP_9           329  ; Key: Keypad 9
  define KeyboardKey.KEY_KP_DECIMAL     330  ; Key: Keypad .
  define KeyboardKey.KEY_KP_DIVIDE      331  ; Key: Keypad /
  define KeyboardKey.KEY_KP_MULTIPLY    332  ; Key: Keypad *
  define KeyboardKey.KEY_KP_SUBTRACT    333  ; Key: Keypad -
  define KeyboardKey.KEY_KP_ADD         334  ; Key: Keypad +
  define KeyboardKey.KEY_KP_ENTER       335  ; Key: Keypad Enter
  define KeyboardKey.KEY_KP_EQUAL       336  ; Key: Keypad =
  define KeyboardKey.KEY_BACK           4  ; Key: Android back button
  define KeyboardKey.KEY_MENU           5  ; Key: Android menu button
  define KeyboardKey.KEY_VOLUME_UP      24  ; Key: Android volume up button
  define KeyboardKey.KEY_VOLUME_DOWN    25  ; Key: Android volume down button

  ; Mouse buttons
  define MouseButton MouseButton
  define MouseButton.MOUSE_BUTTON_LEFT     0  ; Mouse button left
  define MouseButton.MOUSE_BUTTON_RIGHT    1  ; Mouse button right
  define MouseButton.MOUSE_BUTTON_MIDDLE   2  ; Mouse button middle (pressed wheel)
  define MouseButton.MOUSE_BUTTON_SIDE     3  ; Mouse button side (advanced mouse device)
  define MouseButton.MOUSE_BUTTON_EXTRA    4  ; Mouse button extra (advanced mouse device)
  define MouseButton.MOUSE_BUTTON_FORWARD  5  ; Mouse button forward (advanced mouse device)
  define MouseButton.MOUSE_BUTTON_BACK     6  ; Mouse button back (advanced mouse device)

  ; Mouse cursor
  define MouseCursor MouseCursor
  define MouseCursor.MOUSE_CURSOR_DEFAULT        0  ; Default pointer shape
  define MouseCursor.MOUSE_CURSOR_ARROW          1  ; Arrow shape
  define MouseCursor.MOUSE_CURSOR_IBEAM          2  ; Text writing cursor shape
  define MouseCursor.MOUSE_CURSOR_CROSSHAIR      3  ; Cross shape
  define MouseCursor.MOUSE_CURSOR_POINTING_HAND  4  ; Pointing hand cursor
  define MouseCursor.MOUSE_CURSOR_RESIZE_EW      5  ; Horizontal resize/move arrow shape
  define MouseCursor.MOUSE_CURSOR_RESIZE_NS      6  ; Vertical resize/move arrow shape
  define MouseCursor.MOUSE_CURSOR_RESIZE_NWSE    7  ; Top-left to bottom-right diagonal resize/move arrow shape
  define MouseCursor.MOUSE_CURSOR_RESIZE_NESW    8  ; The top-right to bottom-left diagonal resize/move arrow shape
  define MouseCursor.MOUSE_CURSOR_RESIZE_ALL     9  ; The omnidirectional resize/move cursor shape
  define MouseCursor.MOUSE_CURSOR_NOT_ALLOWED    10  ; The operation-not-allowed shape

  ; Gamepad buttons
  define GamepadButton GamepadButton
  define GamepadButton.GAMEPAD_BUTTON_UNKNOWN           0  ; Unknown button, for error checking
  define GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_UP      1  ; Gamepad left DPAD up button
  define GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_RIGHT   2  ; Gamepad left DPAD right button
  define GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_DOWN    3  ; Gamepad left DPAD down button
  define GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_LEFT    4  ; Gamepad left DPAD left button
  define GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_UP     5  ; Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
  define GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_RIGHT  6  ; Gamepad right button right (i.e. PS3: Circle, Xbox: B)
  define GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_DOWN   7  ; Gamepad right button down (i.e. PS3: Cross, Xbox: A)
  define GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_LEFT   8  ; Gamepad right button left (i.e. PS3: Square, Xbox: X)
  define GamepadButton.GAMEPAD_BUTTON_LEFT_TRIGGER_1    9  ; Gamepad top/back trigger left (first), it could be a trailing button
  define GamepadButton.GAMEPAD_BUTTON_LEFT_TRIGGER_2    10  ; Gamepad top/back trigger left (second), it could be a trailing button
  define GamepadButton.GAMEPAD_BUTTON_RIGHT_TRIGGER_1   11  ; Gamepad top/back trigger right (first), it could be a trailing button
  define GamepadButton.GAMEPAD_BUTTON_RIGHT_TRIGGER_2   12  ; Gamepad top/back trigger right (second), it could be a trailing button
  define GamepadButton.GAMEPAD_BUTTON_MIDDLE_LEFT       13  ; Gamepad center buttons, left one (i.e. PS3: Select)
  define GamepadButton.GAMEPAD_BUTTON_MIDDLE            14  ; Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
  define GamepadButton.GAMEPAD_BUTTON_MIDDLE_RIGHT      15  ; Gamepad center buttons, right one (i.e. PS3: Start)
  define GamepadButton.GAMEPAD_BUTTON_LEFT_THUMB        16  ; Gamepad joystick pressed button left
  define GamepadButton.GAMEPAD_BUTTON_RIGHT_THUMB       17  ; Gamepad joystick pressed button right

  ; Gamepad axes
  define GamepadAxis GamepadAxis
  define GamepadAxis.GAMEPAD_AXIS_LEFT_X         0  ; Gamepad left stick X axis
  define GamepadAxis.GAMEPAD_AXIS_LEFT_Y         1  ; Gamepad left stick Y axis
  define GamepadAxis.GAMEPAD_AXIS_RIGHT_X        2  ; Gamepad right stick X axis
  define GamepadAxis.GAMEPAD_AXIS_RIGHT_Y        3  ; Gamepad right stick Y axis
  define GamepadAxis.GAMEPAD_AXIS_LEFT_TRIGGER   4  ; Gamepad back trigger left, pressure level: [1..-1]
  define GamepadAxis.GAMEPAD_AXIS_RIGHT_TRIGGER  5  ; Gamepad back trigger right, pressure level: [1..-1]

  ; Material map index
  define MaterialMapIndex MaterialMapIndex
  define MaterialMapIndex.MATERIAL_MAP_ALBEDO      0  ; Albedo material (same as: MATERIAL_MAP_DIFFUSE)
  define MaterialMapIndex.MATERIAL_MAP_METALNESS   1  ; Metalness material (same as: MATERIAL_MAP_SPECULAR)
  define MaterialMapIndex.MATERIAL_MAP_NORMAL      2  ; Normal material
  define MaterialMapIndex.MATERIAL_MAP_ROUGHNESS   3  ; Roughness material
  define MaterialMapIndex.MATERIAL_MAP_OCCLUSION   4  ; Ambient occlusion material
  define MaterialMapIndex.MATERIAL_MAP_EMISSION    5  ; Emission material
  define MaterialMapIndex.MATERIAL_MAP_HEIGHT      6  ; Heightmap material
  define MaterialMapIndex.MATERIAL_MAP_CUBEMAP     7  ; Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
  define MaterialMapIndex.MATERIAL_MAP_IRRADIANCE  8  ; Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
  define MaterialMapIndex.MATERIAL_MAP_PREFILTER   9  ; Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
  define MaterialMapIndex.MATERIAL_MAP_BRDF        10  ; Brdf material

  ; Shader location index
  define ShaderLocationIndex ShaderLocationIndex
  define ShaderLocationIndex.SHADER_LOC_VERTEX_POSITION           0  ; Shader location: vertex attribute: position
  define ShaderLocationIndex.SHADER_LOC_VERTEX_TEXCOORD01         1  ; Shader location: vertex attribute: texcoord01
  define ShaderLocationIndex.SHADER_LOC_VERTEX_TEXCOORD02         2  ; Shader location: vertex attribute: texcoord02
  define ShaderLocationIndex.SHADER_LOC_VERTEX_NORMAL             3  ; Shader location: vertex attribute: normal
  define ShaderLocationIndex.SHADER_LOC_VERTEX_TANGENT            4  ; Shader location: vertex attribute: tangent
  define ShaderLocationIndex.SHADER_LOC_VERTEX_COLOR              5  ; Shader location: vertex attribute: color
  define ShaderLocationIndex.SHADER_LOC_MATRIX_MVP                6  ; Shader location: matrix uniform: model-view-projection
  define ShaderLocationIndex.SHADER_LOC_MATRIX_VIEW               7  ; Shader location: matrix uniform: view (camera transform)
  define ShaderLocationIndex.SHADER_LOC_MATRIX_PROJECTION         8  ; Shader location: matrix uniform: projection
  define ShaderLocationIndex.SHADER_LOC_MATRIX_MODEL              9  ; Shader location: matrix uniform: model (transform)
  define ShaderLocationIndex.SHADER_LOC_MATRIX_NORMAL             10  ; Shader location: matrix uniform: normal
  define ShaderLocationIndex.SHADER_LOC_VECTOR_VIEW               11  ; Shader location: vector uniform: view
  define ShaderLocationIndex.SHADER_LOC_COLOR_DIFFUSE             12  ; Shader location: vector uniform: diffuse color
  define ShaderLocationIndex.SHADER_LOC_COLOR_SPECULAR            13  ; Shader location: vector uniform: specular color
  define ShaderLocationIndex.SHADER_LOC_COLOR_AMBIENT             14  ; Shader location: vector uniform: ambient color
  define ShaderLocationIndex.SHADER_LOC_MAP_ALBEDO                15  ; Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)
  define ShaderLocationIndex.SHADER_LOC_MAP_METALNESS             16  ; Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)
  define ShaderLocationIndex.SHADER_LOC_MAP_NORMAL                17  ; Shader location: sampler2d texture: normal
  define ShaderLocationIndex.SHADER_LOC_MAP_ROUGHNESS             18  ; Shader location: sampler2d texture: roughness
  define ShaderLocationIndex.SHADER_LOC_MAP_OCCLUSION             19  ; Shader location: sampler2d texture: occlusion
  define ShaderLocationIndex.SHADER_LOC_MAP_EMISSION              20  ; Shader location: sampler2d texture: emission
  define ShaderLocationIndex.SHADER_LOC_MAP_HEIGHT                21  ; Shader location: sampler2d texture: heightmap
  define ShaderLocationIndex.SHADER_LOC_MAP_CUBEMAP               22  ; Shader location: samplerCube texture: cubemap
  define ShaderLocationIndex.SHADER_LOC_MAP_IRRADIANCE            23  ; Shader location: samplerCube texture: irradiance
  define ShaderLocationIndex.SHADER_LOC_MAP_PREFILTER             24  ; Shader location: samplerCube texture: prefilter
  define ShaderLocationIndex.SHADER_LOC_MAP_BRDF                  25  ; Shader location: sampler2d texture: brdf
  define ShaderLocationIndex.SHADER_LOC_VERTEX_BONEIDS            26  ; Shader location: vertex attribute: bone indices
  define ShaderLocationIndex.SHADER_LOC_VERTEX_BONEWEIGHTS        27  ; Shader location: vertex attribute: bone weights
  define ShaderLocationIndex.SHADER_LOC_MATRIX_BONETRANSFORMS     28  ; Shader location: matrix attribute: bone transforms (animation)
  define ShaderLocationIndex.SHADER_LOC_VERTEX_INSTANCETRANSFORM  29  ; Shader location: vertex attribute: instance transforms

  ; Shader uniform data type
  define ShaderUniformDataType ShaderUniformDataType
  define ShaderUniformDataType.SHADER_UNIFORM_FLOAT      0  ; Shader uniform type: float
  define ShaderUniformDataType.SHADER_UNIFORM_VEC2       1  ; Shader uniform type: vec2 (2 float)
  define ShaderUniformDataType.SHADER_UNIFORM_VEC3       2  ; Shader uniform type: vec3 (3 float)
  define ShaderUniformDataType.SHADER_UNIFORM_VEC4       3  ; Shader uniform type: vec4 (4 float)
  define ShaderUniformDataType.SHADER_UNIFORM_INT        4  ; Shader uniform type: int
  define ShaderUniformDataType.SHADER_UNIFORM_IVEC2      5  ; Shader uniform type: ivec2 (2 int)
  define ShaderUniformDataType.SHADER_UNIFORM_IVEC3      6  ; Shader uniform type: ivec3 (3 int)
  define ShaderUniformDataType.SHADER_UNIFORM_IVEC4      7  ; Shader uniform type: ivec4 (4 int)
  define ShaderUniformDataType.SHADER_UNIFORM_UINT       8  ; Shader uniform type: unsigned int
  define ShaderUniformDataType.SHADER_UNIFORM_UIVEC2     9  ; Shader uniform type: uivec2 (2 unsigned int)
  define ShaderUniformDataType.SHADER_UNIFORM_UIVEC3     10  ; Shader uniform type: uivec3 (3 unsigned int)
  define ShaderUniformDataType.SHADER_UNIFORM_UIVEC4     11  ; Shader uniform type: uivec4 (4 unsigned int)
  define ShaderUniformDataType.SHADER_UNIFORM_SAMPLER2D  12  ; Shader uniform type: sampler2d

  ; Shader attribute data types
  define ShaderAttributeDataType ShaderAttributeDataType
  define ShaderAttributeDataType.SHADER_ATTRIB_FLOAT  0  ; Shader attribute type: float
  define ShaderAttributeDataType.SHADER_ATTRIB_VEC2   1  ; Shader attribute type: vec2 (2 float)
  define ShaderAttributeDataType.SHADER_ATTRIB_VEC3   2  ; Shader attribute type: vec3 (3 float)
  define ShaderAttributeDataType.SHADER_ATTRIB_VEC4   3  ; Shader attribute type: vec4 (4 float)

  ; Pixel formats
  define PixelFormat PixelFormat
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_GRAYSCALE     1  ; 8 bit per pixel (no alpha)
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA    2  ; 8*2 bpp (2 channels)
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R5G6B5        3  ; 16 bpp
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R8G8B8        4  ; 24 bpp
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R5G5B5A1      5  ; 16 bpp (1 bit alpha)
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R4G4B4A4      6  ; 16 bpp (4 bit alpha)
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R8G8B8A8      7  ; 32 bpp
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R32           8  ; 32 bpp (1 channel - float)
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R32G32B32     9  ; 32*3 bpp (3 channels - float)
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R32G32B32A32  10  ; 32*4 bpp (4 channels - float)
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R16           11  ; 16 bpp (1 channel - half float)
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R16G16B16     12  ; 16*3 bpp (3 channels - half float)
  define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R16G16B16A16  13  ; 16*4 bpp (4 channels - half float)
  define PixelFormat.PIXELFORMAT_COMPRESSED_DXT1_RGB        14  ; 4 bpp (no alpha)
  define PixelFormat.PIXELFORMAT_COMPRESSED_DXT1_RGBA       15  ; 4 bpp (1 bit alpha)
  define PixelFormat.PIXELFORMAT_COMPRESSED_DXT3_RGBA       16  ; 8 bpp
  define PixelFormat.PIXELFORMAT_COMPRESSED_DXT5_RGBA       17  ; 8 bpp
  define PixelFormat.PIXELFORMAT_COMPRESSED_ETC1_RGB        18  ; 4 bpp
  define PixelFormat.PIXELFORMAT_COMPRESSED_ETC2_RGB        19  ; 4 bpp
  define PixelFormat.PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA   20  ; 8 bpp
  define PixelFormat.PIXELFORMAT_COMPRESSED_PVRT_RGB        21  ; 4 bpp
  define PixelFormat.PIXELFORMAT_COMPRESSED_PVRT_RGBA       22  ; 4 bpp
  define PixelFormat.PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA   23  ; 8 bpp
  define PixelFormat.PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA   24  ; 2 bpp

  ; Texture parameters: filter mode
  define TextureFilter TextureFilter
  define TextureFilter.TEXTURE_FILTER_POINT            0  ; No filter, pixel approximation
  define TextureFilter.TEXTURE_FILTER_BILINEAR         1  ; Linear filtering
  define TextureFilter.TEXTURE_FILTER_TRILINEAR        2  ; Trilinear filtering (linear with mipmaps)
  define TextureFilter.TEXTURE_FILTER_ANISOTROPIC_4X   3  ; Anisotropic filtering 4x
  define TextureFilter.TEXTURE_FILTER_ANISOTROPIC_8X   4  ; Anisotropic filtering 8x
  define TextureFilter.TEXTURE_FILTER_ANISOTROPIC_16X  5  ; Anisotropic filtering 16x

  ; Texture parameters: wrap mode
  define TextureWrap TextureWrap
  define TextureWrap.TEXTURE_WRAP_REPEAT         0  ; Repeats texture in tiled mode
  define TextureWrap.TEXTURE_WRAP_CLAMP          1  ; Clamps texture to edge pixel in tiled mode
  define TextureWrap.TEXTURE_WRAP_MIRROR_REPEAT  2  ; Mirrors and repeats the texture in tiled mode
  define TextureWrap.TEXTURE_WRAP_MIRROR_CLAMP   3  ; Mirrors and clamps to border the texture in tiled mode

  ; Cubemap layouts
  define CubemapLayout CubemapLayout
  define CubemapLayout.CUBEMAP_LAYOUT_AUTO_DETECT          0  ; Automatically detect layout type
  define CubemapLayout.CUBEMAP_LAYOUT_LINE_VERTICAL        1  ; Layout is defined by a vertical line with faces
  define CubemapLayout.CUBEMAP_LAYOUT_LINE_HORIZONTAL      2  ; Layout is defined by a horizontal line with faces
  define CubemapLayout.CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR  3  ; Layout is defined by a 3x4 cross with cubemap faces
  define CubemapLayout.CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE  4  ; Layout is defined by a 4x3 cross with cubemap faces

  ; Font type, defines generation method
  define FontType FontType
  define FontType.FONT_DEFAULT  0  ; Default font generation, anti-aliased
  define FontType.FONT_BITMAP   1  ; Bitmap font generation, no anti-aliasing
  define FontType.FONT_SDF      2  ; SDF font generation, requires external shader

  ; Color blending modes (pre-defined)
  define BlendMode BlendMode
  define BlendMode.BLEND_ALPHA              0  ; Blend textures considering alpha (default)
  define BlendMode.BLEND_ADDITIVE           1  ; Blend textures adding colors
  define BlendMode.BLEND_MULTIPLIED         2  ; Blend textures multiplying colors
  define BlendMode.BLEND_ADD_COLORS         3  ; Blend textures adding colors (alternative)
  define BlendMode.BLEND_SUBTRACT_COLORS    4  ; Blend textures subtracting colors (alternative)
  define BlendMode.BLEND_ALPHA_PREMULTIPLY  5  ; Blend premultiplied textures considering alpha
  define BlendMode.BLEND_CUSTOM             6  ; Blend textures using custom src/dst factors (use rlSetBlendFactors())
  define BlendMode.BLEND_CUSTOM_SEPARATE    7  ; Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())

  ; Gesture
  define Gesture Gesture
  define Gesture.GESTURE_NONE         0  ; No gesture
  define Gesture.GESTURE_TAP          1  ; Tap gesture
  define Gesture.GESTURE_DOUBLETAP    2  ; Double tap gesture
  define Gesture.GESTURE_HOLD         4  ; Hold gesture
  define Gesture.GESTURE_DRAG         8  ; Drag gesture
  define Gesture.GESTURE_SWIPE_RIGHT  16  ; Swipe right gesture
  define Gesture.GESTURE_SWIPE_LEFT   32  ; Swipe left gesture
  define Gesture.GESTURE_SWIPE_UP     64  ; Swipe up gesture
  define Gesture.GESTURE_SWIPE_DOWN   128  ; Swipe down gesture
  define Gesture.GESTURE_PINCH_IN     256  ; Pinch in gesture
  define Gesture.GESTURE_PINCH_OUT    512  ; Pinch out gesture

  ; Camera system modes
  define CameraMode CameraMode
  define CameraMode.CAMERA_CUSTOM        0  ; Camera custom, controlled by user (UpdateCamera() does nothing)
  define CameraMode.CAMERA_FREE          1  ; Camera free mode
  define CameraMode.CAMERA_ORBITAL       2  ; Camera orbital, around target, zoom supported
  define CameraMode.CAMERA_FIRST_PERSON  3  ; Camera first person
  define CameraMode.CAMERA_THIRD_PERSON  4  ; Camera third person

  ; Camera projection
  define CameraProjection CameraProjection
  define CameraProjection.CAMERA_PERSPECTIVE   0  ; Perspective projection
  define CameraProjection.CAMERA_ORTHOGRAPHIC  1  ; Orthographic projection

  ; N-patch layout
  define NPatchLayout NPatchLayout
  define NPatchLayout.NPATCH_NINE_PATCH              0  ; Npatch layout: 3x3 tiles
  define NPatchLayout.NPATCH_THREE_PATCH_VERTICAL    1  ; Npatch layout: 1x3 tiles
  define NPatchLayout.NPATCH_THREE_PATCH_HORIZONTAL  2  ; Npatch layout: 3x1 tiles

end namespace ; RayLib