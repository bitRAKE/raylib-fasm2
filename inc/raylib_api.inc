; raylib calminstruction wrappers — generated
;
; Each wrapper:
;   1. Validates parameter count via the `*` (required) marker.
;   2. Applies `transform` to typed parameters so callers can use
;      short enum names (KEY_ESCAPE, FLAG_VSYNC_HINT, …) and so
;      misspellings or wrong-enum mixing fail at assemble time.
;   3. Assembles `invoke _Func, args…`, where `_Func` is the import-
;      table label produced from raylib_imports.inc.

; Initialize window and OpenGL context
calminstruction InitWindow width*, height*, title*
	local fname, args
	arrange fname, =InitWindow
	arrange args, width, height, title
	call RLAPI, fname, args
end calminstruction

; Close window and unload OpenGL context
calminstruction CloseWindow
	local fname, args
	arrange fname, =CloseWindow
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
calminstruction WindowShouldClose
	local fname, args
	arrange fname, =WindowShouldClose
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if window has been initialized successfully
calminstruction IsWindowReady
	local fname, args
	arrange fname, =IsWindowReady
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if window is currently fullscreen
calminstruction IsWindowFullscreen
	local fname, args
	arrange fname, =IsWindowFullscreen
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if window is currently hidden
calminstruction IsWindowHidden
	local fname, args
	arrange fname, =IsWindowHidden
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if window is currently minimized
calminstruction IsWindowMinimized
	local fname, args
	arrange fname, =IsWindowMinimized
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if window is currently maximized
calminstruction IsWindowMaximized
	local fname, args
	arrange fname, =IsWindowMaximized
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if window is currently focused
calminstruction IsWindowFocused
	local fname, args
	arrange fname, =IsWindowFocused
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if window has been resized last frame
calminstruction IsWindowResized
	local fname, args
	arrange fname, =IsWindowResized
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if one specific window flag is enabled
calminstruction IsWindowState flag*
    reduce:
	transform flag
	jyes reduce
	transform flag, RayLib.ConfigFlags
	local fname, args
	arrange fname, =IsWindowState
	arrange args, flag
	call RLAPI, fname, args
end calminstruction

; Set window configuration state using flags
calminstruction SetWindowState flags*
    reduce:
	transform flags
	jyes reduce
	transform flags, RayLib.ConfigFlags
	local fname, args
	arrange fname, =SetWindowState
	arrange args, flags
	call RLAPI, fname, args
end calminstruction

; Clear window configuration state flags
calminstruction ClearWindowState flags*
    reduce:
	transform flags
	jyes reduce
	transform flags, RayLib.ConfigFlags
	local fname, args
	arrange fname, =ClearWindowState
	arrange args, flags
	call RLAPI, fname, args
end calminstruction

; Toggle window state: fullscreen/windowed, resizes monitor to match window resolution
calminstruction ToggleFullscreen
	local fname, args
	arrange fname, =ToggleFullscreen
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Toggle window state: borderless windowed, resizes window to match monitor resolution
calminstruction ToggleBorderlessWindowed
	local fname, args
	arrange fname, =ToggleBorderlessWindowed
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Set window state: maximized, if resizable
calminstruction MaximizeWindow
	local fname, args
	arrange fname, =MaximizeWindow
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Set window state: minimized, if resizable
calminstruction MinimizeWindow
	local fname, args
	arrange fname, =MinimizeWindow
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Restore window from being minimized/maximized
calminstruction RestoreWindow
	local fname, args
	arrange fname, =RestoreWindow
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Set icon for window (single image, RGBA 32bit)
calminstruction SetWindowIcon image*
	local fname, args
	arrange fname, =SetWindowIcon
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Set icon for window (multiple images, RGBA 32bit)
calminstruction SetWindowIcons images*, count*
	local fname, args
	arrange fname, =SetWindowIcons
	arrange args, images, count
	call RLAPI, fname, args
end calminstruction

; Set title for window
calminstruction SetWindowTitle title*
	local fname, args
	arrange fname, =SetWindowTitle
	arrange args, title
	call RLAPI, fname, args
end calminstruction

; Set window position on screen
calminstruction SetWindowPosition x*, y*
	local fname, args
	arrange fname, =SetWindowPosition
	arrange args, x, y
	call RLAPI, fname, args
end calminstruction

; Set monitor for the current window
calminstruction SetWindowMonitor monitor*
	local fname, args
	arrange fname, =SetWindowMonitor
	arrange args, monitor
	call RLAPI, fname, args
end calminstruction

; Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
calminstruction SetWindowMinSize width*, height*
	local fname, args
	arrange fname, =SetWindowMinSize
	arrange args, width, height
	call RLAPI, fname, args
end calminstruction

; Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
calminstruction SetWindowMaxSize width*, height*
	local fname, args
	arrange fname, =SetWindowMaxSize
	arrange args, width, height
	call RLAPI, fname, args
end calminstruction

; Set window dimensions
calminstruction SetWindowSize width*, height*
	local fname, args
	arrange fname, =SetWindowSize
	arrange args, width, height
	call RLAPI, fname, args
end calminstruction

; Set window opacity [0.0f..1.0f]
calminstruction SetWindowOpacity opacity*
	local fname, args
	arrange fname, =SetWindowOpacity
	arrange args, opacity
	call RLAPI, fname, args
end calminstruction

; Set window focused
calminstruction SetWindowFocused
	local fname, args
	arrange fname, =SetWindowFocused
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get native window handle
calminstruction GetWindowHandle
	local fname, args
	arrange fname, =GetWindowHandle
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get current screen width
calminstruction GetScreenWidth
	local fname, args
	arrange fname, =GetScreenWidth
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get current screen height
calminstruction GetScreenHeight
	local fname, args
	arrange fname, =GetScreenHeight
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get current render width (it considers HiDPI)
calminstruction GetRenderWidth
	local fname, args
	arrange fname, =GetRenderWidth
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get current render height (it considers HiDPI)
calminstruction GetRenderHeight
	local fname, args
	arrange fname, =GetRenderHeight
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get number of connected monitors
calminstruction GetMonitorCount
	local fname, args
	arrange fname, =GetMonitorCount
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get current monitor where window is placed
calminstruction GetCurrentMonitor
	local fname, args
	arrange fname, =GetCurrentMonitor
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get specified monitor position
calminstruction GetMonitorPosition monitor*
	local fname, args
	arrange fname, =GetMonitorPosition
	arrange args, monitor
	call RLAPI, fname, args
end calminstruction

; Get specified monitor width (current video mode used by monitor)
calminstruction GetMonitorWidth monitor*
	local fname, args
	arrange fname, =GetMonitorWidth
	arrange args, monitor
	call RLAPI, fname, args
end calminstruction

; Get specified monitor height (current video mode used by monitor)
calminstruction GetMonitorHeight monitor*
	local fname, args
	arrange fname, =GetMonitorHeight
	arrange args, monitor
	call RLAPI, fname, args
end calminstruction

; Get specified monitor physical width in millimetres
calminstruction GetMonitorPhysicalWidth monitor*
	local fname, args
	arrange fname, =GetMonitorPhysicalWidth
	arrange args, monitor
	call RLAPI, fname, args
end calminstruction

; Get specified monitor physical height in millimetres
calminstruction GetMonitorPhysicalHeight monitor*
	local fname, args
	arrange fname, =GetMonitorPhysicalHeight
	arrange args, monitor
	call RLAPI, fname, args
end calminstruction

; Get specified monitor refresh rate
calminstruction GetMonitorRefreshRate monitor*
	local fname, args
	arrange fname, =GetMonitorRefreshRate
	arrange args, monitor
	call RLAPI, fname, args
end calminstruction

; Get window position XY on monitor
calminstruction GetWindowPosition
	local fname, args
	arrange fname, =GetWindowPosition
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get window scale DPI factor
calminstruction GetWindowScaleDPI
	local fname, args
	arrange fname, =GetWindowScaleDPI
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get the human-readable, UTF-8 encoded name of the specified monitor
calminstruction GetMonitorName monitor*
	local fname, args
	arrange fname, =GetMonitorName
	arrange args, monitor
	call RLAPI, fname, args
end calminstruction

; Set clipboard text content
calminstruction SetClipboardText text*
	local fname, args
	arrange fname, =SetClipboardText
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Get clipboard text content
calminstruction GetClipboardText
	local fname, args
	arrange fname, =GetClipboardText
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get clipboard image content
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetClipboardImage dest*
	local fname, args
	arrange fname, =GetClipboardImage
	arrange args, dest
	call RLAPI, fname, args
end calminstruction

; Enable waiting for events on EndDrawing(), no automatic event polling
calminstruction EnableEventWaiting
	local fname, args
	arrange fname, =EnableEventWaiting
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Disable waiting for events on EndDrawing(), automatic events polling
calminstruction DisableEventWaiting
	local fname, args
	arrange fname, =DisableEventWaiting
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Shows cursor
calminstruction ShowCursor
	local fname, args
	arrange fname, =ShowCursor
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Hides cursor
calminstruction HideCursor
	local fname, args
	arrange fname, =HideCursor
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if cursor is not visible
calminstruction IsCursorHidden
	local fname, args
	arrange fname, =IsCursorHidden
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Enables cursor (unlock cursor)
calminstruction EnableCursor
	local fname, args
	arrange fname, =EnableCursor
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Disables cursor (lock cursor)
calminstruction DisableCursor
	local fname, args
	arrange fname, =DisableCursor
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if cursor is on the screen
calminstruction IsCursorOnScreen
	local fname, args
	arrange fname, =IsCursorOnScreen
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Set background color (framebuffer clear color)
calminstruction ClearBackground color*
	local fname, args
	arrange fname, =ClearBackground
	arrange args, color
	call RLAPI, fname, args
end calminstruction

; Setup canvas (framebuffer) to start drawing
calminstruction BeginDrawing
	local fname, args
	arrange fname, =BeginDrawing
	arrange args,
	call RLAPI, fname, args
end calminstruction

; End canvas drawing and swap buffers (double buffering)
calminstruction EndDrawing
	local fname, args
	arrange fname, =EndDrawing
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Begin 2D mode with custom camera (2D)
calminstruction BeginMode2D camera*
	local fname, args
	arrange fname, =BeginMode2D
	arrange args, camera
	call RLAPI, fname, args
end calminstruction

; Ends 2D mode with custom camera
calminstruction EndMode2D
	local fname, args
	arrange fname, =EndMode2D
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Begin 3D mode with custom camera (3D)
calminstruction BeginMode3D camera*
	local fname, args
	arrange fname, =BeginMode3D
	arrange args, camera
	call RLAPI, fname, args
end calminstruction

; Ends 3D mode and returns to default 2D orthographic mode
calminstruction EndMode3D
	local fname, args
	arrange fname, =EndMode3D
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Begin drawing to render texture
calminstruction BeginTextureMode target*
	local fname, args
	arrange fname, =BeginTextureMode
	arrange args, target
	call RLAPI, fname, args
end calminstruction

; Ends drawing to render texture
calminstruction EndTextureMode
	local fname, args
	arrange fname, =EndTextureMode
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Begin custom shader drawing
calminstruction BeginShaderMode shader*
	local fname, args
	arrange fname, =BeginShaderMode
	arrange args, shader
	call RLAPI, fname, args
end calminstruction

; End custom shader drawing (use default shader)
calminstruction EndShaderMode
	local fname, args
	arrange fname, =EndShaderMode
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Begin blending mode (alpha, additive, multiplied, subtract, custom)
calminstruction BeginBlendMode mode*
    reduce:
	transform mode
	jyes reduce
	transform mode, RayLib.BlendMode
	local fname, args
	arrange fname, =BeginBlendMode
	arrange args, mode
	call RLAPI, fname, args
end calminstruction

; End blending mode (reset to default: alpha blending)
calminstruction EndBlendMode
	local fname, args
	arrange fname, =EndBlendMode
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Begin scissor mode (define screen area for following drawing)
calminstruction BeginScissorMode x*, y*, width*, height*
	local fname, args
	arrange fname, =BeginScissorMode
	arrange args, x, y, width, height
	call RLAPI, fname, args
end calminstruction

; End scissor mode
calminstruction EndScissorMode
	local fname, args
	arrange fname, =EndScissorMode
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Begin stereo rendering (requires VR simulator)
calminstruction BeginVrStereoMode config*
	local fname, args
	arrange fname, =BeginVrStereoMode
	arrange args, config
	call RLAPI, fname, args
end calminstruction

; End stereo rendering (requires VR simulator)
calminstruction EndVrStereoMode
	local fname, args
	arrange fname, =EndVrStereoMode
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Load VR stereo config for VR simulator device parameters
; (returns VrStereoConfig via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadVrStereoConfig dest*, device*
	local fname, args
	arrange fname, =LoadVrStereoConfig
	arrange args, dest, device
	call RLAPI, fname, args
end calminstruction

; Unload VR stereo config
calminstruction UnloadVrStereoConfig config*
	local fname, args
	arrange fname, =UnloadVrStereoConfig
	arrange args, config
	call RLAPI, fname, args
end calminstruction

; Load shader from files and bind default locations
; (returns Shader via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadShader dest*, vsFileName*, fsFileName*
	local fname, args
	arrange fname, =LoadShader
	arrange args, dest, vsFileName, fsFileName
	call RLAPI, fname, args
end calminstruction

; Load shader from code strings and bind default locations
; (returns Shader via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadShaderFromMemory dest*, vsCode*, fsCode*
	local fname, args
	arrange fname, =LoadShaderFromMemory
	arrange args, dest, vsCode, fsCode
	call RLAPI, fname, args
end calminstruction

; Check if a shader is valid (loaded on GPU)
calminstruction IsShaderValid shader*
	local fname, args
	arrange fname, =IsShaderValid
	arrange args, shader
	call RLAPI, fname, args
end calminstruction

; Get shader uniform location
calminstruction GetShaderLocation shader*, uniformName*
	local fname, args
	arrange fname, =GetShaderLocation
	arrange args, shader, uniformName
	call RLAPI, fname, args
end calminstruction

; Get shader attribute location
calminstruction GetShaderLocationAttrib shader*, attribName*
	local fname, args
	arrange fname, =GetShaderLocationAttrib
	arrange args, shader, attribName
	call RLAPI, fname, args
end calminstruction

; Set shader uniform value
calminstruction SetShaderValue shader*, locIndex*, value*, uniformType*
    reduce:
	transform uniformType
	jyes reduce
	transform uniformType, RayLib.ShaderUniformDataType
	local fname, args
	arrange fname, =SetShaderValue
	arrange args, shader, locIndex, value, uniformType
	call RLAPI, fname, args
end calminstruction

; Set shader uniform value vector
calminstruction SetShaderValueV shader*, locIndex*, value*, uniformType*, count*
    reduce:
	transform uniformType
	jyes reduce
	transform uniformType, RayLib.ShaderUniformDataType
	local fname, args
	arrange fname, =SetShaderValueV
	arrange args, shader, locIndex, value, uniformType, count
	call RLAPI, fname, args
end calminstruction

; Set shader uniform value (matrix 4x4)
calminstruction SetShaderValueMatrix shader*, locIndex*, mat*
	local fname, args
	arrange fname, =SetShaderValueMatrix
	arrange args, shader, locIndex, mat
	call RLAPI, fname, args
end calminstruction

; Set shader uniform value and bind the texture (sampler2d)
calminstruction SetShaderValueTexture shader*, locIndex*, texture*
	local fname, args
	arrange fname, =SetShaderValueTexture
	arrange args, shader, locIndex, texture
	call RLAPI, fname, args
end calminstruction

; Unload shader from GPU memory (VRAM)
calminstruction UnloadShader shader*
	local fname, args
	arrange fname, =UnloadShader
	arrange args, shader
	call RLAPI, fname, args
end calminstruction

; Get a ray trace from screen position (i.e mouse)
; (returns Ray via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetScreenToWorldRay dest*, position*, camera*
	local fname, args
	arrange fname, =GetScreenToWorldRay
	arrange args, dest, position, camera
	call RLAPI, fname, args
end calminstruction

; Get a ray trace from screen position (i.e mouse) in a viewport
; (returns Ray via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetScreenToWorldRayEx dest*, position*, camera*, width*, height*
	local fname, args
	arrange fname, =GetScreenToWorldRayEx
	arrange args, dest, position, camera, width, height
	call RLAPI, fname, args
end calminstruction

; Get the screen space position for a 3d world space position
calminstruction GetWorldToScreen position*, camera*
	local fname, args
	arrange fname, =GetWorldToScreen
	arrange args, position, camera
	call RLAPI, fname, args
end calminstruction

; Get size position for a 3d world space position
calminstruction GetWorldToScreenEx position*, camera*, width*, height*
	local fname, args
	arrange fname, =GetWorldToScreenEx
	arrange args, position, camera, width, height
	call RLAPI, fname, args
end calminstruction

; Get the screen space position for a 2d camera world space position
calminstruction GetWorldToScreen2D position*, camera*
	local fname, args
	arrange fname, =GetWorldToScreen2D
	arrange args, position, camera
	call RLAPI, fname, args
end calminstruction

; Get the world space position for a 2d camera screen space position
calminstruction GetScreenToWorld2D position*, camera*
	local fname, args
	arrange fname, =GetScreenToWorld2D
	arrange args, position, camera
	call RLAPI, fname, args
end calminstruction

; Get camera transform matrix (view matrix)
; (returns Matrix via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetCameraMatrix dest*, camera*
	local fname, args
	arrange fname, =GetCameraMatrix
	arrange args, dest, camera
	call RLAPI, fname, args
end calminstruction

; Get camera 2d transform matrix
; (returns Matrix via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetCameraMatrix2D dest*, camera*
	local fname, args
	arrange fname, =GetCameraMatrix2D
	arrange args, dest, camera
	call RLAPI, fname, args
end calminstruction

; Set target FPS (maximum)
calminstruction SetTargetFPS fps*
	local fname, args
	arrange fname, =SetTargetFPS
	arrange args, fps
	call RLAPI, fname, args
end calminstruction

; Get time in seconds for last frame drawn (delta time)
calminstruction GetFrameTime
	local fname, args
	arrange fname, =GetFrameTime
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get elapsed time in seconds since InitWindow()
calminstruction GetTime
	local fname, args
	arrange fname, =GetTime
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get current FPS
calminstruction GetFPS
	local fname, args
	arrange fname, =GetFPS
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Swap back buffer with front buffer (screen drawing)
calminstruction SwapScreenBuffer
	local fname, args
	arrange fname, =SwapScreenBuffer
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Register all input events
calminstruction PollInputEvents
	local fname, args
	arrange fname, =PollInputEvents
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Wait for some time (halt program execution)
calminstruction WaitTime seconds*
	local fname, args
	arrange fname, =WaitTime
	arrange args, seconds
	call RLAPI, fname, args
end calminstruction

; Set the seed for the random number generator
calminstruction SetRandomSeed seed*
	local fname, args
	arrange fname, =SetRandomSeed
	arrange args, seed
	call RLAPI, fname, args
end calminstruction

; Get a random value between min and max (both included)
calminstruction GetRandomValue min*, max*
	local fname, args
	arrange fname, =GetRandomValue
	arrange args, min, max
	call RLAPI, fname, args
end calminstruction

; Load random values sequence, no values repeated
calminstruction LoadRandomSequence count*, min*, max*
	local fname, args
	arrange fname, =LoadRandomSequence
	arrange args, count, min, max
	call RLAPI, fname, args
end calminstruction

; Unload random values sequence
calminstruction UnloadRandomSequence sequence*
	local fname, args
	arrange fname, =UnloadRandomSequence
	arrange args, sequence
	call RLAPI, fname, args
end calminstruction

; Takes a screenshot of current screen (filename extension defines format)
calminstruction TakeScreenshot fileName*
	local fname, args
	arrange fname, =TakeScreenshot
	arrange args, fileName
	call RLAPI, fname, args
end calminstruction

; Setup init configuration flags (view FLAGS)
calminstruction SetConfigFlags flags*
    reduce:
	transform flags
	jyes reduce
	transform flags, RayLib.ConfigFlags
	local fname, args
	arrange fname, =SetConfigFlags
	arrange args, flags
	call RLAPI, fname, args
end calminstruction

; Open URL with default system browser (if available)
calminstruction OpenURL url*
	local fname, args
	arrange fname, =OpenURL
	arrange args, url
	call RLAPI, fname, args
end calminstruction

; Set the current threshold (minimum) log level
calminstruction SetTraceLogLevel logLevel*
    reduce:
	transform logLevel
	jyes reduce
	transform logLevel, RayLib.TraceLogLevel
	local fname, args
	arrange fname, =SetTraceLogLevel
	arrange args, logLevel
	call RLAPI, fname, args
end calminstruction

; Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
calminstruction TraceLog logLevel*, text*, rest&
    reduce:
	transform logLevel
	jyes reduce
	transform logLevel, RayLib.TraceLogLevel
	local fname, args
	arrange fname, =TraceLog
	arrange args, logLevel, text, rest
	call RLAPI, fname, args
end calminstruction

; Set custom trace log
calminstruction SetTraceLogCallback callback*
	local fname, args
	arrange fname, =SetTraceLogCallback
	arrange args, callback
	call RLAPI, fname, args
end calminstruction

; Internal memory allocator
calminstruction MemAlloc size*
	local fname, args
	arrange fname, =MemAlloc
	arrange args, size
	call RLAPI, fname, args
end calminstruction

; Internal memory reallocator
calminstruction MemRealloc ptr*, size*
	local fname, args
	arrange fname, =MemRealloc
	arrange args, ptr, size
	call RLAPI, fname, args
end calminstruction

; Internal memory free
calminstruction MemFree ptr*
	local fname, args
	arrange fname, =MemFree
	arrange args, ptr
	call RLAPI, fname, args
end calminstruction

; Load file data as byte array (read)
calminstruction LoadFileData fileName*, dataSize*
	local fname, args
	arrange fname, =LoadFileData
	arrange args, fileName, dataSize
	call RLAPI, fname, args
end calminstruction

; Unload file data allocated by LoadFileData()
calminstruction UnloadFileData data*
	local fname, args
	arrange fname, =UnloadFileData
	arrange args, data
	call RLAPI, fname, args
end calminstruction

; Save data to file from byte array (write), returns true on success
calminstruction SaveFileData fileName*, data*, dataSize*
	local fname, args
	arrange fname, =SaveFileData
	arrange args, fileName, data, dataSize
	call RLAPI, fname, args
end calminstruction

; Export data to code (.h), returns true on success
calminstruction ExportDataAsCode data*, dataSize*, fileName*
	local fname, args
	arrange fname, =ExportDataAsCode
	arrange args, data, dataSize, fileName
	call RLAPI, fname, args
end calminstruction

; Load text data from file (read), returns a '\0' terminated string
calminstruction LoadFileText fileName*
	local fname, args
	arrange fname, =LoadFileText
	arrange args, fileName
	call RLAPI, fname, args
end calminstruction

; Unload file text data allocated by LoadFileText()
calminstruction UnloadFileText text*
	local fname, args
	arrange fname, =UnloadFileText
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Save text data to file (write), string must be '\0' terminated, returns true on success
calminstruction SaveFileText fileName*, text*
	local fname, args
	arrange fname, =SaveFileText
	arrange args, fileName, text
	call RLAPI, fname, args
end calminstruction

; Set custom file binary data loader
calminstruction SetLoadFileDataCallback callback*
	local fname, args
	arrange fname, =SetLoadFileDataCallback
	arrange args, callback
	call RLAPI, fname, args
end calminstruction

; Set custom file binary data saver
calminstruction SetSaveFileDataCallback callback*
	local fname, args
	arrange fname, =SetSaveFileDataCallback
	arrange args, callback
	call RLAPI, fname, args
end calminstruction

; Set custom file text data loader
calminstruction SetLoadFileTextCallback callback*
	local fname, args
	arrange fname, =SetLoadFileTextCallback
	arrange args, callback
	call RLAPI, fname, args
end calminstruction

; Set custom file text data saver
calminstruction SetSaveFileTextCallback callback*
	local fname, args
	arrange fname, =SetSaveFileTextCallback
	arrange args, callback
	call RLAPI, fname, args
end calminstruction

; Rename file (if exists)
calminstruction FileRename fileName*, fileRename*
	local fname, args
	arrange fname, =FileRename
	arrange args, fileName, fileRename
	call RLAPI, fname, args
end calminstruction

; Remove file (if exists)
calminstruction FileRemove fileName*
	local fname, args
	arrange fname, =FileRemove
	arrange args, fileName
	call RLAPI, fname, args
end calminstruction

; Copy file from one path to another, dstPath created if it doesn't exist
calminstruction FileCopy srcPath*, dstPath*
	local fname, args
	arrange fname, =FileCopy
	arrange args, srcPath, dstPath
	call RLAPI, fname, args
end calminstruction

; Move file from one directory to another, dstPath created if it doesn't exist
calminstruction FileMove srcPath*, dstPath*
	local fname, args
	arrange fname, =FileMove
	arrange args, srcPath, dstPath
	call RLAPI, fname, args
end calminstruction

; Replace text in an existing file
calminstruction FileTextReplace fileName*, search*, replacement*
	local fname, args
	arrange fname, =FileTextReplace
	arrange args, fileName, search, replacement
	call RLAPI, fname, args
end calminstruction

; Find text in existing file
calminstruction FileTextFindIndex fileName*, search*
	local fname, args
	arrange fname, =FileTextFindIndex
	arrange args, fileName, search
	call RLAPI, fname, args
end calminstruction

; Check if file exists
calminstruction FileExists fileName*
	local fname, args
	arrange fname, =FileExists
	arrange args, fileName
	call RLAPI, fname, args
end calminstruction

; Check if a directory path exists
calminstruction DirectoryExists dirPath*
	local fname, args
	arrange fname, =DirectoryExists
	arrange args, dirPath
	call RLAPI, fname, args
end calminstruction

; Check file extension (recommended include point: .png, .wav)
calminstruction IsFileExtension fileName*, ext*
	local fname, args
	arrange fname, =IsFileExtension
	arrange args, fileName, ext
	call RLAPI, fname, args
end calminstruction

; Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
calminstruction GetFileLength fileName*
	local fname, args
	arrange fname, =GetFileLength
	arrange args, fileName
	call RLAPI, fname, args
end calminstruction

; Get file modification time (last write time)
calminstruction GetFileModTime fileName*
	local fname, args
	arrange fname, =GetFileModTime
	arrange args, fileName
	call RLAPI, fname, args
end calminstruction

; Get pointer to extension for a filename string (includes dot: '.png')
calminstruction GetFileExtension fileName*
	local fname, args
	arrange fname, =GetFileExtension
	arrange args, fileName
	call RLAPI, fname, args
end calminstruction

; Get pointer to filename for a path string
calminstruction GetFileName filePath*
	local fname, args
	arrange fname, =GetFileName
	arrange args, filePath
	call RLAPI, fname, args
end calminstruction

; Get filename string without extension (uses static string)
calminstruction GetFileNameWithoutExt filePath*
	local fname, args
	arrange fname, =GetFileNameWithoutExt
	arrange args, filePath
	call RLAPI, fname, args
end calminstruction

; Get full path for a given fileName with path (uses static string)
calminstruction GetDirectoryPath filePath*
	local fname, args
	arrange fname, =GetDirectoryPath
	arrange args, filePath
	call RLAPI, fname, args
end calminstruction

; Get previous directory path for a given path (uses static string)
calminstruction GetPrevDirectoryPath dirPath*
	local fname, args
	arrange fname, =GetPrevDirectoryPath
	arrange args, dirPath
	call RLAPI, fname, args
end calminstruction

; Get current working directory (uses static string)
calminstruction GetWorkingDirectory
	local fname, args
	arrange fname, =GetWorkingDirectory
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get the directory of the running application (uses static string)
calminstruction GetApplicationDirectory
	local fname, args
	arrange fname, =GetApplicationDirectory
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Create directories (including full path requested), returns 0 on success
calminstruction MakeDirectory dirPath*
	local fname, args
	arrange fname, =MakeDirectory
	arrange args, dirPath
	call RLAPI, fname, args
end calminstruction

; Change working directory, return true on success
calminstruction ChangeDirectory dirPath*
	local fname, args
	arrange fname, =ChangeDirectory
	arrange args, dirPath
	call RLAPI, fname, args
end calminstruction

; Check if a given path is a file or a directory
calminstruction IsPathFile path*
	local fname, args
	arrange fname, =IsPathFile
	arrange args, path
	call RLAPI, fname, args
end calminstruction

; Check if fileName is valid for the platform/OS
calminstruction IsFileNameValid fileName*
	local fname, args
	arrange fname, =IsFileNameValid
	arrange args, fileName
	call RLAPI, fname, args
end calminstruction

; Load directory filepaths, files and directories, no subdirs scan
; (returns FilePathList via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadDirectoryFiles dest*, dirPath*
	local fname, args
	arrange fname, =LoadDirectoryFiles
	arrange args, dest, dirPath
	call RLAPI, fname, args
end calminstruction

; Load directory filepaths with extension filtering and subdir scan; some filters available: "*.*", "FILES*", "DIRS*"
; (returns FilePathList via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadDirectoryFilesEx dest*, basePath*, filter*, scanSubdirs*
	local fname, args
	arrange fname, =LoadDirectoryFilesEx
	arrange args, dest, basePath, filter, scanSubdirs
	call RLAPI, fname, args
end calminstruction

; Unload filepaths
calminstruction UnloadDirectoryFiles files*
	local fname, args
	arrange fname, =UnloadDirectoryFiles
	arrange args, files
	call RLAPI, fname, args
end calminstruction

; Check if a file has been dropped into window
calminstruction IsFileDropped
	local fname, args
	arrange fname, =IsFileDropped
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Load dropped filepaths
; (returns FilePathList via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadDroppedFiles dest*
	local fname, args
	arrange fname, =LoadDroppedFiles
	arrange args, dest
	call RLAPI, fname, args
end calminstruction

; Unload dropped filepaths
calminstruction UnloadDroppedFiles files*
	local fname, args
	arrange fname, =UnloadDroppedFiles
	arrange args, files
	call RLAPI, fname, args
end calminstruction

; Get the file count in a directory
calminstruction GetDirectoryFileCount dirPath*
	local fname, args
	arrange fname, =GetDirectoryFileCount
	arrange args, dirPath
	call RLAPI, fname, args
end calminstruction

; Get the file count in a directory with extension filtering and recursive directory scan. Use 'DIR' in the filter string to include directories in the result
calminstruction GetDirectoryFileCountEx basePath*, filter*, scanSubdirs*
	local fname, args
	arrange fname, =GetDirectoryFileCountEx
	arrange args, basePath, filter, scanSubdirs
	call RLAPI, fname, args
end calminstruction

; Compress data (DEFLATE algorithm), memory must be MemFree()
calminstruction CompressData data*, dataSize*, compDataSize*
	local fname, args
	arrange fname, =CompressData
	arrange args, data, dataSize, compDataSize
	call RLAPI, fname, args
end calminstruction

; Decompress data (DEFLATE algorithm), memory must be MemFree()
calminstruction DecompressData compData*, compDataSize*, dataSize*
	local fname, args
	arrange fname, =DecompressData
	arrange args, compData, compDataSize, dataSize
	call RLAPI, fname, args
end calminstruction

; Encode data to Base64 string (includes NULL terminator), memory must be MemFree()
calminstruction EncodeDataBase64 data*, dataSize*, outputSize*
	local fname, args
	arrange fname, =EncodeDataBase64
	arrange args, data, dataSize, outputSize
	call RLAPI, fname, args
end calminstruction

; Decode Base64 string (expected NULL terminated), memory must be MemFree()
calminstruction DecodeDataBase64 text*, outputSize*
	local fname, args
	arrange fname, =DecodeDataBase64
	arrange args, text, outputSize
	call RLAPI, fname, args
end calminstruction

; Compute CRC32 hash code
calminstruction ComputeCRC32 data*, dataSize*
	local fname, args
	arrange fname, =ComputeCRC32
	arrange args, data, dataSize
	call RLAPI, fname, args
end calminstruction

; Compute MD5 hash code, returns static int[4] (16 bytes)
calminstruction ComputeMD5 data*, dataSize*
	local fname, args
	arrange fname, =ComputeMD5
	arrange args, data, dataSize
	call RLAPI, fname, args
end calminstruction

; Compute SHA1 hash code, returns static int[5] (20 bytes)
calminstruction ComputeSHA1 data*, dataSize*
	local fname, args
	arrange fname, =ComputeSHA1
	arrange args, data, dataSize
	call RLAPI, fname, args
end calminstruction

; Compute SHA256 hash code, returns static int[8] (32 bytes)
calminstruction ComputeSHA256 data*, dataSize*
	local fname, args
	arrange fname, =ComputeSHA256
	arrange args, data, dataSize
	call RLAPI, fname, args
end calminstruction

; Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS
; (returns AutomationEventList via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadAutomationEventList dest*, fileName*
	local fname, args
	arrange fname, =LoadAutomationEventList
	arrange args, dest, fileName
	call RLAPI, fname, args
end calminstruction

; Unload automation events list from file
calminstruction UnloadAutomationEventList list*
	local fname, args
	arrange fname, =UnloadAutomationEventList
	arrange args, list
	call RLAPI, fname, args
end calminstruction

; Export automation events list as text file
calminstruction ExportAutomationEventList list*, fileName*
	local fname, args
	arrange fname, =ExportAutomationEventList
	arrange args, list, fileName
	call RLAPI, fname, args
end calminstruction

; Set automation event list to record to
calminstruction SetAutomationEventList list*
	local fname, args
	arrange fname, =SetAutomationEventList
	arrange args, list
	call RLAPI, fname, args
end calminstruction

; Set automation event internal base frame to start recording
calminstruction SetAutomationEventBaseFrame frame*
	local fname, args
	arrange fname, =SetAutomationEventBaseFrame
	arrange args, frame
	call RLAPI, fname, args
end calminstruction

; Start recording automation events (AutomationEventList must be set)
calminstruction StartAutomationEventRecording
	local fname, args
	arrange fname, =StartAutomationEventRecording
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Stop recording automation events
calminstruction StopAutomationEventRecording
	local fname, args
	arrange fname, =StopAutomationEventRecording
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Play a recorded automation event
calminstruction PlayAutomationEvent event*
	local fname, args
	arrange fname, =PlayAutomationEvent
	arrange args, event
	call RLAPI, fname, args
end calminstruction

; Check if a key has been pressed once
calminstruction IsKeyPressed key*
    reduce:
	transform key
	jyes reduce
	transform key, RayLib.KeyboardKey
	local fname, args
	arrange fname, =IsKeyPressed
	arrange args, key
	call RLAPI, fname, args
end calminstruction

; Check if a key has been pressed again
calminstruction IsKeyPressedRepeat key*
    reduce:
	transform key
	jyes reduce
	transform key, RayLib.KeyboardKey
	local fname, args
	arrange fname, =IsKeyPressedRepeat
	arrange args, key
	call RLAPI, fname, args
end calminstruction

; Check if a key is being pressed
calminstruction IsKeyDown key*
    reduce:
	transform key
	jyes reduce
	transform key, RayLib.KeyboardKey
	local fname, args
	arrange fname, =IsKeyDown
	arrange args, key
	call RLAPI, fname, args
end calminstruction

; Check if a key has been released once
calminstruction IsKeyReleased key*
    reduce:
	transform key
	jyes reduce
	transform key, RayLib.KeyboardKey
	local fname, args
	arrange fname, =IsKeyReleased
	arrange args, key
	call RLAPI, fname, args
end calminstruction

; Check if a key is NOT being pressed
calminstruction IsKeyUp key*
    reduce:
	transform key
	jyes reduce
	transform key, RayLib.KeyboardKey
	local fname, args
	arrange fname, =IsKeyUp
	arrange args, key
	call RLAPI, fname, args
end calminstruction

; Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
calminstruction GetKeyPressed
	local fname, args
	arrange fname, =GetKeyPressed
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
calminstruction GetCharPressed
	local fname, args
	arrange fname, =GetCharPressed
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get name of a QWERTY key on the current keyboard layout (eg returns string 'q' for KEY_A on an AZERTY keyboard)
calminstruction GetKeyName key*
    reduce:
	transform key
	jyes reduce
	transform key, RayLib.KeyboardKey
	local fname, args
	arrange fname, =GetKeyName
	arrange args, key
	call RLAPI, fname, args
end calminstruction

; Set a custom key to exit program (default is ESC)
calminstruction SetExitKey key*
    reduce:
	transform key
	jyes reduce
	transform key, RayLib.KeyboardKey
	local fname, args
	arrange fname, =SetExitKey
	arrange args, key
	call RLAPI, fname, args
end calminstruction

; Check if a gamepad is available
calminstruction IsGamepadAvailable gamepad*
	local fname, args
	arrange fname, =IsGamepadAvailable
	arrange args, gamepad
	call RLAPI, fname, args
end calminstruction

; Get gamepad internal name id
calminstruction GetGamepadName gamepad*
	local fname, args
	arrange fname, =GetGamepadName
	arrange args, gamepad
	call RLAPI, fname, args
end calminstruction

; Check if a gamepad button has been pressed once
calminstruction IsGamepadButtonPressed gamepad*, button*
    reduce:
	transform button
	jyes reduce
	transform button, RayLib.GamepadButton
	local fname, args
	arrange fname, =IsGamepadButtonPressed
	arrange args, gamepad, button
	call RLAPI, fname, args
end calminstruction

; Check if a gamepad button is being pressed
calminstruction IsGamepadButtonDown gamepad*, button*
    reduce:
	transform button
	jyes reduce
	transform button, RayLib.GamepadButton
	local fname, args
	arrange fname, =IsGamepadButtonDown
	arrange args, gamepad, button
	call RLAPI, fname, args
end calminstruction

; Check if a gamepad button has been released once
calminstruction IsGamepadButtonReleased gamepad*, button*
    reduce:
	transform button
	jyes reduce
	transform button, RayLib.GamepadButton
	local fname, args
	arrange fname, =IsGamepadButtonReleased
	arrange args, gamepad, button
	call RLAPI, fname, args
end calminstruction

; Check if a gamepad button is NOT being pressed
calminstruction IsGamepadButtonUp gamepad*, button*
    reduce:
	transform button
	jyes reduce
	transform button, RayLib.GamepadButton
	local fname, args
	arrange fname, =IsGamepadButtonUp
	arrange args, gamepad, button
	call RLAPI, fname, args
end calminstruction

; Get the last gamepad button pressed
calminstruction GetGamepadButtonPressed
	local fname, args
	arrange fname, =GetGamepadButtonPressed
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get axis count for a gamepad
calminstruction GetGamepadAxisCount gamepad*
	local fname, args
	arrange fname, =GetGamepadAxisCount
	arrange args, gamepad
	call RLAPI, fname, args
end calminstruction

; Get movement value for a gamepad axis
calminstruction GetGamepadAxisMovement gamepad*, axis*
    reduce:
	transform axis
	jyes reduce
	transform axis, RayLib.GamepadAxis
	local fname, args
	arrange fname, =GetGamepadAxisMovement
	arrange args, gamepad, axis
	call RLAPI, fname, args
end calminstruction

; Set internal gamepad mappings (SDL_GameControllerDB)
calminstruction SetGamepadMappings mappings*
	local fname, args
	arrange fname, =SetGamepadMappings
	arrange args, mappings
	call RLAPI, fname, args
end calminstruction

; Set gamepad vibration for both motors (duration in seconds)
calminstruction SetGamepadVibration gamepad*, leftMotor*, rightMotor*, duration*
	local fname, args
	arrange fname, =SetGamepadVibration
	arrange args, gamepad, leftMotor, rightMotor, duration
	call RLAPI, fname, args
end calminstruction

; Check if a mouse button has been pressed once
calminstruction IsMouseButtonPressed button*
    reduce:
	transform button
	jyes reduce
	transform button, RayLib.MouseButton
	local fname, args
	arrange fname, =IsMouseButtonPressed
	arrange args, button
	call RLAPI, fname, args
end calminstruction

; Check if a mouse button is being pressed
calminstruction IsMouseButtonDown button*
    reduce:
	transform button
	jyes reduce
	transform button, RayLib.MouseButton
	local fname, args
	arrange fname, =IsMouseButtonDown
	arrange args, button
	call RLAPI, fname, args
end calminstruction

; Check if a mouse button has been released once
calminstruction IsMouseButtonReleased button*
    reduce:
	transform button
	jyes reduce
	transform button, RayLib.MouseButton
	local fname, args
	arrange fname, =IsMouseButtonReleased
	arrange args, button
	call RLAPI, fname, args
end calminstruction

; Check if a mouse button is NOT being pressed
calminstruction IsMouseButtonUp button*
    reduce:
	transform button
	jyes reduce
	transform button, RayLib.MouseButton
	local fname, args
	arrange fname, =IsMouseButtonUp
	arrange args, button
	call RLAPI, fname, args
end calminstruction

; Get mouse position X
calminstruction GetMouseX
	local fname, args
	arrange fname, =GetMouseX
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get mouse position Y
calminstruction GetMouseY
	local fname, args
	arrange fname, =GetMouseY
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get mouse position XY
calminstruction GetMousePosition
	local fname, args
	arrange fname, =GetMousePosition
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get mouse delta between frames
calminstruction GetMouseDelta
	local fname, args
	arrange fname, =GetMouseDelta
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Set mouse position XY
calminstruction SetMousePosition x*, y*
	local fname, args
	arrange fname, =SetMousePosition
	arrange args, x, y
	call RLAPI, fname, args
end calminstruction

; Set mouse offset
calminstruction SetMouseOffset offsetX*, offsetY*
	local fname, args
	arrange fname, =SetMouseOffset
	arrange args, offsetX, offsetY
	call RLAPI, fname, args
end calminstruction

; Set mouse scaling
calminstruction SetMouseScale scaleX*, scaleY*
	local fname, args
	arrange fname, =SetMouseScale
	arrange args, scaleX, scaleY
	call RLAPI, fname, args
end calminstruction

; Get mouse wheel movement for X or Y, whichever is larger
calminstruction GetMouseWheelMove
	local fname, args
	arrange fname, =GetMouseWheelMove
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get mouse wheel movement for both X and Y
calminstruction GetMouseWheelMoveV
	local fname, args
	arrange fname, =GetMouseWheelMoveV
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Set mouse cursor
calminstruction SetMouseCursor cursor*
    reduce:
	transform cursor
	jyes reduce
	transform cursor, RayLib.MouseCursor
	local fname, args
	arrange fname, =SetMouseCursor
	arrange args, cursor
	call RLAPI, fname, args
end calminstruction

; Get touch position X for touch point 0 (relative to screen size)
calminstruction GetTouchX
	local fname, args
	arrange fname, =GetTouchX
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get touch position Y for touch point 0 (relative to screen size)
calminstruction GetTouchY
	local fname, args
	arrange fname, =GetTouchY
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get touch position XY for a touch point index (relative to screen size)
calminstruction GetTouchPosition index*
	local fname, args
	arrange fname, =GetTouchPosition
	arrange args, index
	call RLAPI, fname, args
end calminstruction

; Get touch point identifier for given index
calminstruction GetTouchPointId index*
	local fname, args
	arrange fname, =GetTouchPointId
	arrange args, index
	call RLAPI, fname, args
end calminstruction

; Get number of touch points
calminstruction GetTouchPointCount
	local fname, args
	arrange fname, =GetTouchPointCount
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Enable a set of gestures using flags
calminstruction SetGesturesEnabled flags*
    reduce:
	transform flags
	jyes reduce
	transform flags, RayLib.Gesture
	local fname, args
	arrange fname, =SetGesturesEnabled
	arrange args, flags
	call RLAPI, fname, args
end calminstruction

; Check if a gesture have been detected
calminstruction IsGestureDetected gesture*
    reduce:
	transform gesture
	jyes reduce
	transform gesture, RayLib.Gesture
	local fname, args
	arrange fname, =IsGestureDetected
	arrange args, gesture
	call RLAPI, fname, args
end calminstruction

; Get latest detected gesture
calminstruction GetGestureDetected
	local fname, args
	arrange fname, =GetGestureDetected
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get gesture hold time in seconds
calminstruction GetGestureHoldDuration
	local fname, args
	arrange fname, =GetGestureHoldDuration
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get gesture drag vector
calminstruction GetGestureDragVector
	local fname, args
	arrange fname, =GetGestureDragVector
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get gesture drag angle
calminstruction GetGestureDragAngle
	local fname, args
	arrange fname, =GetGestureDragAngle
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get gesture pinch delta
calminstruction GetGesturePinchVector
	local fname, args
	arrange fname, =GetGesturePinchVector
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Get gesture pinch angle
calminstruction GetGesturePinchAngle
	local fname, args
	arrange fname, =GetGesturePinchAngle
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Update camera position for selected mode
calminstruction UpdateCamera camera*, mode*
    reduce:
	transform mode
	jyes reduce
	transform mode, RayLib.CameraMode
	local fname, args
	arrange fname, =UpdateCamera
	arrange args, camera, mode
	call RLAPI, fname, args
end calminstruction

; Update camera movement/rotation
calminstruction UpdateCameraPro camera*, movement*, rotation*, zoom*
	local fname, args
	arrange fname, =UpdateCameraPro
	arrange args, camera, movement, rotation, zoom
	call RLAPI, fname, args
end calminstruction

; Set texture and rectangle to be used on shapes drawing
calminstruction SetShapesTexture texture*, source*
	local fname, args
	arrange fname, =SetShapesTexture
	arrange args, texture, source
	call RLAPI, fname, args
end calminstruction

; Get texture that is used for shapes drawing
; (returns Texture2D via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetShapesTexture dest*
	local fname, args
	arrange fname, =GetShapesTexture
	arrange args, dest
	call RLAPI, fname, args
end calminstruction

; Get texture source rectangle that is used for shapes drawing
; (returns Rectangle via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetShapesTextureRectangle dest*
	local fname, args
	arrange fname, =GetShapesTextureRectangle
	arrange args, dest
	call RLAPI, fname, args
end calminstruction

; Draw a pixel using geometry [Can be slow, use with care]
calminstruction DrawPixel posX*, posY*, color*
	local fname, args
	arrange fname, =DrawPixel
	arrange args, posX, posY, color
	call RLAPI, fname, args
end calminstruction

; Draw a pixel using geometry (Vector version) [Can be slow, use with care]
calminstruction DrawPixelV position*, color*
	local fname, args
	arrange fname, =DrawPixelV
	arrange args, position, color
	call RLAPI, fname, args
end calminstruction

; Draw a line
calminstruction DrawLine startPosX*, startPosY*, endPosX*, endPosY*, color*
	local fname, args
	arrange fname, =DrawLine
	arrange args, startPosX, startPosY, endPosX, endPosY, color
	call RLAPI, fname, args
end calminstruction

; Draw a line (using gl lines)
calminstruction DrawLineV startPos*, endPos*, color*
	local fname, args
	arrange fname, =DrawLineV
	arrange args, startPos, endPos, color
	call RLAPI, fname, args
end calminstruction

; Draw a line (using triangles/quads)
calminstruction DrawLineEx startPos*, endPos*, thick*, color*
	local fname, args
	arrange fname, =DrawLineEx
	arrange args, startPos, endPos, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw lines sequence (using gl lines)
calminstruction DrawLineStrip points*, pointCount*, color*
	local fname, args
	arrange fname, =DrawLineStrip
	arrange args, points, pointCount, color
	call RLAPI, fname, args
end calminstruction

; Draw line segment cubic-bezier in-out interpolation
calminstruction DrawLineBezier startPos*, endPos*, thick*, color*
	local fname, args
	arrange fname, =DrawLineBezier
	arrange args, startPos, endPos, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw a dashed line
calminstruction DrawLineDashed startPos*, endPos*, dashSize*, spaceSize*, color*
	local fname, args
	arrange fname, =DrawLineDashed
	arrange args, startPos, endPos, dashSize, spaceSize, color
	call RLAPI, fname, args
end calminstruction

; Draw a color-filled circle
calminstruction DrawCircle centerX*, centerY*, radius*, color*
	local fname, args
	arrange fname, =DrawCircle
	arrange args, centerX, centerY, radius, color
	call RLAPI, fname, args
end calminstruction

; Draw a color-filled circle (Vector version)
calminstruction DrawCircleV center*, radius*, color*
	local fname, args
	arrange fname, =DrawCircleV
	arrange args, center, radius, color
	call RLAPI, fname, args
end calminstruction

; Draw a gradient-filled circle
calminstruction DrawCircleGradient center*, radius*, inner*, outer*
	local fname, args
	arrange fname, =DrawCircleGradient
	arrange args, center, radius, inner, outer
	call RLAPI, fname, args
end calminstruction

; Draw a piece of a circle
calminstruction DrawCircleSector center*, radius*, startAngle*, endAngle*, segments*, color*
	local fname, args
	arrange fname, =DrawCircleSector
	arrange args, center, radius, startAngle, endAngle, segments, color
	call RLAPI, fname, args
end calminstruction

; Draw circle sector outline
calminstruction DrawCircleSectorLines center*, radius*, startAngle*, endAngle*, segments*, color*
	local fname, args
	arrange fname, =DrawCircleSectorLines
	arrange args, center, radius, startAngle, endAngle, segments, color
	call RLAPI, fname, args
end calminstruction

; Draw circle outline
calminstruction DrawCircleLines centerX*, centerY*, radius*, color*
	local fname, args
	arrange fname, =DrawCircleLines
	arrange args, centerX, centerY, radius, color
	call RLAPI, fname, args
end calminstruction

; Draw circle outline (Vector version)
calminstruction DrawCircleLinesV center*, radius*, color*
	local fname, args
	arrange fname, =DrawCircleLinesV
	arrange args, center, radius, color
	call RLAPI, fname, args
end calminstruction

; Draw ellipse
calminstruction DrawEllipse centerX*, centerY*, radiusH*, radiusV*, color*
	local fname, args
	arrange fname, =DrawEllipse
	arrange args, centerX, centerY, radiusH, radiusV, color
	call RLAPI, fname, args
end calminstruction

; Draw ellipse (Vector version)
calminstruction DrawEllipseV center*, radiusH*, radiusV*, color*
	local fname, args
	arrange fname, =DrawEllipseV
	arrange args, center, radiusH, radiusV, color
	call RLAPI, fname, args
end calminstruction

; Draw ellipse outline
calminstruction DrawEllipseLines centerX*, centerY*, radiusH*, radiusV*, color*
	local fname, args
	arrange fname, =DrawEllipseLines
	arrange args, centerX, centerY, radiusH, radiusV, color
	call RLAPI, fname, args
end calminstruction

; Draw ellipse outline (Vector version)
calminstruction DrawEllipseLinesV center*, radiusH*, radiusV*, color*
	local fname, args
	arrange fname, =DrawEllipseLinesV
	arrange args, center, radiusH, radiusV, color
	call RLAPI, fname, args
end calminstruction

; Draw ring
calminstruction DrawRing center*, innerRadius*, outerRadius*, startAngle*, endAngle*, segments*, color*
	local fname, args
	arrange fname, =DrawRing
	arrange args, center, innerRadius, outerRadius, startAngle, endAngle, segments, color
	call RLAPI, fname, args
end calminstruction

; Draw ring outline
calminstruction DrawRingLines center*, innerRadius*, outerRadius*, startAngle*, endAngle*, segments*, color*
	local fname, args
	arrange fname, =DrawRingLines
	arrange args, center, innerRadius, outerRadius, startAngle, endAngle, segments, color
	call RLAPI, fname, args
end calminstruction

; Draw a color-filled rectangle
calminstruction DrawRectangle posX*, posY*, width*, height*, color*
	local fname, args
	arrange fname, =DrawRectangle
	arrange args, posX, posY, width, height, color
	call RLAPI, fname, args
end calminstruction

; Draw a color-filled rectangle (Vector version)
calminstruction DrawRectangleV position*, size*, color*
	local fname, args
	arrange fname, =DrawRectangleV
	arrange args, position, size, color
	call RLAPI, fname, args
end calminstruction

; Draw a color-filled rectangle
calminstruction DrawRectangleRec rec*, color*
	local fname, args
	arrange fname, =DrawRectangleRec
	arrange args, rec, color
	call RLAPI, fname, args
end calminstruction

; Draw a color-filled rectangle with pro parameters
calminstruction DrawRectanglePro rec*, origin*, rotation*, color*
	local fname, args
	arrange fname, =DrawRectanglePro
	arrange args, rec, origin, rotation, color
	call RLAPI, fname, args
end calminstruction

; Draw a vertical-gradient-filled rectangle
calminstruction DrawRectangleGradientV posX*, posY*, width*, height*, top*, bottom*
	local fname, args
	arrange fname, =DrawRectangleGradientV
	arrange args, posX, posY, width, height, top, bottom
	call RLAPI, fname, args
end calminstruction

; Draw a horizontal-gradient-filled rectangle
calminstruction DrawRectangleGradientH posX*, posY*, width*, height*, left*, right*
	local fname, args
	arrange fname, =DrawRectangleGradientH
	arrange args, posX, posY, width, height, left, right
	call RLAPI, fname, args
end calminstruction

; Draw a gradient-filled rectangle with custom vertex colors
calminstruction DrawRectangleGradientEx rec*, topLeft*, bottomLeft*, bottomRight*, topRight*
	local fname, args
	arrange fname, =DrawRectangleGradientEx
	arrange args, rec, topLeft, bottomLeft, bottomRight, topRight
	call RLAPI, fname, args
end calminstruction

; Draw rectangle outline
calminstruction DrawRectangleLines posX*, posY*, width*, height*, color*
	local fname, args
	arrange fname, =DrawRectangleLines
	arrange args, posX, posY, width, height, color
	call RLAPI, fname, args
end calminstruction

; Draw rectangle outline with extended parameters
calminstruction DrawRectangleLinesEx rec*, lineThick*, color*
	local fname, args
	arrange fname, =DrawRectangleLinesEx
	arrange args, rec, lineThick, color
	call RLAPI, fname, args
end calminstruction

; Draw rectangle with rounded edges
calminstruction DrawRectangleRounded rec*, roundness*, segments*, color*
	local fname, args
	arrange fname, =DrawRectangleRounded
	arrange args, rec, roundness, segments, color
	call RLAPI, fname, args
end calminstruction

; Draw rectangle lines with rounded edges
calminstruction DrawRectangleRoundedLines rec*, roundness*, segments*, color*
	local fname, args
	arrange fname, =DrawRectangleRoundedLines
	arrange args, rec, roundness, segments, color
	call RLAPI, fname, args
end calminstruction

; Draw rectangle with rounded edges outline
calminstruction DrawRectangleRoundedLinesEx rec*, roundness*, segments*, lineThick*, color*
	local fname, args
	arrange fname, =DrawRectangleRoundedLinesEx
	arrange args, rec, roundness, segments, lineThick, color
	call RLAPI, fname, args
end calminstruction

; Draw a color-filled triangle (vertex in counter-clockwise order!)
calminstruction DrawTriangle v1*, v2*, v3*, color*
	local fname, args
	arrange fname, =DrawTriangle
	arrange args, v1, v2, v3, color
	call RLAPI, fname, args
end calminstruction

; Draw triangle outline (vertex in counter-clockwise order!)
calminstruction DrawTriangleLines v1*, v2*, v3*, color*
	local fname, args
	arrange fname, =DrawTriangleLines
	arrange args, v1, v2, v3, color
	call RLAPI, fname, args
end calminstruction

; Draw a triangle fan defined by points (first vertex is the center)
calminstruction DrawTriangleFan points*, pointCount*, color*
	local fname, args
	arrange fname, =DrawTriangleFan
	arrange args, points, pointCount, color
	call RLAPI, fname, args
end calminstruction

; Draw a triangle strip defined by points
calminstruction DrawTriangleStrip points*, pointCount*, color*
	local fname, args
	arrange fname, =DrawTriangleStrip
	arrange args, points, pointCount, color
	call RLAPI, fname, args
end calminstruction

; Draw a regular polygon (Vector version)
calminstruction DrawPoly center*, sides*, radius*, rotation*, color*
	local fname, args
	arrange fname, =DrawPoly
	arrange args, center, sides, radius, rotation, color
	call RLAPI, fname, args
end calminstruction

; Draw a polygon outline of n sides
calminstruction DrawPolyLines center*, sides*, radius*, rotation*, color*
	local fname, args
	arrange fname, =DrawPolyLines
	arrange args, center, sides, radius, rotation, color
	call RLAPI, fname, args
end calminstruction

; Draw a polygon outline of n sides with extended parameters
calminstruction DrawPolyLinesEx center*, sides*, radius*, rotation*, lineThick*, color*
	local fname, args
	arrange fname, =DrawPolyLinesEx
	arrange args, center, sides, radius, rotation, lineThick, color
	call RLAPI, fname, args
end calminstruction

; Draw spline: Linear, minimum 2 points
calminstruction DrawSplineLinear points*, pointCount*, thick*, color*
	local fname, args
	arrange fname, =DrawSplineLinear
	arrange args, points, pointCount, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw spline: B-Spline, minimum 4 points
calminstruction DrawSplineBasis points*, pointCount*, thick*, color*
	local fname, args
	arrange fname, =DrawSplineBasis
	arrange args, points, pointCount, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw spline: Catmull-Rom, minimum 4 points
calminstruction DrawSplineCatmullRom points*, pointCount*, thick*, color*
	local fname, args
	arrange fname, =DrawSplineCatmullRom
	arrange args, points, pointCount, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
calminstruction DrawSplineBezierQuadratic points*, pointCount*, thick*, color*
	local fname, args
	arrange fname, =DrawSplineBezierQuadratic
	arrange args, points, pointCount, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
calminstruction DrawSplineBezierCubic points*, pointCount*, thick*, color*
	local fname, args
	arrange fname, =DrawSplineBezierCubic
	arrange args, points, pointCount, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw spline segment: Linear, 2 points
calminstruction DrawSplineSegmentLinear p1*, p2*, thick*, color*
	local fname, args
	arrange fname, =DrawSplineSegmentLinear
	arrange args, p1, p2, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw spline segment: B-Spline, 4 points
calminstruction DrawSplineSegmentBasis p1*, p2*, p3*, p4*, thick*, color*
	local fname, args
	arrange fname, =DrawSplineSegmentBasis
	arrange args, p1, p2, p3, p4, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw spline segment: Catmull-Rom, 4 points
calminstruction DrawSplineSegmentCatmullRom p1*, p2*, p3*, p4*, thick*, color*
	local fname, args
	arrange fname, =DrawSplineSegmentCatmullRom
	arrange args, p1, p2, p3, p4, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw spline segment: Quadratic Bezier, 2 points, 1 control point
calminstruction DrawSplineSegmentBezierQuadratic p1*, c2*, p3*, thick*, color*
	local fname, args
	arrange fname, =DrawSplineSegmentBezierQuadratic
	arrange args, p1, c2, p3, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw spline segment: Cubic Bezier, 2 points, 2 control points
calminstruction DrawSplineSegmentBezierCubic p1*, c2*, c3*, p4*, thick*, color*
	local fname, args
	arrange fname, =DrawSplineSegmentBezierCubic
	arrange args, p1, c2, c3, p4, thick, color
	call RLAPI, fname, args
end calminstruction

; Get (evaluate) spline point: Linear
calminstruction GetSplinePointLinear startPos*, endPos*, t*
	local fname, args
	arrange fname, =GetSplinePointLinear
	arrange args, startPos, endPos, t
	call RLAPI, fname, args
end calminstruction

; Get (evaluate) spline point: B-Spline
calminstruction GetSplinePointBasis p1*, p2*, p3*, p4*, t*
	local fname, args
	arrange fname, =GetSplinePointBasis
	arrange args, p1, p2, p3, p4, t
	call RLAPI, fname, args
end calminstruction

; Get (evaluate) spline point: Catmull-Rom
calminstruction GetSplinePointCatmullRom p1*, p2*, p3*, p4*, t*
	local fname, args
	arrange fname, =GetSplinePointCatmullRom
	arrange args, p1, p2, p3, p4, t
	call RLAPI, fname, args
end calminstruction

; Get (evaluate) spline point: Quadratic Bezier
calminstruction GetSplinePointBezierQuad p1*, c2*, p3*, t*
	local fname, args
	arrange fname, =GetSplinePointBezierQuad
	arrange args, p1, c2, p3, t
	call RLAPI, fname, args
end calminstruction

; Get (evaluate) spline point: Cubic Bezier
calminstruction GetSplinePointBezierCubic p1*, c2*, c3*, p4*, t*
	local fname, args
	arrange fname, =GetSplinePointBezierCubic
	arrange args, p1, c2, c3, p4, t
	call RLAPI, fname, args
end calminstruction

; Check collision between two rectangles
calminstruction CheckCollisionRecs rec1*, rec2*
	local fname, args
	arrange fname, =CheckCollisionRecs
	arrange args, rec1, rec2
	call RLAPI, fname, args
end calminstruction

; Check collision between two circles
calminstruction CheckCollisionCircles center1*, radius1*, center2*, radius2*
	local fname, args
	arrange fname, =CheckCollisionCircles
	arrange args, center1, radius1, center2, radius2
	call RLAPI, fname, args
end calminstruction

; Check collision between circle and rectangle
calminstruction CheckCollisionCircleRec center*, radius*, rec*
	local fname, args
	arrange fname, =CheckCollisionCircleRec
	arrange args, center, radius, rec
	call RLAPI, fname, args
end calminstruction

; Check if circle collides with a line created betweeen two points [p1] and [p2]
calminstruction CheckCollisionCircleLine center*, radius*, p1*, p2*
	local fname, args
	arrange fname, =CheckCollisionCircleLine
	arrange args, center, radius, p1, p2
	call RLAPI, fname, args
end calminstruction

; Check if point is inside rectangle
calminstruction CheckCollisionPointRec point*, rec*
	local fname, args
	arrange fname, =CheckCollisionPointRec
	arrange args, point, rec
	call RLAPI, fname, args
end calminstruction

; Check if point is inside circle
calminstruction CheckCollisionPointCircle point*, center*, radius*
	local fname, args
	arrange fname, =CheckCollisionPointCircle
	arrange args, point, center, radius
	call RLAPI, fname, args
end calminstruction

; Check if point is inside a triangle
calminstruction CheckCollisionPointTriangle point*, p1*, p2*, p3*
	local fname, args
	arrange fname, =CheckCollisionPointTriangle
	arrange args, point, p1, p2, p3
	call RLAPI, fname, args
end calminstruction

; Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
calminstruction CheckCollisionPointLine point*, p1*, p2*, threshold*
	local fname, args
	arrange fname, =CheckCollisionPointLine
	arrange args, point, p1, p2, threshold
	call RLAPI, fname, args
end calminstruction

; Check if point is within a polygon described by array of vertices
calminstruction CheckCollisionPointPoly point*, points*, pointCount*
	local fname, args
	arrange fname, =CheckCollisionPointPoly
	arrange args, point, points, pointCount
	call RLAPI, fname, args
end calminstruction

; Check the collision between two lines defined by two points each, returns collision point by reference
calminstruction CheckCollisionLines startPos1*, endPos1*, startPos2*, endPos2*, collisionPoint*
	local fname, args
	arrange fname, =CheckCollisionLines
	arrange args, startPos1, endPos1, startPos2, endPos2, collisionPoint
	call RLAPI, fname, args
end calminstruction

; Get collision rectangle for two rectangles collision
; (returns Rectangle via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetCollisionRec dest*, rec1*, rec2*
	local fname, args
	arrange fname, =GetCollisionRec
	arrange args, dest, rec1, rec2
	call RLAPI, fname, args
end calminstruction

; Load image from file into CPU memory (RAM)
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadImage dest*, fileName*
	local fname, args
	arrange fname, =LoadImage
	arrange args, dest, fileName
	call RLAPI, fname, args
end calminstruction

; Load image from RAW file data
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadImageRaw dest*, fileName*, width*, height*, format*, headerSize*
    reduce:
	transform format
	jyes reduce
	transform format, RayLib.PixelFormat
	local fname, args
	arrange fname, =LoadImageRaw
	arrange args, dest, fileName, width, height, format, headerSize
	call RLAPI, fname, args
end calminstruction

; Load image sequence from file (frames appended to image.data)
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadImageAnim dest*, fileName*, frames*
	local fname, args
	arrange fname, =LoadImageAnim
	arrange args, dest, fileName, frames
	call RLAPI, fname, args
end calminstruction

; Load image sequence from memory buffer
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadImageAnimFromMemory dest*, fileType*, fileData*, dataSize*, frames*
	local fname, args
	arrange fname, =LoadImageAnimFromMemory
	arrange args, dest, fileType, fileData, dataSize, frames
	call RLAPI, fname, args
end calminstruction

; Load image from memory buffer, fileType refers to extension: i.e. '.png'
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadImageFromMemory dest*, fileType*, fileData*, dataSize*
	local fname, args
	arrange fname, =LoadImageFromMemory
	arrange args, dest, fileType, fileData, dataSize
	call RLAPI, fname, args
end calminstruction

; Load image from GPU texture data
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadImageFromTexture dest*, texture*
	local fname, args
	arrange fname, =LoadImageFromTexture
	arrange args, dest, texture
	call RLAPI, fname, args
end calminstruction

; Load image from screen buffer and (screenshot)
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadImageFromScreen dest*
	local fname, args
	arrange fname, =LoadImageFromScreen
	arrange args, dest
	call RLAPI, fname, args
end calminstruction

; Check if an image is valid (data and parameters)
calminstruction IsImageValid image*
	local fname, args
	arrange fname, =IsImageValid
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Unload image from CPU memory (RAM)
calminstruction UnloadImage image*
	local fname, args
	arrange fname, =UnloadImage
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Export image data to file, returns true on success
calminstruction ExportImage image*, fileName*
	local fname, args
	arrange fname, =ExportImage
	arrange args, image, fileName
	call RLAPI, fname, args
end calminstruction

; Export image to memory buffer, memory must be MemFree()
calminstruction ExportImageToMemory image*, fileType*, fileSize*
	local fname, args
	arrange fname, =ExportImageToMemory
	arrange args, image, fileType, fileSize
	call RLAPI, fname, args
end calminstruction

; Export image as code file defining an array of bytes, returns true on success
calminstruction ExportImageAsCode image*, fileName*
	local fname, args
	arrange fname, =ExportImageAsCode
	arrange args, image, fileName
	call RLAPI, fname, args
end calminstruction

; Generate image: plain color
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenImageColor dest*, width*, height*, color*
	local fname, args
	arrange fname, =GenImageColor
	arrange args, dest, width, height, color
	call RLAPI, fname, args
end calminstruction

; Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenImageGradientLinear dest*, width*, height*, direction*, start*, end*
	local fname, args
	arrange fname, =GenImageGradientLinear
	arrange args, dest, width, height, direction, start, end
	call RLAPI, fname, args
end calminstruction

; Generate image: radial gradient
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenImageGradientRadial dest*, width*, height*, density*, inner*, outer*
	local fname, args
	arrange fname, =GenImageGradientRadial
	arrange args, dest, width, height, density, inner, outer
	call RLAPI, fname, args
end calminstruction

; Generate image: square gradient
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenImageGradientSquare dest*, width*, height*, density*, inner*, outer*
	local fname, args
	arrange fname, =GenImageGradientSquare
	arrange args, dest, width, height, density, inner, outer
	call RLAPI, fname, args
end calminstruction

; Generate image: checked
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenImageChecked dest*, width*, height*, checksX*, checksY*, col1*, col2*
	local fname, args
	arrange fname, =GenImageChecked
	arrange args, dest, width, height, checksX, checksY, col1, col2
	call RLAPI, fname, args
end calminstruction

; Generate image: white noise
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenImageWhiteNoise dest*, width*, height*, factor*
	local fname, args
	arrange fname, =GenImageWhiteNoise
	arrange args, dest, width, height, factor
	call RLAPI, fname, args
end calminstruction

; Generate image: perlin noise
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenImagePerlinNoise dest*, width*, height*, offsetX*, offsetY*, scale*
	local fname, args
	arrange fname, =GenImagePerlinNoise
	arrange args, dest, width, height, offsetX, offsetY, scale
	call RLAPI, fname, args
end calminstruction

; Generate image: cellular algorithm, bigger tileSize means bigger cells
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenImageCellular dest*, width*, height*, tileSize*
	local fname, args
	arrange fname, =GenImageCellular
	arrange args, dest, width, height, tileSize
	call RLAPI, fname, args
end calminstruction

; Generate image: grayscale image from text data
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenImageText dest*, width*, height*, text*
	local fname, args
	arrange fname, =GenImageText
	arrange args, dest, width, height, text
	call RLAPI, fname, args
end calminstruction

; Create an image duplicate (useful for transformations)
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction ImageCopy dest*, image*
	local fname, args
	arrange fname, =ImageCopy
	arrange args, dest, image
	call RLAPI, fname, args
end calminstruction

; Create an image from another image piece
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction ImageFromImage dest*, image*, rec*
	local fname, args
	arrange fname, =ImageFromImage
	arrange args, dest, image, rec
	call RLAPI, fname, args
end calminstruction

; Create an image from a selected channel of another image (GRAYSCALE)
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction ImageFromChannel dest*, image*, selectedChannel*
	local fname, args
	arrange fname, =ImageFromChannel
	arrange args, dest, image, selectedChannel
	call RLAPI, fname, args
end calminstruction

; Create an image from text (default font)
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction ImageText dest*, text*, fontSize*, color*
	local fname, args
	arrange fname, =ImageText
	arrange args, dest, text, fontSize, color
	call RLAPI, fname, args
end calminstruction

; Create an image from text (custom sprite font)
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction ImageTextEx dest*, font*, text*, fontSize*, spacing*, tint*
	local fname, args
	arrange fname, =ImageTextEx
	arrange args, dest, font, text, fontSize, spacing, tint
	call RLAPI, fname, args
end calminstruction

; Convert image data to desired format
calminstruction ImageFormat image*, newFormat*
    reduce:
	transform newFormat
	jyes reduce
	transform newFormat, RayLib.PixelFormat
	local fname, args
	arrange fname, =ImageFormat
	arrange args, image, newFormat
	call RLAPI, fname, args
end calminstruction

; Convert image to POT (power-of-two)
calminstruction ImageToPOT image*, fill*
	local fname, args
	arrange fname, =ImageToPOT
	arrange args, image, fill
	call RLAPI, fname, args
end calminstruction

; Crop an image to a defined rectangle
calminstruction ImageCrop image*, crop*
	local fname, args
	arrange fname, =ImageCrop
	arrange args, image, crop
	call RLAPI, fname, args
end calminstruction

; Crop image depending on alpha value
calminstruction ImageAlphaCrop image*, threshold*
	local fname, args
	arrange fname, =ImageAlphaCrop
	arrange args, image, threshold
	call RLAPI, fname, args
end calminstruction

; Clear alpha channel to desired color
calminstruction ImageAlphaClear image*, color*, threshold*
	local fname, args
	arrange fname, =ImageAlphaClear
	arrange args, image, color, threshold
	call RLAPI, fname, args
end calminstruction

; Apply alpha mask to image
calminstruction ImageAlphaMask image*, alphaMask*
	local fname, args
	arrange fname, =ImageAlphaMask
	arrange args, image, alphaMask
	call RLAPI, fname, args
end calminstruction

; Premultiply alpha channel
calminstruction ImageAlphaPremultiply image*
	local fname, args
	arrange fname, =ImageAlphaPremultiply
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Apply Gaussian blur using a box blur approximation
calminstruction ImageBlurGaussian image*, blurSize*
	local fname, args
	arrange fname, =ImageBlurGaussian
	arrange args, image, blurSize
	call RLAPI, fname, args
end calminstruction

; Apply custom square convolution kernel to image
calminstruction ImageKernelConvolution image*, kernel*, kernelSize*
	local fname, args
	arrange fname, =ImageKernelConvolution
	arrange args, image, kernel, kernelSize
	call RLAPI, fname, args
end calminstruction

; Resize image (Bicubic scaling algorithm)
calminstruction ImageResize image*, newWidth*, newHeight*
	local fname, args
	arrange fname, =ImageResize
	arrange args, image, newWidth, newHeight
	call RLAPI, fname, args
end calminstruction

; Resize image (Nearest-Neighbor scaling algorithm)
calminstruction ImageResizeNN image*, newWidth*, newHeight*
	local fname, args
	arrange fname, =ImageResizeNN
	arrange args, image, newWidth, newHeight
	call RLAPI, fname, args
end calminstruction

; Resize canvas and fill with color
calminstruction ImageResizeCanvas image*, newWidth*, newHeight*, offsetX*, offsetY*, fill*
	local fname, args
	arrange fname, =ImageResizeCanvas
	arrange args, image, newWidth, newHeight, offsetX, offsetY, fill
	call RLAPI, fname, args
end calminstruction

; Compute all mipmap levels for a provided image
calminstruction ImageMipmaps image*
	local fname, args
	arrange fname, =ImageMipmaps
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
calminstruction ImageDither image*, rBpp*, gBpp*, bBpp*, aBpp*
	local fname, args
	arrange fname, =ImageDither
	arrange args, image, rBpp, gBpp, bBpp, aBpp
	call RLAPI, fname, args
end calminstruction

; Flip image vertically
calminstruction ImageFlipVertical image*
	local fname, args
	arrange fname, =ImageFlipVertical
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Flip image horizontally
calminstruction ImageFlipHorizontal image*
	local fname, args
	arrange fname, =ImageFlipHorizontal
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Rotate image by input angle in degrees (-359 to 359)
calminstruction ImageRotate image*, degrees*
	local fname, args
	arrange fname, =ImageRotate
	arrange args, image, degrees
	call RLAPI, fname, args
end calminstruction

; Rotate image clockwise 90deg
calminstruction ImageRotateCW image*
	local fname, args
	arrange fname, =ImageRotateCW
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Rotate image counter-clockwise 90deg
calminstruction ImageRotateCCW image*
	local fname, args
	arrange fname, =ImageRotateCCW
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Modify image color: tint
calminstruction ImageColorTint image*, color*
	local fname, args
	arrange fname, =ImageColorTint
	arrange args, image, color
	call RLAPI, fname, args
end calminstruction

; Modify image color: invert
calminstruction ImageColorInvert image*
	local fname, args
	arrange fname, =ImageColorInvert
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Modify image color: grayscale
calminstruction ImageColorGrayscale image*
	local fname, args
	arrange fname, =ImageColorGrayscale
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Modify image color: contrast (-100 to 100)
calminstruction ImageColorContrast image*, contrast*
	local fname, args
	arrange fname, =ImageColorContrast
	arrange args, image, contrast
	call RLAPI, fname, args
end calminstruction

; Modify image color: brightness (-255 to 255)
calminstruction ImageColorBrightness image*, brightness*
	local fname, args
	arrange fname, =ImageColorBrightness
	arrange args, image, brightness
	call RLAPI, fname, args
end calminstruction

; Modify image color: replace color
calminstruction ImageColorReplace image*, color*, replace*
	local fname, args
	arrange fname, =ImageColorReplace
	arrange args, image, color, replace
	call RLAPI, fname, args
end calminstruction

; Load color data from image as a Color array (RGBA - 32bit)
calminstruction LoadImageColors image*
	local fname, args
	arrange fname, =LoadImageColors
	arrange args, image
	call RLAPI, fname, args
end calminstruction

; Load colors palette from image as a Color array (RGBA - 32bit)
calminstruction LoadImagePalette image*, maxPaletteSize*, colorCount*
	local fname, args
	arrange fname, =LoadImagePalette
	arrange args, image, maxPaletteSize, colorCount
	call RLAPI, fname, args
end calminstruction

; Unload color data loaded with LoadImageColors()
calminstruction UnloadImageColors colors*
	local fname, args
	arrange fname, =UnloadImageColors
	arrange args, colors
	call RLAPI, fname, args
end calminstruction

; Unload colors palette loaded with LoadImagePalette()
calminstruction UnloadImagePalette colors*
	local fname, args
	arrange fname, =UnloadImagePalette
	arrange args, colors
	call RLAPI, fname, args
end calminstruction

; Get image alpha border rectangle
; (returns Rectangle via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetImageAlphaBorder dest*, image*, threshold*
	local fname, args
	arrange fname, =GetImageAlphaBorder
	arrange args, dest, image, threshold
	call RLAPI, fname, args
end calminstruction

; Get image pixel color at (x, y) position
calminstruction GetImageColor image*, x*, y*
	local fname, args
	arrange fname, =GetImageColor
	arrange args, image, x, y
	call RLAPI, fname, args
end calminstruction

; Clear image background with given color
calminstruction ImageClearBackground dst*, color*
	local fname, args
	arrange fname, =ImageClearBackground
	arrange args, dst, color
	call RLAPI, fname, args
end calminstruction

; Draw pixel within an image
calminstruction ImageDrawPixel dst*, posX*, posY*, color*
	local fname, args
	arrange fname, =ImageDrawPixel
	arrange args, dst, posX, posY, color
	call RLAPI, fname, args
end calminstruction

; Draw pixel within an image (Vector version)
calminstruction ImageDrawPixelV dst*, position*, color*
	local fname, args
	arrange fname, =ImageDrawPixelV
	arrange args, dst, position, color
	call RLAPI, fname, args
end calminstruction

; Draw line within an image
calminstruction ImageDrawLine dst*, startPosX*, startPosY*, endPosX*, endPosY*, color*
	local fname, args
	arrange fname, =ImageDrawLine
	arrange args, dst, startPosX, startPosY, endPosX, endPosY, color
	call RLAPI, fname, args
end calminstruction

; Draw line within an image (Vector version)
calminstruction ImageDrawLineV dst*, start*, end*, color*
	local fname, args
	arrange fname, =ImageDrawLineV
	arrange args, dst, start, end, color
	call RLAPI, fname, args
end calminstruction

; Draw a line defining thickness within an image
calminstruction ImageDrawLineEx dst*, start*, end*, thick*, color*
	local fname, args
	arrange fname, =ImageDrawLineEx
	arrange args, dst, start, end, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw a filled circle within an image
calminstruction ImageDrawCircle dst*, centerX*, centerY*, radius*, color*
	local fname, args
	arrange fname, =ImageDrawCircle
	arrange args, dst, centerX, centerY, radius, color
	call RLAPI, fname, args
end calminstruction

; Draw a filled circle within an image (Vector version)
calminstruction ImageDrawCircleV dst*, center*, radius*, color*
	local fname, args
	arrange fname, =ImageDrawCircleV
	arrange args, dst, center, radius, color
	call RLAPI, fname, args
end calminstruction

; Draw circle outline within an image
calminstruction ImageDrawCircleLines dst*, centerX*, centerY*, radius*, color*
	local fname, args
	arrange fname, =ImageDrawCircleLines
	arrange args, dst, centerX, centerY, radius, color
	call RLAPI, fname, args
end calminstruction

; Draw circle outline within an image (Vector version)
calminstruction ImageDrawCircleLinesV dst*, center*, radius*, color*
	local fname, args
	arrange fname, =ImageDrawCircleLinesV
	arrange args, dst, center, radius, color
	call RLAPI, fname, args
end calminstruction

; Draw rectangle within an image
calminstruction ImageDrawRectangle dst*, posX*, posY*, width*, height*, color*
	local fname, args
	arrange fname, =ImageDrawRectangle
	arrange args, dst, posX, posY, width, height, color
	call RLAPI, fname, args
end calminstruction

; Draw rectangle within an image (Vector version)
calminstruction ImageDrawRectangleV dst*, position*, size*, color*
	local fname, args
	arrange fname, =ImageDrawRectangleV
	arrange args, dst, position, size, color
	call RLAPI, fname, args
end calminstruction

; Draw rectangle within an image
calminstruction ImageDrawRectangleRec dst*, rec*, color*
	local fname, args
	arrange fname, =ImageDrawRectangleRec
	arrange args, dst, rec, color
	call RLAPI, fname, args
end calminstruction

; Draw rectangle lines within an image
calminstruction ImageDrawRectangleLines dst*, rec*, thick*, color*
	local fname, args
	arrange fname, =ImageDrawRectangleLines
	arrange args, dst, rec, thick, color
	call RLAPI, fname, args
end calminstruction

; Draw triangle within an image
calminstruction ImageDrawTriangle dst*, v1*, v2*, v3*, color*
	local fname, args
	arrange fname, =ImageDrawTriangle
	arrange args, dst, v1, v2, v3, color
	call RLAPI, fname, args
end calminstruction

; Draw triangle with interpolated colors within an image
calminstruction ImageDrawTriangleEx dst*, v1*, v2*, v3*, c1*, c2*, c3*
	local fname, args
	arrange fname, =ImageDrawTriangleEx
	arrange args, dst, v1, v2, v3, c1, c2, c3
	call RLAPI, fname, args
end calminstruction

; Draw triangle outline within an image
calminstruction ImageDrawTriangleLines dst*, v1*, v2*, v3*, color*
	local fname, args
	arrange fname, =ImageDrawTriangleLines
	arrange args, dst, v1, v2, v3, color
	call RLAPI, fname, args
end calminstruction

; Draw a triangle fan defined by points within an image (first vertex is the center)
calminstruction ImageDrawTriangleFan dst*, points*, pointCount*, color*
	local fname, args
	arrange fname, =ImageDrawTriangleFan
	arrange args, dst, points, pointCount, color
	call RLAPI, fname, args
end calminstruction

; Draw a triangle strip defined by points within an image
calminstruction ImageDrawTriangleStrip dst*, points*, pointCount*, color*
	local fname, args
	arrange fname, =ImageDrawTriangleStrip
	arrange args, dst, points, pointCount, color
	call RLAPI, fname, args
end calminstruction

; Draw a source image within a destination image (tint applied to source)
calminstruction ImageDraw dst*, src*, srcRec*, dstRec*, tint*
	local fname, args
	arrange fname, =ImageDraw
	arrange args, dst, src, srcRec, dstRec, tint
	call RLAPI, fname, args
end calminstruction

; Draw text (using default font) within an image (destination)
calminstruction ImageDrawText dst*, text*, posX*, posY*, fontSize*, color*
	local fname, args
	arrange fname, =ImageDrawText
	arrange args, dst, text, posX, posY, fontSize, color
	call RLAPI, fname, args
end calminstruction

; Draw text (custom sprite font) within an image (destination)
calminstruction ImageDrawTextEx dst*, font*, text*, position*, fontSize*, spacing*, tint*
	local fname, args
	arrange fname, =ImageDrawTextEx
	arrange args, dst, font, text, position, fontSize, spacing, tint
	call RLAPI, fname, args
end calminstruction

; Load texture from file into GPU memory (VRAM)
; (returns Texture2D via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadTexture dest*, fileName*
	local fname, args
	arrange fname, =LoadTexture
	arrange args, dest, fileName
	call RLAPI, fname, args
end calminstruction

; Load texture from image data
; (returns Texture2D via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadTextureFromImage dest*, image*
	local fname, args
	arrange fname, =LoadTextureFromImage
	arrange args, dest, image
	call RLAPI, fname, args
end calminstruction

; Load cubemap from image, multiple image cubemap layouts supported
; (returns TextureCubemap via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadTextureCubemap dest*, image*, layout*
    reduce:
	transform layout
	jyes reduce
	transform layout, RayLib.CubemapLayout
	local fname, args
	arrange fname, =LoadTextureCubemap
	arrange args, dest, image, layout
	call RLAPI, fname, args
end calminstruction

; Load texture for rendering (framebuffer)
; (returns RenderTexture2D via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadRenderTexture dest*, width*, height*
	local fname, args
	arrange fname, =LoadRenderTexture
	arrange args, dest, width, height
	call RLAPI, fname, args
end calminstruction

; Check if a texture is valid (loaded in GPU)
calminstruction IsTextureValid texture*
	local fname, args
	arrange fname, =IsTextureValid
	arrange args, texture
	call RLAPI, fname, args
end calminstruction

; Unload texture from GPU memory (VRAM)
calminstruction UnloadTexture texture*
	local fname, args
	arrange fname, =UnloadTexture
	arrange args, texture
	call RLAPI, fname, args
end calminstruction

; Check if a render texture is valid (loaded in GPU)
calminstruction IsRenderTextureValid target*
	local fname, args
	arrange fname, =IsRenderTextureValid
	arrange args, target
	call RLAPI, fname, args
end calminstruction

; Unload render texture from GPU memory (VRAM)
calminstruction UnloadRenderTexture target*
	local fname, args
	arrange fname, =UnloadRenderTexture
	arrange args, target
	call RLAPI, fname, args
end calminstruction

; Update GPU texture with new data (pixels should be able to fill texture)
calminstruction UpdateTexture texture*, pixels*
	local fname, args
	arrange fname, =UpdateTexture
	arrange args, texture, pixels
	call RLAPI, fname, args
end calminstruction

; Update GPU texture rectangle with new data (pixels and rec should fit in texture)
calminstruction UpdateTextureRec texture*, rec*, pixels*
	local fname, args
	arrange fname, =UpdateTextureRec
	arrange args, texture, rec, pixels
	call RLAPI, fname, args
end calminstruction

; Generate GPU mipmaps for a texture
calminstruction GenTextureMipmaps texture*
	local fname, args
	arrange fname, =GenTextureMipmaps
	arrange args, texture
	call RLAPI, fname, args
end calminstruction

; Set texture scaling filter mode
calminstruction SetTextureFilter texture*, filter*
    reduce:
	transform filter
	jyes reduce
	transform filter, RayLib.TextureFilter
	local fname, args
	arrange fname, =SetTextureFilter
	arrange args, texture, filter
	call RLAPI, fname, args
end calminstruction

; Set texture wrapping mode
calminstruction SetTextureWrap texture*, wrap*
    reduce:
	transform wrap
	jyes reduce
	transform wrap, RayLib.TextureWrap
	local fname, args
	arrange fname, =SetTextureWrap
	arrange args, texture, wrap
	call RLAPI, fname, args
end calminstruction

; Draw a Texture2D
calminstruction DrawTexture texture*, posX*, posY*, tint*
	local fname, args
	arrange fname, =DrawTexture
	arrange args, texture, posX, posY, tint
	call RLAPI, fname, args
end calminstruction

; Draw a Texture2D with position defined as Vector2
calminstruction DrawTextureV texture*, position*, tint*
	local fname, args
	arrange fname, =DrawTextureV
	arrange args, texture, position, tint
	call RLAPI, fname, args
end calminstruction

; Draw a Texture2D with extended parameters
calminstruction DrawTextureEx texture*, position*, rotation*, scale*, tint*
	local fname, args
	arrange fname, =DrawTextureEx
	arrange args, texture, position, rotation, scale, tint
	call RLAPI, fname, args
end calminstruction

; Draw a part of a texture defined by a rectangle
calminstruction DrawTextureRec texture*, source*, position*, tint*
	local fname, args
	arrange fname, =DrawTextureRec
	arrange args, texture, source, position, tint
	call RLAPI, fname, args
end calminstruction

; Draw a part of a texture defined by a rectangle with 'pro' parameters
calminstruction DrawTexturePro texture*, source*, dest*, origin*, rotation*, tint*
	local fname, args
	arrange fname, =DrawTexturePro
	arrange args, texture, source, dest, origin, rotation, tint
	call RLAPI, fname, args
end calminstruction

; Draws a texture (or part of it) that stretches or shrinks nicely
calminstruction DrawTextureNPatch texture*, nPatchInfo*, dest*, origin*, rotation*, tint*
	local fname, args
	arrange fname, =DrawTextureNPatch
	arrange args, texture, nPatchInfo, dest, origin, rotation, tint
	call RLAPI, fname, args
end calminstruction

; Check if two colors are equal
calminstruction ColorIsEqual col1*, col2*
	local fname, args
	arrange fname, =ColorIsEqual
	arrange args, col1, col2
	call RLAPI, fname, args
end calminstruction

; Get color with alpha applied, alpha goes from 0.0f to 1.0f
calminstruction Fade color*, alpha*
	local fname, args
	arrange fname, =Fade
	arrange args, color, alpha
	call RLAPI, fname, args
end calminstruction

; Get hexadecimal value for a Color (0xRRGGBBAA)
calminstruction ColorToInt color*
	local fname, args
	arrange fname, =ColorToInt
	arrange args, color
	call RLAPI, fname, args
end calminstruction

; Get Color normalized as float [0..1]
; (returns Vector4 via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction ColorNormalize dest*, color*
	local fname, args
	arrange fname, =ColorNormalize
	arrange args, dest, color
	call RLAPI, fname, args
end calminstruction

; Get Color from normalized values [0..1]
calminstruction ColorFromNormalized normalized*
	local fname, args
	arrange fname, =ColorFromNormalized
	arrange args, normalized
	call RLAPI, fname, args
end calminstruction

; Get HSV values for a Color, hue [0..360], saturation/value [0..1]
; (returns Vector3 via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction ColorToHSV dest*, color*
	local fname, args
	arrange fname, =ColorToHSV
	arrange args, dest, color
	call RLAPI, fname, args
end calminstruction

; Get a Color from HSV values, hue [0..360], saturation/value [0..1]
calminstruction ColorFromHSV hue*, saturation*, value*
	local fname, args
	arrange fname, =ColorFromHSV
	arrange args, hue, saturation, value
	call RLAPI, fname, args
end calminstruction

; Get color multiplied with another color
calminstruction ColorTint color*, tint*
	local fname, args
	arrange fname, =ColorTint
	arrange args, color, tint
	call RLAPI, fname, args
end calminstruction

; Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
calminstruction ColorBrightness color*, factor*
	local fname, args
	arrange fname, =ColorBrightness
	arrange args, color, factor
	call RLAPI, fname, args
end calminstruction

; Get color with contrast correction, contrast values between -1.0f and 1.0f
calminstruction ColorContrast color*, contrast*
	local fname, args
	arrange fname, =ColorContrast
	arrange args, color, contrast
	call RLAPI, fname, args
end calminstruction

; Get color with alpha applied, alpha goes from 0.0f to 1.0f
calminstruction ColorAlpha color*, alpha*
	local fname, args
	arrange fname, =ColorAlpha
	arrange args, color, alpha
	call RLAPI, fname, args
end calminstruction

; Get src alpha-blended into dst color with tint
calminstruction ColorAlphaBlend dst*, src*, tint*
	local fname, args
	arrange fname, =ColorAlphaBlend
	arrange args, dst, src, tint
	call RLAPI, fname, args
end calminstruction

; Get color lerp interpolation between two colors, factor [0.0f..1.0f]
calminstruction ColorLerp color1*, color2*, factor*
	local fname, args
	arrange fname, =ColorLerp
	arrange args, color1, color2, factor
	call RLAPI, fname, args
end calminstruction

; Get Color structure from hexadecimal value
calminstruction GetColor hexValue*
	local fname, args
	arrange fname, =GetColor
	arrange args, hexValue
	call RLAPI, fname, args
end calminstruction

; Get Color from a source pixel pointer of certain format
calminstruction GetPixelColor srcPtr*, format*
    reduce:
	transform format
	jyes reduce
	transform format, RayLib.PixelFormat
	local fname, args
	arrange fname, =GetPixelColor
	arrange args, srcPtr, format
	call RLAPI, fname, args
end calminstruction

; Set color formatted into destination pixel pointer
calminstruction SetPixelColor dstPtr*, color*, format*
    reduce:
	transform format
	jyes reduce
	transform format, RayLib.PixelFormat
	local fname, args
	arrange fname, =SetPixelColor
	arrange args, dstPtr, color, format
	call RLAPI, fname, args
end calminstruction

; Get pixel data size in bytes for certain format
calminstruction GetPixelDataSize width*, height*, format*
    reduce:
	transform format
	jyes reduce
	transform format, RayLib.PixelFormat
	local fname, args
	arrange fname, =GetPixelDataSize
	arrange args, width, height, format
	call RLAPI, fname, args
end calminstruction

; Get the default Font
; (returns Font via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetFontDefault dest*
	local fname, args
	arrange fname, =GetFontDefault
	arrange args, dest
	call RLAPI, fname, args
end calminstruction

; Load font from file into GPU memory (VRAM)
; (returns Font via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadFont dest*, fileName*
	local fname, args
	arrange fname, =LoadFont
	arrange args, dest, fileName
	call RLAPI, fname, args
end calminstruction

; Load font from file with extended parameters, use NULL for codepoints and 0 for codepointCount to load the default character set, font size is provided in pixels height
; (returns Font via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadFontEx dest*, fileName*, fontSize*, codepoints*, codepointCount*
	local fname, args
	arrange fname, =LoadFontEx
	arrange args, dest, fileName, fontSize, codepoints, codepointCount
	call RLAPI, fname, args
end calminstruction

; Load font from Image (XNA style)
; (returns Font via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadFontFromImage dest*, image*, key*, firstChar*
	local fname, args
	arrange fname, =LoadFontFromImage
	arrange args, dest, image, key, firstChar
	call RLAPI, fname, args
end calminstruction

; Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
; (returns Font via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadFontFromMemory dest*, fileType*, fileData*, dataSize*, fontSize*, codepoints*, codepointCount*
	local fname, args
	arrange fname, =LoadFontFromMemory
	arrange args, dest, fileType, fileData, dataSize, fontSize, codepoints, codepointCount
	call RLAPI, fname, args
end calminstruction

; Check if a font is valid (font data loaded, WARNING: GPU texture not checked)
calminstruction IsFontValid font*
	local fname, args
	arrange fname, =IsFontValid
	arrange args, font
	call RLAPI, fname, args
end calminstruction

; Load font data for further use
calminstruction LoadFontData fileData*, dataSize*, fontSize*, codepoints*, codepointCount*, type*, glyphCount*
    reduce:
	transform type
	jyes reduce
	transform type, RayLib.FontType
	local fname, args
	arrange fname, =LoadFontData
	arrange args, fileData, dataSize, fontSize, codepoints, codepointCount, type, glyphCount
	call RLAPI, fname, args
end calminstruction

; Generate image font atlas using chars info
; (returns Image via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenImageFontAtlas dest*, glyphs*, glyphRecs*, glyphCount*, fontSize*, padding*, packMethod*
	local fname, args
	arrange fname, =GenImageFontAtlas
	arrange args, dest, glyphs, glyphRecs, glyphCount, fontSize, padding, packMethod
	call RLAPI, fname, args
end calminstruction

; Unload font chars info data (RAM)
calminstruction UnloadFontData glyphs*, glyphCount*
	local fname, args
	arrange fname, =UnloadFontData
	arrange args, glyphs, glyphCount
	call RLAPI, fname, args
end calminstruction

; Unload font from GPU memory (VRAM)
calminstruction UnloadFont font*
	local fname, args
	arrange fname, =UnloadFont
	arrange args, font
	call RLAPI, fname, args
end calminstruction

; Export font as code file, returns true on success
calminstruction ExportFontAsCode font*, fileName*
	local fname, args
	arrange fname, =ExportFontAsCode
	arrange args, font, fileName
	call RLAPI, fname, args
end calminstruction

; Draw current FPS
calminstruction DrawFPS posX*, posY*
	local fname, args
	arrange fname, =DrawFPS
	arrange args, posX, posY
	call RLAPI, fname, args
end calminstruction

; Draw text (using default font)
calminstruction DrawText text*, posX*, posY*, fontSize*, color*
	local fname, args
	arrange fname, =DrawText
	arrange args, text, posX, posY, fontSize, color
	call RLAPI, fname, args
end calminstruction

; Draw text using font and additional parameters
calminstruction DrawTextEx font*, text*, position*, fontSize*, spacing*, tint*
	local fname, args
	arrange fname, =DrawTextEx
	arrange args, font, text, position, fontSize, spacing, tint
	call RLAPI, fname, args
end calminstruction

; Draw text using Font and pro parameters (rotation)
calminstruction DrawTextPro font*, text*, position*, origin*, rotation*, fontSize*, spacing*, tint*
	local fname, args
	arrange fname, =DrawTextPro
	arrange args, font, text, position, origin, rotation, fontSize, spacing, tint
	call RLAPI, fname, args
end calminstruction

; Draw one character (codepoint)
calminstruction DrawTextCodepoint font*, codepoint*, position*, fontSize*, tint*
	local fname, args
	arrange fname, =DrawTextCodepoint
	arrange args, font, codepoint, position, fontSize, tint
	call RLAPI, fname, args
end calminstruction

; Draw multiple character (codepoint)
calminstruction DrawTextCodepoints font*, codepoints*, codepointCount*, position*, fontSize*, spacing*, tint*
	local fname, args
	arrange fname, =DrawTextCodepoints
	arrange args, font, codepoints, codepointCount, position, fontSize, spacing, tint
	call RLAPI, fname, args
end calminstruction

; Set vertical line spacing when drawing with line-breaks
calminstruction SetTextLineSpacing spacing*
	local fname, args
	arrange fname, =SetTextLineSpacing
	arrange args, spacing
	call RLAPI, fname, args
end calminstruction

; Measure string width for default font
calminstruction MeasureText text*, fontSize*
	local fname, args
	arrange fname, =MeasureText
	arrange args, text, fontSize
	call RLAPI, fname, args
end calminstruction

; Measure string size for Font
calminstruction MeasureTextEx font*, text*, fontSize*, spacing*
	local fname, args
	arrange fname, =MeasureTextEx
	arrange args, font, text, fontSize, spacing
	call RLAPI, fname, args
end calminstruction

; Measure string size for an existing array of codepoints for Font
calminstruction MeasureTextCodepoints font*, codepoints*, length*, fontSize*, spacing*
	local fname, args
	arrange fname, =MeasureTextCodepoints
	arrange args, font, codepoints, length, fontSize, spacing
	call RLAPI, fname, args
end calminstruction

; Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
calminstruction GetGlyphIndex font*, codepoint*
	local fname, args
	arrange fname, =GetGlyphIndex
	arrange args, font, codepoint
	call RLAPI, fname, args
end calminstruction

; Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
; (returns GlyphInfo via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetGlyphInfo dest*, font*, codepoint*
	local fname, args
	arrange fname, =GetGlyphInfo
	arrange args, dest, font, codepoint
	call RLAPI, fname, args
end calminstruction

; Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found
; (returns Rectangle via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetGlyphAtlasRec dest*, font*, codepoint*
	local fname, args
	arrange fname, =GetGlyphAtlasRec
	arrange args, dest, font, codepoint
	call RLAPI, fname, args
end calminstruction

; Load UTF-8 text encoded from codepoints array
calminstruction LoadUTF8 codepoints*, length*
	local fname, args
	arrange fname, =LoadUTF8
	arrange args, codepoints, length
	call RLAPI, fname, args
end calminstruction

; Unload UTF-8 text encoded from codepoints array
calminstruction UnloadUTF8 text*
	local fname, args
	arrange fname, =UnloadUTF8
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
calminstruction LoadCodepoints text*, count*
	local fname, args
	arrange fname, =LoadCodepoints
	arrange args, text, count
	call RLAPI, fname, args
end calminstruction

; Unload codepoints data from memory
calminstruction UnloadCodepoints codepoints*
	local fname, args
	arrange fname, =UnloadCodepoints
	arrange args, codepoints
	call RLAPI, fname, args
end calminstruction

; Get total number of codepoints in a UTF-8 encoded string
calminstruction GetCodepointCount text*
	local fname, args
	arrange fname, =GetCodepointCount
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
calminstruction GetCodepoint text*, codepointSize*
	local fname, args
	arrange fname, =GetCodepoint
	arrange args, text, codepointSize
	call RLAPI, fname, args
end calminstruction

; Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
calminstruction GetCodepointNext text*, codepointSize*
	local fname, args
	arrange fname, =GetCodepointNext
	arrange args, text, codepointSize
	call RLAPI, fname, args
end calminstruction

; Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
calminstruction GetCodepointPrevious text*, codepointSize*
	local fname, args
	arrange fname, =GetCodepointPrevious
	arrange args, text, codepointSize
	call RLAPI, fname, args
end calminstruction

; Encode one codepoint into UTF-8 byte array (array length returned as parameter)
calminstruction CodepointToUTF8 codepoint*, utf8Size*
	local fname, args
	arrange fname, =CodepointToUTF8
	arrange args, codepoint, utf8Size
	call RLAPI, fname, args
end calminstruction

; Load text as separate lines ('\n')
calminstruction LoadTextLines text*, count*
	local fname, args
	arrange fname, =LoadTextLines
	arrange args, text, count
	call RLAPI, fname, args
end calminstruction

; Unload text lines
calminstruction UnloadTextLines text*, lineCount*
	local fname, args
	arrange fname, =UnloadTextLines
	arrange args, text, lineCount
	call RLAPI, fname, args
end calminstruction

; Copy one string to another, returns bytes copied
calminstruction TextCopy dst*, src*
	local fname, args
	arrange fname, =TextCopy
	arrange args, dst, src
	call RLAPI, fname, args
end calminstruction

; Check if two text string are equal
calminstruction TextIsEqual text1*, text2*
	local fname, args
	arrange fname, =TextIsEqual
	arrange args, text1, text2
	call RLAPI, fname, args
end calminstruction

; Get text length, checks for '\0' ending
calminstruction TextLength text*
	local fname, args
	arrange fname, =TextLength
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Text formatting with variables (sprintf() style)
calminstruction TextFormat text*, rest&
	local fname, args
	arrange fname, =TextFormat
	arrange args, text, rest
	call RLAPI, fname, args
end calminstruction

; Get a piece of a text string
calminstruction TextSubtext text*, position*, length*
	local fname, args
	arrange fname, =TextSubtext
	arrange args, text, position, length
	call RLAPI, fname, args
end calminstruction

; Remove text spaces, concat words
calminstruction TextRemoveSpaces text*
	local fname, args
	arrange fname, =TextRemoveSpaces
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Get text between two strings
calminstruction GetTextBetween text*, begin*, end*
	local fname, args
	arrange fname, =GetTextBetween
	arrange args, text, begin, end
	call RLAPI, fname, args
end calminstruction

; Replace text string with new string
calminstruction TextReplace text*, search*, replacement*
	local fname, args
	arrange fname, =TextReplace
	arrange args, text, search, replacement
	call RLAPI, fname, args
end calminstruction

; Replace text string with new string, memory must be MemFree()
calminstruction TextReplaceAlloc text*, search*, replacement*
	local fname, args
	arrange fname, =TextReplaceAlloc
	arrange args, text, search, replacement
	call RLAPI, fname, args
end calminstruction

; Replace text between two specific strings
calminstruction TextReplaceBetween text*, begin*, end*, replacement*
	local fname, args
	arrange fname, =TextReplaceBetween
	arrange args, text, begin, end, replacement
	call RLAPI, fname, args
end calminstruction

; Replace text between two specific strings, memory must be MemFree()
calminstruction TextReplaceBetweenAlloc text*, begin*, end*, replacement*
	local fname, args
	arrange fname, =TextReplaceBetweenAlloc
	arrange args, text, begin, end, replacement
	call RLAPI, fname, args
end calminstruction

; Insert text in a defined byte position
calminstruction TextInsert text*, insert*, position*
	local fname, args
	arrange fname, =TextInsert
	arrange args, text, insert, position
	call RLAPI, fname, args
end calminstruction

; Insert text in a defined byte position, memory must be MemFree()
calminstruction TextInsertAlloc text*, insert*, position*
	local fname, args
	arrange fname, =TextInsertAlloc
	arrange args, text, insert, position
	call RLAPI, fname, args
end calminstruction

; Join text strings with delimiter
calminstruction TextJoin textList*, count*, delimiter*
	local fname, args
	arrange fname, =TextJoin
	arrange args, textList, count, delimiter
	call RLAPI, fname, args
end calminstruction

; Split text into multiple strings, using MAX_TEXTSPLIT_COUNT static strings
calminstruction TextSplit text*, delimiter*, count*
	local fname, args
	arrange fname, =TextSplit
	arrange args, text, delimiter, count
	call RLAPI, fname, args
end calminstruction

; Append text at specific position and move cursor
calminstruction TextAppend text*, append*, position*
	local fname, args
	arrange fname, =TextAppend
	arrange args, text, append, position
	call RLAPI, fname, args
end calminstruction

; Find first text occurrence within a string, -1 if not found
calminstruction TextFindIndex text*, search*
	local fname, args
	arrange fname, =TextFindIndex
	arrange args, text, search
	call RLAPI, fname, args
end calminstruction

; Get upper case version of provided string
calminstruction TextToUpper text*
	local fname, args
	arrange fname, =TextToUpper
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Get lower case version of provided string
calminstruction TextToLower text*
	local fname, args
	arrange fname, =TextToLower
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Get Pascal case notation version of provided string
calminstruction TextToPascal text*
	local fname, args
	arrange fname, =TextToPascal
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Get Snake case notation version of provided string
calminstruction TextToSnake text*
	local fname, args
	arrange fname, =TextToSnake
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Get Camel case notation version of provided string
calminstruction TextToCamel text*
	local fname, args
	arrange fname, =TextToCamel
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Get integer value from text
calminstruction TextToInteger text*
	local fname, args
	arrange fname, =TextToInteger
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Get float value from text
calminstruction TextToFloat text*
	local fname, args
	arrange fname, =TextToFloat
	arrange args, text
	call RLAPI, fname, args
end calminstruction

; Draw a line in 3D world space
calminstruction DrawLine3D startPos*, endPos*, color*
	local fname, args
	arrange fname, =DrawLine3D
	arrange args, startPos, endPos, color
	call RLAPI, fname, args
end calminstruction

; Draw a point in 3D space, actually a small line
calminstruction DrawPoint3D position*, color*
	local fname, args
	arrange fname, =DrawPoint3D
	arrange args, position, color
	call RLAPI, fname, args
end calminstruction

; Draw a circle in 3D world space
calminstruction DrawCircle3D center*, radius*, rotationAxis*, rotationAngle*, color*
	local fname, args
	arrange fname, =DrawCircle3D
	arrange args, center, radius, rotationAxis, rotationAngle, color
	call RLAPI, fname, args
end calminstruction

; Draw a color-filled triangle (vertex in counter-clockwise order!)
calminstruction DrawTriangle3D v1*, v2*, v3*, color*
	local fname, args
	arrange fname, =DrawTriangle3D
	arrange args, v1, v2, v3, color
	call RLAPI, fname, args
end calminstruction

; Draw a triangle strip defined by points
calminstruction DrawTriangleStrip3D points*, pointCount*, color*
	local fname, args
	arrange fname, =DrawTriangleStrip3D
	arrange args, points, pointCount, color
	call RLAPI, fname, args
end calminstruction

; Draw cube
calminstruction DrawCube position*, width*, height*, length*, color*
	local fname, args
	arrange fname, =DrawCube
	arrange args, position, width, height, length, color
	call RLAPI, fname, args
end calminstruction

; Draw cube (Vector version)
calminstruction DrawCubeV position*, size*, color*
	local fname, args
	arrange fname, =DrawCubeV
	arrange args, position, size, color
	call RLAPI, fname, args
end calminstruction

; Draw cube wires
calminstruction DrawCubeWires position*, width*, height*, length*, color*
	local fname, args
	arrange fname, =DrawCubeWires
	arrange args, position, width, height, length, color
	call RLAPI, fname, args
end calminstruction

; Draw cube wires (Vector version)
calminstruction DrawCubeWiresV position*, size*, color*
	local fname, args
	arrange fname, =DrawCubeWiresV
	arrange args, position, size, color
	call RLAPI, fname, args
end calminstruction

; Draw sphere
calminstruction DrawSphere centerPos*, radius*, color*
	local fname, args
	arrange fname, =DrawSphere
	arrange args, centerPos, radius, color
	call RLAPI, fname, args
end calminstruction

; Draw sphere with extended parameters
calminstruction DrawSphereEx centerPos*, radius*, rings*, slices*, color*
	local fname, args
	arrange fname, =DrawSphereEx
	arrange args, centerPos, radius, rings, slices, color
	call RLAPI, fname, args
end calminstruction

; Draw sphere wires
calminstruction DrawSphereWires centerPos*, radius*, rings*, slices*, color*
	local fname, args
	arrange fname, =DrawSphereWires
	arrange args, centerPos, radius, rings, slices, color
	call RLAPI, fname, args
end calminstruction

; Draw a cylinder/cone
calminstruction DrawCylinder position*, radiusTop*, radiusBottom*, height*, slices*, color*
	local fname, args
	arrange fname, =DrawCylinder
	arrange args, position, radiusTop, radiusBottom, height, slices, color
	call RLAPI, fname, args
end calminstruction

; Draw a cylinder with base at startPos and top at endPos
calminstruction DrawCylinderEx startPos*, endPos*, startRadius*, endRadius*, sides*, color*
	local fname, args
	arrange fname, =DrawCylinderEx
	arrange args, startPos, endPos, startRadius, endRadius, sides, color
	call RLAPI, fname, args
end calminstruction

; Draw a cylinder/cone wires
calminstruction DrawCylinderWires position*, radiusTop*, radiusBottom*, height*, slices*, color*
	local fname, args
	arrange fname, =DrawCylinderWires
	arrange args, position, radiusTop, radiusBottom, height, slices, color
	call RLAPI, fname, args
end calminstruction

; Draw a cylinder wires with base at startPos and top at endPos
calminstruction DrawCylinderWiresEx startPos*, endPos*, startRadius*, endRadius*, sides*, color*
	local fname, args
	arrange fname, =DrawCylinderWiresEx
	arrange args, startPos, endPos, startRadius, endRadius, sides, color
	call RLAPI, fname, args
end calminstruction

; Draw a capsule with the center of its sphere caps at startPos and endPos
calminstruction DrawCapsule startPos*, endPos*, radius*, slices*, rings*, color*
	local fname, args
	arrange fname, =DrawCapsule
	arrange args, startPos, endPos, radius, slices, rings, color
	call RLAPI, fname, args
end calminstruction

; Draw capsule wireframe with the center of its sphere caps at startPos and endPos
calminstruction DrawCapsuleWires startPos*, endPos*, radius*, slices*, rings*, color*
	local fname, args
	arrange fname, =DrawCapsuleWires
	arrange args, startPos, endPos, radius, slices, rings, color
	call RLAPI, fname, args
end calminstruction

; Draw a plane XZ
calminstruction DrawPlane centerPos*, size*, color*
	local fname, args
	arrange fname, =DrawPlane
	arrange args, centerPos, size, color
	call RLAPI, fname, args
end calminstruction

; Draw a ray line
calminstruction DrawRay ray*, color*
	local fname, args
	arrange fname, =DrawRay
	arrange args, ray, color
	call RLAPI, fname, args
end calminstruction

; Draw a grid (centered at (0, 0, 0))
calminstruction DrawGrid slices*, spacing*
	local fname, args
	arrange fname, =DrawGrid
	arrange args, slices, spacing
	call RLAPI, fname, args
end calminstruction

; Load model from files (meshes and materials)
; (returns Model via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadModel dest*, fileName*
	local fname, args
	arrange fname, =LoadModel
	arrange args, dest, fileName
	call RLAPI, fname, args
end calminstruction

; Load model from generated mesh (default material)
; (returns Model via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadModelFromMesh dest*, mesh*
	local fname, args
	arrange fname, =LoadModelFromMesh
	arrange args, dest, mesh
	call RLAPI, fname, args
end calminstruction

; Check if a model is valid (loaded in GPU, VAO/VBOs)
calminstruction IsModelValid model*
	local fname, args
	arrange fname, =IsModelValid
	arrange args, model
	call RLAPI, fname, args
end calminstruction

; Unload model (including meshes) from memory (RAM and/or VRAM)
calminstruction UnloadModel model*
	local fname, args
	arrange fname, =UnloadModel
	arrange args, model
	call RLAPI, fname, args
end calminstruction

; Compute model bounding box limits (considers all meshes)
; (returns BoundingBox via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetModelBoundingBox dest*, model*
	local fname, args
	arrange fname, =GetModelBoundingBox
	arrange args, dest, model
	call RLAPI, fname, args
end calminstruction

; Draw a model (with texture if set)
calminstruction DrawModel model*, position*, scale*, tint*
	local fname, args
	arrange fname, =DrawModel
	arrange args, model, position, scale, tint
	call RLAPI, fname, args
end calminstruction

; Draw a model with extended parameters
calminstruction DrawModelEx model*, position*, rotationAxis*, rotationAngle*, scale*, tint*
	local fname, args
	arrange fname, =DrawModelEx
	arrange args, model, position, rotationAxis, rotationAngle, scale, tint
	call RLAPI, fname, args
end calminstruction

; Draw a model wires (with texture if set)
calminstruction DrawModelWires model*, position*, scale*, tint*
	local fname, args
	arrange fname, =DrawModelWires
	arrange args, model, position, scale, tint
	call RLAPI, fname, args
end calminstruction

; Draw a model wires (with texture if set) with extended parameters
calminstruction DrawModelWiresEx model*, position*, rotationAxis*, rotationAngle*, scale*, tint*
	local fname, args
	arrange fname, =DrawModelWiresEx
	arrange args, model, position, rotationAxis, rotationAngle, scale, tint
	call RLAPI, fname, args
end calminstruction

; Draw bounding box (wires)
calminstruction DrawBoundingBox box*, color*
	local fname, args
	arrange fname, =DrawBoundingBox
	arrange args, box, color
	call RLAPI, fname, args
end calminstruction

; Draw a billboard texture
calminstruction DrawBillboard camera*, texture*, position*, scale*, tint*
	local fname, args
	arrange fname, =DrawBillboard
	arrange args, camera, texture, position, scale, tint
	call RLAPI, fname, args
end calminstruction

; Draw a billboard texture defined by source
calminstruction DrawBillboardRec camera*, texture*, source*, position*, size*, tint*
	local fname, args
	arrange fname, =DrawBillboardRec
	arrange args, camera, texture, source, position, size, tint
	call RLAPI, fname, args
end calminstruction

; Draw a billboard texture defined by source and rotation
calminstruction DrawBillboardPro camera*, texture*, source*, position*, up*, size*, origin*, rotation*, tint*
	local fname, args
	arrange fname, =DrawBillboardPro
	arrange args, camera, texture, source, position, up, size, origin, rotation, tint
	call RLAPI, fname, args
end calminstruction

; Upload mesh vertex data in GPU and provide VAO/VBO ids
calminstruction UploadMesh mesh*, dynamic*
	local fname, args
	arrange fname, =UploadMesh
	arrange args, mesh, dynamic
	call RLAPI, fname, args
end calminstruction

; Update mesh vertex data in GPU for a specific buffer index
calminstruction UpdateMeshBuffer mesh*, index*, data*, dataSize*, offset*
	local fname, args
	arrange fname, =UpdateMeshBuffer
	arrange args, mesh, index, data, dataSize, offset
	call RLAPI, fname, args
end calminstruction

; Unload mesh data from CPU and GPU
calminstruction UnloadMesh mesh*
	local fname, args
	arrange fname, =UnloadMesh
	arrange args, mesh
	call RLAPI, fname, args
end calminstruction

; Draw a 3d mesh with material and transform
calminstruction DrawMesh mesh*, material*, transform*
	local fname, args
	arrange fname, =DrawMesh
	arrange args, mesh, material, transform
	call RLAPI, fname, args
end calminstruction

; Draw multiple mesh instances with material and different transforms
calminstruction DrawMeshInstanced mesh*, material*, transforms*, instances*
	local fname, args
	arrange fname, =DrawMeshInstanced
	arrange args, mesh, material, transforms, instances
	call RLAPI, fname, args
end calminstruction

; Compute mesh bounding box limits
; (returns BoundingBox via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetMeshBoundingBox dest*, mesh*
	local fname, args
	arrange fname, =GetMeshBoundingBox
	arrange args, dest, mesh
	call RLAPI, fname, args
end calminstruction

; Compute mesh tangents
calminstruction GenMeshTangents mesh*
	local fname, args
	arrange fname, =GenMeshTangents
	arrange args, mesh
	call RLAPI, fname, args
end calminstruction

; Export mesh data to file, returns true on success
calminstruction ExportMesh mesh*, fileName*
	local fname, args
	arrange fname, =ExportMesh
	arrange args, mesh, fileName
	call RLAPI, fname, args
end calminstruction

; Export mesh as code file (.h) defining multiple arrays of vertex attributes
calminstruction ExportMeshAsCode mesh*, fileName*
	local fname, args
	arrange fname, =ExportMeshAsCode
	arrange args, mesh, fileName
	call RLAPI, fname, args
end calminstruction

; Generate polygonal mesh
; (returns Mesh via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenMeshPoly dest*, sides*, radius*
	local fname, args
	arrange fname, =GenMeshPoly
	arrange args, dest, sides, radius
	call RLAPI, fname, args
end calminstruction

; Generate plane mesh (with subdivisions)
; (returns Mesh via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenMeshPlane dest*, width*, length*, resX*, resZ*
	local fname, args
	arrange fname, =GenMeshPlane
	arrange args, dest, width, length, resX, resZ
	call RLAPI, fname, args
end calminstruction

; Generate cuboid mesh
; (returns Mesh via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenMeshCube dest*, width*, height*, length*
	local fname, args
	arrange fname, =GenMeshCube
	arrange args, dest, width, height, length
	call RLAPI, fname, args
end calminstruction

; Generate sphere mesh (standard sphere)
; (returns Mesh via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenMeshSphere dest*, radius*, rings*, slices*
	local fname, args
	arrange fname, =GenMeshSphere
	arrange args, dest, radius, rings, slices
	call RLAPI, fname, args
end calminstruction

; Generate half-sphere mesh (no bottom cap)
; (returns Mesh via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenMeshHemiSphere dest*, radius*, rings*, slices*
	local fname, args
	arrange fname, =GenMeshHemiSphere
	arrange args, dest, radius, rings, slices
	call RLAPI, fname, args
end calminstruction

; Generate cylinder mesh
; (returns Mesh via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenMeshCylinder dest*, radius*, height*, slices*
	local fname, args
	arrange fname, =GenMeshCylinder
	arrange args, dest, radius, height, slices
	call RLAPI, fname, args
end calminstruction

; Generate cone/pyramid mesh
; (returns Mesh via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenMeshCone dest*, radius*, height*, slices*
	local fname, args
	arrange fname, =GenMeshCone
	arrange args, dest, radius, height, slices
	call RLAPI, fname, args
end calminstruction

; Generate torus mesh
; (returns Mesh via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenMeshTorus dest*, radius*, size*, radSeg*, sides*
	local fname, args
	arrange fname, =GenMeshTorus
	arrange args, dest, radius, size, radSeg, sides
	call RLAPI, fname, args
end calminstruction

; Generate trefoil knot mesh
; (returns Mesh via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenMeshKnot dest*, radius*, size*, radSeg*, sides*
	local fname, args
	arrange fname, =GenMeshKnot
	arrange args, dest, radius, size, radSeg, sides
	call RLAPI, fname, args
end calminstruction

; Generate heightmap mesh from image data
; (returns Mesh via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenMeshHeightmap dest*, heightmap*, size*
	local fname, args
	arrange fname, =GenMeshHeightmap
	arrange args, dest, heightmap, size
	call RLAPI, fname, args
end calminstruction

; Generate cubes-based map mesh from image data
; (returns Mesh via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GenMeshCubicmap dest*, cubicmap*, cubeSize*
	local fname, args
	arrange fname, =GenMeshCubicmap
	arrange args, dest, cubicmap, cubeSize
	call RLAPI, fname, args
end calminstruction

; Load materials from model file
calminstruction LoadMaterials fileName*, materialCount*
	local fname, args
	arrange fname, =LoadMaterials
	arrange args, fileName, materialCount
	call RLAPI, fname, args
end calminstruction

; Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
; (returns Material via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadMaterialDefault dest*
	local fname, args
	arrange fname, =LoadMaterialDefault
	arrange args, dest
	call RLAPI, fname, args
end calminstruction

; Check if a material is valid (shader assigned, map textures loaded in GPU)
calminstruction IsMaterialValid material*
	local fname, args
	arrange fname, =IsMaterialValid
	arrange args, material
	call RLAPI, fname, args
end calminstruction

; Unload material from GPU memory (VRAM)
calminstruction UnloadMaterial material*
	local fname, args
	arrange fname, =UnloadMaterial
	arrange args, material
	call RLAPI, fname, args
end calminstruction

; Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
calminstruction SetMaterialTexture material*, mapType*, texture*
    reduce:
	transform mapType
	jyes reduce
	transform mapType, RayLib.MaterialMapIndex
	local fname, args
	arrange fname, =SetMaterialTexture
	arrange args, material, mapType, texture
	call RLAPI, fname, args
end calminstruction

; Set material for a mesh
calminstruction SetModelMeshMaterial model*, meshId*, materialId*
	local fname, args
	arrange fname, =SetModelMeshMaterial
	arrange args, model, meshId, materialId
	call RLAPI, fname, args
end calminstruction

; Load model animations from file
calminstruction LoadModelAnimations fileName*, animCount*
	local fname, args
	arrange fname, =LoadModelAnimations
	arrange args, fileName, animCount
	call RLAPI, fname, args
end calminstruction

; Update model animation pose (vertex buffers and bone matrices)
calminstruction UpdateModelAnimation model*, anim*, frame*
	local fname, args
	arrange fname, =UpdateModelAnimation
	arrange args, model, anim, frame
	call RLAPI, fname, args
end calminstruction

; Update model animation pose, blending two animations
calminstruction UpdateModelAnimationEx model*, animA*, frameA*, animB*, frameB*, blend*
	local fname, args
	arrange fname, =UpdateModelAnimationEx
	arrange args, model, animA, frameA, animB, frameB, blend
	call RLAPI, fname, args
end calminstruction

; Unload animation array data
calminstruction UnloadModelAnimations animations*, animCount*
	local fname, args
	arrange fname, =UnloadModelAnimations
	arrange args, animations, animCount
	call RLAPI, fname, args
end calminstruction

; Check model animation skeleton match
calminstruction IsModelAnimationValid model*, anim*
	local fname, args
	arrange fname, =IsModelAnimationValid
	arrange args, model, anim
	call RLAPI, fname, args
end calminstruction

; Check collision between two spheres
calminstruction CheckCollisionSpheres center1*, radius1*, center2*, radius2*
	local fname, args
	arrange fname, =CheckCollisionSpheres
	arrange args, center1, radius1, center2, radius2
	call RLAPI, fname, args
end calminstruction

; Check collision between two bounding boxes
calminstruction CheckCollisionBoxes box1*, box2*
	local fname, args
	arrange fname, =CheckCollisionBoxes
	arrange args, box1, box2
	call RLAPI, fname, args
end calminstruction

; Check collision between box and sphere
calminstruction CheckCollisionBoxSphere box*, center*, radius*
	local fname, args
	arrange fname, =CheckCollisionBoxSphere
	arrange args, box, center, radius
	call RLAPI, fname, args
end calminstruction

; Get collision info between ray and sphere
; (returns RayCollision via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetRayCollisionSphere dest*, ray*, center*, radius*
	local fname, args
	arrange fname, =GetRayCollisionSphere
	arrange args, dest, ray, center, radius
	call RLAPI, fname, args
end calminstruction

; Get collision info between ray and box
; (returns RayCollision via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetRayCollisionBox dest*, ray*, box*
	local fname, args
	arrange fname, =GetRayCollisionBox
	arrange args, dest, ray, box
	call RLAPI, fname, args
end calminstruction

; Get collision info between ray and mesh
; (returns RayCollision via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetRayCollisionMesh dest*, ray*, mesh*, transform*
	local fname, args
	arrange fname, =GetRayCollisionMesh
	arrange args, dest, ray, mesh, transform
	call RLAPI, fname, args
end calminstruction

; Get collision info between ray and triangle
; (returns RayCollision via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetRayCollisionTriangle dest*, ray*, p1*, p2*, p3*
	local fname, args
	arrange fname, =GetRayCollisionTriangle
	arrange args, dest, ray, p1, p2, p3
	call RLAPI, fname, args
end calminstruction

; Get collision info between ray and quad
; (returns RayCollision via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction GetRayCollisionQuad dest*, ray*, p1*, p2*, p3*, p4*
	local fname, args
	arrange fname, =GetRayCollisionQuad
	arrange args, dest, ray, p1, p2, p3, p4
	call RLAPI, fname, args
end calminstruction

; Initialize audio device and context
calminstruction InitAudioDevice
	local fname, args
	arrange fname, =InitAudioDevice
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Close the audio device and context
calminstruction CloseAudioDevice
	local fname, args
	arrange fname, =CloseAudioDevice
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Check if audio device has been initialized successfully
calminstruction IsAudioDeviceReady
	local fname, args
	arrange fname, =IsAudioDeviceReady
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Set master volume (listener)
calminstruction SetMasterVolume volume*
	local fname, args
	arrange fname, =SetMasterVolume
	arrange args, volume
	call RLAPI, fname, args
end calminstruction

; Get master volume (listener)
calminstruction GetMasterVolume
	local fname, args
	arrange fname, =GetMasterVolume
	arrange args,
	call RLAPI, fname, args
end calminstruction

; Load wave data from file
; (returns Wave via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadWave dest*, fileName*
	local fname, args
	arrange fname, =LoadWave
	arrange args, dest, fileName
	call RLAPI, fname, args
end calminstruction

; Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
; (returns Wave via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadWaveFromMemory dest*, fileType*, fileData*, dataSize*
	local fname, args
	arrange fname, =LoadWaveFromMemory
	arrange args, dest, fileType, fileData, dataSize
	call RLAPI, fname, args
end calminstruction

; Checks if wave data is valid (data loaded and parameters)
calminstruction IsWaveValid wave*
	local fname, args
	arrange fname, =IsWaveValid
	arrange args, wave
	call RLAPI, fname, args
end calminstruction

; Load sound from file
; (returns Sound via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadSound dest*, fileName*
	local fname, args
	arrange fname, =LoadSound
	arrange args, dest, fileName
	call RLAPI, fname, args
end calminstruction

; Load sound from wave data
; (returns Sound via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadSoundFromWave dest*, wave*
	local fname, args
	arrange fname, =LoadSoundFromWave
	arrange args, dest, wave
	call RLAPI, fname, args
end calminstruction

; Create a new sound that shares the same sample data as the source sound, does not own the sound data
; (returns Sound via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadSoundAlias dest*, source*
	local fname, args
	arrange fname, =LoadSoundAlias
	arrange args, dest, source
	call RLAPI, fname, args
end calminstruction

; Checks if a sound is valid (data loaded and buffers initialized)
calminstruction IsSoundValid sound*
	local fname, args
	arrange fname, =IsSoundValid
	arrange args, sound
	call RLAPI, fname, args
end calminstruction

; Update sound buffer with new data (default data format: 32 bit float, stereo)
calminstruction UpdateSound sound*, data*, sampleCount*
	local fname, args
	arrange fname, =UpdateSound
	arrange args, sound, data, sampleCount
	call RLAPI, fname, args
end calminstruction

; Unload wave data
calminstruction UnloadWave wave*
	local fname, args
	arrange fname, =UnloadWave
	arrange args, wave
	call RLAPI, fname, args
end calminstruction

; Unload sound
calminstruction UnloadSound sound*
	local fname, args
	arrange fname, =UnloadSound
	arrange args, sound
	call RLAPI, fname, args
end calminstruction

; Unload a sound alias (does not deallocate sample data)
calminstruction UnloadSoundAlias alias*
	local fname, args
	arrange fname, =UnloadSoundAlias
	arrange args, alias
	call RLAPI, fname, args
end calminstruction

; Export wave data to file, returns true on success
calminstruction ExportWave wave*, fileName*
	local fname, args
	arrange fname, =ExportWave
	arrange args, wave, fileName
	call RLAPI, fname, args
end calminstruction

; Export wave sample data to code (.h), returns true on success
calminstruction ExportWaveAsCode wave*, fileName*
	local fname, args
	arrange fname, =ExportWaveAsCode
	arrange args, wave, fileName
	call RLAPI, fname, args
end calminstruction

; Play a sound
calminstruction PlaySound sound*
	local fname, args
	arrange fname, =PlaySound
	arrange args, sound
	call RLAPI, fname, args
end calminstruction

; Stop playing a sound
calminstruction StopSound sound*
	local fname, args
	arrange fname, =StopSound
	arrange args, sound
	call RLAPI, fname, args
end calminstruction

; Pause a sound
calminstruction PauseSound sound*
	local fname, args
	arrange fname, =PauseSound
	arrange args, sound
	call RLAPI, fname, args
end calminstruction

; Resume a paused sound
calminstruction ResumeSound sound*
	local fname, args
	arrange fname, =ResumeSound
	arrange args, sound
	call RLAPI, fname, args
end calminstruction

; Check if a sound is currently playing
calminstruction IsSoundPlaying sound*
	local fname, args
	arrange fname, =IsSoundPlaying
	arrange args, sound
	call RLAPI, fname, args
end calminstruction

; Set volume for a sound (1.0 is max level)
calminstruction SetSoundVolume sound*, volume*
	local fname, args
	arrange fname, =SetSoundVolume
	arrange args, sound, volume
	call RLAPI, fname, args
end calminstruction

; Set pitch for a sound (1.0 is base level)
calminstruction SetSoundPitch sound*, pitch*
	local fname, args
	arrange fname, =SetSoundPitch
	arrange args, sound, pitch
	call RLAPI, fname, args
end calminstruction

; Set pan for a sound (-1.0 left, 0.0 center, 1.0 right)
calminstruction SetSoundPan sound*, pan*
	local fname, args
	arrange fname, =SetSoundPan
	arrange args, sound, pan
	call RLAPI, fname, args
end calminstruction

; Copy a wave to a new wave
; (returns Wave via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction WaveCopy dest*, wave*
	local fname, args
	arrange fname, =WaveCopy
	arrange args, dest, wave
	call RLAPI, fname, args
end calminstruction

; Crop a wave to defined frames range
calminstruction WaveCrop wave*, initFrame*, finalFrame*
	local fname, args
	arrange fname, =WaveCrop
	arrange args, wave, initFrame, finalFrame
	call RLAPI, fname, args
end calminstruction

; Convert wave data to desired format
calminstruction WaveFormat wave*, sampleRate*, sampleSize*, channels*
	local fname, args
	arrange fname, =WaveFormat
	arrange args, wave, sampleRate, sampleSize, channels
	call RLAPI, fname, args
end calminstruction

; Load samples data from wave as a 32bit float data array
calminstruction LoadWaveSamples wave*
	local fname, args
	arrange fname, =LoadWaveSamples
	arrange args, wave
	call RLAPI, fname, args
end calminstruction

; Unload samples data loaded with LoadWaveSamples()
calminstruction UnloadWaveSamples samples*
	local fname, args
	arrange fname, =UnloadWaveSamples
	arrange args, samples
	call RLAPI, fname, args
end calminstruction

; Load music stream from file
; (returns Music via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadMusicStream dest*, fileName*
	local fname, args
	arrange fname, =LoadMusicStream
	arrange args, dest, fileName
	call RLAPI, fname, args
end calminstruction

; Load music stream from data
; (returns Music via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadMusicStreamFromMemory dest*, fileType*, data*, dataSize*
	local fname, args
	arrange fname, =LoadMusicStreamFromMemory
	arrange args, dest, fileType, data, dataSize
	call RLAPI, fname, args
end calminstruction

; Checks if a music stream is valid (context and buffers initialized)
calminstruction IsMusicValid music*
	local fname, args
	arrange fname, =IsMusicValid
	arrange args, music
	call RLAPI, fname, args
end calminstruction

; Unload music stream
calminstruction UnloadMusicStream music*
	local fname, args
	arrange fname, =UnloadMusicStream
	arrange args, music
	call RLAPI, fname, args
end calminstruction

; Start music playing
calminstruction PlayMusicStream music*
	local fname, args
	arrange fname, =PlayMusicStream
	arrange args, music
	call RLAPI, fname, args
end calminstruction

; Check if music is playing
calminstruction IsMusicStreamPlaying music*
	local fname, args
	arrange fname, =IsMusicStreamPlaying
	arrange args, music
	call RLAPI, fname, args
end calminstruction

; Updates buffers for music streaming
calminstruction UpdateMusicStream music*
	local fname, args
	arrange fname, =UpdateMusicStream
	arrange args, music
	call RLAPI, fname, args
end calminstruction

; Stop music playing
calminstruction StopMusicStream music*
	local fname, args
	arrange fname, =StopMusicStream
	arrange args, music
	call RLAPI, fname, args
end calminstruction

; Pause music playing
calminstruction PauseMusicStream music*
	local fname, args
	arrange fname, =PauseMusicStream
	arrange args, music
	call RLAPI, fname, args
end calminstruction

; Resume playing paused music
calminstruction ResumeMusicStream music*
	local fname, args
	arrange fname, =ResumeMusicStream
	arrange args, music
	call RLAPI, fname, args
end calminstruction

; Seek music to a position (in seconds)
calminstruction SeekMusicStream music*, position*
	local fname, args
	arrange fname, =SeekMusicStream
	arrange args, music, position
	call RLAPI, fname, args
end calminstruction

; Set volume for music (1.0 is max level)
calminstruction SetMusicVolume music*, volume*
	local fname, args
	arrange fname, =SetMusicVolume
	arrange args, music, volume
	call RLAPI, fname, args
end calminstruction

; Set pitch for a music (1.0 is base level)
calminstruction SetMusicPitch music*, pitch*
	local fname, args
	arrange fname, =SetMusicPitch
	arrange args, music, pitch
	call RLAPI, fname, args
end calminstruction

; Set pan for a music (-1.0 left, 0.0 center, 1.0 right)
calminstruction SetMusicPan music*, pan*
	local fname, args
	arrange fname, =SetMusicPan
	arrange args, music, pan
	call RLAPI, fname, args
end calminstruction

; Get music time length (in seconds)
calminstruction GetMusicTimeLength music*
	local fname, args
	arrange fname, =GetMusicTimeLength
	arrange args, music
	call RLAPI, fname, args
end calminstruction

; Get current music time played (in seconds)
calminstruction GetMusicTimePlayed music*
	local fname, args
	arrange fname, =GetMusicTimePlayed
	arrange args, music
	call RLAPI, fname, args
end calminstruction

; Load audio stream (to stream raw audio pcm data)
; (returns AudioStream via hidden first-arg pointer — pass `dest` as the destination buffer)
calminstruction LoadAudioStream dest*, sampleRate*, sampleSize*, channels*
	local fname, args
	arrange fname, =LoadAudioStream
	arrange args, dest, sampleRate, sampleSize, channels
	call RLAPI, fname, args
end calminstruction

; Checks if an audio stream is valid (buffers initialized)
calminstruction IsAudioStreamValid stream*
	local fname, args
	arrange fname, =IsAudioStreamValid
	arrange args, stream
	call RLAPI, fname, args
end calminstruction

; Unload audio stream and free memory
calminstruction UnloadAudioStream stream*
	local fname, args
	arrange fname, =UnloadAudioStream
	arrange args, stream
	call RLAPI, fname, args
end calminstruction

; Update audio stream buffers with data
calminstruction UpdateAudioStream stream*, data*, frameCount*
	local fname, args
	arrange fname, =UpdateAudioStream
	arrange args, stream, data, frameCount
	call RLAPI, fname, args
end calminstruction

; Check if any audio stream buffers requires refill
calminstruction IsAudioStreamProcessed stream*
	local fname, args
	arrange fname, =IsAudioStreamProcessed
	arrange args, stream
	call RLAPI, fname, args
end calminstruction

; Play audio stream
calminstruction PlayAudioStream stream*
	local fname, args
	arrange fname, =PlayAudioStream
	arrange args, stream
	call RLAPI, fname, args
end calminstruction

; Pause audio stream
calminstruction PauseAudioStream stream*
	local fname, args
	arrange fname, =PauseAudioStream
	arrange args, stream
	call RLAPI, fname, args
end calminstruction

; Resume audio stream
calminstruction ResumeAudioStream stream*
	local fname, args
	arrange fname, =ResumeAudioStream
	arrange args, stream
	call RLAPI, fname, args
end calminstruction

; Check if audio stream is playing
calminstruction IsAudioStreamPlaying stream*
	local fname, args
	arrange fname, =IsAudioStreamPlaying
	arrange args, stream
	call RLAPI, fname, args
end calminstruction

; Stop audio stream
calminstruction StopAudioStream stream*
	local fname, args
	arrange fname, =StopAudioStream
	arrange args, stream
	call RLAPI, fname, args
end calminstruction

; Set volume for audio stream (1.0 is max level)
calminstruction SetAudioStreamVolume stream*, volume*
	local fname, args
	arrange fname, =SetAudioStreamVolume
	arrange args, stream, volume
	call RLAPI, fname, args
end calminstruction

; Set pitch for audio stream (1.0 is base level)
calminstruction SetAudioStreamPitch stream*, pitch*
	local fname, args
	arrange fname, =SetAudioStreamPitch
	arrange args, stream, pitch
	call RLAPI, fname, args
end calminstruction

; Set pan for audio stream (-1.0 to 1.0 range, 0.0 is centered)
calminstruction SetAudioStreamPan stream*, pan*
	local fname, args
	arrange fname, =SetAudioStreamPan
	arrange args, stream, pan
	call RLAPI, fname, args
end calminstruction

; Default size for new audio streams
calminstruction SetAudioStreamBufferSizeDefault size*
	local fname, args
	arrange fname, =SetAudioStreamBufferSizeDefault
	arrange args, size
	call RLAPI, fname, args
end calminstruction

; Audio thread callback to request new data
calminstruction SetAudioStreamCallback stream*, callback*
	local fname, args
	arrange fname, =SetAudioStreamCallback
	arrange args, stream, callback
	call RLAPI, fname, args
end calminstruction

; Attach audio stream processor to stream, receives frames x 2 samples as 'float' (stereo)
calminstruction AttachAudioStreamProcessor stream*, processor*
	local fname, args
	arrange fname, =AttachAudioStreamProcessor
	arrange args, stream, processor
	call RLAPI, fname, args
end calminstruction

; Detach audio stream processor from stream
calminstruction DetachAudioStreamProcessor stream*, processor*
	local fname, args
	arrange fname, =DetachAudioStreamProcessor
	arrange args, stream, processor
	call RLAPI, fname, args
end calminstruction

; Attach audio stream processor to the entire audio pipeline, receives frames x 2 samples as 'float' (stereo)
calminstruction AttachAudioMixedProcessor processor*
	local fname, args
	arrange fname, =AttachAudioMixedProcessor
	arrange args, processor
	call RLAPI, fname, args
end calminstruction

; Detach audio stream processor from the entire audio pipeline
calminstruction DetachAudioMixedProcessor processor*
	local fname, args
	arrange fname, =DetachAudioMixedProcessor
	arrange args, processor
	call RLAPI, fname, args
end calminstruction
