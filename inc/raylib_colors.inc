; raylib predefined colors — generated

; Each color is a packed RGBA dword. Win64 ABI puts struct-by-value
; <= 8 bytes in a register, so passing one of these as a Color arg
; produces the right machine code without any wrapping.

; If you need a Color *instance* (e.g. to take its address), declare
; one yourself in your data section:
;     myColor Color r:200, g:200, b:200, a:255

define LIGHTGRAY 0xFFC8C8C8  ; Light Gray (200,200,200,255)
define GRAY 0xFF828282  ; Gray (130,130,130,255)
define DARKGRAY 0xFF505050  ; Dark Gray (80,80,80,255)
define YELLOW 0xFF00F9FD  ; Yellow (253,249,0,255)
define GOLD 0xFF00CBFF  ; Gold (255,203,0,255)
define ORANGE 0xFF00A1FF  ; Orange (255,161,0,255)
define PINK 0xFFC26DFF  ; Pink (255,109,194,255)
define RED 0xFF3729E6  ; Red (230,41,55,255)
define MAROON 0xFF3721BE  ; Maroon (190,33,55,255)
define GREEN 0xFF30E400  ; Green (0,228,48,255)
define LIME 0xFF2F9E00  ; Lime (0,158,47,255)
define DARKGREEN 0xFF2C7500  ; Dark Green (0,117,44,255)
define SKYBLUE 0xFFFFBF66  ; Sky Blue (102,191,255,255)
define BLUE 0xFFF17900  ; Blue (0,121,241,255)
define DARKBLUE 0xFFAC5200  ; Dark Blue (0,82,172,255)
define PURPLE 0xFFFF7AC8  ; Purple (200,122,255,255)
define VIOLET 0xFFBE3C87  ; Violet (135,60,190,255)
define DARKPURPLE 0xFF7E1F70  ; Dark Purple (112,31,126,255)
define BEIGE 0xFF83B0D3  ; Beige (211,176,131,255)
define BROWN 0xFF4F6A7F  ; Brown (127,106,79,255)
define DARKBROWN 0xFF2F3F4C  ; Dark Brown (76,63,47,255)
define WHITE 0xFFFFFFFF  ; White (255,255,255,255)
define BLACK 0xFF000000  ; Black (0,0,0,255)
define BLANK 0x00000000  ; Blank (Transparent) (0,0,0,0)
define MAGENTA 0xFFFF00FF  ; Magenta (255,0,255,255)
define RAYWHITE 0xFFF5F5F5  ; My own White (raylib logo) (245,245,245,255)