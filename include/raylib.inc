; Auto-generated from raylib_api.xml by tools/generate_raylib_fasmg.py
; Source: raylib tools/rlparser/output/raylib_api.xml
; Raylib API version: 6.0 projection for fasmg

define RayLib
namespace RayLib

; Compile-time constants
define RAYLIB_VERSION_MAJOR               0x6
define RAYLIB_VERSION_MINOR               0x0
define RAYLIB_VERSION_PATCH               0x0
define RAYLIB_VERSION                     '6.0'
define RLAPI                              __declspec(dllexport) ; Building the library as a Win32 shared library (.dll)
define PI                                 3.14159265358979323846
define LIGHTGRAY                          0xFFC8C8C8 ; Light Gray
define GRAY                               0xFF828282 ; Gray
define DARKGRAY                           0xFF505050 ; Dark Gray
define YELLOW                             0xFF00F9FD ; Yellow
define GOLD                               0xFF00CBFF ; Gold
define ORANGE                             0xFF00A1FF ; Orange
define PINK                               0xFFC26DFF ; Pink
define RED                                0xFF3729E6 ; Red
define MAROON                             0xFF3721BE ; Maroon
define GREEN                              0xFF30E400 ; Green
define LIME                               0xFF2F9E00 ; Lime
define DARKGREEN                          0xFF2C7500 ; Dark Green
define SKYBLUE                            0xFFFFBF66 ; Sky Blue
define BLUE                               0xFFF17900 ; Blue
define DARKBLUE                           0xFFAC5200 ; Dark Blue
define PURPLE                             0xFFFF7AC8 ; Purple
define VIOLET                             0xFFBE3C87 ; Violet
define DARKPURPLE                         0xFF7E1F70 ; Dark Purple
define BEIGE                              0xFF83B0D3 ; Beige
define BROWN                              0xFF4F6A7F ; Brown
define DARKBROWN                          0xFF2F3F4C ; Dark Brown
define WHITE                              0xFFFFFFFF ; White
define BLACK                              0xFF000000 ; Black
define BLANK                              0x00000000 ; Blank (Transparent)
define MAGENTA                            0xFFFF00FF ; Magenta
define RAYWHITE                           0xFFF5F5F5 ; My own White (raylib logo)
define MOUSE_LEFT_BUTTON                  MOUSE_BUTTON_LEFT
define MOUSE_RIGHT_BUTTON                 MOUSE_BUTTON_RIGHT
define MOUSE_MIDDLE_BUTTON                MOUSE_BUTTON_MIDDLE
define MATERIAL_MAP_DIFFUSE               MATERIAL_MAP_ALBEDO
define MATERIAL_MAP_SPECULAR              MATERIAL_MAP_METALNESS
define SHADER_LOC_MAP_DIFFUSE             SHADER_LOC_MAP_ALBEDO
define SHADER_LOC_MAP_SPECULAR            SHADER_LOC_MAP_METALNESS
define GetMouseRay                        GetScreenToWorldRay ; Compatibility hack for previous raylib versions

; Enums
; System/Window config flags
define ConfigFlags ConfigFlags
define ConfigFlags.FLAG_VSYNC_HINT                        0x40 ; Set to try enabling V-Sync on GPU
define ConfigFlags.FLAG_FULLSCREEN_MODE                   0x2 ; Set to run program in fullscreen
define ConfigFlags.FLAG_WINDOW_RESIZABLE                  0x4 ; Set to allow resizable window
define ConfigFlags.FLAG_WINDOW_UNDECORATED                0x8 ; Set to disable window decoration (frame and buttons)
define ConfigFlags.FLAG_WINDOW_HIDDEN                     0x80 ; Set to hide window
define ConfigFlags.FLAG_WINDOW_MINIMIZED                  0x200 ; Set to minimize window (iconify)
define ConfigFlags.FLAG_WINDOW_MAXIMIZED                  0x400 ; Set to maximize window (expanded to monitor)
define ConfigFlags.FLAG_WINDOW_UNFOCUSED                  0x800 ; Set to window non focused
define ConfigFlags.FLAG_WINDOW_TOPMOST                    0x1000 ; Set to window always on top
define ConfigFlags.FLAG_WINDOW_ALWAYS_RUN                 0x100 ; Set to allow windows running while minimized
define ConfigFlags.FLAG_WINDOW_TRANSPARENT                0x10 ; Set to allow transparent framebuffer
define ConfigFlags.FLAG_WINDOW_HIGHDPI                    0x2000 ; Set to support HighDPI
define ConfigFlags.FLAG_WINDOW_MOUSE_PASSTHROUGH          0x4000 ; Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
define ConfigFlags.FLAG_BORDERLESS_WINDOWED_MODE          0x8000 ; Set to run program in borderless windowed mode
define ConfigFlags.FLAG_MSAA_4X_HINT                      0x20 ; Set to try enabling MSAA 4X
define ConfigFlags.FLAG_INTERLACED_HINT                   0x10000 ; Set to try enabling interlaced video format (for V3D)

; Trace log level
define TraceLogLevel TraceLogLevel
define TraceLogLevel.LOG_ALL                                0x0 ; Display all logs
define TraceLogLevel.LOG_TRACE                              0x1 ; Trace logging, intended for internal use only
define TraceLogLevel.LOG_DEBUG                              0x2 ; Debug logging, used for internal debugging, it should be disabled on release builds
define TraceLogLevel.LOG_INFO                               0x3 ; Info logging, used for program execution info
define TraceLogLevel.LOG_WARNING                            0x4 ; Warning logging, used on recoverable failures
define TraceLogLevel.LOG_ERROR                              0x5 ; Error logging, used on unrecoverable failures
define TraceLogLevel.LOG_FATAL                              0x6 ; Fatal logging, used to abort program: exit(EXIT_FAILURE)
define TraceLogLevel.LOG_NONE                               0x7 ; Disable logging

; Keyboard keys (US keyboard layout)
define KeyboardKey KeyboardKey
define KeyboardKey.KEY_NULL                               0x0 ; Key: NULL, used for no key pressed
define KeyboardKey.KEY_APOSTROPHE                         0x27 ; Key: '
define KeyboardKey.KEY_COMMA                              0x2C ; Key: ,
define KeyboardKey.KEY_MINUS                              0x2D ; Key: -
define KeyboardKey.KEY_PERIOD                             0x2E ; Key: .
define KeyboardKey.KEY_SLASH                              0x2F ; Key: /
define KeyboardKey.KEY_ZERO                               0x30 ; Key: 0
define KeyboardKey.KEY_ONE                                0x31 ; Key: 1
define KeyboardKey.KEY_TWO                                0x32 ; Key: 2
define KeyboardKey.KEY_THREE                              0x33 ; Key: 3
define KeyboardKey.KEY_FOUR                               0x34 ; Key: 4
define KeyboardKey.KEY_FIVE                               0x35 ; Key: 5
define KeyboardKey.KEY_SIX                                0x36 ; Key: 6
define KeyboardKey.KEY_SEVEN                              0x37 ; Key: 7
define KeyboardKey.KEY_EIGHT                              0x38 ; Key: 8
define KeyboardKey.KEY_NINE                               0x39 ; Key: 9
define KeyboardKey.KEY_SEMICOLON                          0x3B ; Key: ,
define KeyboardKey.KEY_EQUAL                              0x3D ; Key: =
define KeyboardKey.KEY_A                                  0x41 ; Key: A | a
define KeyboardKey.KEY_B                                  0x42 ; Key: B | b
define KeyboardKey.KEY_C                                  0x43 ; Key: C | c
define KeyboardKey.KEY_D                                  0x44 ; Key: D | d
define KeyboardKey.KEY_E                                  0x45 ; Key: E | e
define KeyboardKey.KEY_F                                  0x46 ; Key: F | f
define KeyboardKey.KEY_G                                  0x47 ; Key: G | g
define KeyboardKey.KEY_H                                  0x48 ; Key: H | h
define KeyboardKey.KEY_I                                  0x49 ; Key: I | i
define KeyboardKey.KEY_J                                  0x4A ; Key: J | j
define KeyboardKey.KEY_K                                  0x4B ; Key: K | k
define KeyboardKey.KEY_L                                  0x4C ; Key: L | l
define KeyboardKey.KEY_M                                  0x4D ; Key: M | m
define KeyboardKey.KEY_N                                  0x4E ; Key: N | n
define KeyboardKey.KEY_O                                  0x4F ; Key: O | o
define KeyboardKey.KEY_P                                  0x50 ; Key: P | p
define KeyboardKey.KEY_Q                                  0x51 ; Key: Q | q
define KeyboardKey.KEY_R                                  0x52 ; Key: R | r
define KeyboardKey.KEY_S                                  0x53 ; Key: S | s
define KeyboardKey.KEY_T                                  0x54 ; Key: T | t
define KeyboardKey.KEY_U                                  0x55 ; Key: U | u
define KeyboardKey.KEY_V                                  0x56 ; Key: V | v
define KeyboardKey.KEY_W                                  0x57 ; Key: W | w
define KeyboardKey.KEY_X                                  0x58 ; Key: X | x
define KeyboardKey.KEY_Y                                  0x59 ; Key: Y | y
define KeyboardKey.KEY_Z                                  0x5A ; Key: Z | z
define KeyboardKey.KEY_LEFT_BRACKET                       0x5B ; Key: [
define KeyboardKey.KEY_BACKSLASH                          0x5C ; Key: '\'
define KeyboardKey.KEY_RIGHT_BRACKET                      0x5D ; Key: ]
define KeyboardKey.KEY_GRAVE                              0x60 ; Key: `
define KeyboardKey.KEY_SPACE                              0x20 ; Key: Space
define KeyboardKey.KEY_ESCAPE                             0x100 ; Key: Esc
define KeyboardKey.KEY_ENTER                              0x101 ; Key: Enter
define KeyboardKey.KEY_TAB                                0x102 ; Key: Tab
define KeyboardKey.KEY_BACKSPACE                          0x103 ; Key: Backspace
define KeyboardKey.KEY_INSERT                             0x104 ; Key: Ins
define KeyboardKey.KEY_DELETE                             0x105 ; Key: Del
define KeyboardKey.KEY_RIGHT                              0x106 ; Key: Cursor right
define KeyboardKey.KEY_LEFT                               0x107 ; Key: Cursor left
define KeyboardKey.KEY_DOWN                               0x108 ; Key: Cursor down
define KeyboardKey.KEY_UP                                 0x109 ; Key: Cursor up
define KeyboardKey.KEY_PAGE_UP                            0x10A ; Key: Page up
define KeyboardKey.KEY_PAGE_DOWN                          0x10B ; Key: Page down
define KeyboardKey.KEY_HOME                               0x10C ; Key: Home
define KeyboardKey.KEY_END                                0x10D ; Key: End
define KeyboardKey.KEY_CAPS_LOCK                          0x118 ; Key: Caps lock
define KeyboardKey.KEY_SCROLL_LOCK                        0x119 ; Key: Scroll down
define KeyboardKey.KEY_NUM_LOCK                           0x11A ; Key: Num lock
define KeyboardKey.KEY_PRINT_SCREEN                       0x11B ; Key: Print screen
define KeyboardKey.KEY_PAUSE                              0x11C ; Key: Pause
define KeyboardKey.KEY_F1                                 0x122 ; Key: F1
define KeyboardKey.KEY_F2                                 0x123 ; Key: F2
define KeyboardKey.KEY_F3                                 0x124 ; Key: F3
define KeyboardKey.KEY_F4                                 0x125 ; Key: F4
define KeyboardKey.KEY_F5                                 0x126 ; Key: F5
define KeyboardKey.KEY_F6                                 0x127 ; Key: F6
define KeyboardKey.KEY_F7                                 0x128 ; Key: F7
define KeyboardKey.KEY_F8                                 0x129 ; Key: F8
define KeyboardKey.KEY_F9                                 0x12A ; Key: F9
define KeyboardKey.KEY_F10                                0x12B ; Key: F10
define KeyboardKey.KEY_F11                                0x12C ; Key: F11
define KeyboardKey.KEY_F12                                0x12D ; Key: F12
define KeyboardKey.KEY_LEFT_SHIFT                         0x154 ; Key: Shift left
define KeyboardKey.KEY_LEFT_CONTROL                       0x155 ; Key: Control left
define KeyboardKey.KEY_LEFT_ALT                           0x156 ; Key: Alt left
define KeyboardKey.KEY_LEFT_SUPER                         0x157 ; Key: Super left
define KeyboardKey.KEY_RIGHT_SHIFT                        0x158 ; Key: Shift right
define KeyboardKey.KEY_RIGHT_CONTROL                      0x159 ; Key: Control right
define KeyboardKey.KEY_RIGHT_ALT                          0x15A ; Key: Alt right
define KeyboardKey.KEY_RIGHT_SUPER                        0x15B ; Key: Super right
define KeyboardKey.KEY_KB_MENU                            0x15C ; Key: KB menu
define KeyboardKey.KEY_KP_0                               0x140 ; Key: Keypad 0
define KeyboardKey.KEY_KP_1                               0x141 ; Key: Keypad 1
define KeyboardKey.KEY_KP_2                               0x142 ; Key: Keypad 2
define KeyboardKey.KEY_KP_3                               0x143 ; Key: Keypad 3
define KeyboardKey.KEY_KP_4                               0x144 ; Key: Keypad 4
define KeyboardKey.KEY_KP_5                               0x145 ; Key: Keypad 5
define KeyboardKey.KEY_KP_6                               0x146 ; Key: Keypad 6
define KeyboardKey.KEY_KP_7                               0x147 ; Key: Keypad 7
define KeyboardKey.KEY_KP_8                               0x148 ; Key: Keypad 8
define KeyboardKey.KEY_KP_9                               0x149 ; Key: Keypad 9
define KeyboardKey.KEY_KP_DECIMAL                         0x14A ; Key: Keypad .
define KeyboardKey.KEY_KP_DIVIDE                          0x14B ; Key: Keypad /
define KeyboardKey.KEY_KP_MULTIPLY                        0x14C ; Key: Keypad *
define KeyboardKey.KEY_KP_SUBTRACT                        0x14D ; Key: Keypad -
define KeyboardKey.KEY_KP_ADD                             0x14E ; Key: Keypad +
define KeyboardKey.KEY_KP_ENTER                           0x14F ; Key: Keypad Enter
define KeyboardKey.KEY_KP_EQUAL                           0x150 ; Key: Keypad =
define KeyboardKey.KEY_BACK                               0x4 ; Key: Android back button
define KeyboardKey.KEY_MENU                               0x5 ; Key: Android menu button
define KeyboardKey.KEY_VOLUME_UP                          0x18 ; Key: Android volume up button
define KeyboardKey.KEY_VOLUME_DOWN                        0x19 ; Key: Android volume down button

; Mouse buttons
define MouseButton MouseButton
define MouseButton.MOUSE_BUTTON_LEFT                      0x0 ; Mouse button left
define MouseButton.MOUSE_BUTTON_RIGHT                     0x1 ; Mouse button right
define MouseButton.MOUSE_BUTTON_MIDDLE                    0x2 ; Mouse button middle (pressed wheel)
define MouseButton.MOUSE_BUTTON_SIDE                      0x3 ; Mouse button side (advanced mouse device)
define MouseButton.MOUSE_BUTTON_EXTRA                     0x4 ; Mouse button extra (advanced mouse device)
define MouseButton.MOUSE_BUTTON_FORWARD                   0x5 ; Mouse button forward (advanced mouse device)
define MouseButton.MOUSE_BUTTON_BACK                      0x6 ; Mouse button back (advanced mouse device)

; Mouse cursor
define MouseCursor MouseCursor
define MouseCursor.MOUSE_CURSOR_DEFAULT                   0x0 ; Default pointer shape
define MouseCursor.MOUSE_CURSOR_ARROW                     0x1 ; Arrow shape
define MouseCursor.MOUSE_CURSOR_IBEAM                     0x2 ; Text writing cursor shape
define MouseCursor.MOUSE_CURSOR_CROSSHAIR                 0x3 ; Cross shape
define MouseCursor.MOUSE_CURSOR_POINTING_HAND             0x4 ; Pointing hand cursor
define MouseCursor.MOUSE_CURSOR_RESIZE_EW                 0x5 ; Horizontal resize/move arrow shape
define MouseCursor.MOUSE_CURSOR_RESIZE_NS                 0x6 ; Vertical resize/move arrow shape
define MouseCursor.MOUSE_CURSOR_RESIZE_NWSE               0x7 ; Top-left to bottom-right diagonal resize/move arrow shape
define MouseCursor.MOUSE_CURSOR_RESIZE_NESW               0x8 ; The top-right to bottom-left diagonal resize/move arrow shape
define MouseCursor.MOUSE_CURSOR_RESIZE_ALL                0x9 ; The omnidirectional resize/move cursor shape
define MouseCursor.MOUSE_CURSOR_NOT_ALLOWED               0xA ; The operation-not-allowed shape

; Gamepad buttons
define GamepadButton GamepadButton
define GamepadButton.GAMEPAD_BUTTON_UNKNOWN                 0x0 ; Unknown button, for error checking
define GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_UP            0x1 ; Gamepad left DPAD up button
define GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_RIGHT         0x2 ; Gamepad left DPAD right button
define GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_DOWN          0x3 ; Gamepad left DPAD down button
define GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_LEFT          0x4 ; Gamepad left DPAD left button
define GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_UP           0x5 ; Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
define GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_RIGHT        0x6 ; Gamepad right button right (i.e. PS3: Circle, Xbox: B)
define GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_DOWN         0x7 ; Gamepad right button down (i.e. PS3: Cross, Xbox: A)
define GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_LEFT         0x8 ; Gamepad right button left (i.e. PS3: Square, Xbox: X)
define GamepadButton.GAMEPAD_BUTTON_LEFT_TRIGGER_1          0x9 ; Gamepad top/back trigger left (first), it could be a trailing button
define GamepadButton.GAMEPAD_BUTTON_LEFT_TRIGGER_2          0xA ; Gamepad top/back trigger left (second), it could be a trailing button
define GamepadButton.GAMEPAD_BUTTON_RIGHT_TRIGGER_1         0xB ; Gamepad top/back trigger right (first), it could be a trailing button
define GamepadButton.GAMEPAD_BUTTON_RIGHT_TRIGGER_2         0xC ; Gamepad top/back trigger right (second), it could be a trailing button
define GamepadButton.GAMEPAD_BUTTON_MIDDLE_LEFT             0xD ; Gamepad center buttons, left one (i.e. PS3: Select)
define GamepadButton.GAMEPAD_BUTTON_MIDDLE                  0xE ; Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
define GamepadButton.GAMEPAD_BUTTON_MIDDLE_RIGHT            0xF ; Gamepad center buttons, right one (i.e. PS3: Start)
define GamepadButton.GAMEPAD_BUTTON_LEFT_THUMB              0x10 ; Gamepad joystick pressed button left
define GamepadButton.GAMEPAD_BUTTON_RIGHT_THUMB             0x11 ; Gamepad joystick pressed button right

; Gamepad axes
define GamepadAxis GamepadAxis
define GamepadAxis.GAMEPAD_AXIS_LEFT_X                    0x0 ; Gamepad left stick X axis
define GamepadAxis.GAMEPAD_AXIS_LEFT_Y                    0x1 ; Gamepad left stick Y axis
define GamepadAxis.GAMEPAD_AXIS_RIGHT_X                   0x2 ; Gamepad right stick X axis
define GamepadAxis.GAMEPAD_AXIS_RIGHT_Y                   0x3 ; Gamepad right stick Y axis
define GamepadAxis.GAMEPAD_AXIS_LEFT_TRIGGER              0x4 ; Gamepad back trigger left, pressure level: [1..-1]
define GamepadAxis.GAMEPAD_AXIS_RIGHT_TRIGGER             0x5 ; Gamepad back trigger right, pressure level: [1..-1]

; Material map index
define MaterialMapIndex MaterialMapIndex
define MaterialMapIndex.MATERIAL_MAP_ALBEDO                    0x0 ; Albedo material (same as: MATERIAL_MAP_DIFFUSE)
define MaterialMapIndex.MATERIAL_MAP_METALNESS                 0x1 ; Metalness material (same as: MATERIAL_MAP_SPECULAR)
define MaterialMapIndex.MATERIAL_MAP_NORMAL                    0x2 ; Normal material
define MaterialMapIndex.MATERIAL_MAP_ROUGHNESS                 0x3 ; Roughness material
define MaterialMapIndex.MATERIAL_MAP_OCCLUSION                 0x4 ; Ambient occlusion material
define MaterialMapIndex.MATERIAL_MAP_EMISSION                  0x5 ; Emission material
define MaterialMapIndex.MATERIAL_MAP_HEIGHT                    0x6 ; Heightmap material
define MaterialMapIndex.MATERIAL_MAP_CUBEMAP                   0x7 ; Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
define MaterialMapIndex.MATERIAL_MAP_IRRADIANCE                0x8 ; Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
define MaterialMapIndex.MATERIAL_MAP_PREFILTER                 0x9 ; Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
define MaterialMapIndex.MATERIAL_MAP_BRDF                      0xA ; Brdf material

; Shader location index
define ShaderLocationIndex ShaderLocationIndex
define ShaderLocationIndex.SHADER_LOC_VERTEX_POSITION             0x0 ; Shader location: vertex attribute: position
define ShaderLocationIndex.SHADER_LOC_VERTEX_TEXCOORD01           0x1 ; Shader location: vertex attribute: texcoord01
define ShaderLocationIndex.SHADER_LOC_VERTEX_TEXCOORD02           0x2 ; Shader location: vertex attribute: texcoord02
define ShaderLocationIndex.SHADER_LOC_VERTEX_NORMAL               0x3 ; Shader location: vertex attribute: normal
define ShaderLocationIndex.SHADER_LOC_VERTEX_TANGENT              0x4 ; Shader location: vertex attribute: tangent
define ShaderLocationIndex.SHADER_LOC_VERTEX_COLOR                0x5 ; Shader location: vertex attribute: color
define ShaderLocationIndex.SHADER_LOC_MATRIX_MVP                  0x6 ; Shader location: matrix uniform: model-view-projection
define ShaderLocationIndex.SHADER_LOC_MATRIX_VIEW                 0x7 ; Shader location: matrix uniform: view (camera transform)
define ShaderLocationIndex.SHADER_LOC_MATRIX_PROJECTION           0x8 ; Shader location: matrix uniform: projection
define ShaderLocationIndex.SHADER_LOC_MATRIX_MODEL                0x9 ; Shader location: matrix uniform: model (transform)
define ShaderLocationIndex.SHADER_LOC_MATRIX_NORMAL               0xA ; Shader location: matrix uniform: normal
define ShaderLocationIndex.SHADER_LOC_VECTOR_VIEW                 0xB ; Shader location: vector uniform: view
define ShaderLocationIndex.SHADER_LOC_COLOR_DIFFUSE               0xC ; Shader location: vector uniform: diffuse color
define ShaderLocationIndex.SHADER_LOC_COLOR_SPECULAR              0xD ; Shader location: vector uniform: specular color
define ShaderLocationIndex.SHADER_LOC_COLOR_AMBIENT               0xE ; Shader location: vector uniform: ambient color
define ShaderLocationIndex.SHADER_LOC_MAP_ALBEDO                  0xF ; Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)
define ShaderLocationIndex.SHADER_LOC_MAP_METALNESS               0x10 ; Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)
define ShaderLocationIndex.SHADER_LOC_MAP_NORMAL                  0x11 ; Shader location: sampler2d texture: normal
define ShaderLocationIndex.SHADER_LOC_MAP_ROUGHNESS               0x12 ; Shader location: sampler2d texture: roughness
define ShaderLocationIndex.SHADER_LOC_MAP_OCCLUSION               0x13 ; Shader location: sampler2d texture: occlusion
define ShaderLocationIndex.SHADER_LOC_MAP_EMISSION                0x14 ; Shader location: sampler2d texture: emission
define ShaderLocationIndex.SHADER_LOC_MAP_HEIGHT                  0x15 ; Shader location: sampler2d texture: heightmap
define ShaderLocationIndex.SHADER_LOC_MAP_CUBEMAP                 0x16 ; Shader location: samplerCube texture: cubemap
define ShaderLocationIndex.SHADER_LOC_MAP_IRRADIANCE              0x17 ; Shader location: samplerCube texture: irradiance
define ShaderLocationIndex.SHADER_LOC_MAP_PREFILTER               0x18 ; Shader location: samplerCube texture: prefilter
define ShaderLocationIndex.SHADER_LOC_MAP_BRDF                    0x19 ; Shader location: sampler2d texture: brdf
define ShaderLocationIndex.SHADER_LOC_VERTEX_BONEIDS              0x1A ; Shader location: vertex attribute: bone indices
define ShaderLocationIndex.SHADER_LOC_VERTEX_BONEWEIGHTS          0x1B ; Shader location: vertex attribute: bone weights
define ShaderLocationIndex.SHADER_LOC_MATRIX_BONETRANSFORMS       0x1C ; Shader location: matrix attribute: bone transforms (animation)
define ShaderLocationIndex.SHADER_LOC_VERTEX_INSTANCETRANSFORM    0x1D ; Shader location: vertex attribute: instance transforms

; Shader uniform data type
define ShaderUniformDataType ShaderUniformDataType
define ShaderUniformDataType.SHADER_UNIFORM_FLOAT                   0x0 ; Shader uniform type: float
define ShaderUniformDataType.SHADER_UNIFORM_VEC2                    0x1 ; Shader uniform type: vec2 (2 float)
define ShaderUniformDataType.SHADER_UNIFORM_VEC3                    0x2 ; Shader uniform type: vec3 (3 float)
define ShaderUniformDataType.SHADER_UNIFORM_VEC4                    0x3 ; Shader uniform type: vec4 (4 float)
define ShaderUniformDataType.SHADER_UNIFORM_INT                     0x4 ; Shader uniform type: int
define ShaderUniformDataType.SHADER_UNIFORM_IVEC2                   0x5 ; Shader uniform type: ivec2 (2 int)
define ShaderUniformDataType.SHADER_UNIFORM_IVEC3                   0x6 ; Shader uniform type: ivec3 (3 int)
define ShaderUniformDataType.SHADER_UNIFORM_IVEC4                   0x7 ; Shader uniform type: ivec4 (4 int)
define ShaderUniformDataType.SHADER_UNIFORM_UINT                    0x8 ; Shader uniform type: unsigned int
define ShaderUniformDataType.SHADER_UNIFORM_UIVEC2                  0x9 ; Shader uniform type: uivec2 (2 unsigned int)
define ShaderUniformDataType.SHADER_UNIFORM_UIVEC3                  0xA ; Shader uniform type: uivec3 (3 unsigned int)
define ShaderUniformDataType.SHADER_UNIFORM_UIVEC4                  0xB ; Shader uniform type: uivec4 (4 unsigned int)
define ShaderUniformDataType.SHADER_UNIFORM_SAMPLER2D               0xC ; Shader uniform type: sampler2d

; Shader attribute data types
define ShaderAttributeDataType ShaderAttributeDataType
define ShaderAttributeDataType.SHADER_ATTRIB_FLOAT                    0x0 ; Shader attribute type: float
define ShaderAttributeDataType.SHADER_ATTRIB_VEC2                     0x1 ; Shader attribute type: vec2 (2 float)
define ShaderAttributeDataType.SHADER_ATTRIB_VEC3                     0x2 ; Shader attribute type: vec3 (3 float)
define ShaderAttributeDataType.SHADER_ATTRIB_VEC4                     0x3 ; Shader attribute type: vec4 (4 float)

; Pixel formats
define PixelFormat PixelFormat
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_GRAYSCALE     0x1 ; 8 bit per pixel (no alpha)
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA    0x2 ; 8*2 bpp (2 channels)
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R5G6B5        0x3 ; 16 bpp
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R8G8B8        0x4 ; 24 bpp
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R5G5B5A1      0x5 ; 16 bpp (1 bit alpha)
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R4G4B4A4      0x6 ; 16 bpp (4 bit alpha)
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R8G8B8A8      0x7 ; 32 bpp
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R32           0x8 ; 32 bpp (1 channel - float)
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R32G32B32     0x9 ; 32*3 bpp (3 channels - float)
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R32G32B32A32  0xA ; 32*4 bpp (4 channels - float)
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R16           0xB ; 16 bpp (1 channel - half float)
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R16G16B16     0xC ; 16*3 bpp (3 channels - half float)
define PixelFormat.PIXELFORMAT_UNCOMPRESSED_R16G16B16A16  0xD ; 16*4 bpp (4 channels - half float)
define PixelFormat.PIXELFORMAT_COMPRESSED_DXT1_RGB        0xE ; 4 bpp (no alpha)
define PixelFormat.PIXELFORMAT_COMPRESSED_DXT1_RGBA       0xF ; 4 bpp (1 bit alpha)
define PixelFormat.PIXELFORMAT_COMPRESSED_DXT3_RGBA       0x10 ; 8 bpp
define PixelFormat.PIXELFORMAT_COMPRESSED_DXT5_RGBA       0x11 ; 8 bpp
define PixelFormat.PIXELFORMAT_COMPRESSED_ETC1_RGB        0x12 ; 4 bpp
define PixelFormat.PIXELFORMAT_COMPRESSED_ETC2_RGB        0x13 ; 4 bpp
define PixelFormat.PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA   0x14 ; 8 bpp
define PixelFormat.PIXELFORMAT_COMPRESSED_PVRT_RGB        0x15 ; 4 bpp
define PixelFormat.PIXELFORMAT_COMPRESSED_PVRT_RGBA       0x16 ; 4 bpp
define PixelFormat.PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA   0x17 ; 8 bpp
define PixelFormat.PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA   0x18 ; 2 bpp

; Texture parameters: filter mode
define TextureFilter TextureFilter
define TextureFilter.TEXTURE_FILTER_POINT                   0x0 ; No filter, pixel approximation
define TextureFilter.TEXTURE_FILTER_BILINEAR                0x1 ; Linear filtering
define TextureFilter.TEXTURE_FILTER_TRILINEAR               0x2 ; Trilinear filtering (linear with mipmaps)
define TextureFilter.TEXTURE_FILTER_ANISOTROPIC_4X          0x3 ; Anisotropic filtering 4x
define TextureFilter.TEXTURE_FILTER_ANISOTROPIC_8X          0x4 ; Anisotropic filtering 8x
define TextureFilter.TEXTURE_FILTER_ANISOTROPIC_16X         0x5 ; Anisotropic filtering 16x

; Texture parameters: wrap mode
define TextureWrap TextureWrap
define TextureWrap.TEXTURE_WRAP_REPEAT                    0x0 ; Repeats texture in tiled mode
define TextureWrap.TEXTURE_WRAP_CLAMP                     0x1 ; Clamps texture to edge pixel in tiled mode
define TextureWrap.TEXTURE_WRAP_MIRROR_REPEAT             0x2 ; Mirrors and repeats the texture in tiled mode
define TextureWrap.TEXTURE_WRAP_MIRROR_CLAMP              0x3 ; Mirrors and clamps to border the texture in tiled mode

; Cubemap layouts
define CubemapLayout CubemapLayout
define CubemapLayout.CUBEMAP_LAYOUT_AUTO_DETECT             0x0 ; Automatically detect layout type
define CubemapLayout.CUBEMAP_LAYOUT_LINE_VERTICAL           0x1 ; Layout is defined by a vertical line with faces
define CubemapLayout.CUBEMAP_LAYOUT_LINE_HORIZONTAL         0x2 ; Layout is defined by a horizontal line with faces
define CubemapLayout.CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR     0x3 ; Layout is defined by a 3x4 cross with cubemap faces
define CubemapLayout.CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE     0x4 ; Layout is defined by a 4x3 cross with cubemap faces

; Font type, defines generation method
define FontType FontType
define FontType.FONT_DEFAULT                           0x0 ; Default font generation, anti-aliased
define FontType.FONT_BITMAP                            0x1 ; Bitmap font generation, no anti-aliasing
define FontType.FONT_SDF                               0x2 ; SDF font generation, requires external shader

; Color blending modes (pre-defined)
define BlendMode BlendMode
define BlendMode.BLEND_ALPHA                            0x0 ; Blend textures considering alpha (default)
define BlendMode.BLEND_ADDITIVE                         0x1 ; Blend textures adding colors
define BlendMode.BLEND_MULTIPLIED                       0x2 ; Blend textures multiplying colors
define BlendMode.BLEND_ADD_COLORS                       0x3 ; Blend textures adding colors (alternative)
define BlendMode.BLEND_SUBTRACT_COLORS                  0x4 ; Blend textures subtracting colors (alternative)
define BlendMode.BLEND_ALPHA_PREMULTIPLY                0x5 ; Blend premultiplied textures considering alpha
define BlendMode.BLEND_CUSTOM                           0x6 ; Blend textures using custom src/dst factors (use rlSetBlendFactors())
define BlendMode.BLEND_CUSTOM_SEPARATE                  0x7 ; Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())

; Gesture
define Gesture Gesture
define Gesture.GESTURE_NONE                           0x0 ; No gesture
define Gesture.GESTURE_TAP                            0x1 ; Tap gesture
define Gesture.GESTURE_DOUBLETAP                      0x2 ; Double tap gesture
define Gesture.GESTURE_HOLD                           0x4 ; Hold gesture
define Gesture.GESTURE_DRAG                           0x8 ; Drag gesture
define Gesture.GESTURE_SWIPE_RIGHT                    0x10 ; Swipe right gesture
define Gesture.GESTURE_SWIPE_LEFT                     0x20 ; Swipe left gesture
define Gesture.GESTURE_SWIPE_UP                       0x40 ; Swipe up gesture
define Gesture.GESTURE_SWIPE_DOWN                     0x80 ; Swipe down gesture
define Gesture.GESTURE_PINCH_IN                       0x100 ; Pinch in gesture
define Gesture.GESTURE_PINCH_OUT                      0x200 ; Pinch out gesture

; Camera system modes
define CameraMode CameraMode
define CameraMode.CAMERA_CUSTOM                          0x0 ; Camera custom, controlled by user (UpdateCamera() does nothing)
define CameraMode.CAMERA_FREE                            0x1 ; Camera free mode
define CameraMode.CAMERA_ORBITAL                         0x2 ; Camera orbital, around target, zoom supported
define CameraMode.CAMERA_FIRST_PERSON                    0x3 ; Camera first person
define CameraMode.CAMERA_THIRD_PERSON                    0x4 ; Camera third person

; Camera projection
define CameraProjection CameraProjection
define CameraProjection.CAMERA_PERSPECTIVE                     0x0 ; Perspective projection
define CameraProjection.CAMERA_ORTHOGRAPHIC                    0x1 ; Orthographic projection

; N-patch layout
define NPatchLayout NPatchLayout
define NPatchLayout.NPATCH_NINE_PATCH                      0x0 ; Npatch layout: 3x3 tiles
define NPatchLayout.NPATCH_THREE_PATCH_VERTICAL            0x1 ; Npatch layout: 1x3 tiles
define NPatchLayout.NPATCH_THREE_PATCH_HORIZONTAL          0x2 ; Npatch layout: 3x1 tiles

; Structs
end namespace

; Raylib public headers use ordinary C structs, not pragma-packed structs.
; fasm2 struct definitions are textual, so ABI padding is emitted explicitly.
if defined RAYLIB_TARGET_32

; Structs (Win32 C ABI layout)

; Vector2, 2 components
struct RayLib.Vector2
	x dd ? ; Vector x component
	y dd ? ; Vector y component
ends

; Vector3, 3 components
struct RayLib.Vector3
	x dd ? ; Vector x component
	y dd ? ; Vector y component
	z dd ? ; Vector z component
ends

; Vector4, 4 components
struct RayLib.Vector4
	x dd ? ; Vector x component
	y dd ? ; Vector y component
	z dd ? ; Vector z component
	w dd ? ; Vector w component
ends

; Matrix, 4x4 components, column major, OpenGL style, right-handed
struct RayLib.Matrix
	m0 dd ? ; Matrix first row (4 components)
	m4 dd ? ; Matrix first row (4 components)
	m8 dd ? ; Matrix first row (4 components)
	m12 dd ? ; Matrix first row (4 components)
	m1 dd ? ; Matrix second row (4 components)
	m5 dd ? ; Matrix second row (4 components)
	m9 dd ? ; Matrix second row (4 components)
	m13 dd ? ; Matrix second row (4 components)
	m2 dd ? ; Matrix third row (4 components)
	m6 dd ? ; Matrix third row (4 components)
	m10 dd ? ; Matrix third row (4 components)
	m14 dd ? ; Matrix third row (4 components)
	m3 dd ? ; Matrix fourth row (4 components)
	m7 dd ? ; Matrix fourth row (4 components)
	m11 dd ? ; Matrix fourth row (4 components)
	m15 dd ? ; Matrix fourth row (4 components)
ends

; Color, 4 components, R8G8B8A8 (32bit)
struct RayLib.Color
	r db ? ; Color red value
	g db ? ; Color green value
	b db ? ; Color blue value
	a db ? ; Color alpha value
ends

; Rectangle, 4 components
struct RayLib.Rectangle
	x dd ? ; Rectangle top-left corner position x
	y dd ? ; Rectangle top-left corner position y
	width dd ? ; Rectangle width
	height dd ? ; Rectangle height
ends

; Image, pixel data stored in CPU memory (RAM)
struct RayLib.Image
	.data dd ? ; Image raw data
	width dd ? ; Image base width
	height dd ? ; Image base height
	mipmaps dd ? ; Mipmap levels, 1 by default
	.format dd ? ; Data format (PixelFormat type)
ends

; Texture, tex data stored in GPU memory (VRAM)
struct RayLib.Texture
	id dd ? ; OpenGL texture id
	width dd ? ; Texture base width
	height dd ? ; Texture base height
	mipmaps dd ? ; Mipmap levels, 1 by default
	.format dd ? ; Data format (PixelFormat type)
ends

; RenderTexture, fbo for texture rendering
struct RayLib.RenderTexture
	id dd ? ; OpenGL framebuffer object id
	texture RayLib.Texture ; Color buffer attachment texture
	depth RayLib.Texture ; Depth buffer attachment texture
ends

; NPatchInfo, n-patch layout info
struct RayLib.NPatchInfo
	source RayLib.Rectangle ; Texture source rectangle
	left dd ? ; Left border offset
	top dd ? ; Top border offset
	right dd ? ; Right border offset
	bottom dd ? ; Bottom border offset
	layout dd ? ; Layout of the n-patch: 3x3, 1x3 or 3x1
ends

; GlyphInfo, font characters glyphs info
struct RayLib.GlyphInfo
	value dd ? ; Character value (Unicode)
	offsetX dd ? ; Character offset X when drawing
	offsetY dd ? ; Character offset Y when drawing
	advanceX dd ? ; Character advance position X
	image RayLib.Image ; Character image data
ends

; Font, font texture and GlyphInfo array data
struct RayLib.Font
	baseSize dd ? ; Base size (default chars height)
	glyphCount dd ? ; Number of glyph characters
	glyphPadding dd ? ; Padding around the glyph characters
	texture RayLib.Texture ; Texture atlas containing the glyphs
	recs dd ? ; Rectangles in texture for the glyphs
	glyphs dd ? ; Glyphs info data
ends

; Camera, defines position/orientation in 3d space
struct RayLib.Camera3D
	position RayLib.Vector3 ; Camera position
	target RayLib.Vector3 ; Camera target it looks-at
	up RayLib.Vector3 ; Camera up vector (rotation over its axis)
	fovy dd ? ; Camera field-of-view aperture in Y (degrees) in perspective, used as near plane height in world units in orthographic
	projection dd ? ; Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
ends

; Camera2D, defines position/orientation in 2d space
struct RayLib.Camera2D
	offset RayLib.Vector2 ; Camera offset (screen space offset from window origin)
	target RayLib.Vector2 ; Camera target (world space target point that is mapped to screen space offset)
	rotation dd ? ; Camera rotation in degrees (pivots around target)
	zoom dd ? ; Camera zoom (scaling around target), must not be set to 0, set to 1.0f for no scale
ends

; Mesh, vertex data and vao/vbo
struct RayLib.Mesh
	vertexCount dd ? ; Number of vertices stored in arrays
	triangleCount dd ? ; Number of triangles stored (indexed or not)
	vertices dd ? ; Vertex position (XYZ - 3 components per vertex) (shader-location = 0)
	texcoords dd ? ; Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)
	texcoords2 dd ? ; Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5)
	normals dd ? ; Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)
	tangents dd ? ; Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4)
	colors dd ? ; Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)
	indices dd ? ; Vertex indices (in case vertex data comes indexed)
	boneCount dd ? ; Number of bones (MAX: 256 bones)
	boneIndices dd ? ; Vertex bone indices, up to 4 bones influence by vertex (skinning) (shader-location = 6)
	boneWeights dd ? ; Vertex bone weight, up to 4 bones influence by vertex (skinning) (shader-location = 7)
	animVertices dd ? ; Animated vertex positions (after bones transformations)
	animNormals dd ? ; Animated normals (after bones transformations)
	vaoId dd ? ; OpenGL Vertex Array Object id
	vboId dd ? ; OpenGL Vertex Buffer Objects id (default vertex data)
ends

; Shader
struct RayLib.Shader
	id dd ? ; Shader program id
	locs dd ? ; Shader locations array (RL_MAX_SHADER_LOCATIONS)
ends

; MaterialMap
struct RayLib.MaterialMap
	texture RayLib.Texture ; Material map texture
	color RayLib.Color ; Material map color
	value dd ? ; Material map value
ends

; Material, includes shader and maps
struct RayLib.Material
	shader RayLib.Shader ; Material shader
	maps dd ? ; Material maps array (MAX_MATERIAL_MAPS)
	params dd 4 dup ? ; Material generic parameters (if required)
ends

; Transform, vertex transformation data
struct RayLib.Transform
	translation RayLib.Vector3 ; Translation
	rotation RayLib.Vector4 ; Rotation
	scale RayLib.Vector3 ; Scale
ends

; Bone, skeletal animation bone
struct RayLib.BoneInfo
	name db 32 dup ? ; Bone name
	parent dd ? ; Bone parent
ends

; Skeleton, animation bones hierarchy
struct RayLib.ModelSkeleton
	boneCount dd ? ; Number of bones
	bones dd ? ; Bones information (skeleton)
	bindPose dd ? ; Bones base transformation (Transform[])
ends

; Model, meshes, materials and animation data
struct RayLib.Model
	transform_ RayLib.Matrix ; Local transform matrix
	meshCount dd ? ; Number of meshes
	materialCount dd ? ; Number of materials
	meshes dd ? ; Meshes array
	materials dd ? ; Materials array
	meshMaterial dd ? ; Mesh material number
	skeleton RayLib.ModelSkeleton ; Skeleton for animation
	currentPose dd ? ; Current animation pose (Transform[])
	boneMatrices dd ? ; Bones animated transformation matrices
ends

; ModelAnimation, contains a full animation sequence
struct RayLib.ModelAnimation
	name db 32 dup ? ; Animation name
	boneCount dd ? ; Number of bones (per pose)
	keyframeCount dd ? ; Number of animation key frames
	keyframePoses dd ? ; Animation sequence keyframe poses [keyframe][pose]
ends

; Ray, ray for raycasting
struct RayLib.Ray
	position RayLib.Vector3 ; Ray position (origin)
	direction RayLib.Vector3 ; Ray direction (normalized)
ends

; RayCollision, ray hit information
struct RayLib.RayCollision
	hit db ? ; Did the ray hit something?
	_pad0 rb 3
	distance dd ? ; Distance to the nearest hit
	point RayLib.Vector3 ; Point of the nearest hit
	normal RayLib.Vector3 ; Surface normal of hit
ends

; BoundingBox
struct RayLib.BoundingBox
	min RayLib.Vector3 ; Minimum vertex box-corner
	max RayLib.Vector3 ; Maximum vertex box-corner
ends

; Wave, audio wave data
struct RayLib.Wave
	frameCount dd ? ; Total number of frames (considering channels)
	sampleRate dd ? ; Frequency (samples per second)
	sampleSize dd ? ; Bit depth (bits per sample): 8, 16, 32 (24 not supported)
	channels dd ? ; Number of channels (1-mono, 2-stereo, ...)
	.data dd ? ; Buffer data pointer
ends

; AudioStream, custom audio stream
struct RayLib.AudioStream
	buffer dd ? ; Pointer to internal data used by the audio system
	processor dd ? ; Pointer to internal data processor, useful for audio effects
	sampleRate dd ? ; Frequency (samples per second)
	sampleSize dd ? ; Bit depth (bits per sample): 8, 16, 32 (24 not supported)
	channels dd ? ; Number of channels (1-mono, 2-stereo, ...)
ends

; Sound
struct RayLib.Sound
	stream RayLib.AudioStream ; Audio stream
	frameCount dd ? ; Total number of frames (considering channels)
ends

; Music, audio stream, anything longer than ~10 seconds should be streamed
struct RayLib.Music
	stream RayLib.AudioStream ; Audio stream
	frameCount dd ? ; Total number of frames (considering channels)
	looping db ? ; Music looping enable
	_pad0 rb 3
	ctxType dd ? ; Type of music context (audio filetype)
	ctxData dd ? ; Audio context data, depends on type
ends

; VrDeviceInfo, Head-Mounted-Display device parameters
struct RayLib.VrDeviceInfo
	hResolution dd ? ; Horizontal resolution in pixels
	vResolution dd ? ; Vertical resolution in pixels
	hScreenSize dd ? ; Horizontal size in meters
	vScreenSize dd ? ; Vertical size in meters
	eyeToScreenDistance dd ? ; Distance between eye and display in meters
	lensSeparationDistance dd ? ; Lens separation distance in meters
	interpupillaryDistance dd ? ; IPD (distance between pupils) in meters
	lensDistortionValues dd 4 dup ? ; Lens distortion constant parameters
	chromaAbCorrection dd 4 dup ? ; Chromatic aberration correction parameters
ends

; VrStereoConfig, VR stereo rendering configuration for simulator
struct RayLib.VrStereoConfig
	projection rb 2*sizeof.RayLib.Matrix ; VR projection matrices (per eye)
	viewOffset rb 2*sizeof.RayLib.Matrix ; VR view offset matrices (per eye)
	leftLensCenter dd 2 dup ? ; VR left lens center
	rightLensCenter dd 2 dup ? ; VR right lens center
	leftScreenCenter dd 2 dup ? ; VR left screen center
	rightScreenCenter dd 2 dup ? ; VR right screen center
	scale dd 2 dup ? ; VR distortion scale
	scaleIn dd 2 dup ? ; VR distortion scale in
ends

; File path list
struct RayLib.FilePathList
	count dd ? ; Filepaths entries count
	paths dd ? ; Filepaths entries
ends

; Automation event
struct RayLib.AutomationEvent
	.frame dd ? ; Event frame
	.type dd ? ; Event type (AutomationEventType)
	params dd 4 dup ? ; Event parameters (if required)
ends

; Automation event list
struct RayLib.AutomationEventList
	capacity dd ? ; Events max entries (MAX_AUTOMATION_EVENTS)
	count dd ? ; Events entries count
	events dd ? ; Events entries
ends

else

; Structs (Win64 C ABI layout)

; Vector2, 2 components
struct RayLib.Vector2
	x dd ? ; Vector x component
	y dd ? ; Vector y component
ends

; Vector3, 3 components
struct RayLib.Vector3
	x dd ? ; Vector x component
	y dd ? ; Vector y component
	z dd ? ; Vector z component
ends

; Vector4, 4 components
struct RayLib.Vector4
	x dd ? ; Vector x component
	y dd ? ; Vector y component
	z dd ? ; Vector z component
	w dd ? ; Vector w component
ends

; Matrix, 4x4 components, column major, OpenGL style, right-handed
struct RayLib.Matrix
	m0 dd ? ; Matrix first row (4 components)
	m4 dd ? ; Matrix first row (4 components)
	m8 dd ? ; Matrix first row (4 components)
	m12 dd ? ; Matrix first row (4 components)
	m1 dd ? ; Matrix second row (4 components)
	m5 dd ? ; Matrix second row (4 components)
	m9 dd ? ; Matrix second row (4 components)
	m13 dd ? ; Matrix second row (4 components)
	m2 dd ? ; Matrix third row (4 components)
	m6 dd ? ; Matrix third row (4 components)
	m10 dd ? ; Matrix third row (4 components)
	m14 dd ? ; Matrix third row (4 components)
	m3 dd ? ; Matrix fourth row (4 components)
	m7 dd ? ; Matrix fourth row (4 components)
	m11 dd ? ; Matrix fourth row (4 components)
	m15 dd ? ; Matrix fourth row (4 components)
ends

; Color, 4 components, R8G8B8A8 (32bit)
struct RayLib.Color
	r db ? ; Color red value
	g db ? ; Color green value
	b db ? ; Color blue value
	a db ? ; Color alpha value
ends

; Rectangle, 4 components
struct RayLib.Rectangle
	x dd ? ; Rectangle top-left corner position x
	y dd ? ; Rectangle top-left corner position y
	width dd ? ; Rectangle width
	height dd ? ; Rectangle height
ends

; Image, pixel data stored in CPU memory (RAM)
struct RayLib.Image
	.data dq ? ; Image raw data
	width dd ? ; Image base width
	height dd ? ; Image base height
	mipmaps dd ? ; Mipmap levels, 1 by default
	.format dd ? ; Data format (PixelFormat type)
ends

; Texture, tex data stored in GPU memory (VRAM)
struct RayLib.Texture
	id dd ? ; OpenGL texture id
	width dd ? ; Texture base width
	height dd ? ; Texture base height
	mipmaps dd ? ; Mipmap levels, 1 by default
	.format dd ? ; Data format (PixelFormat type)
ends

; RenderTexture, fbo for texture rendering
struct RayLib.RenderTexture
	id dd ? ; OpenGL framebuffer object id
	texture RayLib.Texture ; Color buffer attachment texture
	depth RayLib.Texture ; Depth buffer attachment texture
ends

; NPatchInfo, n-patch layout info
struct RayLib.NPatchInfo
	source RayLib.Rectangle ; Texture source rectangle
	left dd ? ; Left border offset
	top dd ? ; Top border offset
	right dd ? ; Right border offset
	bottom dd ? ; Bottom border offset
	layout dd ? ; Layout of the n-patch: 3x3, 1x3 or 3x1
ends

; GlyphInfo, font characters glyphs info
struct RayLib.GlyphInfo
	value dd ? ; Character value (Unicode)
	offsetX dd ? ; Character offset X when drawing
	offsetY dd ? ; Character offset Y when drawing
	advanceX dd ? ; Character advance position X
	image RayLib.Image ; Character image data
ends

; Font, font texture and GlyphInfo array data
struct RayLib.Font
	baseSize dd ? ; Base size (default chars height)
	glyphCount dd ? ; Number of glyph characters
	glyphPadding dd ? ; Padding around the glyph characters
	texture RayLib.Texture ; Texture atlas containing the glyphs
	recs dq ? ; Rectangles in texture for the glyphs
	glyphs dq ? ; Glyphs info data
ends

; Camera, defines position/orientation in 3d space
struct RayLib.Camera3D
	position RayLib.Vector3 ; Camera position
	target RayLib.Vector3 ; Camera target it looks-at
	up RayLib.Vector3 ; Camera up vector (rotation over its axis)
	fovy dd ? ; Camera field-of-view aperture in Y (degrees) in perspective, used as near plane height in world units in orthographic
	projection dd ? ; Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
ends

; Camera2D, defines position/orientation in 2d space
struct RayLib.Camera2D
	offset RayLib.Vector2 ; Camera offset (screen space offset from window origin)
	target RayLib.Vector2 ; Camera target (world space target point that is mapped to screen space offset)
	rotation dd ? ; Camera rotation in degrees (pivots around target)
	zoom dd ? ; Camera zoom (scaling around target), must not be set to 0, set to 1.0f for no scale
ends

; Mesh, vertex data and vao/vbo
struct RayLib.Mesh
	vertexCount dd ? ; Number of vertices stored in arrays
	triangleCount dd ? ; Number of triangles stored (indexed or not)
	vertices dq ? ; Vertex position (XYZ - 3 components per vertex) (shader-location = 0)
	texcoords dq ? ; Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)
	texcoords2 dq ? ; Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5)
	normals dq ? ; Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)
	tangents dq ? ; Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4)
	colors dq ? ; Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)
	indices dq ? ; Vertex indices (in case vertex data comes indexed)
	boneCount dd ? ; Number of bones (MAX: 256 bones)
	_pad0 rb 4
	boneIndices dq ? ; Vertex bone indices, up to 4 bones influence by vertex (skinning) (shader-location = 6)
	boneWeights dq ? ; Vertex bone weight, up to 4 bones influence by vertex (skinning) (shader-location = 7)
	animVertices dq ? ; Animated vertex positions (after bones transformations)
	animNormals dq ? ; Animated normals (after bones transformations)
	vaoId dd ? ; OpenGL Vertex Array Object id
	_pad1 rb 4
	vboId dq ? ; OpenGL Vertex Buffer Objects id (default vertex data)
ends

; Shader
struct RayLib.Shader
	id dd ? ; Shader program id
	_pad0 rb 4
	locs dq ? ; Shader locations array (RL_MAX_SHADER_LOCATIONS)
ends

; MaterialMap
struct RayLib.MaterialMap
	texture RayLib.Texture ; Material map texture
	color RayLib.Color ; Material map color
	value dd ? ; Material map value
ends

; Material, includes shader and maps
struct RayLib.Material
	shader RayLib.Shader ; Material shader
	maps dq ? ; Material maps array (MAX_MATERIAL_MAPS)
	params dd 4 dup ? ; Material generic parameters (if required)
ends

; Transform, vertex transformation data
struct RayLib.Transform
	translation RayLib.Vector3 ; Translation
	rotation RayLib.Vector4 ; Rotation
	scale RayLib.Vector3 ; Scale
ends

; Bone, skeletal animation bone
struct RayLib.BoneInfo
	name db 32 dup ? ; Bone name
	parent dd ? ; Bone parent
ends

; Skeleton, animation bones hierarchy
struct RayLib.ModelSkeleton
	boneCount dd ? ; Number of bones
	_pad0 rb 4
	bones dq ? ; Bones information (skeleton)
	bindPose dq ? ; Bones base transformation (Transform[])
ends

; Model, meshes, materials and animation data
struct RayLib.Model
	transform_ RayLib.Matrix ; Local transform matrix
	meshCount dd ? ; Number of meshes
	materialCount dd ? ; Number of materials
	meshes dq ? ; Meshes array
	materials dq ? ; Materials array
	meshMaterial dq ? ; Mesh material number
	skeleton RayLib.ModelSkeleton ; Skeleton for animation
	currentPose dq ? ; Current animation pose (Transform[])
	boneMatrices dq ? ; Bones animated transformation matrices
ends

; ModelAnimation, contains a full animation sequence
struct RayLib.ModelAnimation
	name db 32 dup ? ; Animation name
	boneCount dd ? ; Number of bones (per pose)
	keyframeCount dd ? ; Number of animation key frames
	keyframePoses dq ? ; Animation sequence keyframe poses [keyframe][pose]
ends

; Ray, ray for raycasting
struct RayLib.Ray
	position RayLib.Vector3 ; Ray position (origin)
	direction RayLib.Vector3 ; Ray direction (normalized)
ends

; RayCollision, ray hit information
struct RayLib.RayCollision
	hit db ? ; Did the ray hit something?
	_pad0 rb 3
	distance dd ? ; Distance to the nearest hit
	point RayLib.Vector3 ; Point of the nearest hit
	normal RayLib.Vector3 ; Surface normal of hit
ends

; BoundingBox
struct RayLib.BoundingBox
	min RayLib.Vector3 ; Minimum vertex box-corner
	max RayLib.Vector3 ; Maximum vertex box-corner
ends

; Wave, audio wave data
struct RayLib.Wave
	frameCount dd ? ; Total number of frames (considering channels)
	sampleRate dd ? ; Frequency (samples per second)
	sampleSize dd ? ; Bit depth (bits per sample): 8, 16, 32 (24 not supported)
	channels dd ? ; Number of channels (1-mono, 2-stereo, ...)
	.data dq ? ; Buffer data pointer
ends

; AudioStream, custom audio stream
struct RayLib.AudioStream
	buffer dq ? ; Pointer to internal data used by the audio system
	processor dq ? ; Pointer to internal data processor, useful for audio effects
	sampleRate dd ? ; Frequency (samples per second)
	sampleSize dd ? ; Bit depth (bits per sample): 8, 16, 32 (24 not supported)
	channels dd ? ; Number of channels (1-mono, 2-stereo, ...)
	_pad0 rb 4
ends

; Sound
struct RayLib.Sound
	stream RayLib.AudioStream ; Audio stream
	frameCount dd ? ; Total number of frames (considering channels)
	_pad0 rb 4
ends

; Music, audio stream, anything longer than ~10 seconds should be streamed
struct RayLib.Music
	stream RayLib.AudioStream ; Audio stream
	frameCount dd ? ; Total number of frames (considering channels)
	looping db ? ; Music looping enable
	_pad0 rb 3
	ctxType dd ? ; Type of music context (audio filetype)
	_pad1 rb 4
	ctxData dq ? ; Audio context data, depends on type
ends

; VrDeviceInfo, Head-Mounted-Display device parameters
struct RayLib.VrDeviceInfo
	hResolution dd ? ; Horizontal resolution in pixels
	vResolution dd ? ; Vertical resolution in pixels
	hScreenSize dd ? ; Horizontal size in meters
	vScreenSize dd ? ; Vertical size in meters
	eyeToScreenDistance dd ? ; Distance between eye and display in meters
	lensSeparationDistance dd ? ; Lens separation distance in meters
	interpupillaryDistance dd ? ; IPD (distance between pupils) in meters
	lensDistortionValues dd 4 dup ? ; Lens distortion constant parameters
	chromaAbCorrection dd 4 dup ? ; Chromatic aberration correction parameters
ends

; VrStereoConfig, VR stereo rendering configuration for simulator
struct RayLib.VrStereoConfig
	projection rb 2*sizeof.RayLib.Matrix ; VR projection matrices (per eye)
	viewOffset rb 2*sizeof.RayLib.Matrix ; VR view offset matrices (per eye)
	leftLensCenter dd 2 dup ? ; VR left lens center
	rightLensCenter dd 2 dup ? ; VR right lens center
	leftScreenCenter dd 2 dup ? ; VR left screen center
	rightScreenCenter dd 2 dup ? ; VR right screen center
	scale dd 2 dup ? ; VR distortion scale
	scaleIn dd 2 dup ? ; VR distortion scale in
ends

; File path list
struct RayLib.FilePathList
	count dd ? ; Filepaths entries count
	_pad0 rb 4
	paths dq ? ; Filepaths entries
ends

; Automation event
struct RayLib.AutomationEvent
	.frame dd ? ; Event frame
	.type dd ? ; Event type (AutomationEventType)
	params dd 4 dup ? ; Event parameters (if required)
ends

; Automation event list
struct RayLib.AutomationEventList
	capacity dd ? ; Events max entries (MAX_AUTOMATION_EVENTS)
	count dd ? ; Events entries count
	events dq ? ; Events entries
ends

end if

namespace RayLib

; Type aliases
define Quaternion               Vector4 ; Quaternion, 4 components (Vector4 alias)
define Texture2D                Texture ; Texture2D, same as Texture
define TextureCubemap           Texture ; TextureCubemap, same as Texture
define RenderTexture2D          RenderTexture ; RenderTexture2D, same as RenderTexture
define Camera                   Camera3D ; Camera type fallback, defaults to Camera3D
define ModelAnimPose            Transform ; Anim pose, an array of Transform[]
if defined RAYLIB_TARGET_32
define AudioCallback            dword ; callback pointer
define LoadFileDataCallback     dword ; callback pointer
define LoadFileTextCallback     dword ; callback pointer
define SaveFileDataCallback     dword ; callback pointer
define SaveFileTextCallback     dword ; callback pointer
define TraceLogCallback         dword ; callback pointer
else
define AudioCallback            qword ; callback pointer
define LoadFileDataCallback     qword ; callback pointer
define LoadFileTextCallback     qword ; callback pointer
define SaveFileDataCallback     qword ; callback pointer
define SaveFileTextCallback     qword ; callback pointer
define TraceLogCallback         qword ; callback pointer
end if

end namespace

; Initialize window and OpenGL context
; void InitWindow(int width, int height, const char * title)
calminstruction InitWindow width*, height*, title*
	local line
	arrange line, =RLAPI =InitWindow, width,height,title
	assemble line
end calminstruction

; Close window and unload OpenGL context
; void CloseWindow(void)
calminstruction CloseWindow
	local line
	arrange line, =RLAPI =CloseWindow
	assemble line
end calminstruction

; Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
; bool WindowShouldClose(void)
calminstruction WindowShouldClose
	local line
	arrange line, =RLAPI =WindowShouldClose
	assemble line
end calminstruction

; Check if window has been initialized successfully
; bool IsWindowReady(void)
calminstruction IsWindowReady
	local line
	arrange line, =RLAPI =IsWindowReady
	assemble line
end calminstruction

; Check if window is currently fullscreen
; bool IsWindowFullscreen(void)
calminstruction IsWindowFullscreen
	local line
	arrange line, =RLAPI =IsWindowFullscreen
	assemble line
end calminstruction

; Check if window is currently hidden
; bool IsWindowHidden(void)
calminstruction IsWindowHidden
	local line
	arrange line, =RLAPI =IsWindowHidden
	assemble line
end calminstruction

; Check if window is currently minimized
; bool IsWindowMinimized(void)
calminstruction IsWindowMinimized
	local line
	arrange line, =RLAPI =IsWindowMinimized
	assemble line
end calminstruction

; Check if window is currently maximized
; bool IsWindowMaximized(void)
calminstruction IsWindowMaximized
	local line
	arrange line, =RLAPI =IsWindowMaximized
	assemble line
end calminstruction

; Check if window is currently focused
; bool IsWindowFocused(void)
calminstruction IsWindowFocused
	local line
	arrange line, =RLAPI =IsWindowFocused
	assemble line
end calminstruction

; Check if window has been resized last frame
; bool IsWindowResized(void)
calminstruction IsWindowResized
	local line
	arrange line, =RLAPI =IsWindowResized
	assemble line
end calminstruction

; Check if one specific window flag is enabled
; bool IsWindowState(ConfigFlags flag)
calminstruction IsWindowState flag*
	local line
	transform flag, RayLib.ConfigFlags
	arrange line, =RLAPI =IsWindowState, flag
	assemble line
end calminstruction

; Set window configuration state using flags
; void SetWindowState(ConfigFlags flags)
calminstruction SetWindowState flags*
	local line
	transform flags, RayLib.ConfigFlags
	arrange line, =RLAPI =SetWindowState, flags
	assemble line
end calminstruction

; Clear window configuration state flags
; void ClearWindowState(ConfigFlags flags)
calminstruction ClearWindowState flags*
	local line
	transform flags, RayLib.ConfigFlags
	arrange line, =RLAPI =ClearWindowState, flags
	assemble line
end calminstruction

; Toggle window state: fullscreen/windowed, resizes monitor to match window resolution
; void ToggleFullscreen(void)
calminstruction ToggleFullscreen
	local line
	arrange line, =RLAPI =ToggleFullscreen
	assemble line
end calminstruction

; Toggle window state: borderless windowed, resizes window to match monitor resolution
; void ToggleBorderlessWindowed(void)
calminstruction ToggleBorderlessWindowed
	local line
	arrange line, =RLAPI =ToggleBorderlessWindowed
	assemble line
end calminstruction

; Set window state: maximized, if resizable
; void MaximizeWindow(void)
calminstruction MaximizeWindow
	local line
	arrange line, =RLAPI =MaximizeWindow
	assemble line
end calminstruction

; Set window state: minimized, if resizable
; void MinimizeWindow(void)
calminstruction MinimizeWindow
	local line
	arrange line, =RLAPI =MinimizeWindow
	assemble line
end calminstruction

; Restore window from being minimized/maximized
; void RestoreWindow(void)
calminstruction RestoreWindow
	local line
	arrange line, =RLAPI =RestoreWindow
	assemble line
end calminstruction

; Set icon for window (single image, RGBA 32bit)
; void SetWindowIcon(Image image)
calminstruction SetWindowIcon image*
	local line
	arrange line, =RLAPI =SetWindowIcon, image
	assemble line
end calminstruction

; Set icon for window (multiple images, RGBA 32bit)
; void SetWindowIcons(Image * images, int count)
calminstruction SetWindowIcons images*, count*
	local line
	arrange line, =RLAPI =SetWindowIcons, images,count
	assemble line
end calminstruction

; Set title for window
; void SetWindowTitle(const char * title)
calminstruction SetWindowTitle title*
	local line
	arrange line, =RLAPI =SetWindowTitle, title
	assemble line
end calminstruction

; Set window position on screen
; void SetWindowPosition(int x, int y)
calminstruction SetWindowPosition x*, y*
	local line
	arrange line, =RLAPI =SetWindowPosition, x,y
	assemble line
end calminstruction

; Set monitor for the current window
; void SetWindowMonitor(int monitor)
calminstruction SetWindowMonitor monitor*
	local line
	arrange line, =RLAPI =SetWindowMonitor, monitor
	assemble line
end calminstruction

; Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
; void SetWindowMinSize(int width, int height)
calminstruction SetWindowMinSize width*, height*
	local line
	arrange line, =RLAPI =SetWindowMinSize, width,height
	assemble line
end calminstruction

; Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
; void SetWindowMaxSize(int width, int height)
calminstruction SetWindowMaxSize width*, height*
	local line
	arrange line, =RLAPI =SetWindowMaxSize, width,height
	assemble line
end calminstruction

; Set window dimensions
; void SetWindowSize(int width, int height)
calminstruction SetWindowSize width*, height*
	local line
	arrange line, =RLAPI =SetWindowSize, width,height
	assemble line
end calminstruction

; Set window opacity [0.0f..1.0f]
; void SetWindowOpacity(float opacity)
calminstruction SetWindowOpacity opacity*
	local line
	arrange line, =RLAPI =SetWindowOpacity, opacity
	assemble line
end calminstruction

; Set window focused
; void SetWindowFocused(void)
calminstruction SetWindowFocused
	local line
	arrange line, =RLAPI =SetWindowFocused
	assemble line
end calminstruction

; Get native window handle
; void * GetWindowHandle(void)
calminstruction GetWindowHandle
	local line
	arrange line, =RLAPI =GetWindowHandle
	assemble line
end calminstruction

; Get current screen width
; int GetScreenWidth(void)
calminstruction GetScreenWidth
	local line
	arrange line, =RLAPI =GetScreenWidth
	assemble line
end calminstruction

; Get current screen height
; int GetScreenHeight(void)
calminstruction GetScreenHeight
	local line
	arrange line, =RLAPI =GetScreenHeight
	assemble line
end calminstruction

; Get current render width (it considers HiDPI)
; int GetRenderWidth(void)
calminstruction GetRenderWidth
	local line
	arrange line, =RLAPI =GetRenderWidth
	assemble line
end calminstruction

; Get current render height (it considers HiDPI)
; int GetRenderHeight(void)
calminstruction GetRenderHeight
	local line
	arrange line, =RLAPI =GetRenderHeight
	assemble line
end calminstruction

; Get number of connected monitors
; int GetMonitorCount(void)
calminstruction GetMonitorCount
	local line
	arrange line, =RLAPI =GetMonitorCount
	assemble line
end calminstruction

; Get current monitor where window is placed
; int GetCurrentMonitor(void)
calminstruction GetCurrentMonitor
	local line
	arrange line, =RLAPI =GetCurrentMonitor
	assemble line
end calminstruction

; Get specified monitor position
; Vector2 GetMonitorPosition(int monitor)
calminstruction GetMonitorPosition monitor*
	local line
	arrange line, =RLAPI =GetMonitorPosition, monitor
	assemble line
end calminstruction

; Get specified monitor width (current video mode used by monitor)
; int GetMonitorWidth(int monitor)
calminstruction GetMonitorWidth monitor*
	local line
	arrange line, =RLAPI =GetMonitorWidth, monitor
	assemble line
end calminstruction

; Get specified monitor height (current video mode used by monitor)
; int GetMonitorHeight(int monitor)
calminstruction GetMonitorHeight monitor*
	local line
	arrange line, =RLAPI =GetMonitorHeight, monitor
	assemble line
end calminstruction

; Get specified monitor physical width in millimetres
; int GetMonitorPhysicalWidth(int monitor)
calminstruction GetMonitorPhysicalWidth monitor*
	local line
	arrange line, =RLAPI =GetMonitorPhysicalWidth, monitor
	assemble line
end calminstruction

; Get specified monitor physical height in millimetres
; int GetMonitorPhysicalHeight(int monitor)
calminstruction GetMonitorPhysicalHeight monitor*
	local line
	arrange line, =RLAPI =GetMonitorPhysicalHeight, monitor
	assemble line
end calminstruction

; Get specified monitor refresh rate
; int GetMonitorRefreshRate(int monitor)
calminstruction GetMonitorRefreshRate monitor*
	local line
	arrange line, =RLAPI =GetMonitorRefreshRate, monitor
	assemble line
end calminstruction

; Get window position XY on monitor
; Vector2 GetWindowPosition(void)
calminstruction GetWindowPosition
	local line
	arrange line, =RLAPI =GetWindowPosition
	assemble line
end calminstruction

; Get window scale DPI factor
; Vector2 GetWindowScaleDPI(void)
calminstruction GetWindowScaleDPI
	local line
	arrange line, =RLAPI =GetWindowScaleDPI
	assemble line
end calminstruction

; Get the human-readable, UTF-8 encoded name of the specified monitor
; const char * GetMonitorName(int monitor)
calminstruction GetMonitorName monitor*
	local line
	arrange line, =RLAPI =GetMonitorName, monitor
	assemble line
end calminstruction

; Set clipboard text content
; void SetClipboardText(const char * text)
calminstruction SetClipboardText text*
	local line
	arrange line, =RLAPI =SetClipboardText, text
	assemble line
end calminstruction

; Get clipboard text content
; const char * GetClipboardText(void)
calminstruction GetClipboardText
	local line
	arrange line, =RLAPI =GetClipboardText
	assemble line
end calminstruction

; Get clipboard image content
; Image GetClipboardImage(void)
calminstruction GetClipboardImage
	local line
	arrange line, =RLAPI =GetClipboardImage
	assemble line
end calminstruction

; Enable waiting for events on EndDrawing(), no automatic event polling
; void EnableEventWaiting(void)
calminstruction EnableEventWaiting
	local line
	arrange line, =RLAPI =EnableEventWaiting
	assemble line
end calminstruction

; Disable waiting for events on EndDrawing(), automatic events polling
; void DisableEventWaiting(void)
calminstruction DisableEventWaiting
	local line
	arrange line, =RLAPI =DisableEventWaiting
	assemble line
end calminstruction

; Shows cursor
; void ShowCursor(void)
calminstruction ShowCursor
	local line
	arrange line, =RLAPI =ShowCursor
	assemble line
end calminstruction

; Hides cursor
; void HideCursor(void)
calminstruction HideCursor
	local line
	arrange line, =RLAPI =HideCursor
	assemble line
end calminstruction

; Check if cursor is not visible
; bool IsCursorHidden(void)
calminstruction IsCursorHidden
	local line
	arrange line, =RLAPI =IsCursorHidden
	assemble line
end calminstruction

; Enables cursor (unlock cursor)
; void EnableCursor(void)
calminstruction EnableCursor
	local line
	arrange line, =RLAPI =EnableCursor
	assemble line
end calminstruction

; Disables cursor (lock cursor)
; void DisableCursor(void)
calminstruction DisableCursor
	local line
	arrange line, =RLAPI =DisableCursor
	assemble line
end calminstruction

; Check if cursor is on the screen
; bool IsCursorOnScreen(void)
calminstruction IsCursorOnScreen
	local line
	arrange line, =RLAPI =IsCursorOnScreen
	assemble line
end calminstruction

; Set background color (framebuffer clear color)
; void ClearBackground(Color color)
calminstruction ClearBackground color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ClearBackground, color
	assemble line
end calminstruction

; Setup canvas (framebuffer) to start drawing
; void BeginDrawing(void)
calminstruction BeginDrawing
	local line
	arrange line, =RLAPI =BeginDrawing
	assemble line
end calminstruction

; End canvas drawing and swap buffers (double buffering)
; void EndDrawing(void)
calminstruction EndDrawing
	local line
	arrange line, =RLAPI =EndDrawing
	assemble line
end calminstruction

; Begin 2D mode with custom camera (2D)
; void BeginMode2D(Camera2D camera)
calminstruction BeginMode2D camera*
	local line
	arrange line, =RLAPI =BeginMode2D, camera
	assemble line
end calminstruction

; Ends 2D mode with custom camera
; void EndMode2D(void)
calminstruction EndMode2D
	local line
	arrange line, =RLAPI =EndMode2D
	assemble line
end calminstruction

; Begin 3D mode with custom camera (3D)
; void BeginMode3D(Camera3D camera)
calminstruction BeginMode3D camera*
	local line
	arrange line, =RLAPI =BeginMode3D, camera
	assemble line
end calminstruction

; Ends 3D mode and returns to default 2D orthographic mode
; void EndMode3D(void)
calminstruction EndMode3D
	local line
	arrange line, =RLAPI =EndMode3D
	assemble line
end calminstruction

; Begin drawing to render texture
; void BeginTextureMode(RenderTexture2D target)
calminstruction BeginTextureMode target*
	local line
	arrange line, =RLAPI =BeginTextureMode, target
	assemble line
end calminstruction

; Ends drawing to render texture
; void EndTextureMode(void)
calminstruction EndTextureMode
	local line
	arrange line, =RLAPI =EndTextureMode
	assemble line
end calminstruction

; Begin custom shader drawing
; void BeginShaderMode(Shader shader)
calminstruction BeginShaderMode shader*
	local line
	arrange line, =RLAPI =BeginShaderMode, shader
	assemble line
end calminstruction

; End custom shader drawing (use default shader)
; void EndShaderMode(void)
calminstruction EndShaderMode
	local line
	arrange line, =RLAPI =EndShaderMode
	assemble line
end calminstruction

; Begin blending mode (alpha, additive, multiplied, subtract, custom)
; void BeginBlendMode(BlendMode mode)
calminstruction BeginBlendMode mode*
	local line
	transform mode, RayLib.BlendMode
	arrange line, =RLAPI =BeginBlendMode, mode
	assemble line
end calminstruction

; End blending mode (reset to default: alpha blending)
; void EndBlendMode(void)
calminstruction EndBlendMode
	local line
	arrange line, =RLAPI =EndBlendMode
	assemble line
end calminstruction

; Begin scissor mode (define screen area for following drawing)
; void BeginScissorMode(int x, int y, int width, int height)
calminstruction BeginScissorMode x*, y*, width*, height*
	local line
	arrange line, =RLAPI =BeginScissorMode, x,y,width,height
	assemble line
end calminstruction

; End scissor mode
; void EndScissorMode(void)
calminstruction EndScissorMode
	local line
	arrange line, =RLAPI =EndScissorMode
	assemble line
end calminstruction

; Begin stereo rendering (requires VR simulator)
; void BeginVrStereoMode(VrStereoConfig config)
calminstruction BeginVrStereoMode config*
	local line
	arrange line, =RLAPI =BeginVrStereoMode, config
	assemble line
end calminstruction

; End stereo rendering (requires VR simulator)
; void EndVrStereoMode(void)
calminstruction EndVrStereoMode
	local line
	arrange line, =RLAPI =EndVrStereoMode
	assemble line
end calminstruction

; Load VR stereo config for VR simulator device parameters
; VrStereoConfig LoadVrStereoConfig(VrDeviceInfo device)
calminstruction LoadVrStereoConfig device*
	local line
	arrange line, =RLAPI =LoadVrStereoConfig, device
	assemble line
end calminstruction

; Unload VR stereo config
; void UnloadVrStereoConfig(VrStereoConfig config)
calminstruction UnloadVrStereoConfig config*
	local line
	arrange line, =RLAPI =UnloadVrStereoConfig, config
	assemble line
end calminstruction

; Load shader from files and bind default locations
; Shader LoadShader(const char * vsFileName, const char * fsFileName)
calminstruction LoadShader vsFileName*, fsFileName*
	local line
	arrange line, =RLAPI =LoadShader, vsFileName,fsFileName
	assemble line
end calminstruction

; Load shader from code strings and bind default locations
; Shader LoadShaderFromMemory(const char * vsCode, const char * fsCode)
calminstruction LoadShaderFromMemory vsCode*, fsCode*
	local line
	arrange line, =RLAPI =LoadShaderFromMemory, vsCode,fsCode
	assemble line
end calminstruction

; Check if a shader is valid (loaded on GPU)
; bool IsShaderValid(Shader shader)
calminstruction IsShaderValid shader*
	local line
	arrange line, =RLAPI =IsShaderValid, shader
	assemble line
end calminstruction

; Get shader uniform location
; int GetShaderLocation(Shader shader, const char * uniformName)
calminstruction GetShaderLocation shader*, uniformName*
	local line
	arrange line, =RLAPI =GetShaderLocation, shader,uniformName
	assemble line
end calminstruction

; Get shader attribute location
; int GetShaderLocationAttrib(Shader shader, const char * attribName)
calminstruction GetShaderLocationAttrib shader*, attribName*
	local line
	arrange line, =RLAPI =GetShaderLocationAttrib, shader,attribName
	assemble line
end calminstruction

; Set shader uniform value
; void SetShaderValue(Shader shader, int locIndex, const void * value, ShaderUniformDataType uniformType)
calminstruction SetShaderValue shader*, locIndex*, value*, uniformType*
	local line
	transform uniformType, RayLib.ShaderUniformDataType
	arrange line, =RLAPI =SetShaderValue, shader,locIndex,value,uniformType
	assemble line
end calminstruction

; Set shader uniform value vector
; void SetShaderValueV(Shader shader, int locIndex, const void * value, ShaderUniformDataType uniformType, int count)
calminstruction SetShaderValueV shader*, locIndex*, value*, uniformType*, count*
	local line
	transform uniformType, RayLib.ShaderUniformDataType
	arrange line, =RLAPI =SetShaderValueV, shader,locIndex,value,uniformType,count
	assemble line
end calminstruction

; Set shader uniform value (matrix 4x4)
; void SetShaderValueMatrix(Shader shader, int locIndex, Matrix mat)
calminstruction SetShaderValueMatrix shader*, locIndex*, mat*
	local line
	arrange line, =RLAPI =SetShaderValueMatrix, shader,locIndex,mat
	assemble line
end calminstruction

; Set shader uniform value and bind the texture (sampler2d)
; void SetShaderValueTexture(Shader shader, int locIndex, Texture2D texture)
calminstruction SetShaderValueTexture shader*, locIndex*, texture*
	local line
	arrange line, =RLAPI =SetShaderValueTexture, shader,locIndex,texture
	assemble line
end calminstruction

; Unload shader from GPU memory (VRAM)
; void UnloadShader(Shader shader)
calminstruction UnloadShader shader*
	local line
	arrange line, =RLAPI =UnloadShader, shader
	assemble line
end calminstruction

; Get a ray trace from screen position (i.e mouse)
; Ray GetScreenToWorldRay(Vector2 position, Camera camera)
calminstruction GetScreenToWorldRay position*, camera*
	local line
	arrange line, =RLAPI =GetScreenToWorldRay, position,camera
	assemble line
end calminstruction

; Get a ray trace from screen position (i.e mouse) in a viewport
; Ray GetScreenToWorldRayEx(Vector2 position, Camera camera, int width, int height)
calminstruction GetScreenToWorldRayEx position*, camera*, width*, height*
	local line
	arrange line, =RLAPI =GetScreenToWorldRayEx, position,camera,width,height
	assemble line
end calminstruction

; Get the screen space position for a 3d world space position
; Vector2 GetWorldToScreen(Vector3 position, Camera camera)
calminstruction GetWorldToScreen position*, camera*
	local line
	arrange line, =RLAPI =GetWorldToScreen, position,camera
	assemble line
end calminstruction

; Get size position for a 3d world space position
; Vector2 GetWorldToScreenEx(Vector3 position, Camera camera, int width, int height)
calminstruction GetWorldToScreenEx position*, camera*, width*, height*
	local line
	arrange line, =RLAPI =GetWorldToScreenEx, position,camera,width,height
	assemble line
end calminstruction

; Get the screen space position for a 2d camera world space position
; Vector2 GetWorldToScreen2D(Vector2 position, Camera2D camera)
calminstruction GetWorldToScreen2D position*, camera*
	local line
	arrange line, =RLAPI =GetWorldToScreen2D, position,camera
	assemble line
end calminstruction

; Get the world space position for a 2d camera screen space position
; Vector2 GetScreenToWorld2D(Vector2 position, Camera2D camera)
calminstruction GetScreenToWorld2D position*, camera*
	local line
	arrange line, =RLAPI =GetScreenToWorld2D, position,camera
	assemble line
end calminstruction

; Get camera transform matrix (view matrix)
; Matrix GetCameraMatrix(Camera camera)
calminstruction GetCameraMatrix camera*
	local line
	arrange line, =RLAPI =GetCameraMatrix, camera
	assemble line
end calminstruction

; Get camera 2d transform matrix
; Matrix GetCameraMatrix2D(Camera2D camera)
calminstruction GetCameraMatrix2D camera*
	local line
	arrange line, =RLAPI =GetCameraMatrix2D, camera
	assemble line
end calminstruction

; Set target FPS (maximum)
; void SetTargetFPS(int fps)
calminstruction SetTargetFPS fps*
	local line
	arrange line, =RLAPI =SetTargetFPS, fps
	assemble line
end calminstruction

; Get time in seconds for last frame drawn (delta time)
; float GetFrameTime(void)
calminstruction GetFrameTime
	local line
	arrange line, =RLAPI =GetFrameTime
	assemble line
end calminstruction

; Get elapsed time in seconds since InitWindow()
; double GetTime(void)
calminstruction GetTime
	local line
	arrange line, =RLAPI =GetTime
	assemble line
end calminstruction

; Get current FPS
; int GetFPS(void)
calminstruction GetFPS
	local line
	arrange line, =RLAPI =GetFPS
	assemble line
end calminstruction

; Swap back buffer with front buffer (screen drawing)
; void SwapScreenBuffer(void)
calminstruction SwapScreenBuffer
	local line
	arrange line, =RLAPI =SwapScreenBuffer
	assemble line
end calminstruction

; Register all input events
; void PollInputEvents(void)
calminstruction PollInputEvents
	local line
	arrange line, =RLAPI =PollInputEvents
	assemble line
end calminstruction

; Wait for some time (halt program execution)
; void WaitTime(double seconds)
calminstruction WaitTime seconds*
	local line
	arrange line, =RLAPI =WaitTime, seconds
	assemble line
end calminstruction

; Set the seed for the random number generator
; void SetRandomSeed(unsigned int seed)
calminstruction SetRandomSeed seed*
	local line
	arrange line, =RLAPI =SetRandomSeed, seed
	assemble line
end calminstruction

; Get a random value between min and max (both included)
; int GetRandomValue(int min, int max)
calminstruction GetRandomValue min*, max*
	local line
	arrange line, =RLAPI =GetRandomValue, min,max
	assemble line
end calminstruction

; Load random values sequence, no values repeated
; int * LoadRandomSequence(unsigned int count, int min, int max)
calminstruction LoadRandomSequence count*, min*, max*
	local line
	arrange line, =RLAPI =LoadRandomSequence, count,min,max
	assemble line
end calminstruction

; Unload random values sequence
; void UnloadRandomSequence(int * sequence)
calminstruction UnloadRandomSequence sequence*
	local line
	arrange line, =RLAPI =UnloadRandomSequence, sequence
	assemble line
end calminstruction

; Takes a screenshot of current screen (filename extension defines format)
; void TakeScreenshot(const char * fileName)
calminstruction TakeScreenshot fileName*
	local line
	arrange line, =RLAPI =TakeScreenshot, fileName
	assemble line
end calminstruction

; Setup init configuration flags (view FLAGS)
; void SetConfigFlags(ConfigFlags flags)
calminstruction SetConfigFlags flags*
	local line
	transform flags, RayLib.ConfigFlags
	arrange line, =RLAPI =SetConfigFlags, flags
	assemble line
end calminstruction

; Open URL with default system browser (if available)
; void OpenURL(const char * url)
calminstruction OpenURL url*
	local line
	arrange line, =RLAPI =OpenURL, url
	assemble line
end calminstruction

; Set the current threshold (minimum) log level
; void SetTraceLogLevel(TraceLogLevel logLevel)
calminstruction SetTraceLogLevel logLevel*
	local line
	transform logLevel, RayLib.TraceLogLevel
	arrange line, =RLAPI =SetTraceLogLevel, logLevel
	assemble line
end calminstruction

; Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
; void TraceLog(TraceLogLevel logLevel, const char * text, ... args)
calminstruction TraceLog logLevel*, text*, args*
	local line
	transform logLevel, RayLib.TraceLogLevel
	arrange line, =RLAPI =TraceLog, logLevel,text,args
	assemble line
end calminstruction

; Set custom trace log
; void SetTraceLogCallback(TraceLogCallback callback)
calminstruction SetTraceLogCallback callback*
	local line
	arrange line, =RLAPI =SetTraceLogCallback, callback
	assemble line
end calminstruction

; Internal memory allocator
; void * MemAlloc(unsigned int size)
calminstruction MemAlloc size*
	local line
	arrange line, =RLAPI =MemAlloc, size
	assemble line
end calminstruction

; Internal memory reallocator
; void * MemRealloc(void * ptr, unsigned int size)
calminstruction MemRealloc ptr*, size*
	local line
	arrange line, =RLAPI =MemRealloc, ptr,size
	assemble line
end calminstruction

; Internal memory free
; void MemFree(void * ptr)
calminstruction MemFree ptr*
	local line
	arrange line, =RLAPI =MemFree, ptr
	assemble line
end calminstruction

; Load file data as byte array (read)
; unsigned char * LoadFileData(const char * fileName, int * dataSize)
calminstruction LoadFileData fileName*, dataSize*
	local line
	arrange line, =RLAPI =LoadFileData, fileName,dataSize
	assemble line
end calminstruction

; Unload file data allocated by LoadFileData()
; void UnloadFileData(unsigned char * data)
calminstruction UnloadFileData data*
	local line
	arrange line, =RLAPI =UnloadFileData, data
	assemble line
end calminstruction

; Save data to file from byte array (write), returns true on success
; bool SaveFileData(const char * fileName, void * data, int dataSize)
calminstruction SaveFileData fileName*, data*, dataSize*
	local line
	arrange line, =RLAPI =SaveFileData, fileName,data,dataSize
	assemble line
end calminstruction

; Export data to code (.h), returns true on success
; bool ExportDataAsCode(const unsigned char * data, int dataSize, const char * fileName)
calminstruction ExportDataAsCode data*, dataSize*, fileName*
	local line
	arrange line, =RLAPI =ExportDataAsCode, data,dataSize,fileName
	assemble line
end calminstruction

; Load text data from file (read), returns a '\0' terminated string
; char * LoadFileText(const char * fileName)
calminstruction LoadFileText fileName*
	local line
	arrange line, =RLAPI =LoadFileText, fileName
	assemble line
end calminstruction

; Unload file text data allocated by LoadFileText()
; void UnloadFileText(char * text)
calminstruction UnloadFileText text*
	local line
	arrange line, =RLAPI =UnloadFileText, text
	assemble line
end calminstruction

; Save text data to file (write), string must be '\0' terminated, returns true on success
; bool SaveFileText(const char * fileName, const char * text)
calminstruction SaveFileText fileName*, text*
	local line
	arrange line, =RLAPI =SaveFileText, fileName,text
	assemble line
end calminstruction

; Set custom file binary data loader
; void SetLoadFileDataCallback(LoadFileDataCallback callback)
calminstruction SetLoadFileDataCallback callback*
	local line
	arrange line, =RLAPI =SetLoadFileDataCallback, callback
	assemble line
end calminstruction

; Set custom file binary data saver
; void SetSaveFileDataCallback(SaveFileDataCallback callback)
calminstruction SetSaveFileDataCallback callback*
	local line
	arrange line, =RLAPI =SetSaveFileDataCallback, callback
	assemble line
end calminstruction

; Set custom file text data loader
; void SetLoadFileTextCallback(LoadFileTextCallback callback)
calminstruction SetLoadFileTextCallback callback*
	local line
	arrange line, =RLAPI =SetLoadFileTextCallback, callback
	assemble line
end calminstruction

; Set custom file text data saver
; void SetSaveFileTextCallback(SaveFileTextCallback callback)
calminstruction SetSaveFileTextCallback callback*
	local line
	arrange line, =RLAPI =SetSaveFileTextCallback, callback
	assemble line
end calminstruction

; Rename file (if exists)
; int FileRename(const char * fileName, const char * fileRename)
calminstruction FileRename fileName*, fileRename*
	local line
	arrange line, =RLAPI =FileRename, fileName,fileRename
	assemble line
end calminstruction

; Remove file (if exists)
; int FileRemove(const char * fileName)
calminstruction FileRemove fileName*
	local line
	arrange line, =RLAPI =FileRemove, fileName
	assemble line
end calminstruction

; Copy file from one path to another, dstPath created if it doesn't exist
; int FileCopy(const char * srcPath, const char * dstPath)
calminstruction FileCopy srcPath*, dstPath*
	local line
	arrange line, =RLAPI =FileCopy, srcPath,dstPath
	assemble line
end calminstruction

; Move file from one directory to another, dstPath created if it doesn't exist
; int FileMove(const char * srcPath, const char * dstPath)
calminstruction FileMove srcPath*, dstPath*
	local line
	arrange line, =RLAPI =FileMove, srcPath,dstPath
	assemble line
end calminstruction

; Replace text in an existing file
; int FileTextReplace(const char * fileName, const char * search, const char * replacement)
calminstruction FileTextReplace fileName*, search*, replacement*
	local line
	arrange line, =RLAPI =FileTextReplace, fileName,search,replacement
	assemble line
end calminstruction

; Find text in existing file
; int FileTextFindIndex(const char * fileName, const char * search)
calminstruction FileTextFindIndex fileName*, search*
	local line
	arrange line, =RLAPI =FileTextFindIndex, fileName,search
	assemble line
end calminstruction

; Check if file exists
; bool FileExists(const char * fileName)
calminstruction FileExists fileName*
	local line
	arrange line, =RLAPI =FileExists, fileName
	assemble line
end calminstruction

; Check if a directory path exists
; bool DirectoryExists(const char * dirPath)
calminstruction DirectoryExists dirPath*
	local line
	arrange line, =RLAPI =DirectoryExists, dirPath
	assemble line
end calminstruction

; Check file extension (recommended include point: .png, .wav)
; bool IsFileExtension(const char * fileName, const char * ext)
calminstruction IsFileExtension fileName*, ext*
	local line
	arrange line, =RLAPI =IsFileExtension, fileName,ext
	assemble line
end calminstruction

; Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
; int GetFileLength(const char * fileName)
calminstruction GetFileLength fileName*
	local line
	arrange line, =RLAPI =GetFileLength, fileName
	assemble line
end calminstruction

; Get file modification time (last write time)
; long GetFileModTime(const char * fileName)
calminstruction GetFileModTime fileName*
	local line
	arrange line, =RLAPI =GetFileModTime, fileName
	assemble line
end calminstruction

; Get pointer to extension for a filename string (includes dot: '.png')
; const char * GetFileExtension(const char * fileName)
calminstruction GetFileExtension fileName*
	local line
	arrange line, =RLAPI =GetFileExtension, fileName
	assemble line
end calminstruction

; Get pointer to filename for a path string
; const char * GetFileName(const char * filePath)
calminstruction GetFileName filePath*
	local line
	arrange line, =RLAPI =GetFileName, filePath
	assemble line
end calminstruction

; Get filename string without extension (uses static string)
; const char * GetFileNameWithoutExt(const char * filePath)
calminstruction GetFileNameWithoutExt filePath*
	local line
	arrange line, =RLAPI =GetFileNameWithoutExt, filePath
	assemble line
end calminstruction

; Get full path for a given fileName with path (uses static string)
; const char * GetDirectoryPath(const char * filePath)
calminstruction GetDirectoryPath filePath*
	local line
	arrange line, =RLAPI =GetDirectoryPath, filePath
	assemble line
end calminstruction

; Get previous directory path for a given path (uses static string)
; const char * GetPrevDirectoryPath(const char * dirPath)
calminstruction GetPrevDirectoryPath dirPath*
	local line
	arrange line, =RLAPI =GetPrevDirectoryPath, dirPath
	assemble line
end calminstruction

; Get current working directory (uses static string)
; const char * GetWorkingDirectory(void)
calminstruction GetWorkingDirectory
	local line
	arrange line, =RLAPI =GetWorkingDirectory
	assemble line
end calminstruction

; Get the directory of the running application (uses static string)
; const char * GetApplicationDirectory(void)
calminstruction GetApplicationDirectory
	local line
	arrange line, =RLAPI =GetApplicationDirectory
	assemble line
end calminstruction

; Create directories (including full path requested), returns 0 on success
; int MakeDirectory(const char * dirPath)
calminstruction MakeDirectory dirPath*
	local line
	arrange line, =RLAPI =MakeDirectory, dirPath
	assemble line
end calminstruction

; Change working directory, return true on success
; bool ChangeDirectory(const char * dirPath)
calminstruction ChangeDirectory dirPath*
	local line
	arrange line, =RLAPI =ChangeDirectory, dirPath
	assemble line
end calminstruction

; Check if a given path is a file or a directory
; bool IsPathFile(const char * path)
calminstruction IsPathFile path*
	local line
	arrange line, =RLAPI =IsPathFile, path
	assemble line
end calminstruction

; Check if fileName is valid for the platform/OS
; bool IsFileNameValid(const char * fileName)
calminstruction IsFileNameValid fileName*
	local line
	arrange line, =RLAPI =IsFileNameValid, fileName
	assemble line
end calminstruction

; Load directory filepaths, files and directories, no subdirs scan
; FilePathList LoadDirectoryFiles(const char * dirPath)
calminstruction LoadDirectoryFiles dirPath*
	local line
	arrange line, =RLAPI =LoadDirectoryFiles, dirPath
	assemble line
end calminstruction

; Load directory filepaths with extension filtering and subdir scan, some filters available: "*.*", "FILES*", "DIRS*"
; FilePathList LoadDirectoryFilesEx(const char * basePath, const char * filter, bool scanSubdirs)
calminstruction LoadDirectoryFilesEx basePath*, filter*, scanSubdirs*
	local line
	arrange line, =RLAPI =LoadDirectoryFilesEx, basePath,filter,scanSubdirs
	assemble line
end calminstruction

; Unload filepaths
; void UnloadDirectoryFiles(FilePathList files)
calminstruction UnloadDirectoryFiles files*
	local line
	arrange line, =RLAPI =UnloadDirectoryFiles, files
	assemble line
end calminstruction

; Check if a file has been dropped into window
; bool IsFileDropped(void)
calminstruction IsFileDropped
	local line
	arrange line, =RLAPI =IsFileDropped
	assemble line
end calminstruction

; Load dropped filepaths
; FilePathList LoadDroppedFiles(void)
calminstruction LoadDroppedFiles
	local line
	arrange line, =RLAPI =LoadDroppedFiles
	assemble line
end calminstruction

; Unload dropped filepaths
; void UnloadDroppedFiles(FilePathList files)
calminstruction UnloadDroppedFiles files*
	local line
	arrange line, =RLAPI =UnloadDroppedFiles, files
	assemble line
end calminstruction

; Get the file count in a directory
; unsigned int GetDirectoryFileCount(const char * dirPath)
calminstruction GetDirectoryFileCount dirPath*
	local line
	arrange line, =RLAPI =GetDirectoryFileCount, dirPath
	assemble line
end calminstruction

; Get the file count in a directory with extension filtering and recursive directory scan. Use 'DIR' in the filter string to include directories in the result
; unsigned int GetDirectoryFileCountEx(const char * basePath, const char * filter, bool scanSubdirs)
calminstruction GetDirectoryFileCountEx basePath*, filter*, scanSubdirs*
	local line
	arrange line, =RLAPI =GetDirectoryFileCountEx, basePath,filter,scanSubdirs
	assemble line
end calminstruction

; Compress data (DEFLATE algorithm), memory must be MemFree()
; unsigned char * CompressData(const unsigned char * data, int dataSize, int * compDataSize)
calminstruction CompressData data*, dataSize*, compDataSize*
	local line
	arrange line, =RLAPI =CompressData, data,dataSize,compDataSize
	assemble line
end calminstruction

; Decompress data (DEFLATE algorithm), memory must be MemFree()
; unsigned char * DecompressData(const unsigned char * compData, int compDataSize, int * dataSize)
calminstruction DecompressData compData*, compDataSize*, dataSize*
	local line
	arrange line, =RLAPI =DecompressData, compData,compDataSize,dataSize
	assemble line
end calminstruction

; Encode data to Base64 string (includes NULL terminator), memory must be MemFree()
; char * EncodeDataBase64(const unsigned char * data, int dataSize, int * outputSize)
calminstruction EncodeDataBase64 data*, dataSize*, outputSize*
	local line
	arrange line, =RLAPI =EncodeDataBase64, data,dataSize,outputSize
	assemble line
end calminstruction

; Decode Base64 string (expected NULL terminated), memory must be MemFree()
; unsigned char * DecodeDataBase64(const char * text, int * outputSize)
calminstruction DecodeDataBase64 text*, outputSize*
	local line
	arrange line, =RLAPI =DecodeDataBase64, text,outputSize
	assemble line
end calminstruction

; Compute CRC32 hash code
; unsigned int ComputeCRC32(unsigned char * data, int dataSize)
calminstruction ComputeCRC32 data*, dataSize*
	local line
	arrange line, =RLAPI =ComputeCRC32, data,dataSize
	assemble line
end calminstruction

; Compute MD5 hash code, returns static int[4] (16 bytes)
; unsigned int * ComputeMD5(unsigned char * data, int dataSize)
calminstruction ComputeMD5 data*, dataSize*
	local line
	arrange line, =RLAPI =ComputeMD5, data,dataSize
	assemble line
end calminstruction

; Compute SHA1 hash code, returns static int[5] (20 bytes)
; unsigned int * ComputeSHA1(unsigned char * data, int dataSize)
calminstruction ComputeSHA1 data*, dataSize*
	local line
	arrange line, =RLAPI =ComputeSHA1, data,dataSize
	assemble line
end calminstruction

; Compute SHA256 hash code, returns static int[8] (32 bytes)
; unsigned int * ComputeSHA256(unsigned char * data, int dataSize)
calminstruction ComputeSHA256 data*, dataSize*
	local line
	arrange line, =RLAPI =ComputeSHA256, data,dataSize
	assemble line
end calminstruction

; Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS
; AutomationEventList LoadAutomationEventList(const char * fileName)
calminstruction LoadAutomationEventList fileName*
	local line
	arrange line, =RLAPI =LoadAutomationEventList, fileName
	assemble line
end calminstruction

; Unload automation events list from file
; void UnloadAutomationEventList(AutomationEventList list)
calminstruction UnloadAutomationEventList list*
	local line
	arrange line, =RLAPI =UnloadAutomationEventList, list
	assemble line
end calminstruction

; Export automation events list as text file
; bool ExportAutomationEventList(AutomationEventList list, const char * fileName)
calminstruction ExportAutomationEventList list*, fileName*
	local line
	arrange line, =RLAPI =ExportAutomationEventList, list,fileName
	assemble line
end calminstruction

; Set automation event list to record to
; void SetAutomationEventList(AutomationEventList * list)
calminstruction SetAutomationEventList list*
	local line
	arrange line, =RLAPI =SetAutomationEventList, list
	assemble line
end calminstruction

; Set automation event internal base frame to start recording
; void SetAutomationEventBaseFrame(int frame)
calminstruction SetAutomationEventBaseFrame frame*
	local line
	arrange line, =RLAPI =SetAutomationEventBaseFrame, frame
	assemble line
end calminstruction

; Start recording automation events (AutomationEventList must be set)
; void StartAutomationEventRecording(void)
calminstruction StartAutomationEventRecording
	local line
	arrange line, =RLAPI =StartAutomationEventRecording
	assemble line
end calminstruction

; Stop recording automation events
; void StopAutomationEventRecording(void)
calminstruction StopAutomationEventRecording
	local line
	arrange line, =RLAPI =StopAutomationEventRecording
	assemble line
end calminstruction

; Play a recorded automation event
; void PlayAutomationEvent(AutomationEvent event)
calminstruction PlayAutomationEvent event*
	local line
	arrange line, =RLAPI =PlayAutomationEvent, event
	assemble line
end calminstruction

; Check if a key has been pressed once
; bool IsKeyPressed(KeyboardKey key)
calminstruction IsKeyPressed key*
	local line
	transform key, RayLib.KeyboardKey
	arrange line, =RLAPI =IsKeyPressed, key
	assemble line
end calminstruction

; Check if a key has been pressed again
; bool IsKeyPressedRepeat(KeyboardKey key)
calminstruction IsKeyPressedRepeat key*
	local line
	transform key, RayLib.KeyboardKey
	arrange line, =RLAPI =IsKeyPressedRepeat, key
	assemble line
end calminstruction

; Check if a key is being pressed
; bool IsKeyDown(KeyboardKey key)
calminstruction IsKeyDown key*
	local line
	transform key, RayLib.KeyboardKey
	arrange line, =RLAPI =IsKeyDown, key
	assemble line
end calminstruction

; Check if a key has been released once
; bool IsKeyReleased(KeyboardKey key)
calminstruction IsKeyReleased key*
	local line
	transform key, RayLib.KeyboardKey
	arrange line, =RLAPI =IsKeyReleased, key
	assemble line
end calminstruction

; Check if a key is NOT being pressed
; bool IsKeyUp(KeyboardKey key)
calminstruction IsKeyUp key*
	local line
	transform key, RayLib.KeyboardKey
	arrange line, =RLAPI =IsKeyUp, key
	assemble line
end calminstruction

; Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
; int GetKeyPressed(void)
calminstruction GetKeyPressed
	local line
	arrange line, =RLAPI =GetKeyPressed
	assemble line
end calminstruction

; Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
; int GetCharPressed(void)
calminstruction GetCharPressed
	local line
	arrange line, =RLAPI =GetCharPressed
	assemble line
end calminstruction

; Get name of a QWERTY key on the current keyboard layout (eg returns string 'q' for KEY_A on an AZERTY keyboard)
; const char * GetKeyName(KeyboardKey key)
calminstruction GetKeyName key*
	local line
	transform key, RayLib.KeyboardKey
	arrange line, =RLAPI =GetKeyName, key
	assemble line
end calminstruction

; Set a custom key to exit program (default is ESC)
; void SetExitKey(KeyboardKey key)
calminstruction SetExitKey key*
	local line
	transform key, RayLib.KeyboardKey
	arrange line, =RLAPI =SetExitKey, key
	assemble line
end calminstruction

; Check if a gamepad is available
; bool IsGamepadAvailable(int gamepad)
calminstruction IsGamepadAvailable gamepad*
	local line
	arrange line, =RLAPI =IsGamepadAvailable, gamepad
	assemble line
end calminstruction

; Get gamepad internal name id
; const char * GetGamepadName(int gamepad)
calminstruction GetGamepadName gamepad*
	local line
	arrange line, =RLAPI =GetGamepadName, gamepad
	assemble line
end calminstruction

; Check if a gamepad button has been pressed once
; bool IsGamepadButtonPressed(int gamepad, GamepadButton button)
calminstruction IsGamepadButtonPressed gamepad*, button*
	local line
	transform button, RayLib.GamepadButton
	arrange line, =RLAPI =IsGamepadButtonPressed, gamepad,button
	assemble line
end calminstruction

; Check if a gamepad button is being pressed
; bool IsGamepadButtonDown(int gamepad, GamepadButton button)
calminstruction IsGamepadButtonDown gamepad*, button*
	local line
	transform button, RayLib.GamepadButton
	arrange line, =RLAPI =IsGamepadButtonDown, gamepad,button
	assemble line
end calminstruction

; Check if a gamepad button has been released once
; bool IsGamepadButtonReleased(int gamepad, GamepadButton button)
calminstruction IsGamepadButtonReleased gamepad*, button*
	local line
	transform button, RayLib.GamepadButton
	arrange line, =RLAPI =IsGamepadButtonReleased, gamepad,button
	assemble line
end calminstruction

; Check if a gamepad button is NOT being pressed
; bool IsGamepadButtonUp(int gamepad, GamepadButton button)
calminstruction IsGamepadButtonUp gamepad*, button*
	local line
	transform button, RayLib.GamepadButton
	arrange line, =RLAPI =IsGamepadButtonUp, gamepad,button
	assemble line
end calminstruction

; Get the last gamepad button pressed
; int GetGamepadButtonPressed(void)
calminstruction GetGamepadButtonPressed
	local line
	arrange line, =RLAPI =GetGamepadButtonPressed
	assemble line
end calminstruction

; Get axis count for a gamepad
; int GetGamepadAxisCount(int gamepad)
calminstruction GetGamepadAxisCount gamepad*
	local line
	arrange line, =RLAPI =GetGamepadAxisCount, gamepad
	assemble line
end calminstruction

; Get movement value for a gamepad axis
; float GetGamepadAxisMovement(int gamepad, GamepadAxis axis)
calminstruction GetGamepadAxisMovement gamepad*, axis*
	local line
	transform axis, RayLib.GamepadAxis
	arrange line, =RLAPI =GetGamepadAxisMovement, gamepad,axis
	assemble line
end calminstruction

; Set internal gamepad mappings (SDL_GameControllerDB)
; int SetGamepadMappings(const char * mappings)
calminstruction SetGamepadMappings mappings*
	local line
	arrange line, =RLAPI =SetGamepadMappings, mappings
	assemble line
end calminstruction

; Set gamepad vibration for both motors (duration in seconds)
; void SetGamepadVibration(int gamepad, float leftMotor, float rightMotor, float duration)
calminstruction SetGamepadVibration gamepad*, leftMotor*, rightMotor*, duration*
	local line
	arrange line, =RLAPI =SetGamepadVibration, gamepad,leftMotor,rightMotor,duration
	assemble line
end calminstruction

; Check if a mouse button has been pressed once
; bool IsMouseButtonPressed(MouseButton button)
calminstruction IsMouseButtonPressed button*
	local line
	transform button, RayLib.MouseButton
	arrange line, =RLAPI =IsMouseButtonPressed, button
	assemble line
end calminstruction

; Check if a mouse button is being pressed
; bool IsMouseButtonDown(MouseButton button)
calminstruction IsMouseButtonDown button*
	local line
	transform button, RayLib.MouseButton
	arrange line, =RLAPI =IsMouseButtonDown, button
	assemble line
end calminstruction

; Check if a mouse button has been released once
; bool IsMouseButtonReleased(MouseButton button)
calminstruction IsMouseButtonReleased button*
	local line
	transform button, RayLib.MouseButton
	arrange line, =RLAPI =IsMouseButtonReleased, button
	assemble line
end calminstruction

; Check if a mouse button is NOT being pressed
; bool IsMouseButtonUp(MouseButton button)
calminstruction IsMouseButtonUp button*
	local line
	transform button, RayLib.MouseButton
	arrange line, =RLAPI =IsMouseButtonUp, button
	assemble line
end calminstruction

; Get mouse position X
; int GetMouseX(void)
calminstruction GetMouseX
	local line
	arrange line, =RLAPI =GetMouseX
	assemble line
end calminstruction

; Get mouse position Y
; int GetMouseY(void)
calminstruction GetMouseY
	local line
	arrange line, =RLAPI =GetMouseY
	assemble line
end calminstruction

; Get mouse position XY
; Vector2 GetMousePosition(void)
calminstruction GetMousePosition
	local line
	arrange line, =RLAPI =GetMousePosition
	assemble line
end calminstruction

; Get mouse delta between frames
; Vector2 GetMouseDelta(void)
calminstruction GetMouseDelta
	local line
	arrange line, =RLAPI =GetMouseDelta
	assemble line
end calminstruction

; Set mouse position XY
; void SetMousePosition(int x, int y)
calminstruction SetMousePosition x*, y*
	local line
	arrange line, =RLAPI =SetMousePosition, x,y
	assemble line
end calminstruction

; Set mouse offset
; void SetMouseOffset(int offsetX, int offsetY)
calminstruction SetMouseOffset offsetX*, offsetY*
	local line
	arrange line, =RLAPI =SetMouseOffset, offsetX,offsetY
	assemble line
end calminstruction

; Set mouse scaling
; void SetMouseScale(float scaleX, float scaleY)
calminstruction SetMouseScale scaleX*, scaleY*
	local line
	arrange line, =RLAPI =SetMouseScale, scaleX,scaleY
	assemble line
end calminstruction

; Get mouse wheel movement for X or Y, whichever is larger
; float GetMouseWheelMove(void)
calminstruction GetMouseWheelMove
	local line
	arrange line, =RLAPI =GetMouseWheelMove
	assemble line
end calminstruction

; Get mouse wheel movement for both X and Y
; Vector2 GetMouseWheelMoveV(void)
calminstruction GetMouseWheelMoveV
	local line
	arrange line, =RLAPI =GetMouseWheelMoveV
	assemble line
end calminstruction

; Set mouse cursor
; void SetMouseCursor(MouseCursor cursor)
calminstruction SetMouseCursor cursor*
	local line
	transform cursor, RayLib.MouseCursor
	arrange line, =RLAPI =SetMouseCursor, cursor
	assemble line
end calminstruction

; Get touch position X for touch point 0 (relative to screen size)
; int GetTouchX(void)
calminstruction GetTouchX
	local line
	arrange line, =RLAPI =GetTouchX
	assemble line
end calminstruction

; Get touch position Y for touch point 0 (relative to screen size)
; int GetTouchY(void)
calminstruction GetTouchY
	local line
	arrange line, =RLAPI =GetTouchY
	assemble line
end calminstruction

; Get touch position XY for a touch point index (relative to screen size)
; Vector2 GetTouchPosition(int index)
calminstruction GetTouchPosition index*
	local line
	arrange line, =RLAPI =GetTouchPosition, index
	assemble line
end calminstruction

; Get touch point identifier for given index
; int GetTouchPointId(int index)
calminstruction GetTouchPointId index*
	local line
	arrange line, =RLAPI =GetTouchPointId, index
	assemble line
end calminstruction

; Get number of touch points
; int GetTouchPointCount(void)
calminstruction GetTouchPointCount
	local line
	arrange line, =RLAPI =GetTouchPointCount
	assemble line
end calminstruction

; Enable a set of gestures using flags
; void SetGesturesEnabled(Gesture flags)
calminstruction SetGesturesEnabled flags*
	local line
	transform flags, RayLib.Gesture
	arrange line, =RLAPI =SetGesturesEnabled, flags
	assemble line
end calminstruction

; Check if a gesture have been detected
; bool IsGestureDetected(Gesture gesture)
calminstruction IsGestureDetected gesture*
	local line
	transform gesture, RayLib.Gesture
	arrange line, =RLAPI =IsGestureDetected, gesture
	assemble line
end calminstruction

; Get latest detected gesture
; int GetGestureDetected(void)
calminstruction GetGestureDetected
	local line
	arrange line, =RLAPI =GetGestureDetected
	assemble line
end calminstruction

; Get gesture hold time in seconds
; float GetGestureHoldDuration(void)
calminstruction GetGestureHoldDuration
	local line
	arrange line, =RLAPI =GetGestureHoldDuration
	assemble line
end calminstruction

; Get gesture drag vector
; Vector2 GetGestureDragVector(void)
calminstruction GetGestureDragVector
	local line
	arrange line, =RLAPI =GetGestureDragVector
	assemble line
end calminstruction

; Get gesture drag angle
; float GetGestureDragAngle(void)
calminstruction GetGestureDragAngle
	local line
	arrange line, =RLAPI =GetGestureDragAngle
	assemble line
end calminstruction

; Get gesture pinch delta
; Vector2 GetGesturePinchVector(void)
calminstruction GetGesturePinchVector
	local line
	arrange line, =RLAPI =GetGesturePinchVector
	assemble line
end calminstruction

; Get gesture pinch angle
; float GetGesturePinchAngle(void)
calminstruction GetGesturePinchAngle
	local line
	arrange line, =RLAPI =GetGesturePinchAngle
	assemble line
end calminstruction

; Update camera position for selected mode
; void UpdateCamera(Camera * camera, CameraMode mode)
calminstruction UpdateCamera camera*, mode*
	local line
	transform mode, RayLib.CameraMode
	arrange line, =RLAPI =UpdateCamera, camera,mode
	assemble line
end calminstruction

; Update camera movement/rotation
; void UpdateCameraPro(Camera * camera, Vector3 movement, Vector3 rotation, float zoom)
calminstruction UpdateCameraPro camera*, movement*, rotation*, zoom*
	local line
	arrange line, =RLAPI =UpdateCameraPro, camera,movement,rotation,zoom
	assemble line
end calminstruction

; Set texture and rectangle to be used on shapes drawing
; void SetShapesTexture(Texture2D texture, Rectangle source)
calminstruction SetShapesTexture texture*, source*
	local line
	arrange line, =RLAPI =SetShapesTexture, texture,source
	assemble line
end calminstruction

; Get texture that is used for shapes drawing
; Texture2D GetShapesTexture(void)
calminstruction GetShapesTexture
	local line
	arrange line, =RLAPI =GetShapesTexture
	assemble line
end calminstruction

; Get texture source rectangle that is used for shapes drawing
; Rectangle GetShapesTextureRectangle(void)
calminstruction GetShapesTextureRectangle
	local line
	arrange line, =RLAPI =GetShapesTextureRectangle
	assemble line
end calminstruction

; Draw a pixel using geometry [Can be slow, use with care]
; void DrawPixel(int posX, int posY, Color color)
calminstruction DrawPixel posX*, posY*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawPixel, posX,posY,color
	assemble line
end calminstruction

; Draw a pixel using geometry (Vector version) [Can be slow, use with care]
; void DrawPixelV(Vector2 position, Color color)
calminstruction DrawPixelV position*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawPixelV, position,color
	assemble line
end calminstruction

; Draw a line
; void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color)
calminstruction DrawLine startPosX*, startPosY*, endPosX*, endPosY*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawLine, startPosX,startPosY,endPosX,endPosY,color
	assemble line
end calminstruction

; Draw a line (using gl lines)
; void DrawLineV(Vector2 startPos, Vector2 endPos, Color color)
calminstruction DrawLineV startPos*, endPos*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawLineV, startPos,endPos,color
	assemble line
end calminstruction

; Draw a line (using triangles/quads)
; void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color)
calminstruction DrawLineEx startPos*, endPos*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawLineEx, startPos,endPos,thick,color
	assemble line
end calminstruction

; Draw lines sequence (using gl lines)
; void DrawLineStrip(const Vector2 * points, int pointCount, Color color)
calminstruction DrawLineStrip points*, pointCount*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawLineStrip, points,pointCount,color
	assemble line
end calminstruction

; Draw line segment cubic-bezier in-out interpolation
; void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color)
calminstruction DrawLineBezier startPos*, endPos*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawLineBezier, startPos,endPos,thick,color
	assemble line
end calminstruction

; Draw a dashed line
; void DrawLineDashed(Vector2 startPos, Vector2 endPos, int dashSize, int spaceSize, Color color)
calminstruction DrawLineDashed startPos*, endPos*, dashSize*, spaceSize*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawLineDashed, startPos,endPos,dashSize,spaceSize,color
	assemble line
end calminstruction

; Draw a color-filled circle
; void DrawCircle(int centerX, int centerY, float radius, Color color)
calminstruction DrawCircle centerX*, centerY*, radius*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCircle, centerX,centerY,radius,color
	assemble line
end calminstruction

; Draw a color-filled circle (Vector version)
; void DrawCircleV(Vector2 center, float radius, Color color)
calminstruction DrawCircleV center*, radius*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCircleV, center,radius,color
	assemble line
end calminstruction

; Draw a gradient-filled circle
; void DrawCircleGradient(Vector2 center, float radius, Color inner, Color outer)
calminstruction DrawCircleGradient center*, radius*, inner*, outer*
	local line
	transform inner, RayLib
	transform outer, RayLib
	arrange line, =RLAPI =DrawCircleGradient, center,radius,inner,outer
	assemble line
end calminstruction

; Draw a piece of a circle
; void DrawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color)
calminstruction DrawCircleSector center*, radius*, startAngle*, endAngle*, segments*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCircleSector, center,radius,startAngle,endAngle,segments,color
	assemble line
end calminstruction

; Draw circle sector outline
; void DrawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color)
calminstruction DrawCircleSectorLines center*, radius*, startAngle*, endAngle*, segments*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCircleSectorLines, center,radius,startAngle,endAngle,segments,color
	assemble line
end calminstruction

; Draw circle outline
; void DrawCircleLines(int centerX, int centerY, float radius, Color color)
calminstruction DrawCircleLines centerX*, centerY*, radius*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCircleLines, centerX,centerY,radius,color
	assemble line
end calminstruction

; Draw circle outline (Vector version)
; void DrawCircleLinesV(Vector2 center, float radius, Color color)
calminstruction DrawCircleLinesV center*, radius*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCircleLinesV, center,radius,color
	assemble line
end calminstruction

; Draw ellipse
; void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color)
calminstruction DrawEllipse centerX*, centerY*, radiusH*, radiusV*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawEllipse, centerX,centerY,radiusH,radiusV,color
	assemble line
end calminstruction

; Draw ellipse (Vector version)
; void DrawEllipseV(Vector2 center, float radiusH, float radiusV, Color color)
calminstruction DrawEllipseV center*, radiusH*, radiusV*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawEllipseV, center,radiusH,radiusV,color
	assemble line
end calminstruction

; Draw ellipse outline
; void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color)
calminstruction DrawEllipseLines centerX*, centerY*, radiusH*, radiusV*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawEllipseLines, centerX,centerY,radiusH,radiusV,color
	assemble line
end calminstruction

; Draw ellipse outline (Vector version)
; void DrawEllipseLinesV(Vector2 center, float radiusH, float radiusV, Color color)
calminstruction DrawEllipseLinesV center*, radiusH*, radiusV*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawEllipseLinesV, center,radiusH,radiusV,color
	assemble line
end calminstruction

; Draw ring
; void DrawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color)
calminstruction DrawRing center*, innerRadius*, outerRadius*, startAngle*, endAngle*, segments*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRing, center,innerRadius,outerRadius,startAngle,endAngle,segments,color
	assemble line
end calminstruction

; Draw ring outline
; void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color)
calminstruction DrawRingLines center*, innerRadius*, outerRadius*, startAngle*, endAngle*, segments*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRingLines, center,innerRadius,outerRadius,startAngle,endAngle,segments,color
	assemble line
end calminstruction

; Draw a color-filled rectangle
; void DrawRectangle(int posX, int posY, int width, int height, Color color)
calminstruction DrawRectangle posX*, posY*, width*, height*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRectangle, posX,posY,width,height,color
	assemble line
end calminstruction

; Draw a color-filled rectangle (Vector version)
; void DrawRectangleV(Vector2 position, Vector2 size, Color color)
calminstruction DrawRectangleV position*, size*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRectangleV, position,size,color
	assemble line
end calminstruction

; Draw a color-filled rectangle
; void DrawRectangleRec(Rectangle rec, Color color)
calminstruction DrawRectangleRec rec*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRectangleRec, rec,color
	assemble line
end calminstruction

; Draw a color-filled rectangle with pro parameters
; void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color)
calminstruction DrawRectanglePro rec*, origin*, rotation*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRectanglePro, rec,origin,rotation,color
	assemble line
end calminstruction

; Draw a vertical-gradient-filled rectangle
; void DrawRectangleGradientV(int posX, int posY, int width, int height, Color top, Color bottom)
calminstruction DrawRectangleGradientV posX*, posY*, width*, height*, top*, bottom*
	local line
	transform top, RayLib
	transform bottom, RayLib
	arrange line, =RLAPI =DrawRectangleGradientV, posX,posY,width,height,top,bottom
	assemble line
end calminstruction

; Draw a horizontal-gradient-filled rectangle
; void DrawRectangleGradientH(int posX, int posY, int width, int height, Color left, Color right)
calminstruction DrawRectangleGradientH posX*, posY*, width*, height*, left*, right*
	local line
	transform left, RayLib
	transform right, RayLib
	arrange line, =RLAPI =DrawRectangleGradientH, posX,posY,width,height,left,right
	assemble line
end calminstruction

; Draw a gradient-filled rectangle with custom vertex colors
; void DrawRectangleGradientEx(Rectangle rec, Color topLeft, Color bottomLeft, Color bottomRight, Color topRight)
calminstruction DrawRectangleGradientEx rec*, topLeft*, bottomLeft*, bottomRight*, topRight*
	local line
	transform topLeft, RayLib
	transform bottomLeft, RayLib
	transform bottomRight, RayLib
	transform topRight, RayLib
	arrange line, =RLAPI =DrawRectangleGradientEx, rec,topLeft,bottomLeft,bottomRight,topRight
	assemble line
end calminstruction

; Draw rectangle outline
; void DrawRectangleLines(int posX, int posY, int width, int height, Color color)
calminstruction DrawRectangleLines posX*, posY*, width*, height*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRectangleLines, posX,posY,width,height,color
	assemble line
end calminstruction

; Draw rectangle outline with extended parameters
; void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color)
calminstruction DrawRectangleLinesEx rec*, lineThick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRectangleLinesEx, rec,lineThick,color
	assemble line
end calminstruction

; Draw rectangle with rounded edges
; void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color)
calminstruction DrawRectangleRounded rec*, roundness*, segments*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRectangleRounded, rec,roundness,segments,color
	assemble line
end calminstruction

; Draw rectangle lines with rounded edges
; void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, Color color)
calminstruction DrawRectangleRoundedLines rec*, roundness*, segments*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRectangleRoundedLines, rec,roundness,segments,color
	assemble line
end calminstruction

; Draw rectangle with rounded edges outline
; void DrawRectangleRoundedLinesEx(Rectangle rec, float roundness, int segments, float lineThick, Color color)
calminstruction DrawRectangleRoundedLinesEx rec*, roundness*, segments*, lineThick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRectangleRoundedLinesEx, rec,roundness,segments,lineThick,color
	assemble line
end calminstruction

; Draw a color-filled triangle (vertex in counter-clockwise order!)
; void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color)
calminstruction DrawTriangle v1*, v2*, v3*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawTriangle, v1,v2,v3,color
	assemble line
end calminstruction

; Draw triangle outline (vertex in counter-clockwise order!)
; void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color)
calminstruction DrawTriangleLines v1*, v2*, v3*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawTriangleLines, v1,v2,v3,color
	assemble line
end calminstruction

; Draw a triangle fan defined by points (first vertex is the center)
; void DrawTriangleFan(const Vector2 * points, int pointCount, Color color)
calminstruction DrawTriangleFan points*, pointCount*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawTriangleFan, points,pointCount,color
	assemble line
end calminstruction

; Draw a triangle strip defined by points
; void DrawTriangleStrip(const Vector2 * points, int pointCount, Color color)
calminstruction DrawTriangleStrip points*, pointCount*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawTriangleStrip, points,pointCount,color
	assemble line
end calminstruction

; Draw a regular polygon (Vector version)
; void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color)
calminstruction DrawPoly center*, sides*, radius*, rotation*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawPoly, center,sides,radius,rotation,color
	assemble line
end calminstruction

; Draw a polygon outline of n sides
; void DrawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color)
calminstruction DrawPolyLines center*, sides*, radius*, rotation*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawPolyLines, center,sides,radius,rotation,color
	assemble line
end calminstruction

; Draw a polygon outline of n sides with extended parameters
; void DrawPolyLinesEx(Vector2 center, int sides, float radius, float rotation, float lineThick, Color color)
calminstruction DrawPolyLinesEx center*, sides*, radius*, rotation*, lineThick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawPolyLinesEx, center,sides,radius,rotation,lineThick,color
	assemble line
end calminstruction

; Draw spline: Linear, minimum 2 points
; void DrawSplineLinear(const Vector2 * points, int pointCount, float thick, Color color)
calminstruction DrawSplineLinear points*, pointCount*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSplineLinear, points,pointCount,thick,color
	assemble line
end calminstruction

; Draw spline: B-Spline, minimum 4 points
; void DrawSplineBasis(const Vector2 * points, int pointCount, float thick, Color color)
calminstruction DrawSplineBasis points*, pointCount*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSplineBasis, points,pointCount,thick,color
	assemble line
end calminstruction

; Draw spline: Catmull-Rom, minimum 4 points
; void DrawSplineCatmullRom(const Vector2 * points, int pointCount, float thick, Color color)
calminstruction DrawSplineCatmullRom points*, pointCount*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSplineCatmullRom, points,pointCount,thick,color
	assemble line
end calminstruction

; Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
; void DrawSplineBezierQuadratic(const Vector2 * points, int pointCount, float thick, Color color)
calminstruction DrawSplineBezierQuadratic points*, pointCount*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSplineBezierQuadratic, points,pointCount,thick,color
	assemble line
end calminstruction

; Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
; void DrawSplineBezierCubic(const Vector2 * points, int pointCount, float thick, Color color)
calminstruction DrawSplineBezierCubic points*, pointCount*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSplineBezierCubic, points,pointCount,thick,color
	assemble line
end calminstruction

; Draw spline segment: Linear, 2 points
; void DrawSplineSegmentLinear(Vector2 p1, Vector2 p2, float thick, Color color)
calminstruction DrawSplineSegmentLinear p1*, p2*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSplineSegmentLinear, p1,p2,thick,color
	assemble line
end calminstruction

; Draw spline segment: B-Spline, 4 points
; void DrawSplineSegmentBasis(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color)
calminstruction DrawSplineSegmentBasis p1*, p2*, p3*, p4*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSplineSegmentBasis, p1,p2,p3,p4,thick,color
	assemble line
end calminstruction

; Draw spline segment: Catmull-Rom, 4 points
; void DrawSplineSegmentCatmullRom(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color)
calminstruction DrawSplineSegmentCatmullRom p1*, p2*, p3*, p4*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSplineSegmentCatmullRom, p1,p2,p3,p4,thick,color
	assemble line
end calminstruction

; Draw spline segment: Quadratic Bezier, 2 points, 1 control point
; void DrawSplineSegmentBezierQuadratic(Vector2 p1, Vector2 c2, Vector2 p3, float thick, Color color)
calminstruction DrawSplineSegmentBezierQuadratic p1*, c2*, p3*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSplineSegmentBezierQuadratic, p1,c2,p3,thick,color
	assemble line
end calminstruction

; Draw spline segment: Cubic Bezier, 2 points, 2 control points
; void DrawSplineSegmentBezierCubic(Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float thick, Color color)
calminstruction DrawSplineSegmentBezierCubic p1*, c2*, c3*, p4*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSplineSegmentBezierCubic, p1,c2,c3,p4,thick,color
	assemble line
end calminstruction

; Get (evaluate) spline point: Linear
; Vector2 GetSplinePointLinear(Vector2 startPos, Vector2 endPos, float t)
calminstruction GetSplinePointLinear startPos*, endPos*, t*
	local line
	arrange line, =RLAPI =GetSplinePointLinear, startPos,endPos,t
	assemble line
end calminstruction

; Get (evaluate) spline point: B-Spline
; Vector2 GetSplinePointBasis(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t)
calminstruction GetSplinePointBasis p1*, p2*, p3*, p4*, t*
	local line
	arrange line, =RLAPI =GetSplinePointBasis, p1,p2,p3,p4,t
	assemble line
end calminstruction

; Get (evaluate) spline point: Catmull-Rom
; Vector2 GetSplinePointCatmullRom(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t)
calminstruction GetSplinePointCatmullRom p1*, p2*, p3*, p4*, t*
	local line
	arrange line, =RLAPI =GetSplinePointCatmullRom, p1,p2,p3,p4,t
	assemble line
end calminstruction

; Get (evaluate) spline point: Quadratic Bezier
; Vector2 GetSplinePointBezierQuad(Vector2 p1, Vector2 c2, Vector2 p3, float t)
calminstruction GetSplinePointBezierQuad p1*, c2*, p3*, t*
	local line
	arrange line, =RLAPI =GetSplinePointBezierQuad, p1,c2,p3,t
	assemble line
end calminstruction

; Get (evaluate) spline point: Cubic Bezier
; Vector2 GetSplinePointBezierCubic(Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float t)
calminstruction GetSplinePointBezierCubic p1*, c2*, c3*, p4*, t*
	local line
	arrange line, =RLAPI =GetSplinePointBezierCubic, p1,c2,c3,p4,t
	assemble line
end calminstruction

; Check collision between two rectangles
; bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2)
calminstruction CheckCollisionRecs rec1*, rec2*
	local line
	arrange line, =RLAPI =CheckCollisionRecs, rec1,rec2
	assemble line
end calminstruction

; Check collision between two circles
; bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2)
calminstruction CheckCollisionCircles center1*, radius1*, center2*, radius2*
	local line
	arrange line, =RLAPI =CheckCollisionCircles, center1,radius1,center2,radius2
	assemble line
end calminstruction

; Check collision between circle and rectangle
; bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec)
calminstruction CheckCollisionCircleRec center*, radius*, rec*
	local line
	arrange line, =RLAPI =CheckCollisionCircleRec, center,radius,rec
	assemble line
end calminstruction

; Check if circle collides with a line created betweeen two points [p1] and [p2]
; bool CheckCollisionCircleLine(Vector2 center, float radius, Vector2 p1, Vector2 p2)
calminstruction CheckCollisionCircleLine center*, radius*, p1*, p2*
	local line
	arrange line, =RLAPI =CheckCollisionCircleLine, center,radius,p1,p2
	assemble line
end calminstruction

; Check if point is inside rectangle
; bool CheckCollisionPointRec(Vector2 point, Rectangle rec)
calminstruction CheckCollisionPointRec point*, rec*
	local line
	arrange line, =RLAPI =CheckCollisionPointRec, point,rec
	assemble line
end calminstruction

; Check if point is inside circle
; bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius)
calminstruction CheckCollisionPointCircle point*, center*, radius*
	local line
	arrange line, =RLAPI =CheckCollisionPointCircle, point,center,radius
	assemble line
end calminstruction

; Check if point is inside a triangle
; bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3)
calminstruction CheckCollisionPointTriangle point*, p1*, p2*, p3*
	local line
	arrange line, =RLAPI =CheckCollisionPointTriangle, point,p1,p2,p3
	assemble line
end calminstruction

; Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
; bool CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold)
calminstruction CheckCollisionPointLine point*, p1*, p2*, threshold*
	local line
	arrange line, =RLAPI =CheckCollisionPointLine, point,p1,p2,threshold
	assemble line
end calminstruction

; Check if point is within a polygon described by array of vertices
; bool CheckCollisionPointPoly(Vector2 point, const Vector2 * points, int pointCount)
calminstruction CheckCollisionPointPoly point*, points*, pointCount*
	local line
	arrange line, =RLAPI =CheckCollisionPointPoly, point,points,pointCount
	assemble line
end calminstruction

; Check the collision between two lines defined by two points each, returns collision point by reference
; bool CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 * collisionPoint)
calminstruction CheckCollisionLines startPos1*, endPos1*, startPos2*, endPos2*, collisionPoint*
	local line
	arrange line, =RLAPI =CheckCollisionLines, startPos1,endPos1,startPos2,endPos2,collisionPoint
	assemble line
end calminstruction

; Get collision rectangle for two rectangles collision
; Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2)
calminstruction GetCollisionRec rec1*, rec2*
	local line
	arrange line, =RLAPI =GetCollisionRec, rec1,rec2
	assemble line
end calminstruction

; Load image from file into CPU memory (RAM)
; Image LoadImage(const char * fileName)
calminstruction LoadImage fileName*
	local line
	arrange line, =RLAPI =LoadImage, fileName
	assemble line
end calminstruction

; Load image from RAW file data
; Image LoadImageRaw(const char * fileName, int width, int height, PixelFormat format, int headerSize)
calminstruction LoadImageRaw fileName*, width*, height*, format*, headerSize*
	local line
	transform format, RayLib.PixelFormat
	arrange line, =RLAPI =LoadImageRaw, fileName,width,height,format,headerSize
	assemble line
end calminstruction

; Load image sequence from file (frames appended to image.data)
; Image LoadImageAnim(const char * fileName, int * frames)
calminstruction LoadImageAnim fileName*, frames*
	local line
	arrange line, =RLAPI =LoadImageAnim, fileName,frames
	assemble line
end calminstruction

; Load image sequence from memory buffer
; Image LoadImageAnimFromMemory(const char * fileType, const unsigned char * fileData, int dataSize, int * frames)
calminstruction LoadImageAnimFromMemory fileType*, fileData*, dataSize*, frames*
	local line
	arrange line, =RLAPI =LoadImageAnimFromMemory, fileType,fileData,dataSize,frames
	assemble line
end calminstruction

; Load image from memory buffer, fileType refers to extension: i.e. '.png'
; Image LoadImageFromMemory(const char * fileType, const unsigned char * fileData, int dataSize)
calminstruction LoadImageFromMemory fileType*, fileData*, dataSize*
	local line
	arrange line, =RLAPI =LoadImageFromMemory, fileType,fileData,dataSize
	assemble line
end calminstruction

; Load image from GPU texture data
; Image LoadImageFromTexture(Texture2D texture)
calminstruction LoadImageFromTexture texture*
	local line
	arrange line, =RLAPI =LoadImageFromTexture, texture
	assemble line
end calminstruction

; Load image from screen buffer and (screenshot)
; Image LoadImageFromScreen(void)
calminstruction LoadImageFromScreen
	local line
	arrange line, =RLAPI =LoadImageFromScreen
	assemble line
end calminstruction

; Check if an image is valid (data and parameters)
; bool IsImageValid(Image image)
calminstruction IsImageValid image*
	local line
	arrange line, =RLAPI =IsImageValid, image
	assemble line
end calminstruction

; Unload image from CPU memory (RAM)
; void UnloadImage(Image image)
calminstruction UnloadImage image*
	local line
	arrange line, =RLAPI =UnloadImage, image
	assemble line
end calminstruction

; Export image data to file, returns true on success
; bool ExportImage(Image image, const char * fileName)
calminstruction ExportImage image*, fileName*
	local line
	arrange line, =RLAPI =ExportImage, image,fileName
	assemble line
end calminstruction

; Export image to memory buffer, memory must be MemFree()
; unsigned char * ExportImageToMemory(Image image, const char * fileType, int * fileSize)
calminstruction ExportImageToMemory image*, fileType*, fileSize*
	local line
	arrange line, =RLAPI =ExportImageToMemory, image,fileType,fileSize
	assemble line
end calminstruction

; Export image as code file defining an array of bytes, returns true on success
; bool ExportImageAsCode(Image image, const char * fileName)
calminstruction ExportImageAsCode image*, fileName*
	local line
	arrange line, =RLAPI =ExportImageAsCode, image,fileName
	assemble line
end calminstruction

; Generate image: plain color
; Image GenImageColor(int width, int height, Color color)
calminstruction GenImageColor width*, height*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =GenImageColor, width,height,color
	assemble line
end calminstruction

; Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient
; Image GenImageGradientLinear(int width, int height, int direction, Color start, Color end)
calminstruction GenImageGradientLinear width*, height*, direction*, start*, end_*
	local line
	transform start, RayLib
	transform end_, RayLib
	arrange line, =RLAPI =GenImageGradientLinear, width,height,direction,start,end_
	assemble line
end calminstruction

; Generate image: radial gradient
; Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer)
calminstruction GenImageGradientRadial width*, height*, density*, inner*, outer*
	local line
	transform inner, RayLib
	transform outer, RayLib
	arrange line, =RLAPI =GenImageGradientRadial, width,height,density,inner,outer
	assemble line
end calminstruction

; Generate image: square gradient
; Image GenImageGradientSquare(int width, int height, float density, Color inner, Color outer)
calminstruction GenImageGradientSquare width*, height*, density*, inner*, outer*
	local line
	transform inner, RayLib
	transform outer, RayLib
	arrange line, =RLAPI =GenImageGradientSquare, width,height,density,inner,outer
	assemble line
end calminstruction

; Generate image: checked
; Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2)
calminstruction GenImageChecked width*, height*, checksX*, checksY*, col1*, col2*
	local line
	transform col1, RayLib
	transform col2, RayLib
	arrange line, =RLAPI =GenImageChecked, width,height,checksX,checksY,col1,col2
	assemble line
end calminstruction

; Generate image: white noise
; Image GenImageWhiteNoise(int width, int height, float factor)
calminstruction GenImageWhiteNoise width*, height*, factor*
	local line
	arrange line, =RLAPI =GenImageWhiteNoise, width,height,factor
	assemble line
end calminstruction

; Generate image: perlin noise
; Image GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale)
calminstruction GenImagePerlinNoise width*, height*, offsetX*, offsetY*, scale*
	local line
	arrange line, =RLAPI =GenImagePerlinNoise, width,height,offsetX,offsetY,scale
	assemble line
end calminstruction

; Generate image: cellular algorithm, bigger tileSize means bigger cells
; Image GenImageCellular(int width, int height, int tileSize)
calminstruction GenImageCellular width*, height*, tileSize*
	local line
	arrange line, =RLAPI =GenImageCellular, width,height,tileSize
	assemble line
end calminstruction

; Generate image: grayscale image from text data
; Image GenImageText(int width, int height, const char * text)
calminstruction GenImageText width*, height*, text*
	local line
	arrange line, =RLAPI =GenImageText, width,height,text
	assemble line
end calminstruction

; Create an image duplicate (useful for transformations)
; Image ImageCopy(Image image)
calminstruction ImageCopy image*
	local line
	arrange line, =RLAPI =ImageCopy, image
	assemble line
end calminstruction

; Create an image from another image piece
; Image ImageFromImage(Image image, Rectangle rec)
calminstruction ImageFromImage image*, rec*
	local line
	arrange line, =RLAPI =ImageFromImage, image,rec
	assemble line
end calminstruction

; Create an image from a selected channel of another image (GRAYSCALE)
; Image ImageFromChannel(Image image, int selectedChannel)
calminstruction ImageFromChannel image*, selectedChannel*
	local line
	arrange line, =RLAPI =ImageFromChannel, image,selectedChannel
	assemble line
end calminstruction

; Create an image from text (default font)
; Image ImageText(const char * text, int fontSize, Color color)
calminstruction ImageText text*, fontSize*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageText, text,fontSize,color
	assemble line
end calminstruction

; Create an image from text (custom sprite font)
; Image ImageTextEx(Font font, const char * text, float fontSize, float spacing, Color tint)
calminstruction ImageTextEx font*, text*, fontSize*, spacing*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =ImageTextEx, font,text,fontSize,spacing,tint
	assemble line
end calminstruction

; Convert image data to desired format
; void ImageFormat(Image * image, PixelFormat newFormat)
calminstruction ImageFormat image*, newFormat*
	local line
	transform newFormat, RayLib.PixelFormat
	arrange line, =RLAPI =ImageFormat, image,newFormat
	assemble line
end calminstruction

; Convert image to POT (power-of-two)
; void ImageToPOT(Image * image, Color fill)
calminstruction ImageToPOT image*, fill*
	local line
	transform fill, RayLib
	arrange line, =RLAPI =ImageToPOT, image,fill
	assemble line
end calminstruction

; Crop an image to a defined rectangle
; void ImageCrop(Image * image, Rectangle crop)
calminstruction ImageCrop image*, crop*
	local line
	arrange line, =RLAPI =ImageCrop, image,crop
	assemble line
end calminstruction

; Crop image depending on alpha value
; void ImageAlphaCrop(Image * image, float threshold)
calminstruction ImageAlphaCrop image*, threshold*
	local line
	arrange line, =RLAPI =ImageAlphaCrop, image,threshold
	assemble line
end calminstruction

; Clear alpha channel to desired color
; void ImageAlphaClear(Image * image, Color color, float threshold)
calminstruction ImageAlphaClear image*, color*, threshold*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageAlphaClear, image,color,threshold
	assemble line
end calminstruction

; Apply alpha mask to image
; void ImageAlphaMask(Image * image, Image alphaMask)
calminstruction ImageAlphaMask image*, alphaMask*
	local line
	arrange line, =RLAPI =ImageAlphaMask, image,alphaMask
	assemble line
end calminstruction

; Premultiply alpha channel
; void ImageAlphaPremultiply(Image * image)
calminstruction ImageAlphaPremultiply image*
	local line
	arrange line, =RLAPI =ImageAlphaPremultiply, image
	assemble line
end calminstruction

; Apply Gaussian blur using a box blur approximation
; void ImageBlurGaussian(Image * image, int blurSize)
calminstruction ImageBlurGaussian image*, blurSize*
	local line
	arrange line, =RLAPI =ImageBlurGaussian, image,blurSize
	assemble line
end calminstruction

; Apply custom square convolution kernel to image
; void ImageKernelConvolution(Image * image, const float * kernel, int kernelSize)
calminstruction ImageKernelConvolution image*, kernel*, kernelSize*
	local line
	arrange line, =RLAPI =ImageKernelConvolution, image,kernel,kernelSize
	assemble line
end calminstruction

; Resize image (Bicubic scaling algorithm)
; void ImageResize(Image * image, int newWidth, int newHeight)
calminstruction ImageResize image*, newWidth*, newHeight*
	local line
	arrange line, =RLAPI =ImageResize, image,newWidth,newHeight
	assemble line
end calminstruction

; Resize image (Nearest-Neighbor scaling algorithm)
; void ImageResizeNN(Image * image, int newWidth, int newHeight)
calminstruction ImageResizeNN image*, newWidth*, newHeight*
	local line
	arrange line, =RLAPI =ImageResizeNN, image,newWidth,newHeight
	assemble line
end calminstruction

; Resize canvas and fill with color
; void ImageResizeCanvas(Image * image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill)
calminstruction ImageResizeCanvas image*, newWidth*, newHeight*, offsetX*, offsetY*, fill*
	local line
	transform fill, RayLib
	arrange line, =RLAPI =ImageResizeCanvas, image,newWidth,newHeight,offsetX,offsetY,fill
	assemble line
end calminstruction

; Compute all mipmap levels for a provided image
; void ImageMipmaps(Image * image)
calminstruction ImageMipmaps image*
	local line
	arrange line, =RLAPI =ImageMipmaps, image
	assemble line
end calminstruction

; Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
; void ImageDither(Image * image, int rBpp, int gBpp, int bBpp, int aBpp)
calminstruction ImageDither image*, rBpp*, gBpp*, bBpp*, aBpp*
	local line
	arrange line, =RLAPI =ImageDither, image,rBpp,gBpp,bBpp,aBpp
	assemble line
end calminstruction

; Flip image vertically
; void ImageFlipVertical(Image * image)
calminstruction ImageFlipVertical image*
	local line
	arrange line, =RLAPI =ImageFlipVertical, image
	assemble line
end calminstruction

; Flip image horizontally
; void ImageFlipHorizontal(Image * image)
calminstruction ImageFlipHorizontal image*
	local line
	arrange line, =RLAPI =ImageFlipHorizontal, image
	assemble line
end calminstruction

; Rotate image by input angle in degrees (-359 to 359)
; void ImageRotate(Image * image, int degrees)
calminstruction ImageRotate image*, degrees*
	local line
	arrange line, =RLAPI =ImageRotate, image,degrees
	assemble line
end calminstruction

; Rotate image clockwise 90deg
; void ImageRotateCW(Image * image)
calminstruction ImageRotateCW image*
	local line
	arrange line, =RLAPI =ImageRotateCW, image
	assemble line
end calminstruction

; Rotate image counter-clockwise 90deg
; void ImageRotateCCW(Image * image)
calminstruction ImageRotateCCW image*
	local line
	arrange line, =RLAPI =ImageRotateCCW, image
	assemble line
end calminstruction

; Modify image color: tint
; void ImageColorTint(Image * image, Color color)
calminstruction ImageColorTint image*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageColorTint, image,color
	assemble line
end calminstruction

; Modify image color: invert
; void ImageColorInvert(Image * image)
calminstruction ImageColorInvert image*
	local line
	arrange line, =RLAPI =ImageColorInvert, image
	assemble line
end calminstruction

; Modify image color: grayscale
; void ImageColorGrayscale(Image * image)
calminstruction ImageColorGrayscale image*
	local line
	arrange line, =RLAPI =ImageColorGrayscale, image
	assemble line
end calminstruction

; Modify image color: contrast (-100 to 100)
; void ImageColorContrast(Image * image, float contrast)
calminstruction ImageColorContrast image*, contrast*
	local line
	arrange line, =RLAPI =ImageColorContrast, image,contrast
	assemble line
end calminstruction

; Modify image color: brightness (-255 to 255)
; void ImageColorBrightness(Image * image, int brightness)
calminstruction ImageColorBrightness image*, brightness*
	local line
	arrange line, =RLAPI =ImageColorBrightness, image,brightness
	assemble line
end calminstruction

; Modify image color: replace color
; void ImageColorReplace(Image * image, Color color, Color replace)
calminstruction ImageColorReplace image*, color*, replace*
	local line
	transform color, RayLib
	transform replace, RayLib
	arrange line, =RLAPI =ImageColorReplace, image,color,replace
	assemble line
end calminstruction

; Load color data from image as a Color array (RGBA - 32bit)
; Color * LoadImageColors(Image image)
calminstruction LoadImageColors image*
	local line
	arrange line, =RLAPI =LoadImageColors, image
	assemble line
end calminstruction

; Load colors palette from image as a Color array (RGBA - 32bit)
; Color * LoadImagePalette(Image image, int maxPaletteSize, int * colorCount)
calminstruction LoadImagePalette image*, maxPaletteSize*, colorCount*
	local line
	arrange line, =RLAPI =LoadImagePalette, image,maxPaletteSize,colorCount
	assemble line
end calminstruction

; Unload color data loaded with LoadImageColors()
; void UnloadImageColors(Color * colors)
calminstruction UnloadImageColors colors*
	local line
	arrange line, =RLAPI =UnloadImageColors, colors
	assemble line
end calminstruction

; Unload colors palette loaded with LoadImagePalette()
; void UnloadImagePalette(Color * colors)
calminstruction UnloadImagePalette colors*
	local line
	arrange line, =RLAPI =UnloadImagePalette, colors
	assemble line
end calminstruction

; Get image alpha border rectangle
; Rectangle GetImageAlphaBorder(Image image, float threshold)
calminstruction GetImageAlphaBorder image*, threshold*
	local line
	arrange line, =RLAPI =GetImageAlphaBorder, image,threshold
	assemble line
end calminstruction

; Get image pixel color at (x, y) position
; Color GetImageColor(Image image, int x, int y)
calminstruction GetImageColor image*, x*, y*
	local line
	arrange line, =RLAPI =GetImageColor, image,x,y
	assemble line
end calminstruction

; Clear image background with given color
; void ImageClearBackground(Image * dst, Color color)
calminstruction ImageClearBackground dst*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageClearBackground, dst,color
	assemble line
end calminstruction

; Draw pixel within an image
; void ImageDrawPixel(Image * dst, int posX, int posY, Color color)
calminstruction ImageDrawPixel dst*, posX*, posY*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawPixel, dst,posX,posY,color
	assemble line
end calminstruction

; Draw pixel within an image (Vector version)
; void ImageDrawPixelV(Image * dst, Vector2 position, Color color)
calminstruction ImageDrawPixelV dst*, position*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawPixelV, dst,position,color
	assemble line
end calminstruction

; Draw line within an image
; void ImageDrawLine(Image * dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color)
calminstruction ImageDrawLine dst*, startPosX*, startPosY*, endPosX*, endPosY*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawLine, dst,startPosX,startPosY,endPosX,endPosY,color
	assemble line
end calminstruction

; Draw line within an image (Vector version)
; void ImageDrawLineV(Image * dst, Vector2 start, Vector2 end, Color color)
calminstruction ImageDrawLineV dst*, start*, end_*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawLineV, dst,start,end_,color
	assemble line
end calminstruction

; Draw a line defining thickness within an image
; void ImageDrawLineEx(Image * dst, Vector2 start, Vector2 end, int thick, Color color)
calminstruction ImageDrawLineEx dst*, start*, end_*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawLineEx, dst,start,end_,thick,color
	assemble line
end calminstruction

; Draw a filled circle within an image
; void ImageDrawCircle(Image * dst, int centerX, int centerY, int radius, Color color)
calminstruction ImageDrawCircle dst*, centerX*, centerY*, radius*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawCircle, dst,centerX,centerY,radius,color
	assemble line
end calminstruction

; Draw a filled circle within an image (Vector version)
; void ImageDrawCircleV(Image * dst, Vector2 center, int radius, Color color)
calminstruction ImageDrawCircleV dst*, center*, radius*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawCircleV, dst,center,radius,color
	assemble line
end calminstruction

; Draw circle outline within an image
; void ImageDrawCircleLines(Image * dst, int centerX, int centerY, int radius, Color color)
calminstruction ImageDrawCircleLines dst*, centerX*, centerY*, radius*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawCircleLines, dst,centerX,centerY,radius,color
	assemble line
end calminstruction

; Draw circle outline within an image (Vector version)
; void ImageDrawCircleLinesV(Image * dst, Vector2 center, int radius, Color color)
calminstruction ImageDrawCircleLinesV dst*, center*, radius*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawCircleLinesV, dst,center,radius,color
	assemble line
end calminstruction

; Draw rectangle within an image
; void ImageDrawRectangle(Image * dst, int posX, int posY, int width, int height, Color color)
calminstruction ImageDrawRectangle dst*, posX*, posY*, width*, height*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawRectangle, dst,posX,posY,width,height,color
	assemble line
end calminstruction

; Draw rectangle within an image (Vector version)
; void ImageDrawRectangleV(Image * dst, Vector2 position, Vector2 size, Color color)
calminstruction ImageDrawRectangleV dst*, position*, size*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawRectangleV, dst,position,size,color
	assemble line
end calminstruction

; Draw rectangle within an image
; void ImageDrawRectangleRec(Image * dst, Rectangle rec, Color color)
calminstruction ImageDrawRectangleRec dst*, rec*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawRectangleRec, dst,rec,color
	assemble line
end calminstruction

; Draw rectangle lines within an image
; void ImageDrawRectangleLines(Image * dst, Rectangle rec, int thick, Color color)
calminstruction ImageDrawRectangleLines dst*, rec*, thick*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawRectangleLines, dst,rec,thick,color
	assemble line
end calminstruction

; Draw triangle within an image
; void ImageDrawTriangle(Image * dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color)
calminstruction ImageDrawTriangle dst*, v1*, v2*, v3*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawTriangle, dst,v1,v2,v3,color
	assemble line
end calminstruction

; Draw triangle with interpolated colors within an image
; void ImageDrawTriangleEx(Image * dst, Vector2 v1, Vector2 v2, Vector2 v3, Color c1, Color c2, Color c3)
calminstruction ImageDrawTriangleEx dst*, v1*, v2*, v3*, c1*, c2*, c3*
	local line
	transform c1, RayLib
	transform c2, RayLib
	transform c3, RayLib
	arrange line, =RLAPI =ImageDrawTriangleEx, dst,v1,v2,v3,c1,c2,c3
	assemble line
end calminstruction

; Draw triangle outline within an image
; void ImageDrawTriangleLines(Image * dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color)
calminstruction ImageDrawTriangleLines dst*, v1*, v2*, v3*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawTriangleLines, dst,v1,v2,v3,color
	assemble line
end calminstruction

; Draw a triangle fan defined by points within an image (first vertex is the center)
; void ImageDrawTriangleFan(Image * dst, const Vector2 * points, int pointCount, Color color)
calminstruction ImageDrawTriangleFan dst*, points*, pointCount*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawTriangleFan, dst,points,pointCount,color
	assemble line
end calminstruction

; Draw a triangle strip defined by points within an image
; void ImageDrawTriangleStrip(Image * dst, const Vector2 * points, int pointCount, Color color)
calminstruction ImageDrawTriangleStrip dst*, points*, pointCount*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawTriangleStrip, dst,points,pointCount,color
	assemble line
end calminstruction

; Draw a source image within a destination image (tint applied to source)
; void ImageDraw(Image * dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint)
calminstruction ImageDraw dst*, src*, srcRec*, dstRec*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =ImageDraw, dst,src,srcRec,dstRec,tint
	assemble line
end calminstruction

; Draw text (using default font) within an image (destination)
; void ImageDrawText(Image * dst, const char * text, int posX, int posY, int fontSize, Color color)
calminstruction ImageDrawText dst*, text*, posX*, posY*, fontSize*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ImageDrawText, dst,text,posX,posY,fontSize,color
	assemble line
end calminstruction

; Draw text (custom sprite font) within an image (destination)
; void ImageDrawTextEx(Image * dst, Font font, const char * text, Vector2 position, float fontSize, float spacing, Color tint)
calminstruction ImageDrawTextEx dst*, font*, text*, position*, fontSize*, spacing*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =ImageDrawTextEx, dst,font,text,position,fontSize,spacing,tint
	assemble line
end calminstruction

; Load texture from file into GPU memory (VRAM)
; Texture2D LoadTexture(const char * fileName)
calminstruction LoadTexture fileName*
	local line
	arrange line, =RLAPI =LoadTexture, fileName
	assemble line
end calminstruction

; Load texture from image data
; Texture2D LoadTextureFromImage(Image image)
calminstruction LoadTextureFromImage image*
	local line
	arrange line, =RLAPI =LoadTextureFromImage, image
	assemble line
end calminstruction

; Load cubemap from image, multiple image cubemap layouts supported
; TextureCubemap LoadTextureCubemap(Image image, CubemapLayout layout)
calminstruction LoadTextureCubemap image*, layout*
	local line
	transform layout, RayLib.CubemapLayout
	arrange line, =RLAPI =LoadTextureCubemap, image,layout
	assemble line
end calminstruction

; Load texture for rendering (framebuffer)
; RenderTexture2D LoadRenderTexture(int width, int height)
calminstruction LoadRenderTexture width*, height*
	local line
	arrange line, =RLAPI =LoadRenderTexture, width,height
	assemble line
end calminstruction

; Check if a texture is valid (loaded in GPU)
; bool IsTextureValid(Texture2D texture)
calminstruction IsTextureValid texture*
	local line
	arrange line, =RLAPI =IsTextureValid, texture
	assemble line
end calminstruction

; Unload texture from GPU memory (VRAM)
; void UnloadTexture(Texture2D texture)
calminstruction UnloadTexture texture*
	local line
	arrange line, =RLAPI =UnloadTexture, texture
	assemble line
end calminstruction

; Check if a render texture is valid (loaded in GPU)
; bool IsRenderTextureValid(RenderTexture2D target)
calminstruction IsRenderTextureValid target*
	local line
	arrange line, =RLAPI =IsRenderTextureValid, target
	assemble line
end calminstruction

; Unload render texture from GPU memory (VRAM)
; void UnloadRenderTexture(RenderTexture2D target)
calminstruction UnloadRenderTexture target*
	local line
	arrange line, =RLAPI =UnloadRenderTexture, target
	assemble line
end calminstruction

; Update GPU texture with new data (pixels should be able to fill texture)
; void UpdateTexture(Texture2D texture, const void * pixels)
calminstruction UpdateTexture texture*, pixels*
	local line
	arrange line, =RLAPI =UpdateTexture, texture,pixels
	assemble line
end calminstruction

; Update GPU texture rectangle with new data (pixels and rec should fit in texture)
; void UpdateTextureRec(Texture2D texture, Rectangle rec, const void * pixels)
calminstruction UpdateTextureRec texture*, rec*, pixels*
	local line
	arrange line, =RLAPI =UpdateTextureRec, texture,rec,pixels
	assemble line
end calminstruction

; Generate GPU mipmaps for a texture
; void GenTextureMipmaps(Texture2D * texture)
calminstruction GenTextureMipmaps texture*
	local line
	arrange line, =RLAPI =GenTextureMipmaps, texture
	assemble line
end calminstruction

; Set texture scaling filter mode
; void SetTextureFilter(Texture2D texture, TextureFilter filter)
calminstruction SetTextureFilter texture*, filter*
	local line
	transform filter, RayLib.TextureFilter
	arrange line, =RLAPI =SetTextureFilter, texture,filter
	assemble line
end calminstruction

; Set texture wrapping mode
; void SetTextureWrap(Texture2D texture, TextureWrap wrap)
calminstruction SetTextureWrap texture*, wrap*
	local line
	transform wrap, RayLib.TextureWrap
	arrange line, =RLAPI =SetTextureWrap, texture,wrap
	assemble line
end calminstruction

; Draw a Texture2D
; void DrawTexture(Texture2D texture, int posX, int posY, Color tint)
calminstruction DrawTexture texture*, posX*, posY*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawTexture, texture,posX,posY,tint
	assemble line
end calminstruction

; Draw a Texture2D with position defined as Vector2
; void DrawTextureV(Texture2D texture, Vector2 position, Color tint)
calminstruction DrawTextureV texture*, position*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawTextureV, texture,position,tint
	assemble line
end calminstruction

; Draw a Texture2D with extended parameters
; void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint)
calminstruction DrawTextureEx texture*, position*, rotation*, scale*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawTextureEx, texture,position,rotation,scale,tint
	assemble line
end calminstruction

; Draw a part of a texture defined by a rectangle
; void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint)
calminstruction DrawTextureRec texture*, source*, position*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawTextureRec, texture,source,position,tint
	assemble line
end calminstruction

; Draw a part of a texture defined by a rectangle with 'pro' parameters
; void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint)
calminstruction DrawTexturePro texture*, source*, dest*, origin*, rotation*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawTexturePro, texture,source,dest,origin,rotation,tint
	assemble line
end calminstruction

; Draws a texture (or part of it) that stretches or shrinks nicely
; void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint)
calminstruction DrawTextureNPatch texture*, nPatchInfo*, dest*, origin*, rotation*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawTextureNPatch, texture,nPatchInfo,dest,origin,rotation,tint
	assemble line
end calminstruction

; Check if two colors are equal
; bool ColorIsEqual(Color col1, Color col2)
calminstruction ColorIsEqual col1*, col2*
	local line
	transform col1, RayLib
	transform col2, RayLib
	arrange line, =RLAPI =ColorIsEqual, col1,col2
	assemble line
end calminstruction

; Get color with alpha applied, alpha goes from 0.0f to 1.0f
; Color Fade(Color color, float alpha)
calminstruction Fade color*, alpha*
	local line
	transform color, RayLib
	arrange line, =RLAPI =Fade, color,alpha
	assemble line
end calminstruction

; Get hexadecimal value for a Color (0xRRGGBBAA)
; int ColorToInt(Color color)
calminstruction ColorToInt color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ColorToInt, color
	assemble line
end calminstruction

; Get Color normalized as float [0..1]
; Vector4 ColorNormalize(Color color)
calminstruction ColorNormalize color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ColorNormalize, color
	assemble line
end calminstruction

; Get Color from normalized values [0..1]
; Color ColorFromNormalized(Vector4 normalized)
calminstruction ColorFromNormalized normalized*
	local line
	arrange line, =RLAPI =ColorFromNormalized, normalized
	assemble line
end calminstruction

; Get HSV values for a Color, hue [0..360], saturation/value [0..1]
; Vector3 ColorToHSV(Color color)
calminstruction ColorToHSV color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ColorToHSV, color
	assemble line
end calminstruction

; Get a Color from HSV values, hue [0..360], saturation/value [0..1]
; Color ColorFromHSV(float hue, float saturation, float value)
calminstruction ColorFromHSV hue*, saturation*, value*
	local line
	arrange line, =RLAPI =ColorFromHSV, hue,saturation,value
	assemble line
end calminstruction

; Get color multiplied with another color
; Color ColorTint(Color color, Color tint)
calminstruction ColorTint color*, tint*
	local line
	transform color, RayLib
	transform tint, RayLib
	arrange line, =RLAPI =ColorTint, color,tint
	assemble line
end calminstruction

; Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
; Color ColorBrightness(Color color, float factor)
calminstruction ColorBrightness color*, factor*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ColorBrightness, color,factor
	assemble line
end calminstruction

; Get color with contrast correction, contrast values between -1.0f and 1.0f
; Color ColorContrast(Color color, float contrast)
calminstruction ColorContrast color*, contrast*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ColorContrast, color,contrast
	assemble line
end calminstruction

; Get color with alpha applied, alpha goes from 0.0f to 1.0f
; Color ColorAlpha(Color color, float alpha)
calminstruction ColorAlpha color*, alpha*
	local line
	transform color, RayLib
	arrange line, =RLAPI =ColorAlpha, color,alpha
	assemble line
end calminstruction

; Get src alpha-blended into dst color with tint
; Color ColorAlphaBlend(Color dst, Color src, Color tint)
calminstruction ColorAlphaBlend dst*, src*, tint*
	local line
	transform dst, RayLib
	transform src, RayLib
	transform tint, RayLib
	arrange line, =RLAPI =ColorAlphaBlend, dst,src,tint
	assemble line
end calminstruction

; Get color lerp interpolation between two colors, factor [0.0f..1.0f]
; Color ColorLerp(Color color1, Color color2, float factor)
calminstruction ColorLerp color1*, color2*, factor*
	local line
	transform color1, RayLib
	transform color2, RayLib
	arrange line, =RLAPI =ColorLerp, color1,color2,factor
	assemble line
end calminstruction

; Get Color structure from hexadecimal value
; Color GetColor(unsigned int hexValue)
calminstruction GetColor hexValue*
	local line
	arrange line, =RLAPI =GetColor, hexValue
	assemble line
end calminstruction

; Get Color from a source pixel pointer of certain format
; Color GetPixelColor(void * srcPtr, PixelFormat format)
calminstruction GetPixelColor srcPtr*, format*
	local line
	transform format, RayLib.PixelFormat
	arrange line, =RLAPI =GetPixelColor, srcPtr,format
	assemble line
end calminstruction

; Set color formatted into destination pixel pointer
; void SetPixelColor(void * dstPtr, Color color, PixelFormat format)
calminstruction SetPixelColor dstPtr*, color*, format*
	local line
	transform color, RayLib
	transform format, RayLib.PixelFormat
	arrange line, =RLAPI =SetPixelColor, dstPtr,color,format
	assemble line
end calminstruction

; Get pixel data size in bytes for certain format
; int GetPixelDataSize(int width, int height, PixelFormat format)
calminstruction GetPixelDataSize width*, height*, format*
	local line
	transform format, RayLib.PixelFormat
	arrange line, =RLAPI =GetPixelDataSize, width,height,format
	assemble line
end calminstruction

; Get the default Font
; Font GetFontDefault(void)
calminstruction GetFontDefault
	local line
	arrange line, =RLAPI =GetFontDefault
	assemble line
end calminstruction

; Load font from file into GPU memory (VRAM)
; Font LoadFont(const char * fileName)
calminstruction LoadFont fileName*
	local line
	arrange line, =RLAPI =LoadFont, fileName
	assemble line
end calminstruction

; Load font from file with extended parameters, use NULL for codepoints and 0 for codepointCount to load the default character set, font size is provided in pixels height
; Font LoadFontEx(const char * fileName, int fontSize, const int * codepoints, int codepointCount)
calminstruction LoadFontEx fileName*, fontSize*, codepoints*, codepointCount*
	local line
	arrange line, =RLAPI =LoadFontEx, fileName,fontSize,codepoints,codepointCount
	assemble line
end calminstruction

; Load font from Image (XNA style)
; Font LoadFontFromImage(Image image, Color key, int firstChar)
calminstruction LoadFontFromImage image*, key*, firstChar*
	local line
	transform key, RayLib
	arrange line, =RLAPI =LoadFontFromImage, image,key,firstChar
	assemble line
end calminstruction

; Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
; Font LoadFontFromMemory(const char * fileType, const unsigned char * fileData, int dataSize, int fontSize, const int * codepoints, int codepointCount)
calminstruction LoadFontFromMemory fileType*, fileData*, dataSize*, fontSize*, codepoints*, codepointCount*
	local line
	arrange line, =RLAPI =LoadFontFromMemory, fileType,fileData,dataSize,fontSize,codepoints,codepointCount
	assemble line
end calminstruction

; Check if a font is valid (font data loaded, WARNING: GPU texture not checked)
; bool IsFontValid(Font font)
calminstruction IsFontValid font*
	local line
	arrange line, =RLAPI =IsFontValid, font
	assemble line
end calminstruction

; Load font data for further use
; GlyphInfo * LoadFontData(const unsigned char * fileData, int dataSize, int fontSize, const int * codepoints, int codepointCount, FontType type, int * glyphCount)
calminstruction LoadFontData fileData*, dataSize*, fontSize*, codepoints*, codepointCount*, type*, glyphCount*
	local line
	transform type, RayLib.FontType
	arrange line, =RLAPI =LoadFontData, fileData,dataSize,fontSize,codepoints,codepointCount,type,glyphCount
	assemble line
end calminstruction

; Generate image font atlas using chars info
; Image GenImageFontAtlas(const GlyphInfo * glyphs, Rectangle ** glyphRecs, int glyphCount, int fontSize, int padding, int packMethod)
calminstruction GenImageFontAtlas glyphs*, glyphRecs*, glyphCount*, fontSize*, padding*, packMethod*
	local line
	arrange line, =RLAPI =GenImageFontAtlas, glyphs,glyphRecs,glyphCount,fontSize,padding,packMethod
	assemble line
end calminstruction

; Unload font chars info data (RAM)
; void UnloadFontData(GlyphInfo * glyphs, int glyphCount)
calminstruction UnloadFontData glyphs*, glyphCount*
	local line
	arrange line, =RLAPI =UnloadFontData, glyphs,glyphCount
	assemble line
end calminstruction

; Unload font from GPU memory (VRAM)
; void UnloadFont(Font font)
calminstruction UnloadFont font*
	local line
	arrange line, =RLAPI =UnloadFont, font
	assemble line
end calminstruction

; Export font as code file, returns true on success
; bool ExportFontAsCode(Font font, const char * fileName)
calminstruction ExportFontAsCode font*, fileName*
	local line
	arrange line, =RLAPI =ExportFontAsCode, font,fileName
	assemble line
end calminstruction

; Draw current FPS
; void DrawFPS(int posX, int posY)
calminstruction DrawFPS posX*, posY*
	local line
	arrange line, =RLAPI =DrawFPS, posX,posY
	assemble line
end calminstruction

; Draw text (using default font)
; void DrawText(const char * text, int posX, int posY, int fontSize, Color color)
calminstruction DrawText text*, posX*, posY*, fontSize*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawText, text,posX,posY,fontSize,color
	assemble line
end calminstruction

; Draw text using font and additional parameters
; void DrawTextEx(Font font, const char * text, Vector2 position, float fontSize, float spacing, Color tint)
calminstruction DrawTextEx font*, text*, position*, fontSize*, spacing*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawTextEx, font,text,position,fontSize,spacing,tint
	assemble line
end calminstruction

; Draw text using Font and pro parameters (rotation)
; void DrawTextPro(Font font, const char * text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint)
calminstruction DrawTextPro font*, text*, position*, origin*, rotation*, fontSize*, spacing*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawTextPro, font,text,position,origin,rotation,fontSize,spacing,tint
	assemble line
end calminstruction

; Draw one character (codepoint)
; void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint)
calminstruction DrawTextCodepoint font*, codepoint*, position*, fontSize*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawTextCodepoint, font,codepoint,position,fontSize,tint
	assemble line
end calminstruction

; Draw multiple character (codepoint)
; void DrawTextCodepoints(Font font, const int * codepoints, int codepointCount, Vector2 position, float fontSize, float spacing, Color tint)
calminstruction DrawTextCodepoints font*, codepoints*, codepointCount*, position*, fontSize*, spacing*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawTextCodepoints, font,codepoints,codepointCount,position,fontSize,spacing,tint
	assemble line
end calminstruction

; Set vertical line spacing when drawing with line-breaks
; void SetTextLineSpacing(int spacing)
calminstruction SetTextLineSpacing spacing*
	local line
	arrange line, =RLAPI =SetTextLineSpacing, spacing
	assemble line
end calminstruction

; Measure string width for default font
; int MeasureText(const char * text, int fontSize)
calminstruction MeasureText text*, fontSize*
	local line
	arrange line, =RLAPI =MeasureText, text,fontSize
	assemble line
end calminstruction

; Measure string size for Font
; Vector2 MeasureTextEx(Font font, const char * text, float fontSize, float spacing)
calminstruction MeasureTextEx font*, text*, fontSize*, spacing*
	local line
	arrange line, =RLAPI =MeasureTextEx, font,text,fontSize,spacing
	assemble line
end calminstruction

; Measure string size for an existing array of codepoints for Font
; Vector2 MeasureTextCodepoints(Font font, const int * codepoints, int length, float fontSize, float spacing)
calminstruction MeasureTextCodepoints font*, codepoints*, length*, fontSize*, spacing*
	local line
	arrange line, =RLAPI =MeasureTextCodepoints, font,codepoints,length,fontSize,spacing
	assemble line
end calminstruction

; Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
; int GetGlyphIndex(Font font, int codepoint)
calminstruction GetGlyphIndex font*, codepoint*
	local line
	arrange line, =RLAPI =GetGlyphIndex, font,codepoint
	assemble line
end calminstruction

; Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
; GlyphInfo GetGlyphInfo(Font font, int codepoint)
calminstruction GetGlyphInfo font*, codepoint*
	local line
	arrange line, =RLAPI =GetGlyphInfo, font,codepoint
	assemble line
end calminstruction

; Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found
; Rectangle GetGlyphAtlasRec(Font font, int codepoint)
calminstruction GetGlyphAtlasRec font*, codepoint*
	local line
	arrange line, =RLAPI =GetGlyphAtlasRec, font,codepoint
	assemble line
end calminstruction

; Load UTF-8 text encoded from codepoints array
; char * LoadUTF8(const int * codepoints, int length)
calminstruction LoadUTF8 codepoints*, length*
	local line
	arrange line, =RLAPI =LoadUTF8, codepoints,length
	assemble line
end calminstruction

; Unload UTF-8 text encoded from codepoints array
; void UnloadUTF8(char * text)
calminstruction UnloadUTF8 text*
	local line
	arrange line, =RLAPI =UnloadUTF8, text
	assemble line
end calminstruction

; Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
; int * LoadCodepoints(const char * text, int * count)
calminstruction LoadCodepoints text*, count*
	local line
	arrange line, =RLAPI =LoadCodepoints, text,count
	assemble line
end calminstruction

; Unload codepoints data from memory
; void UnloadCodepoints(int * codepoints)
calminstruction UnloadCodepoints codepoints*
	local line
	arrange line, =RLAPI =UnloadCodepoints, codepoints
	assemble line
end calminstruction

; Get total number of codepoints in a UTF-8 encoded string
; int GetCodepointCount(const char * text)
calminstruction GetCodepointCount text*
	local line
	arrange line, =RLAPI =GetCodepointCount, text
	assemble line
end calminstruction

; Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
; int GetCodepoint(const char * text, int * codepointSize)
calminstruction GetCodepoint text*, codepointSize*
	local line
	arrange line, =RLAPI =GetCodepoint, text,codepointSize
	assemble line
end calminstruction

; Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
; int GetCodepointNext(const char * text, int * codepointSize)
calminstruction GetCodepointNext text*, codepointSize*
	local line
	arrange line, =RLAPI =GetCodepointNext, text,codepointSize
	assemble line
end calminstruction

; Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
; int GetCodepointPrevious(const char * text, int * codepointSize)
calminstruction GetCodepointPrevious text*, codepointSize*
	local line
	arrange line, =RLAPI =GetCodepointPrevious, text,codepointSize
	assemble line
end calminstruction

; Encode one codepoint into UTF-8 byte array (array length returned as parameter)
; const char * CodepointToUTF8(int codepoint, int * utf8Size)
calminstruction CodepointToUTF8 codepoint*, utf8Size*
	local line
	arrange line, =RLAPI =CodepointToUTF8, codepoint,utf8Size
	assemble line
end calminstruction

; Load text as separate lines ('\n')
; char ** LoadTextLines(const char * text, int * count)
calminstruction LoadTextLines text*, count*
	local line
	arrange line, =RLAPI =LoadTextLines, text,count
	assemble line
end calminstruction

; Unload text lines
; void UnloadTextLines(char ** text, int lineCount)
calminstruction UnloadTextLines text*, lineCount*
	local line
	arrange line, =RLAPI =UnloadTextLines, text,lineCount
	assemble line
end calminstruction

; Copy one string to another, returns bytes copied
; int TextCopy(char * dst, const char * src)
calminstruction TextCopy dst*, src*
	local line
	arrange line, =RLAPI =TextCopy, dst,src
	assemble line
end calminstruction

; Check if two text string are equal
; bool TextIsEqual(const char * text1, const char * text2)
calminstruction TextIsEqual text1*, text2*
	local line
	arrange line, =RLAPI =TextIsEqual, text1,text2
	assemble line
end calminstruction

; Get text length, checks for '\0' ending
; unsigned int TextLength(const char * text)
calminstruction TextLength text*
	local line
	arrange line, =RLAPI =TextLength, text
	assemble line
end calminstruction

; Text formatting with variables (sprintf() style)
; const char * TextFormat(const char * text, ... args)
calminstruction TextFormat text*, args*
	local line
	arrange line, =RLAPI =TextFormat, text,args
	assemble line
end calminstruction

; Get a piece of a text string
; const char * TextSubtext(const char * text, int position, int length)
calminstruction TextSubtext text*, position*, length*
	local line
	arrange line, =RLAPI =TextSubtext, text,position,length
	assemble line
end calminstruction

; Remove text spaces, concat words
; const char * TextRemoveSpaces(const char * text)
calminstruction TextRemoveSpaces text*
	local line
	arrange line, =RLAPI =TextRemoveSpaces, text
	assemble line
end calminstruction

; Get text between two strings
; char * GetTextBetween(const char * text, const char * begin, const char * end)
calminstruction GetTextBetween text*, begin*, end_*
	local line
	arrange line, =RLAPI =GetTextBetween, text,begin,end_
	assemble line
end calminstruction

; Replace text string with new string
; char * TextReplace(const char * text, const char * search, const char * replacement)
calminstruction TextReplace text*, search*, replacement*
	local line
	arrange line, =RLAPI =TextReplace, text,search,replacement
	assemble line
end calminstruction

; Replace text string with new string, memory must be MemFree()
; char * TextReplaceAlloc(const char * text, const char * search, const char * replacement)
calminstruction TextReplaceAlloc text*, search*, replacement*
	local line
	arrange line, =RLAPI =TextReplaceAlloc, text,search,replacement
	assemble line
end calminstruction

; Replace text between two specific strings
; char * TextReplaceBetween(const char * text, const char * begin, const char * end, const char * replacement)
calminstruction TextReplaceBetween text*, begin*, end_*, replacement*
	local line
	arrange line, =RLAPI =TextReplaceBetween, text,begin,end_,replacement
	assemble line
end calminstruction

; Replace text between two specific strings, memory must be MemFree()
; char * TextReplaceBetweenAlloc(const char * text, const char * begin, const char * end, const char * replacement)
calminstruction TextReplaceBetweenAlloc text*, begin*, end_*, replacement*
	local line
	arrange line, =RLAPI =TextReplaceBetweenAlloc, text,begin,end_,replacement
	assemble line
end calminstruction

; Insert text in a defined byte position
; char * TextInsert(const char * text, const char * insert, int position)
calminstruction TextInsert text*, insert*, position*
	local line
	arrange line, =RLAPI =TextInsert, text,insert,position
	assemble line
end calminstruction

; Insert text in a defined byte position, memory must be MemFree()
; char * TextInsertAlloc(const char * text, const char * insert, int position)
calminstruction TextInsertAlloc text*, insert*, position*
	local line
	arrange line, =RLAPI =TextInsertAlloc, text,insert,position
	assemble line
end calminstruction

; Join text strings with delimiter
; char * TextJoin(char ** textList, int count, const char * delimiter)
calminstruction TextJoin textList*, count*, delimiter*
	local line
	arrange line, =RLAPI =TextJoin, textList,count,delimiter
	assemble line
end calminstruction

; Split text into multiple strings, using MAX_TEXTSPLIT_COUNT static strings
; char ** TextSplit(const char * text, char delimiter, int * count)
calminstruction TextSplit text*, delimiter*, count*
	local line
	arrange line, =RLAPI =TextSplit, text,delimiter,count
	assemble line
end calminstruction

; Append text at specific position and move cursor
; void TextAppend(char * text, const char * append, int * position)
calminstruction TextAppend text*, append*, position*
	local line
	arrange line, =RLAPI =TextAppend, text,append,position
	assemble line
end calminstruction

; Find first text occurrence within a string, -1 if not found
; int TextFindIndex(const char * text, const char * search)
calminstruction TextFindIndex text*, search*
	local line
	arrange line, =RLAPI =TextFindIndex, text,search
	assemble line
end calminstruction

; Get upper case version of provided string
; char * TextToUpper(const char * text)
calminstruction TextToUpper text*
	local line
	arrange line, =RLAPI =TextToUpper, text
	assemble line
end calminstruction

; Get lower case version of provided string
; char * TextToLower(const char * text)
calminstruction TextToLower text*
	local line
	arrange line, =RLAPI =TextToLower, text
	assemble line
end calminstruction

; Get Pascal case notation version of provided string
; char * TextToPascal(const char * text)
calminstruction TextToPascal text*
	local line
	arrange line, =RLAPI =TextToPascal, text
	assemble line
end calminstruction

; Get Snake case notation version of provided string
; char * TextToSnake(const char * text)
calminstruction TextToSnake text*
	local line
	arrange line, =RLAPI =TextToSnake, text
	assemble line
end calminstruction

; Get Camel case notation version of provided string
; char * TextToCamel(const char * text)
calminstruction TextToCamel text*
	local line
	arrange line, =RLAPI =TextToCamel, text
	assemble line
end calminstruction

; Get integer value from text
; int TextToInteger(const char * text)
calminstruction TextToInteger text*
	local line
	arrange line, =RLAPI =TextToInteger, text
	assemble line
end calminstruction

; Get float value from text
; float TextToFloat(const char * text)
calminstruction TextToFloat text*
	local line
	arrange line, =RLAPI =TextToFloat, text
	assemble line
end calminstruction

; Draw a line in 3D world space
; void DrawLine3D(Vector3 startPos, Vector3 endPos, Color color)
calminstruction DrawLine3D startPos*, endPos*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawLine3D, startPos,endPos,color
	assemble line
end calminstruction

; Draw a point in 3D space, actually a small line
; void DrawPoint3D(Vector3 position, Color color)
calminstruction DrawPoint3D position*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawPoint3D, position,color
	assemble line
end calminstruction

; Draw a circle in 3D world space
; void DrawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color)
calminstruction DrawCircle3D center*, radius*, rotationAxis*, rotationAngle*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCircle3D, center,radius,rotationAxis,rotationAngle,color
	assemble line
end calminstruction

; Draw a color-filled triangle (vertex in counter-clockwise order!)
; void DrawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color)
calminstruction DrawTriangle3D v1*, v2*, v3*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawTriangle3D, v1,v2,v3,color
	assemble line
end calminstruction

; Draw a triangle strip defined by points
; void DrawTriangleStrip3D(const Vector3 * points, int pointCount, Color color)
calminstruction DrawTriangleStrip3D points*, pointCount*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawTriangleStrip3D, points,pointCount,color
	assemble line
end calminstruction

; Draw cube
; void DrawCube(Vector3 position, float width, float height, float length, Color color)
calminstruction DrawCube position*, width*, height*, length*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCube, position,width,height,length,color
	assemble line
end calminstruction

; Draw cube (Vector version)
; void DrawCubeV(Vector3 position, Vector3 size, Color color)
calminstruction DrawCubeV position*, size*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCubeV, position,size,color
	assemble line
end calminstruction

; Draw cube wires
; void DrawCubeWires(Vector3 position, float width, float height, float length, Color color)
calminstruction DrawCubeWires position*, width*, height*, length*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCubeWires, position,width,height,length,color
	assemble line
end calminstruction

; Draw cube wires (Vector version)
; void DrawCubeWiresV(Vector3 position, Vector3 size, Color color)
calminstruction DrawCubeWiresV position*, size*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCubeWiresV, position,size,color
	assemble line
end calminstruction

; Draw sphere
; void DrawSphere(Vector3 centerPos, float radius, Color color)
calminstruction DrawSphere centerPos*, radius*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSphere, centerPos,radius,color
	assemble line
end calminstruction

; Draw sphere with extended parameters
; void DrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color)
calminstruction DrawSphereEx centerPos*, radius*, rings*, slices*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSphereEx, centerPos,radius,rings,slices,color
	assemble line
end calminstruction

; Draw sphere wires
; void DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color)
calminstruction DrawSphereWires centerPos*, radius*, rings*, slices*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawSphereWires, centerPos,radius,rings,slices,color
	assemble line
end calminstruction

; Draw a cylinder/cone
; void DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color)
calminstruction DrawCylinder position*, radiusTop*, radiusBottom*, height*, slices*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCylinder, position,radiusTop,radiusBottom,height,slices,color
	assemble line
end calminstruction

; Draw a cylinder with base at startPos and top at endPos
; void DrawCylinderEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color)
calminstruction DrawCylinderEx startPos*, endPos*, startRadius*, endRadius*, sides*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCylinderEx, startPos,endPos,startRadius,endRadius,sides,color
	assemble line
end calminstruction

; Draw a cylinder/cone wires
; void DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color)
calminstruction DrawCylinderWires position*, radiusTop*, radiusBottom*, height*, slices*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCylinderWires, position,radiusTop,radiusBottom,height,slices,color
	assemble line
end calminstruction

; Draw a cylinder wires with base at startPos and top at endPos
; void DrawCylinderWiresEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color)
calminstruction DrawCylinderWiresEx startPos*, endPos*, startRadius*, endRadius*, sides*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCylinderWiresEx, startPos,endPos,startRadius,endRadius,sides,color
	assemble line
end calminstruction

; Draw a capsule with the center of its sphere caps at startPos and endPos
; void DrawCapsule(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color)
calminstruction DrawCapsule startPos*, endPos*, radius*, slices*, rings*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCapsule, startPos,endPos,radius,slices,rings,color
	assemble line
end calminstruction

; Draw capsule wireframe with the center of its sphere caps at startPos and endPos
; void DrawCapsuleWires(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color)
calminstruction DrawCapsuleWires startPos*, endPos*, radius*, slices*, rings*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawCapsuleWires, startPos,endPos,radius,slices,rings,color
	assemble line
end calminstruction

; Draw a plane XZ
; void DrawPlane(Vector3 centerPos, Vector2 size, Color color)
calminstruction DrawPlane centerPos*, size*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawPlane, centerPos,size,color
	assemble line
end calminstruction

; Draw a ray line
; void DrawRay(Ray ray, Color color)
calminstruction DrawRay ray*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawRay, ray,color
	assemble line
end calminstruction

; Draw a grid (centered at (0, 0, 0))
; void DrawGrid(int slices, float spacing)
calminstruction DrawGrid slices*, spacing*
	local line
	arrange line, =RLAPI =DrawGrid, slices,spacing
	assemble line
end calminstruction

; Load model from files (meshes and materials)
; Model LoadModel(const char * fileName)
calminstruction LoadModel fileName*
	local line
	arrange line, =RLAPI =LoadModel, fileName
	assemble line
end calminstruction

; Load model from generated mesh (default material)
; Model LoadModelFromMesh(Mesh mesh)
calminstruction LoadModelFromMesh mesh*
	local line
	arrange line, =RLAPI =LoadModelFromMesh, mesh
	assemble line
end calminstruction

; Check if a model is valid (loaded in GPU, VAO/VBOs)
; bool IsModelValid(Model model)
calminstruction IsModelValid model*
	local line
	arrange line, =RLAPI =IsModelValid, model
	assemble line
end calminstruction

; Unload model (including meshes) from memory (RAM and/or VRAM)
; void UnloadModel(Model model)
calminstruction UnloadModel model*
	local line
	arrange line, =RLAPI =UnloadModel, model
	assemble line
end calminstruction

; Compute model bounding box limits (considers all meshes)
; BoundingBox GetModelBoundingBox(Model model)
calminstruction GetModelBoundingBox model*
	local line
	arrange line, =RLAPI =GetModelBoundingBox, model
	assemble line
end calminstruction

; Draw a model (with texture if set)
; void DrawModel(Model model, Vector3 position, float scale, Color tint)
calminstruction DrawModel model*, position*, scale*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawModel, model,position,scale,tint
	assemble line
end calminstruction

; Draw a model with extended parameters
; void DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint)
calminstruction DrawModelEx model*, position*, rotationAxis*, rotationAngle*, scale*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawModelEx, model,position,rotationAxis,rotationAngle,scale,tint
	assemble line
end calminstruction

; Draw a model wires (with texture if set)
; void DrawModelWires(Model model, Vector3 position, float scale, Color tint)
calminstruction DrawModelWires model*, position*, scale*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawModelWires, model,position,scale,tint
	assemble line
end calminstruction

; Draw a model wires (with texture if set) with extended parameters
; void DrawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint)
calminstruction DrawModelWiresEx model*, position*, rotationAxis*, rotationAngle*, scale*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawModelWiresEx, model,position,rotationAxis,rotationAngle,scale,tint
	assemble line
end calminstruction

; Draw bounding box (wires)
; void DrawBoundingBox(BoundingBox box, Color color)
calminstruction DrawBoundingBox box*, color*
	local line
	transform color, RayLib
	arrange line, =RLAPI =DrawBoundingBox, box,color
	assemble line
end calminstruction

; Draw a billboard texture
; void DrawBillboard(Camera camera, Texture2D texture, Vector3 position, float scale, Color tint)
calminstruction DrawBillboard camera*, texture*, position*, scale*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawBillboard, camera,texture,position,scale,tint
	assemble line
end calminstruction

; Draw a billboard texture defined by source
; void DrawBillboardRec(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint)
calminstruction DrawBillboardRec camera*, texture*, source*, position*, size*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawBillboardRec, camera,texture,source,position,size,tint
	assemble line
end calminstruction

; Draw a billboard texture defined by source and rotation
; void DrawBillboardPro(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint)
calminstruction DrawBillboardPro camera*, texture*, source*, position*, up*, size*, origin*, rotation*, tint*
	local line
	transform tint, RayLib
	arrange line, =RLAPI =DrawBillboardPro, camera,texture,source,position,up,size,origin,rotation,tint
	assemble line
end calminstruction

; Upload mesh vertex data in GPU and provide VAO/VBO ids
; void UploadMesh(Mesh * mesh, bool dynamic)
calminstruction UploadMesh mesh*, dynamic*
	local line
	arrange line, =RLAPI =UploadMesh, mesh,dynamic
	assemble line
end calminstruction

; Update mesh vertex data in GPU for a specific buffer index
; void UpdateMeshBuffer(Mesh mesh, int index, const void * data, int dataSize, int offset)
calminstruction UpdateMeshBuffer mesh*, index*, data*, dataSize*, offset*
	local line
	arrange line, =RLAPI =UpdateMeshBuffer, mesh,index,data,dataSize,offset
	assemble line
end calminstruction

; Unload mesh data from CPU and GPU
; void UnloadMesh(Mesh mesh)
calminstruction UnloadMesh mesh*
	local line
	arrange line, =RLAPI =UnloadMesh, mesh
	assemble line
end calminstruction

; Draw a 3d mesh with material and transform
; void DrawMesh(Mesh mesh, Material material, Matrix transform)
calminstruction DrawMesh mesh*, material*, transform_*
	local line
	arrange line, =RLAPI =DrawMesh, mesh,material,transform_
	assemble line
end calminstruction

; Draw multiple mesh instances with material and different transforms
; void DrawMeshInstanced(Mesh mesh, Material material, const Matrix * transforms, int instances)
calminstruction DrawMeshInstanced mesh*, material*, transforms*, instances*
	local line
	arrange line, =RLAPI =DrawMeshInstanced, mesh,material,transforms,instances
	assemble line
end calminstruction

; Compute mesh bounding box limits
; BoundingBox GetMeshBoundingBox(Mesh mesh)
calminstruction GetMeshBoundingBox mesh*
	local line
	arrange line, =RLAPI =GetMeshBoundingBox, mesh
	assemble line
end calminstruction

; Compute mesh tangents
; void GenMeshTangents(Mesh * mesh)
calminstruction GenMeshTangents mesh*
	local line
	arrange line, =RLAPI =GenMeshTangents, mesh
	assemble line
end calminstruction

; Export mesh data to file, returns true on success
; bool ExportMesh(Mesh mesh, const char * fileName)
calminstruction ExportMesh mesh*, fileName*
	local line
	arrange line, =RLAPI =ExportMesh, mesh,fileName
	assemble line
end calminstruction

; Export mesh as code file (.h) defining multiple arrays of vertex attributes
; bool ExportMeshAsCode(Mesh mesh, const char * fileName)
calminstruction ExportMeshAsCode mesh*, fileName*
	local line
	arrange line, =RLAPI =ExportMeshAsCode, mesh,fileName
	assemble line
end calminstruction

; Generate polygonal mesh
; Mesh GenMeshPoly(int sides, float radius)
calminstruction GenMeshPoly sides*, radius*
	local line
	arrange line, =RLAPI =GenMeshPoly, sides,radius
	assemble line
end calminstruction

; Generate plane mesh (with subdivisions)
; Mesh GenMeshPlane(float width, float length, int resX, int resZ)
calminstruction GenMeshPlane width*, length*, resX*, resZ*
	local line
	arrange line, =RLAPI =GenMeshPlane, width,length,resX,resZ
	assemble line
end calminstruction

; Generate cuboid mesh
; Mesh GenMeshCube(float width, float height, float length)
calminstruction GenMeshCube width*, height*, length*
	local line
	arrange line, =RLAPI =GenMeshCube, width,height,length
	assemble line
end calminstruction

; Generate sphere mesh (standard sphere)
; Mesh GenMeshSphere(float radius, int rings, int slices)
calminstruction GenMeshSphere radius*, rings*, slices*
	local line
	arrange line, =RLAPI =GenMeshSphere, radius,rings,slices
	assemble line
end calminstruction

; Generate half-sphere mesh (no bottom cap)
; Mesh GenMeshHemiSphere(float radius, int rings, int slices)
calminstruction GenMeshHemiSphere radius*, rings*, slices*
	local line
	arrange line, =RLAPI =GenMeshHemiSphere, radius,rings,slices
	assemble line
end calminstruction

; Generate cylinder mesh
; Mesh GenMeshCylinder(float radius, float height, int slices)
calminstruction GenMeshCylinder radius*, height*, slices*
	local line
	arrange line, =RLAPI =GenMeshCylinder, radius,height,slices
	assemble line
end calminstruction

; Generate cone/pyramid mesh
; Mesh GenMeshCone(float radius, float height, int slices)
calminstruction GenMeshCone radius*, height*, slices*
	local line
	arrange line, =RLAPI =GenMeshCone, radius,height,slices
	assemble line
end calminstruction

; Generate torus mesh
; Mesh GenMeshTorus(float radius, float size, int radSeg, int sides)
calminstruction GenMeshTorus radius*, size*, radSeg*, sides*
	local line
	arrange line, =RLAPI =GenMeshTorus, radius,size,radSeg,sides
	assemble line
end calminstruction

; Generate trefoil knot mesh
; Mesh GenMeshKnot(float radius, float size, int radSeg, int sides)
calminstruction GenMeshKnot radius*, size*, radSeg*, sides*
	local line
	arrange line, =RLAPI =GenMeshKnot, radius,size,radSeg,sides
	assemble line
end calminstruction

; Generate heightmap mesh from image data
; Mesh GenMeshHeightmap(Image heightmap, Vector3 size)
calminstruction GenMeshHeightmap heightmap*, size*
	local line
	arrange line, =RLAPI =GenMeshHeightmap, heightmap,size
	assemble line
end calminstruction

; Generate cubes-based map mesh from image data
; Mesh GenMeshCubicmap(Image cubicmap, Vector3 cubeSize)
calminstruction GenMeshCubicmap cubicmap*, cubeSize*
	local line
	arrange line, =RLAPI =GenMeshCubicmap, cubicmap,cubeSize
	assemble line
end calminstruction

; Load materials from model file
; Material * LoadMaterials(const char * fileName, int * materialCount)
calminstruction LoadMaterials fileName*, materialCount*
	local line
	arrange line, =RLAPI =LoadMaterials, fileName,materialCount
	assemble line
end calminstruction

; Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
; Material LoadMaterialDefault(void)
calminstruction LoadMaterialDefault
	local line
	arrange line, =RLAPI =LoadMaterialDefault
	assemble line
end calminstruction

; Check if a material is valid (shader assigned, map textures loaded in GPU)
; bool IsMaterialValid(Material material)
calminstruction IsMaterialValid material*
	local line
	arrange line, =RLAPI =IsMaterialValid, material
	assemble line
end calminstruction

; Unload material from GPU memory (VRAM)
; void UnloadMaterial(Material material)
calminstruction UnloadMaterial material*
	local line
	arrange line, =RLAPI =UnloadMaterial, material
	assemble line
end calminstruction

; Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
; void SetMaterialTexture(Material * material, MaterialMapIndex mapType, Texture2D texture)
calminstruction SetMaterialTexture material*, mapType*, texture*
	local line
	transform mapType, RayLib.MaterialMapIndex
	arrange line, =RLAPI =SetMaterialTexture, material,mapType,texture
	assemble line
end calminstruction

; Set material for a mesh
; void SetModelMeshMaterial(Model * model, int meshId, int materialId)
calminstruction SetModelMeshMaterial model*, meshId*, materialId*
	local line
	arrange line, =RLAPI =SetModelMeshMaterial, model,meshId,materialId
	assemble line
end calminstruction

; Load model animations from file
; ModelAnimation * LoadModelAnimations(const char * fileName, int * animCount)
calminstruction LoadModelAnimations fileName*, animCount*
	local line
	arrange line, =RLAPI =LoadModelAnimations, fileName,animCount
	assemble line
end calminstruction

; Update model animation pose (vertex buffers and bone matrices)
; void UpdateModelAnimation(Model model, ModelAnimation anim, float frame)
calminstruction UpdateModelAnimation model*, anim*, frame*
	local line
	arrange line, =RLAPI =UpdateModelAnimation, model,anim,frame
	assemble line
end calminstruction

; Update model animation pose, blending two animations
; void UpdateModelAnimationEx(Model model, ModelAnimation animA, float frameA, ModelAnimation animB, float frameB, float blend)
calminstruction UpdateModelAnimationEx model*, animA*, frameA*, animB*, frameB*, blend*
	local line
	arrange line, =RLAPI =UpdateModelAnimationEx, model,animA,frameA,animB,frameB,blend
	assemble line
end calminstruction

; Unload animation array data
; void UnloadModelAnimations(ModelAnimation * animations, int animCount)
calminstruction UnloadModelAnimations animations*, animCount*
	local line
	arrange line, =RLAPI =UnloadModelAnimations, animations,animCount
	assemble line
end calminstruction

; Check model animation skeleton match
; bool IsModelAnimationValid(Model model, ModelAnimation anim)
calminstruction IsModelAnimationValid model*, anim*
	local line
	arrange line, =RLAPI =IsModelAnimationValid, model,anim
	assemble line
end calminstruction

; Check collision between two spheres
; bool CheckCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2)
calminstruction CheckCollisionSpheres center1*, radius1*, center2*, radius2*
	local line
	arrange line, =RLAPI =CheckCollisionSpheres, center1,radius1,center2,radius2
	assemble line
end calminstruction

; Check collision between two bounding boxes
; bool CheckCollisionBoxes(BoundingBox box1, BoundingBox box2)
calminstruction CheckCollisionBoxes box1*, box2*
	local line
	arrange line, =RLAPI =CheckCollisionBoxes, box1,box2
	assemble line
end calminstruction

; Check collision between box and sphere
; bool CheckCollisionBoxSphere(BoundingBox box, Vector3 center, float radius)
calminstruction CheckCollisionBoxSphere box*, center*, radius*
	local line
	arrange line, =RLAPI =CheckCollisionBoxSphere, box,center,radius
	assemble line
end calminstruction

; Get collision info between ray and sphere
; RayCollision GetRayCollisionSphere(Ray ray, Vector3 center, float radius)
calminstruction GetRayCollisionSphere ray*, center*, radius*
	local line
	arrange line, =RLAPI =GetRayCollisionSphere, ray,center,radius
	assemble line
end calminstruction

; Get collision info between ray and box
; RayCollision GetRayCollisionBox(Ray ray, BoundingBox box)
calminstruction GetRayCollisionBox ray*, box*
	local line
	arrange line, =RLAPI =GetRayCollisionBox, ray,box
	assemble line
end calminstruction

; Get collision info between ray and mesh
; RayCollision GetRayCollisionMesh(Ray ray, Mesh mesh, Matrix transform)
calminstruction GetRayCollisionMesh ray*, mesh*, transform_*
	local line
	arrange line, =RLAPI =GetRayCollisionMesh, ray,mesh,transform_
	assemble line
end calminstruction

; Get collision info between ray and triangle
; RayCollision GetRayCollisionTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3)
calminstruction GetRayCollisionTriangle ray*, p1*, p2*, p3*
	local line
	arrange line, =RLAPI =GetRayCollisionTriangle, ray,p1,p2,p3
	assemble line
end calminstruction

; Get collision info between ray and quad
; RayCollision GetRayCollisionQuad(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4)
calminstruction GetRayCollisionQuad ray*, p1*, p2*, p3*, p4*
	local line
	arrange line, =RLAPI =GetRayCollisionQuad, ray,p1,p2,p3,p4
	assemble line
end calminstruction

; Initialize audio device and context
; void InitAudioDevice(void)
calminstruction InitAudioDevice
	local line
	arrange line, =RLAPI =InitAudioDevice
	assemble line
end calminstruction

; Close the audio device and context
; void CloseAudioDevice(void)
calminstruction CloseAudioDevice
	local line
	arrange line, =RLAPI =CloseAudioDevice
	assemble line
end calminstruction

; Check if audio device has been initialized successfully
; bool IsAudioDeviceReady(void)
calminstruction IsAudioDeviceReady
	local line
	arrange line, =RLAPI =IsAudioDeviceReady
	assemble line
end calminstruction

; Set master volume (listener)
; void SetMasterVolume(float volume)
calminstruction SetMasterVolume volume*
	local line
	arrange line, =RLAPI =SetMasterVolume, volume
	assemble line
end calminstruction

; Get master volume (listener)
; float GetMasterVolume(void)
calminstruction GetMasterVolume
	local line
	arrange line, =RLAPI =GetMasterVolume
	assemble line
end calminstruction

; Load wave data from file
; Wave LoadWave(const char * fileName)
calminstruction LoadWave fileName*
	local line
	arrange line, =RLAPI =LoadWave, fileName
	assemble line
end calminstruction

; Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
; Wave LoadWaveFromMemory(const char * fileType, const unsigned char * fileData, int dataSize)
calminstruction LoadWaveFromMemory fileType*, fileData*, dataSize*
	local line
	arrange line, =RLAPI =LoadWaveFromMemory, fileType,fileData,dataSize
	assemble line
end calminstruction

; Checks if wave data is valid (data loaded and parameters)
; bool IsWaveValid(Wave wave)
calminstruction IsWaveValid wave*
	local line
	arrange line, =RLAPI =IsWaveValid, wave
	assemble line
end calminstruction

; Load sound from file
; Sound LoadSound(const char * fileName)
calminstruction LoadSound fileName*
	local line
	arrange line, =RLAPI =LoadSound, fileName
	assemble line
end calminstruction

; Load sound from wave data
; Sound LoadSoundFromWave(Wave wave)
calminstruction LoadSoundFromWave wave*
	local line
	arrange line, =RLAPI =LoadSoundFromWave, wave
	assemble line
end calminstruction

; Create a new sound that shares the same sample data as the source sound, does not own the sound data
; Sound LoadSoundAlias(Sound source)
calminstruction LoadSoundAlias source*
	local line
	arrange line, =RLAPI =LoadSoundAlias, source
	assemble line
end calminstruction

; Checks if a sound is valid (data loaded and buffers initialized)
; bool IsSoundValid(Sound sound)
calminstruction IsSoundValid sound*
	local line
	arrange line, =RLAPI =IsSoundValid, sound
	assemble line
end calminstruction

; Update sound buffer with new data (default data format: 32 bit float, stereo)
; void UpdateSound(Sound sound, const void * data, int sampleCount)
calminstruction UpdateSound sound*, data*, sampleCount*
	local line
	arrange line, =RLAPI =UpdateSound, sound,data,sampleCount
	assemble line
end calminstruction

; Unload wave data
; void UnloadWave(Wave wave)
calminstruction UnloadWave wave*
	local line
	arrange line, =RLAPI =UnloadWave, wave
	assemble line
end calminstruction

; Unload sound
; void UnloadSound(Sound sound)
calminstruction UnloadSound sound*
	local line
	arrange line, =RLAPI =UnloadSound, sound
	assemble line
end calminstruction

; Unload a sound alias (does not deallocate sample data)
; void UnloadSoundAlias(Sound alias)
calminstruction UnloadSoundAlias alias*
	local line
	arrange line, =RLAPI =UnloadSoundAlias, alias
	assemble line
end calminstruction

; Export wave data to file, returns true on success
; bool ExportWave(Wave wave, const char * fileName)
calminstruction ExportWave wave*, fileName*
	local line
	arrange line, =RLAPI =ExportWave, wave,fileName
	assemble line
end calminstruction

; Export wave sample data to code (.h), returns true on success
; bool ExportWaveAsCode(Wave wave, const char * fileName)
calminstruction ExportWaveAsCode wave*, fileName*
	local line
	arrange line, =RLAPI =ExportWaveAsCode, wave,fileName
	assemble line
end calminstruction

; Play a sound
; void PlaySound(Sound sound)
calminstruction PlaySound sound*
	local line
	arrange line, =RLAPI =PlaySound, sound
	assemble line
end calminstruction

; Stop playing a sound
; void StopSound(Sound sound)
calminstruction StopSound sound*
	local line
	arrange line, =RLAPI =StopSound, sound
	assemble line
end calminstruction

; Pause a sound
; void PauseSound(Sound sound)
calminstruction PauseSound sound*
	local line
	arrange line, =RLAPI =PauseSound, sound
	assemble line
end calminstruction

; Resume a paused sound
; void ResumeSound(Sound sound)
calminstruction ResumeSound sound*
	local line
	arrange line, =RLAPI =ResumeSound, sound
	assemble line
end calminstruction

; Check if a sound is currently playing
; bool IsSoundPlaying(Sound sound)
calminstruction IsSoundPlaying sound*
	local line
	arrange line, =RLAPI =IsSoundPlaying, sound
	assemble line
end calminstruction

; Set volume for a sound (1.0 is max level)
; void SetSoundVolume(Sound sound, float volume)
calminstruction SetSoundVolume sound*, volume*
	local line
	arrange line, =RLAPI =SetSoundVolume, sound,volume
	assemble line
end calminstruction

; Set pitch for a sound (1.0 is base level)
; void SetSoundPitch(Sound sound, float pitch)
calminstruction SetSoundPitch sound*, pitch*
	local line
	arrange line, =RLAPI =SetSoundPitch, sound,pitch
	assemble line
end calminstruction

; Set pan for a sound (-1.0 left, 0.0 center, 1.0 right)
; void SetSoundPan(Sound sound, float pan)
calminstruction SetSoundPan sound*, pan*
	local line
	arrange line, =RLAPI =SetSoundPan, sound,pan
	assemble line
end calminstruction

; Copy a wave to a new wave
; Wave WaveCopy(Wave wave)
calminstruction WaveCopy wave*
	local line
	arrange line, =RLAPI =WaveCopy, wave
	assemble line
end calminstruction

; Crop a wave to defined frames range
; void WaveCrop(Wave * wave, int initFrame, int finalFrame)
calminstruction WaveCrop wave*, initFrame*, finalFrame*
	local line
	arrange line, =RLAPI =WaveCrop, wave,initFrame,finalFrame
	assemble line
end calminstruction

; Convert wave data to desired format
; void WaveFormat(Wave * wave, int sampleRate, int sampleSize, int channels)
calminstruction WaveFormat wave*, sampleRate*, sampleSize*, channels*
	local line
	arrange line, =RLAPI =WaveFormat, wave,sampleRate,sampleSize,channels
	assemble line
end calminstruction

; Load samples data from wave as a 32bit float data array
; float * LoadWaveSamples(Wave wave)
calminstruction LoadWaveSamples wave*
	local line
	arrange line, =RLAPI =LoadWaveSamples, wave
	assemble line
end calminstruction

; Unload samples data loaded with LoadWaveSamples()
; void UnloadWaveSamples(float * samples)
calminstruction UnloadWaveSamples samples*
	local line
	arrange line, =RLAPI =UnloadWaveSamples, samples
	assemble line
end calminstruction

; Load music stream from file
; Music LoadMusicStream(const char * fileName)
calminstruction LoadMusicStream fileName*
	local line
	arrange line, =RLAPI =LoadMusicStream, fileName
	assemble line
end calminstruction

; Load music stream from data
; Music LoadMusicStreamFromMemory(const char * fileType, const unsigned char * data, int dataSize)
calminstruction LoadMusicStreamFromMemory fileType*, data*, dataSize*
	local line
	arrange line, =RLAPI =LoadMusicStreamFromMemory, fileType,data,dataSize
	assemble line
end calminstruction

; Checks if a music stream is valid (context and buffers initialized)
; bool IsMusicValid(Music music)
calminstruction IsMusicValid music*
	local line
	arrange line, =RLAPI =IsMusicValid, music
	assemble line
end calminstruction

; Unload music stream
; void UnloadMusicStream(Music music)
calminstruction UnloadMusicStream music*
	local line
	arrange line, =RLAPI =UnloadMusicStream, music
	assemble line
end calminstruction

; Start music playing
; void PlayMusicStream(Music music)
calminstruction PlayMusicStream music*
	local line
	arrange line, =RLAPI =PlayMusicStream, music
	assemble line
end calminstruction

; Check if music is playing
; bool IsMusicStreamPlaying(Music music)
calminstruction IsMusicStreamPlaying music*
	local line
	arrange line, =RLAPI =IsMusicStreamPlaying, music
	assemble line
end calminstruction

; Updates buffers for music streaming
; void UpdateMusicStream(Music music)
calminstruction UpdateMusicStream music*
	local line
	arrange line, =RLAPI =UpdateMusicStream, music
	assemble line
end calminstruction

; Stop music playing
; void StopMusicStream(Music music)
calminstruction StopMusicStream music*
	local line
	arrange line, =RLAPI =StopMusicStream, music
	assemble line
end calminstruction

; Pause music playing
; void PauseMusicStream(Music music)
calminstruction PauseMusicStream music*
	local line
	arrange line, =RLAPI =PauseMusicStream, music
	assemble line
end calminstruction

; Resume playing paused music
; void ResumeMusicStream(Music music)
calminstruction ResumeMusicStream music*
	local line
	arrange line, =RLAPI =ResumeMusicStream, music
	assemble line
end calminstruction

; Seek music to a position (in seconds)
; void SeekMusicStream(Music music, float position)
calminstruction SeekMusicStream music*, position*
	local line
	arrange line, =RLAPI =SeekMusicStream, music,position
	assemble line
end calminstruction

; Set volume for music (1.0 is max level)
; void SetMusicVolume(Music music, float volume)
calminstruction SetMusicVolume music*, volume*
	local line
	arrange line, =RLAPI =SetMusicVolume, music,volume
	assemble line
end calminstruction

; Set pitch for a music (1.0 is base level)
; void SetMusicPitch(Music music, float pitch)
calminstruction SetMusicPitch music*, pitch*
	local line
	arrange line, =RLAPI =SetMusicPitch, music,pitch
	assemble line
end calminstruction

; Set pan for a music (-1.0 left, 0.0 center, 1.0 right)
; void SetMusicPan(Music music, float pan)
calminstruction SetMusicPan music*, pan*
	local line
	arrange line, =RLAPI =SetMusicPan, music,pan
	assemble line
end calminstruction

; Get music time length (in seconds)
; float GetMusicTimeLength(Music music)
calminstruction GetMusicTimeLength music*
	local line
	arrange line, =RLAPI =GetMusicTimeLength, music
	assemble line
end calminstruction

; Get current music time played (in seconds)
; float GetMusicTimePlayed(Music music)
calminstruction GetMusicTimePlayed music*
	local line
	arrange line, =RLAPI =GetMusicTimePlayed, music
	assemble line
end calminstruction

; Load audio stream (to stream raw audio pcm data)
; AudioStream LoadAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels)
calminstruction LoadAudioStream sampleRate*, sampleSize*, channels*
	local line
	arrange line, =RLAPI =LoadAudioStream, sampleRate,sampleSize,channels
	assemble line
end calminstruction

; Checks if an audio stream is valid (buffers initialized)
; bool IsAudioStreamValid(AudioStream stream)
calminstruction IsAudioStreamValid stream*
	local line
	arrange line, =RLAPI =IsAudioStreamValid, stream
	assemble line
end calminstruction

; Unload audio stream and free memory
; void UnloadAudioStream(AudioStream stream)
calminstruction UnloadAudioStream stream*
	local line
	arrange line, =RLAPI =UnloadAudioStream, stream
	assemble line
end calminstruction

; Update audio stream buffers with data
; void UpdateAudioStream(AudioStream stream, const void * data, int frameCount)
calminstruction UpdateAudioStream stream*, data*, frameCount*
	local line
	arrange line, =RLAPI =UpdateAudioStream, stream,data,frameCount
	assemble line
end calminstruction

; Check if any audio stream buffers requires refill
; bool IsAudioStreamProcessed(AudioStream stream)
calminstruction IsAudioStreamProcessed stream*
	local line
	arrange line, =RLAPI =IsAudioStreamProcessed, stream
	assemble line
end calminstruction

; Play audio stream
; void PlayAudioStream(AudioStream stream)
calminstruction PlayAudioStream stream*
	local line
	arrange line, =RLAPI =PlayAudioStream, stream
	assemble line
end calminstruction

; Pause audio stream
; void PauseAudioStream(AudioStream stream)
calminstruction PauseAudioStream stream*
	local line
	arrange line, =RLAPI =PauseAudioStream, stream
	assemble line
end calminstruction

; Resume audio stream
; void ResumeAudioStream(AudioStream stream)
calminstruction ResumeAudioStream stream*
	local line
	arrange line, =RLAPI =ResumeAudioStream, stream
	assemble line
end calminstruction

; Check if audio stream is playing
; bool IsAudioStreamPlaying(AudioStream stream)
calminstruction IsAudioStreamPlaying stream*
	local line
	arrange line, =RLAPI =IsAudioStreamPlaying, stream
	assemble line
end calminstruction

; Stop audio stream
; void StopAudioStream(AudioStream stream)
calminstruction StopAudioStream stream*
	local line
	arrange line, =RLAPI =StopAudioStream, stream
	assemble line
end calminstruction

; Set volume for audio stream (1.0 is max level)
; void SetAudioStreamVolume(AudioStream stream, float volume)
calminstruction SetAudioStreamVolume stream*, volume*
	local line
	arrange line, =RLAPI =SetAudioStreamVolume, stream,volume
	assemble line
end calminstruction

; Set pitch for audio stream (1.0 is base level)
; void SetAudioStreamPitch(AudioStream stream, float pitch)
calminstruction SetAudioStreamPitch stream*, pitch*
	local line
	arrange line, =RLAPI =SetAudioStreamPitch, stream,pitch
	assemble line
end calminstruction

; Set pan for audio stream (-1.0 to 1.0 range, 0.0 is centered)
; void SetAudioStreamPan(AudioStream stream, float pan)
calminstruction SetAudioStreamPan stream*, pan*
	local line
	arrange line, =RLAPI =SetAudioStreamPan, stream,pan
	assemble line
end calminstruction

; Default size for new audio streams
; void SetAudioStreamBufferSizeDefault(int size)
calminstruction SetAudioStreamBufferSizeDefault size*
	local line
	arrange line, =RLAPI =SetAudioStreamBufferSizeDefault, size
	assemble line
end calminstruction

; Audio thread callback to request new data
; void SetAudioStreamCallback(AudioStream stream, AudioCallback callback)
calminstruction SetAudioStreamCallback stream*, callback*
	local line
	arrange line, =RLAPI =SetAudioStreamCallback, stream,callback
	assemble line
end calminstruction

; Attach audio stream processor to stream, receives frames x 2 samples as 'float' (stereo)
; void AttachAudioStreamProcessor(AudioStream stream, AudioCallback processor)
calminstruction AttachAudioStreamProcessor stream*, processor*
	local line
	arrange line, =RLAPI =AttachAudioStreamProcessor, stream,processor
	assemble line
end calminstruction

; Detach audio stream processor from stream
; void DetachAudioStreamProcessor(AudioStream stream, AudioCallback processor)
calminstruction DetachAudioStreamProcessor stream*, processor*
	local line
	arrange line, =RLAPI =DetachAudioStreamProcessor, stream,processor
	assemble line
end calminstruction

; Attach audio stream processor to the entire audio pipeline, receives frames x 2 samples as 'float' (stereo)
; void AttachAudioMixedProcessor(AudioCallback processor)
calminstruction AttachAudioMixedProcessor processor*
	local line
	arrange line, =RLAPI =AttachAudioMixedProcessor, processor
	assemble line
end calminstruction

; Detach audio stream processor from the entire audio pipeline
; void DetachAudioMixedProcessor(AudioCallback processor)
calminstruction DetachAudioMixedProcessor processor*
	local line
	arrange line, =RLAPI =DetachAudioMixedProcessor, processor
	assemble line
end calminstruction
