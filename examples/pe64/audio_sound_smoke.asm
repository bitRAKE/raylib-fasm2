
; raylib [audio] smoke — embedded .wav
;
; The .wav payload is incbin'd straight into the .data section via
; fasmg's `file` directive — no external resources, no file I/O at
; runtime. raylib's LoadWaveFromMemory + LoadSoundFromWave path
; turns it into a Sound at startup; SPACE plays it on demand.

format PE64 GUI 5.0
entry start

include 'raylib.inc'

section '.text' code readable executable

  start:
	sub	rsp, 8

	InitWindow		800, 450, _title
	InitAudioDevice
	SetTargetFPS		60

	; wave = LoadWaveFromMemory(".wav", coin_data, coin_size)
	LoadWaveFromMemory	addr wave, _wav_ext, coin_data, coin_size
	; sound = LoadSoundFromWave(wave)
	LoadSoundFromWave	addr fx, addr wave
	UnloadWave		addr wave

  game_loop:
	WindowShouldClose
	test	eax, eax
	jnz	shutdown

	IsKeyPressed		KEY_SPACE
	test	eax, eax
	jz	.no_play
	PlaySound		addr fx
  .no_play:

	BeginDrawing
	ClearBackground		RAYWHITE
	DrawText		_msg1, 180, 180, 20, LIGHTGRAY
	DrawText		_msg2, 180, 220, 20, GRAY
	EndDrawing
	jmp	game_loop

  shutdown:
	UnloadSound		addr fx
	CloseAudioDevice
	CloseWindow
	invoke	ExitProcess, 0

section '.data' data readable writeable

  _title   db 'audio sound smoke (embedded wav)', 0
  _msg1    db 'Press SPACE to play the embedded coin sound', 0
  _msg2    db 'fasmg + raylib audio path', 0
  _wav_ext db '.wav', 0

  ; Embed the .wav directly. `file` is fasmg's incbin equivalent.
  coin_data: file 'coin.wav'
  coin_size = $ - coin_data

  wave Wave
  fx   Sound

section '.idata' import data readable writeable
  library raylib,'raylib.dll', kernel32,'KERNEL32.DLL'
  include 'raylib_imports.inc'
  import kernel32, ExitProcess,'ExitProcess'
