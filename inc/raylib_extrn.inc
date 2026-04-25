; raylib extrn declarations — OBJ mode, generated
;
; Place anywhere in the source after `format MS64 COFF`:
;   include 'raylib_extrn.inc'
;
; The external symbol is `Func` (raylib.lib's actual export); we
; alias it to `RLAPI.Func` so the dispatcher can address it the
; same way it would in DLL mode. Each declaration is gated by
; `if used RLAPI.Func` so only referenced symbols make it into
; the .obj — important when raylib.lib's API surface is a
; subset of what this projection covers.

if used RLAPI.InitWindow
	extrn 'InitWindow' as RLAPI.InitWindow
end if
if used RLAPI.CloseWindow
	extrn 'CloseWindow' as RLAPI.CloseWindow
end if
if used RLAPI.WindowShouldClose
	extrn 'WindowShouldClose' as RLAPI.WindowShouldClose
end if
if used RLAPI.IsWindowReady
	extrn 'IsWindowReady' as RLAPI.IsWindowReady
end if
if used RLAPI.IsWindowFullscreen
	extrn 'IsWindowFullscreen' as RLAPI.IsWindowFullscreen
end if
if used RLAPI.IsWindowHidden
	extrn 'IsWindowHidden' as RLAPI.IsWindowHidden
end if
if used RLAPI.IsWindowMinimized
	extrn 'IsWindowMinimized' as RLAPI.IsWindowMinimized
end if
if used RLAPI.IsWindowMaximized
	extrn 'IsWindowMaximized' as RLAPI.IsWindowMaximized
end if
if used RLAPI.IsWindowFocused
	extrn 'IsWindowFocused' as RLAPI.IsWindowFocused
end if
if used RLAPI.IsWindowResized
	extrn 'IsWindowResized' as RLAPI.IsWindowResized
end if
if used RLAPI.IsWindowState
	extrn 'IsWindowState' as RLAPI.IsWindowState
end if
if used RLAPI.SetWindowState
	extrn 'SetWindowState' as RLAPI.SetWindowState
end if
if used RLAPI.ClearWindowState
	extrn 'ClearWindowState' as RLAPI.ClearWindowState
end if
if used RLAPI.ToggleFullscreen
	extrn 'ToggleFullscreen' as RLAPI.ToggleFullscreen
end if
if used RLAPI.ToggleBorderlessWindowed
	extrn 'ToggleBorderlessWindowed' as RLAPI.ToggleBorderlessWindowed
end if
if used RLAPI.MaximizeWindow
	extrn 'MaximizeWindow' as RLAPI.MaximizeWindow
end if
if used RLAPI.MinimizeWindow
	extrn 'MinimizeWindow' as RLAPI.MinimizeWindow
end if
if used RLAPI.RestoreWindow
	extrn 'RestoreWindow' as RLAPI.RestoreWindow
end if
if used RLAPI.SetWindowIcon
	extrn 'SetWindowIcon' as RLAPI.SetWindowIcon
end if
if used RLAPI.SetWindowIcons
	extrn 'SetWindowIcons' as RLAPI.SetWindowIcons
end if
if used RLAPI.SetWindowTitle
	extrn 'SetWindowTitle' as RLAPI.SetWindowTitle
end if
if used RLAPI.SetWindowPosition
	extrn 'SetWindowPosition' as RLAPI.SetWindowPosition
end if
if used RLAPI.SetWindowMonitor
	extrn 'SetWindowMonitor' as RLAPI.SetWindowMonitor
end if
if used RLAPI.SetWindowMinSize
	extrn 'SetWindowMinSize' as RLAPI.SetWindowMinSize
end if
if used RLAPI.SetWindowMaxSize
	extrn 'SetWindowMaxSize' as RLAPI.SetWindowMaxSize
end if
if used RLAPI.SetWindowSize
	extrn 'SetWindowSize' as RLAPI.SetWindowSize
end if
if used RLAPI.SetWindowOpacity
	extrn 'SetWindowOpacity' as RLAPI.SetWindowOpacity
end if
if used RLAPI.SetWindowFocused
	extrn 'SetWindowFocused' as RLAPI.SetWindowFocused
end if
if used RLAPI.GetWindowHandle
	extrn 'GetWindowHandle' as RLAPI.GetWindowHandle
end if
if used RLAPI.GetScreenWidth
	extrn 'GetScreenWidth' as RLAPI.GetScreenWidth
end if
if used RLAPI.GetScreenHeight
	extrn 'GetScreenHeight' as RLAPI.GetScreenHeight
end if
if used RLAPI.GetRenderWidth
	extrn 'GetRenderWidth' as RLAPI.GetRenderWidth
end if
if used RLAPI.GetRenderHeight
	extrn 'GetRenderHeight' as RLAPI.GetRenderHeight
end if
if used RLAPI.GetMonitorCount
	extrn 'GetMonitorCount' as RLAPI.GetMonitorCount
end if
if used RLAPI.GetCurrentMonitor
	extrn 'GetCurrentMonitor' as RLAPI.GetCurrentMonitor
end if
if used RLAPI.GetMonitorPosition
	extrn 'GetMonitorPosition' as RLAPI.GetMonitorPosition
end if
if used RLAPI.GetMonitorWidth
	extrn 'GetMonitorWidth' as RLAPI.GetMonitorWidth
end if
if used RLAPI.GetMonitorHeight
	extrn 'GetMonitorHeight' as RLAPI.GetMonitorHeight
end if
if used RLAPI.GetMonitorPhysicalWidth
	extrn 'GetMonitorPhysicalWidth' as RLAPI.GetMonitorPhysicalWidth
end if
if used RLAPI.GetMonitorPhysicalHeight
	extrn 'GetMonitorPhysicalHeight' as RLAPI.GetMonitorPhysicalHeight
end if
if used RLAPI.GetMonitorRefreshRate
	extrn 'GetMonitorRefreshRate' as RLAPI.GetMonitorRefreshRate
end if
if used RLAPI.GetWindowPosition
	extrn 'GetWindowPosition' as RLAPI.GetWindowPosition
end if
if used RLAPI.GetWindowScaleDPI
	extrn 'GetWindowScaleDPI' as RLAPI.GetWindowScaleDPI
end if
if used RLAPI.GetMonitorName
	extrn 'GetMonitorName' as RLAPI.GetMonitorName
end if
if used RLAPI.SetClipboardText
	extrn 'SetClipboardText' as RLAPI.SetClipboardText
end if
if used RLAPI.GetClipboardText
	extrn 'GetClipboardText' as RLAPI.GetClipboardText
end if
if used RLAPI.GetClipboardImage
	extrn 'GetClipboardImage' as RLAPI.GetClipboardImage
end if
if used RLAPI.EnableEventWaiting
	extrn 'EnableEventWaiting' as RLAPI.EnableEventWaiting
end if
if used RLAPI.DisableEventWaiting
	extrn 'DisableEventWaiting' as RLAPI.DisableEventWaiting
end if
if used RLAPI.ShowCursor
	extrn 'ShowCursor' as RLAPI.ShowCursor
end if
if used RLAPI.HideCursor
	extrn 'HideCursor' as RLAPI.HideCursor
end if
if used RLAPI.IsCursorHidden
	extrn 'IsCursorHidden' as RLAPI.IsCursorHidden
end if
if used RLAPI.EnableCursor
	extrn 'EnableCursor' as RLAPI.EnableCursor
end if
if used RLAPI.DisableCursor
	extrn 'DisableCursor' as RLAPI.DisableCursor
end if
if used RLAPI.IsCursorOnScreen
	extrn 'IsCursorOnScreen' as RLAPI.IsCursorOnScreen
end if
if used RLAPI.ClearBackground
	extrn 'ClearBackground' as RLAPI.ClearBackground
end if
if used RLAPI.BeginDrawing
	extrn 'BeginDrawing' as RLAPI.BeginDrawing
end if
if used RLAPI.EndDrawing
	extrn 'EndDrawing' as RLAPI.EndDrawing
end if
if used RLAPI.BeginMode2D
	extrn 'BeginMode2D' as RLAPI.BeginMode2D
end if
if used RLAPI.EndMode2D
	extrn 'EndMode2D' as RLAPI.EndMode2D
end if
if used RLAPI.BeginMode3D
	extrn 'BeginMode3D' as RLAPI.BeginMode3D
end if
if used RLAPI.EndMode3D
	extrn 'EndMode3D' as RLAPI.EndMode3D
end if
if used RLAPI.BeginTextureMode
	extrn 'BeginTextureMode' as RLAPI.BeginTextureMode
end if
if used RLAPI.EndTextureMode
	extrn 'EndTextureMode' as RLAPI.EndTextureMode
end if
if used RLAPI.BeginShaderMode
	extrn 'BeginShaderMode' as RLAPI.BeginShaderMode
end if
if used RLAPI.EndShaderMode
	extrn 'EndShaderMode' as RLAPI.EndShaderMode
end if
if used RLAPI.BeginBlendMode
	extrn 'BeginBlendMode' as RLAPI.BeginBlendMode
end if
if used RLAPI.EndBlendMode
	extrn 'EndBlendMode' as RLAPI.EndBlendMode
end if
if used RLAPI.BeginScissorMode
	extrn 'BeginScissorMode' as RLAPI.BeginScissorMode
end if
if used RLAPI.EndScissorMode
	extrn 'EndScissorMode' as RLAPI.EndScissorMode
end if
if used RLAPI.BeginVrStereoMode
	extrn 'BeginVrStereoMode' as RLAPI.BeginVrStereoMode
end if
if used RLAPI.EndVrStereoMode
	extrn 'EndVrStereoMode' as RLAPI.EndVrStereoMode
end if
if used RLAPI.LoadVrStereoConfig
	extrn 'LoadVrStereoConfig' as RLAPI.LoadVrStereoConfig
end if
if used RLAPI.UnloadVrStereoConfig
	extrn 'UnloadVrStereoConfig' as RLAPI.UnloadVrStereoConfig
end if
if used RLAPI.LoadShader
	extrn 'LoadShader' as RLAPI.LoadShader
end if
if used RLAPI.LoadShaderFromMemory
	extrn 'LoadShaderFromMemory' as RLAPI.LoadShaderFromMemory
end if
if used RLAPI.IsShaderValid
	extrn 'IsShaderValid' as RLAPI.IsShaderValid
end if
if used RLAPI.GetShaderLocation
	extrn 'GetShaderLocation' as RLAPI.GetShaderLocation
end if
if used RLAPI.GetShaderLocationAttrib
	extrn 'GetShaderLocationAttrib' as RLAPI.GetShaderLocationAttrib
end if
if used RLAPI.SetShaderValue
	extrn 'SetShaderValue' as RLAPI.SetShaderValue
end if
if used RLAPI.SetShaderValueV
	extrn 'SetShaderValueV' as RLAPI.SetShaderValueV
end if
if used RLAPI.SetShaderValueMatrix
	extrn 'SetShaderValueMatrix' as RLAPI.SetShaderValueMatrix
end if
if used RLAPI.SetShaderValueTexture
	extrn 'SetShaderValueTexture' as RLAPI.SetShaderValueTexture
end if
if used RLAPI.UnloadShader
	extrn 'UnloadShader' as RLAPI.UnloadShader
end if
if used RLAPI.GetScreenToWorldRay
	extrn 'GetScreenToWorldRay' as RLAPI.GetScreenToWorldRay
end if
if used RLAPI.GetScreenToWorldRayEx
	extrn 'GetScreenToWorldRayEx' as RLAPI.GetScreenToWorldRayEx
end if
if used RLAPI.GetWorldToScreen
	extrn 'GetWorldToScreen' as RLAPI.GetWorldToScreen
end if
if used RLAPI.GetWorldToScreenEx
	extrn 'GetWorldToScreenEx' as RLAPI.GetWorldToScreenEx
end if
if used RLAPI.GetWorldToScreen2D
	extrn 'GetWorldToScreen2D' as RLAPI.GetWorldToScreen2D
end if
if used RLAPI.GetScreenToWorld2D
	extrn 'GetScreenToWorld2D' as RLAPI.GetScreenToWorld2D
end if
if used RLAPI.GetCameraMatrix
	extrn 'GetCameraMatrix' as RLAPI.GetCameraMatrix
end if
if used RLAPI.GetCameraMatrix2D
	extrn 'GetCameraMatrix2D' as RLAPI.GetCameraMatrix2D
end if
if used RLAPI.SetTargetFPS
	extrn 'SetTargetFPS' as RLAPI.SetTargetFPS
end if
if used RLAPI.GetFrameTime
	extrn 'GetFrameTime' as RLAPI.GetFrameTime
end if
if used RLAPI.GetTime
	extrn 'GetTime' as RLAPI.GetTime
end if
if used RLAPI.GetFPS
	extrn 'GetFPS' as RLAPI.GetFPS
end if
if used RLAPI.SwapScreenBuffer
	extrn 'SwapScreenBuffer' as RLAPI.SwapScreenBuffer
end if
if used RLAPI.PollInputEvents
	extrn 'PollInputEvents' as RLAPI.PollInputEvents
end if
if used RLAPI.WaitTime
	extrn 'WaitTime' as RLAPI.WaitTime
end if
if used RLAPI.SetRandomSeed
	extrn 'SetRandomSeed' as RLAPI.SetRandomSeed
end if
if used RLAPI.GetRandomValue
	extrn 'GetRandomValue' as RLAPI.GetRandomValue
end if
if used RLAPI.LoadRandomSequence
	extrn 'LoadRandomSequence' as RLAPI.LoadRandomSequence
end if
if used RLAPI.UnloadRandomSequence
	extrn 'UnloadRandomSequence' as RLAPI.UnloadRandomSequence
end if
if used RLAPI.TakeScreenshot
	extrn 'TakeScreenshot' as RLAPI.TakeScreenshot
end if
if used RLAPI.SetConfigFlags
	extrn 'SetConfigFlags' as RLAPI.SetConfigFlags
end if
if used RLAPI.OpenURL
	extrn 'OpenURL' as RLAPI.OpenURL
end if
if used RLAPI.SetTraceLogLevel
	extrn 'SetTraceLogLevel' as RLAPI.SetTraceLogLevel
end if
if used RLAPI.TraceLog
	extrn 'TraceLog' as RLAPI.TraceLog
end if
if used RLAPI.SetTraceLogCallback
	extrn 'SetTraceLogCallback' as RLAPI.SetTraceLogCallback
end if
if used RLAPI.MemAlloc
	extrn 'MemAlloc' as RLAPI.MemAlloc
end if
if used RLAPI.MemRealloc
	extrn 'MemRealloc' as RLAPI.MemRealloc
end if
if used RLAPI.MemFree
	extrn 'MemFree' as RLAPI.MemFree
end if
if used RLAPI.LoadFileData
	extrn 'LoadFileData' as RLAPI.LoadFileData
end if
if used RLAPI.UnloadFileData
	extrn 'UnloadFileData' as RLAPI.UnloadFileData
end if
if used RLAPI.SaveFileData
	extrn 'SaveFileData' as RLAPI.SaveFileData
end if
if used RLAPI.ExportDataAsCode
	extrn 'ExportDataAsCode' as RLAPI.ExportDataAsCode
end if
if used RLAPI.LoadFileText
	extrn 'LoadFileText' as RLAPI.LoadFileText
end if
if used RLAPI.UnloadFileText
	extrn 'UnloadFileText' as RLAPI.UnloadFileText
end if
if used RLAPI.SaveFileText
	extrn 'SaveFileText' as RLAPI.SaveFileText
end if
if used RLAPI.SetLoadFileDataCallback
	extrn 'SetLoadFileDataCallback' as RLAPI.SetLoadFileDataCallback
end if
if used RLAPI.SetSaveFileDataCallback
	extrn 'SetSaveFileDataCallback' as RLAPI.SetSaveFileDataCallback
end if
if used RLAPI.SetLoadFileTextCallback
	extrn 'SetLoadFileTextCallback' as RLAPI.SetLoadFileTextCallback
end if
if used RLAPI.SetSaveFileTextCallback
	extrn 'SetSaveFileTextCallback' as RLAPI.SetSaveFileTextCallback
end if
if used RLAPI.FileRename
	extrn 'FileRename' as RLAPI.FileRename
end if
if used RLAPI.FileRemove
	extrn 'FileRemove' as RLAPI.FileRemove
end if
if used RLAPI.FileCopy
	extrn 'FileCopy' as RLAPI.FileCopy
end if
if used RLAPI.FileMove
	extrn 'FileMove' as RLAPI.FileMove
end if
if used RLAPI.FileTextReplace
	extrn 'FileTextReplace' as RLAPI.FileTextReplace
end if
if used RLAPI.FileTextFindIndex
	extrn 'FileTextFindIndex' as RLAPI.FileTextFindIndex
end if
if used RLAPI.FileExists
	extrn 'FileExists' as RLAPI.FileExists
end if
if used RLAPI.DirectoryExists
	extrn 'DirectoryExists' as RLAPI.DirectoryExists
end if
if used RLAPI.IsFileExtension
	extrn 'IsFileExtension' as RLAPI.IsFileExtension
end if
if used RLAPI.GetFileLength
	extrn 'GetFileLength' as RLAPI.GetFileLength
end if
if used RLAPI.GetFileModTime
	extrn 'GetFileModTime' as RLAPI.GetFileModTime
end if
if used RLAPI.GetFileExtension
	extrn 'GetFileExtension' as RLAPI.GetFileExtension
end if
if used RLAPI.GetFileName
	extrn 'GetFileName' as RLAPI.GetFileName
end if
if used RLAPI.GetFileNameWithoutExt
	extrn 'GetFileNameWithoutExt' as RLAPI.GetFileNameWithoutExt
end if
if used RLAPI.GetDirectoryPath
	extrn 'GetDirectoryPath' as RLAPI.GetDirectoryPath
end if
if used RLAPI.GetPrevDirectoryPath
	extrn 'GetPrevDirectoryPath' as RLAPI.GetPrevDirectoryPath
end if
if used RLAPI.GetWorkingDirectory
	extrn 'GetWorkingDirectory' as RLAPI.GetWorkingDirectory
end if
if used RLAPI.GetApplicationDirectory
	extrn 'GetApplicationDirectory' as RLAPI.GetApplicationDirectory
end if
if used RLAPI.MakeDirectory
	extrn 'MakeDirectory' as RLAPI.MakeDirectory
end if
if used RLAPI.ChangeDirectory
	extrn 'ChangeDirectory' as RLAPI.ChangeDirectory
end if
if used RLAPI.IsPathFile
	extrn 'IsPathFile' as RLAPI.IsPathFile
end if
if used RLAPI.IsFileNameValid
	extrn 'IsFileNameValid' as RLAPI.IsFileNameValid
end if
if used RLAPI.LoadDirectoryFiles
	extrn 'LoadDirectoryFiles' as RLAPI.LoadDirectoryFiles
end if
if used RLAPI.LoadDirectoryFilesEx
	extrn 'LoadDirectoryFilesEx' as RLAPI.LoadDirectoryFilesEx
end if
if used RLAPI.UnloadDirectoryFiles
	extrn 'UnloadDirectoryFiles' as RLAPI.UnloadDirectoryFiles
end if
if used RLAPI.IsFileDropped
	extrn 'IsFileDropped' as RLAPI.IsFileDropped
end if
if used RLAPI.LoadDroppedFiles
	extrn 'LoadDroppedFiles' as RLAPI.LoadDroppedFiles
end if
if used RLAPI.UnloadDroppedFiles
	extrn 'UnloadDroppedFiles' as RLAPI.UnloadDroppedFiles
end if
if used RLAPI.GetDirectoryFileCount
	extrn 'GetDirectoryFileCount' as RLAPI.GetDirectoryFileCount
end if
if used RLAPI.GetDirectoryFileCountEx
	extrn 'GetDirectoryFileCountEx' as RLAPI.GetDirectoryFileCountEx
end if
if used RLAPI.CompressData
	extrn 'CompressData' as RLAPI.CompressData
end if
if used RLAPI.DecompressData
	extrn 'DecompressData' as RLAPI.DecompressData
end if
if used RLAPI.EncodeDataBase64
	extrn 'EncodeDataBase64' as RLAPI.EncodeDataBase64
end if
if used RLAPI.DecodeDataBase64
	extrn 'DecodeDataBase64' as RLAPI.DecodeDataBase64
end if
if used RLAPI.ComputeCRC32
	extrn 'ComputeCRC32' as RLAPI.ComputeCRC32
end if
if used RLAPI.ComputeMD5
	extrn 'ComputeMD5' as RLAPI.ComputeMD5
end if
if used RLAPI.ComputeSHA1
	extrn 'ComputeSHA1' as RLAPI.ComputeSHA1
end if
if used RLAPI.ComputeSHA256
	extrn 'ComputeSHA256' as RLAPI.ComputeSHA256
end if
if used RLAPI.LoadAutomationEventList
	extrn 'LoadAutomationEventList' as RLAPI.LoadAutomationEventList
end if
if used RLAPI.UnloadAutomationEventList
	extrn 'UnloadAutomationEventList' as RLAPI.UnloadAutomationEventList
end if
if used RLAPI.ExportAutomationEventList
	extrn 'ExportAutomationEventList' as RLAPI.ExportAutomationEventList
end if
if used RLAPI.SetAutomationEventList
	extrn 'SetAutomationEventList' as RLAPI.SetAutomationEventList
end if
if used RLAPI.SetAutomationEventBaseFrame
	extrn 'SetAutomationEventBaseFrame' as RLAPI.SetAutomationEventBaseFrame
end if
if used RLAPI.StartAutomationEventRecording
	extrn 'StartAutomationEventRecording' as RLAPI.StartAutomationEventRecording
end if
if used RLAPI.StopAutomationEventRecording
	extrn 'StopAutomationEventRecording' as RLAPI.StopAutomationEventRecording
end if
if used RLAPI.PlayAutomationEvent
	extrn 'PlayAutomationEvent' as RLAPI.PlayAutomationEvent
end if
if used RLAPI.IsKeyPressed
	extrn 'IsKeyPressed' as RLAPI.IsKeyPressed
end if
if used RLAPI.IsKeyPressedRepeat
	extrn 'IsKeyPressedRepeat' as RLAPI.IsKeyPressedRepeat
end if
if used RLAPI.IsKeyDown
	extrn 'IsKeyDown' as RLAPI.IsKeyDown
end if
if used RLAPI.IsKeyReleased
	extrn 'IsKeyReleased' as RLAPI.IsKeyReleased
end if
if used RLAPI.IsKeyUp
	extrn 'IsKeyUp' as RLAPI.IsKeyUp
end if
if used RLAPI.GetKeyPressed
	extrn 'GetKeyPressed' as RLAPI.GetKeyPressed
end if
if used RLAPI.GetCharPressed
	extrn 'GetCharPressed' as RLAPI.GetCharPressed
end if
if used RLAPI.GetKeyName
	extrn 'GetKeyName' as RLAPI.GetKeyName
end if
if used RLAPI.SetExitKey
	extrn 'SetExitKey' as RLAPI.SetExitKey
end if
if used RLAPI.IsGamepadAvailable
	extrn 'IsGamepadAvailable' as RLAPI.IsGamepadAvailable
end if
if used RLAPI.GetGamepadName
	extrn 'GetGamepadName' as RLAPI.GetGamepadName
end if
if used RLAPI.IsGamepadButtonPressed
	extrn 'IsGamepadButtonPressed' as RLAPI.IsGamepadButtonPressed
end if
if used RLAPI.IsGamepadButtonDown
	extrn 'IsGamepadButtonDown' as RLAPI.IsGamepadButtonDown
end if
if used RLAPI.IsGamepadButtonReleased
	extrn 'IsGamepadButtonReleased' as RLAPI.IsGamepadButtonReleased
end if
if used RLAPI.IsGamepadButtonUp
	extrn 'IsGamepadButtonUp' as RLAPI.IsGamepadButtonUp
end if
if used RLAPI.GetGamepadButtonPressed
	extrn 'GetGamepadButtonPressed' as RLAPI.GetGamepadButtonPressed
end if
if used RLAPI.GetGamepadAxisCount
	extrn 'GetGamepadAxisCount' as RLAPI.GetGamepadAxisCount
end if
if used RLAPI.GetGamepadAxisMovement
	extrn 'GetGamepadAxisMovement' as RLAPI.GetGamepadAxisMovement
end if
if used RLAPI.SetGamepadMappings
	extrn 'SetGamepadMappings' as RLAPI.SetGamepadMappings
end if
if used RLAPI.SetGamepadVibration
	extrn 'SetGamepadVibration' as RLAPI.SetGamepadVibration
end if
if used RLAPI.IsMouseButtonPressed
	extrn 'IsMouseButtonPressed' as RLAPI.IsMouseButtonPressed
end if
if used RLAPI.IsMouseButtonDown
	extrn 'IsMouseButtonDown' as RLAPI.IsMouseButtonDown
end if
if used RLAPI.IsMouseButtonReleased
	extrn 'IsMouseButtonReleased' as RLAPI.IsMouseButtonReleased
end if
if used RLAPI.IsMouseButtonUp
	extrn 'IsMouseButtonUp' as RLAPI.IsMouseButtonUp
end if
if used RLAPI.GetMouseX
	extrn 'GetMouseX' as RLAPI.GetMouseX
end if
if used RLAPI.GetMouseY
	extrn 'GetMouseY' as RLAPI.GetMouseY
end if
if used RLAPI.GetMousePosition
	extrn 'GetMousePosition' as RLAPI.GetMousePosition
end if
if used RLAPI.GetMouseDelta
	extrn 'GetMouseDelta' as RLAPI.GetMouseDelta
end if
if used RLAPI.SetMousePosition
	extrn 'SetMousePosition' as RLAPI.SetMousePosition
end if
if used RLAPI.SetMouseOffset
	extrn 'SetMouseOffset' as RLAPI.SetMouseOffset
end if
if used RLAPI.SetMouseScale
	extrn 'SetMouseScale' as RLAPI.SetMouseScale
end if
if used RLAPI.GetMouseWheelMove
	extrn 'GetMouseWheelMove' as RLAPI.GetMouseWheelMove
end if
if used RLAPI.GetMouseWheelMoveV
	extrn 'GetMouseWheelMoveV' as RLAPI.GetMouseWheelMoveV
end if
if used RLAPI.SetMouseCursor
	extrn 'SetMouseCursor' as RLAPI.SetMouseCursor
end if
if used RLAPI.GetTouchX
	extrn 'GetTouchX' as RLAPI.GetTouchX
end if
if used RLAPI.GetTouchY
	extrn 'GetTouchY' as RLAPI.GetTouchY
end if
if used RLAPI.GetTouchPosition
	extrn 'GetTouchPosition' as RLAPI.GetTouchPosition
end if
if used RLAPI.GetTouchPointId
	extrn 'GetTouchPointId' as RLAPI.GetTouchPointId
end if
if used RLAPI.GetTouchPointCount
	extrn 'GetTouchPointCount' as RLAPI.GetTouchPointCount
end if
if used RLAPI.SetGesturesEnabled
	extrn 'SetGesturesEnabled' as RLAPI.SetGesturesEnabled
end if
if used RLAPI.IsGestureDetected
	extrn 'IsGestureDetected' as RLAPI.IsGestureDetected
end if
if used RLAPI.GetGestureDetected
	extrn 'GetGestureDetected' as RLAPI.GetGestureDetected
end if
if used RLAPI.GetGestureHoldDuration
	extrn 'GetGestureHoldDuration' as RLAPI.GetGestureHoldDuration
end if
if used RLAPI.GetGestureDragVector
	extrn 'GetGestureDragVector' as RLAPI.GetGestureDragVector
end if
if used RLAPI.GetGestureDragAngle
	extrn 'GetGestureDragAngle' as RLAPI.GetGestureDragAngle
end if
if used RLAPI.GetGesturePinchVector
	extrn 'GetGesturePinchVector' as RLAPI.GetGesturePinchVector
end if
if used RLAPI.GetGesturePinchAngle
	extrn 'GetGesturePinchAngle' as RLAPI.GetGesturePinchAngle
end if
if used RLAPI.UpdateCamera
	extrn 'UpdateCamera' as RLAPI.UpdateCamera
end if
if used RLAPI.UpdateCameraPro
	extrn 'UpdateCameraPro' as RLAPI.UpdateCameraPro
end if
if used RLAPI.SetShapesTexture
	extrn 'SetShapesTexture' as RLAPI.SetShapesTexture
end if
if used RLAPI.GetShapesTexture
	extrn 'GetShapesTexture' as RLAPI.GetShapesTexture
end if
if used RLAPI.GetShapesTextureRectangle
	extrn 'GetShapesTextureRectangle' as RLAPI.GetShapesTextureRectangle
end if
if used RLAPI.DrawPixel
	extrn 'DrawPixel' as RLAPI.DrawPixel
end if
if used RLAPI.DrawPixelV
	extrn 'DrawPixelV' as RLAPI.DrawPixelV
end if
if used RLAPI.DrawLine
	extrn 'DrawLine' as RLAPI.DrawLine
end if
if used RLAPI.DrawLineV
	extrn 'DrawLineV' as RLAPI.DrawLineV
end if
if used RLAPI.DrawLineEx
	extrn 'DrawLineEx' as RLAPI.DrawLineEx
end if
if used RLAPI.DrawLineStrip
	extrn 'DrawLineStrip' as RLAPI.DrawLineStrip
end if
if used RLAPI.DrawLineBezier
	extrn 'DrawLineBezier' as RLAPI.DrawLineBezier
end if
if used RLAPI.DrawLineDashed
	extrn 'DrawLineDashed' as RLAPI.DrawLineDashed
end if
if used RLAPI.DrawCircle
	extrn 'DrawCircle' as RLAPI.DrawCircle
end if
if used RLAPI.DrawCircleV
	extrn 'DrawCircleV' as RLAPI.DrawCircleV
end if
if used RLAPI.DrawCircleGradient
	extrn 'DrawCircleGradient' as RLAPI.DrawCircleGradient
end if
if used RLAPI.DrawCircleSector
	extrn 'DrawCircleSector' as RLAPI.DrawCircleSector
end if
if used RLAPI.DrawCircleSectorLines
	extrn 'DrawCircleSectorLines' as RLAPI.DrawCircleSectorLines
end if
if used RLAPI.DrawCircleLines
	extrn 'DrawCircleLines' as RLAPI.DrawCircleLines
end if
if used RLAPI.DrawCircleLinesV
	extrn 'DrawCircleLinesV' as RLAPI.DrawCircleLinesV
end if
if used RLAPI.DrawEllipse
	extrn 'DrawEllipse' as RLAPI.DrawEllipse
end if
if used RLAPI.DrawEllipseV
	extrn 'DrawEllipseV' as RLAPI.DrawEllipseV
end if
if used RLAPI.DrawEllipseLines
	extrn 'DrawEllipseLines' as RLAPI.DrawEllipseLines
end if
if used RLAPI.DrawEllipseLinesV
	extrn 'DrawEllipseLinesV' as RLAPI.DrawEllipseLinesV
end if
if used RLAPI.DrawRing
	extrn 'DrawRing' as RLAPI.DrawRing
end if
if used RLAPI.DrawRingLines
	extrn 'DrawRingLines' as RLAPI.DrawRingLines
end if
if used RLAPI.DrawRectangle
	extrn 'DrawRectangle' as RLAPI.DrawRectangle
end if
if used RLAPI.DrawRectangleV
	extrn 'DrawRectangleV' as RLAPI.DrawRectangleV
end if
if used RLAPI.DrawRectangleRec
	extrn 'DrawRectangleRec' as RLAPI.DrawRectangleRec
end if
if used RLAPI.DrawRectanglePro
	extrn 'DrawRectanglePro' as RLAPI.DrawRectanglePro
end if
if used RLAPI.DrawRectangleGradientV
	extrn 'DrawRectangleGradientV' as RLAPI.DrawRectangleGradientV
end if
if used RLAPI.DrawRectangleGradientH
	extrn 'DrawRectangleGradientH' as RLAPI.DrawRectangleGradientH
end if
if used RLAPI.DrawRectangleGradientEx
	extrn 'DrawRectangleGradientEx' as RLAPI.DrawRectangleGradientEx
end if
if used RLAPI.DrawRectangleLines
	extrn 'DrawRectangleLines' as RLAPI.DrawRectangleLines
end if
if used RLAPI.DrawRectangleLinesEx
	extrn 'DrawRectangleLinesEx' as RLAPI.DrawRectangleLinesEx
end if
if used RLAPI.DrawRectangleRounded
	extrn 'DrawRectangleRounded' as RLAPI.DrawRectangleRounded
end if
if used RLAPI.DrawRectangleRoundedLines
	extrn 'DrawRectangleRoundedLines' as RLAPI.DrawRectangleRoundedLines
end if
if used RLAPI.DrawRectangleRoundedLinesEx
	extrn 'DrawRectangleRoundedLinesEx' as RLAPI.DrawRectangleRoundedLinesEx
end if
if used RLAPI.DrawTriangle
	extrn 'DrawTriangle' as RLAPI.DrawTriangle
end if
if used RLAPI.DrawTriangleLines
	extrn 'DrawTriangleLines' as RLAPI.DrawTriangleLines
end if
if used RLAPI.DrawTriangleFan
	extrn 'DrawTriangleFan' as RLAPI.DrawTriangleFan
end if
if used RLAPI.DrawTriangleStrip
	extrn 'DrawTriangleStrip' as RLAPI.DrawTriangleStrip
end if
if used RLAPI.DrawPoly
	extrn 'DrawPoly' as RLAPI.DrawPoly
end if
if used RLAPI.DrawPolyLines
	extrn 'DrawPolyLines' as RLAPI.DrawPolyLines
end if
if used RLAPI.DrawPolyLinesEx
	extrn 'DrawPolyLinesEx' as RLAPI.DrawPolyLinesEx
end if
if used RLAPI.DrawSplineLinear
	extrn 'DrawSplineLinear' as RLAPI.DrawSplineLinear
end if
if used RLAPI.DrawSplineBasis
	extrn 'DrawSplineBasis' as RLAPI.DrawSplineBasis
end if
if used RLAPI.DrawSplineCatmullRom
	extrn 'DrawSplineCatmullRom' as RLAPI.DrawSplineCatmullRom
end if
if used RLAPI.DrawSplineBezierQuadratic
	extrn 'DrawSplineBezierQuadratic' as RLAPI.DrawSplineBezierQuadratic
end if
if used RLAPI.DrawSplineBezierCubic
	extrn 'DrawSplineBezierCubic' as RLAPI.DrawSplineBezierCubic
end if
if used RLAPI.DrawSplineSegmentLinear
	extrn 'DrawSplineSegmentLinear' as RLAPI.DrawSplineSegmentLinear
end if
if used RLAPI.DrawSplineSegmentBasis
	extrn 'DrawSplineSegmentBasis' as RLAPI.DrawSplineSegmentBasis
end if
if used RLAPI.DrawSplineSegmentCatmullRom
	extrn 'DrawSplineSegmentCatmullRom' as RLAPI.DrawSplineSegmentCatmullRom
end if
if used RLAPI.DrawSplineSegmentBezierQuadratic
	extrn 'DrawSplineSegmentBezierQuadratic' as RLAPI.DrawSplineSegmentBezierQuadratic
end if
if used RLAPI.DrawSplineSegmentBezierCubic
	extrn 'DrawSplineSegmentBezierCubic' as RLAPI.DrawSplineSegmentBezierCubic
end if
if used RLAPI.GetSplinePointLinear
	extrn 'GetSplinePointLinear' as RLAPI.GetSplinePointLinear
end if
if used RLAPI.GetSplinePointBasis
	extrn 'GetSplinePointBasis' as RLAPI.GetSplinePointBasis
end if
if used RLAPI.GetSplinePointCatmullRom
	extrn 'GetSplinePointCatmullRom' as RLAPI.GetSplinePointCatmullRom
end if
if used RLAPI.GetSplinePointBezierQuad
	extrn 'GetSplinePointBezierQuad' as RLAPI.GetSplinePointBezierQuad
end if
if used RLAPI.GetSplinePointBezierCubic
	extrn 'GetSplinePointBezierCubic' as RLAPI.GetSplinePointBezierCubic
end if
if used RLAPI.CheckCollisionRecs
	extrn 'CheckCollisionRecs' as RLAPI.CheckCollisionRecs
end if
if used RLAPI.CheckCollisionCircles
	extrn 'CheckCollisionCircles' as RLAPI.CheckCollisionCircles
end if
if used RLAPI.CheckCollisionCircleRec
	extrn 'CheckCollisionCircleRec' as RLAPI.CheckCollisionCircleRec
end if
if used RLAPI.CheckCollisionCircleLine
	extrn 'CheckCollisionCircleLine' as RLAPI.CheckCollisionCircleLine
end if
if used RLAPI.CheckCollisionPointRec
	extrn 'CheckCollisionPointRec' as RLAPI.CheckCollisionPointRec
end if
if used RLAPI.CheckCollisionPointCircle
	extrn 'CheckCollisionPointCircle' as RLAPI.CheckCollisionPointCircle
end if
if used RLAPI.CheckCollisionPointTriangle
	extrn 'CheckCollisionPointTriangle' as RLAPI.CheckCollisionPointTriangle
end if
if used RLAPI.CheckCollisionPointLine
	extrn 'CheckCollisionPointLine' as RLAPI.CheckCollisionPointLine
end if
if used RLAPI.CheckCollisionPointPoly
	extrn 'CheckCollisionPointPoly' as RLAPI.CheckCollisionPointPoly
end if
if used RLAPI.CheckCollisionLines
	extrn 'CheckCollisionLines' as RLAPI.CheckCollisionLines
end if
if used RLAPI.GetCollisionRec
	extrn 'GetCollisionRec' as RLAPI.GetCollisionRec
end if
if used RLAPI.LoadImage
	extrn 'LoadImage' as RLAPI.LoadImage
end if
if used RLAPI.LoadImageRaw
	extrn 'LoadImageRaw' as RLAPI.LoadImageRaw
end if
if used RLAPI.LoadImageAnim
	extrn 'LoadImageAnim' as RLAPI.LoadImageAnim
end if
if used RLAPI.LoadImageAnimFromMemory
	extrn 'LoadImageAnimFromMemory' as RLAPI.LoadImageAnimFromMemory
end if
if used RLAPI.LoadImageFromMemory
	extrn 'LoadImageFromMemory' as RLAPI.LoadImageFromMemory
end if
if used RLAPI.LoadImageFromTexture
	extrn 'LoadImageFromTexture' as RLAPI.LoadImageFromTexture
end if
if used RLAPI.LoadImageFromScreen
	extrn 'LoadImageFromScreen' as RLAPI.LoadImageFromScreen
end if
if used RLAPI.IsImageValid
	extrn 'IsImageValid' as RLAPI.IsImageValid
end if
if used RLAPI.UnloadImage
	extrn 'UnloadImage' as RLAPI.UnloadImage
end if
if used RLAPI.ExportImage
	extrn 'ExportImage' as RLAPI.ExportImage
end if
if used RLAPI.ExportImageToMemory
	extrn 'ExportImageToMemory' as RLAPI.ExportImageToMemory
end if
if used RLAPI.ExportImageAsCode
	extrn 'ExportImageAsCode' as RLAPI.ExportImageAsCode
end if
if used RLAPI.GenImageColor
	extrn 'GenImageColor' as RLAPI.GenImageColor
end if
if used RLAPI.GenImageGradientLinear
	extrn 'GenImageGradientLinear' as RLAPI.GenImageGradientLinear
end if
if used RLAPI.GenImageGradientRadial
	extrn 'GenImageGradientRadial' as RLAPI.GenImageGradientRadial
end if
if used RLAPI.GenImageGradientSquare
	extrn 'GenImageGradientSquare' as RLAPI.GenImageGradientSquare
end if
if used RLAPI.GenImageChecked
	extrn 'GenImageChecked' as RLAPI.GenImageChecked
end if
if used RLAPI.GenImageWhiteNoise
	extrn 'GenImageWhiteNoise' as RLAPI.GenImageWhiteNoise
end if
if used RLAPI.GenImagePerlinNoise
	extrn 'GenImagePerlinNoise' as RLAPI.GenImagePerlinNoise
end if
if used RLAPI.GenImageCellular
	extrn 'GenImageCellular' as RLAPI.GenImageCellular
end if
if used RLAPI.GenImageText
	extrn 'GenImageText' as RLAPI.GenImageText
end if
if used RLAPI.ImageCopy
	extrn 'ImageCopy' as RLAPI.ImageCopy
end if
if used RLAPI.ImageFromImage
	extrn 'ImageFromImage' as RLAPI.ImageFromImage
end if
if used RLAPI.ImageFromChannel
	extrn 'ImageFromChannel' as RLAPI.ImageFromChannel
end if
if used RLAPI.ImageText
	extrn 'ImageText' as RLAPI.ImageText
end if
if used RLAPI.ImageTextEx
	extrn 'ImageTextEx' as RLAPI.ImageTextEx
end if
if used RLAPI.ImageFormat
	extrn 'ImageFormat' as RLAPI.ImageFormat
end if
if used RLAPI.ImageToPOT
	extrn 'ImageToPOT' as RLAPI.ImageToPOT
end if
if used RLAPI.ImageCrop
	extrn 'ImageCrop' as RLAPI.ImageCrop
end if
if used RLAPI.ImageAlphaCrop
	extrn 'ImageAlphaCrop' as RLAPI.ImageAlphaCrop
end if
if used RLAPI.ImageAlphaClear
	extrn 'ImageAlphaClear' as RLAPI.ImageAlphaClear
end if
if used RLAPI.ImageAlphaMask
	extrn 'ImageAlphaMask' as RLAPI.ImageAlphaMask
end if
if used RLAPI.ImageAlphaPremultiply
	extrn 'ImageAlphaPremultiply' as RLAPI.ImageAlphaPremultiply
end if
if used RLAPI.ImageBlurGaussian
	extrn 'ImageBlurGaussian' as RLAPI.ImageBlurGaussian
end if
if used RLAPI.ImageKernelConvolution
	extrn 'ImageKernelConvolution' as RLAPI.ImageKernelConvolution
end if
if used RLAPI.ImageResize
	extrn 'ImageResize' as RLAPI.ImageResize
end if
if used RLAPI.ImageResizeNN
	extrn 'ImageResizeNN' as RLAPI.ImageResizeNN
end if
if used RLAPI.ImageResizeCanvas
	extrn 'ImageResizeCanvas' as RLAPI.ImageResizeCanvas
end if
if used RLAPI.ImageMipmaps
	extrn 'ImageMipmaps' as RLAPI.ImageMipmaps
end if
if used RLAPI.ImageDither
	extrn 'ImageDither' as RLAPI.ImageDither
end if
if used RLAPI.ImageFlipVertical
	extrn 'ImageFlipVertical' as RLAPI.ImageFlipVertical
end if
if used RLAPI.ImageFlipHorizontal
	extrn 'ImageFlipHorizontal' as RLAPI.ImageFlipHorizontal
end if
if used RLAPI.ImageRotate
	extrn 'ImageRotate' as RLAPI.ImageRotate
end if
if used RLAPI.ImageRotateCW
	extrn 'ImageRotateCW' as RLAPI.ImageRotateCW
end if
if used RLAPI.ImageRotateCCW
	extrn 'ImageRotateCCW' as RLAPI.ImageRotateCCW
end if
if used RLAPI.ImageColorTint
	extrn 'ImageColorTint' as RLAPI.ImageColorTint
end if
if used RLAPI.ImageColorInvert
	extrn 'ImageColorInvert' as RLAPI.ImageColorInvert
end if
if used RLAPI.ImageColorGrayscale
	extrn 'ImageColorGrayscale' as RLAPI.ImageColorGrayscale
end if
if used RLAPI.ImageColorContrast
	extrn 'ImageColorContrast' as RLAPI.ImageColorContrast
end if
if used RLAPI.ImageColorBrightness
	extrn 'ImageColorBrightness' as RLAPI.ImageColorBrightness
end if
if used RLAPI.ImageColorReplace
	extrn 'ImageColorReplace' as RLAPI.ImageColorReplace
end if
if used RLAPI.LoadImageColors
	extrn 'LoadImageColors' as RLAPI.LoadImageColors
end if
if used RLAPI.LoadImagePalette
	extrn 'LoadImagePalette' as RLAPI.LoadImagePalette
end if
if used RLAPI.UnloadImageColors
	extrn 'UnloadImageColors' as RLAPI.UnloadImageColors
end if
if used RLAPI.UnloadImagePalette
	extrn 'UnloadImagePalette' as RLAPI.UnloadImagePalette
end if
if used RLAPI.GetImageAlphaBorder
	extrn 'GetImageAlphaBorder' as RLAPI.GetImageAlphaBorder
end if
if used RLAPI.GetImageColor
	extrn 'GetImageColor' as RLAPI.GetImageColor
end if
if used RLAPI.ImageClearBackground
	extrn 'ImageClearBackground' as RLAPI.ImageClearBackground
end if
if used RLAPI.ImageDrawPixel
	extrn 'ImageDrawPixel' as RLAPI.ImageDrawPixel
end if
if used RLAPI.ImageDrawPixelV
	extrn 'ImageDrawPixelV' as RLAPI.ImageDrawPixelV
end if
if used RLAPI.ImageDrawLine
	extrn 'ImageDrawLine' as RLAPI.ImageDrawLine
end if
if used RLAPI.ImageDrawLineV
	extrn 'ImageDrawLineV' as RLAPI.ImageDrawLineV
end if
if used RLAPI.ImageDrawLineEx
	extrn 'ImageDrawLineEx' as RLAPI.ImageDrawLineEx
end if
if used RLAPI.ImageDrawCircle
	extrn 'ImageDrawCircle' as RLAPI.ImageDrawCircle
end if
if used RLAPI.ImageDrawCircleV
	extrn 'ImageDrawCircleV' as RLAPI.ImageDrawCircleV
end if
if used RLAPI.ImageDrawCircleLines
	extrn 'ImageDrawCircleLines' as RLAPI.ImageDrawCircleLines
end if
if used RLAPI.ImageDrawCircleLinesV
	extrn 'ImageDrawCircleLinesV' as RLAPI.ImageDrawCircleLinesV
end if
if used RLAPI.ImageDrawRectangle
	extrn 'ImageDrawRectangle' as RLAPI.ImageDrawRectangle
end if
if used RLAPI.ImageDrawRectangleV
	extrn 'ImageDrawRectangleV' as RLAPI.ImageDrawRectangleV
end if
if used RLAPI.ImageDrawRectangleRec
	extrn 'ImageDrawRectangleRec' as RLAPI.ImageDrawRectangleRec
end if
if used RLAPI.ImageDrawRectangleLines
	extrn 'ImageDrawRectangleLines' as RLAPI.ImageDrawRectangleLines
end if
if used RLAPI.ImageDrawTriangle
	extrn 'ImageDrawTriangle' as RLAPI.ImageDrawTriangle
end if
if used RLAPI.ImageDrawTriangleEx
	extrn 'ImageDrawTriangleEx' as RLAPI.ImageDrawTriangleEx
end if
if used RLAPI.ImageDrawTriangleLines
	extrn 'ImageDrawTriangleLines' as RLAPI.ImageDrawTriangleLines
end if
if used RLAPI.ImageDrawTriangleFan
	extrn 'ImageDrawTriangleFan' as RLAPI.ImageDrawTriangleFan
end if
if used RLAPI.ImageDrawTriangleStrip
	extrn 'ImageDrawTriangleStrip' as RLAPI.ImageDrawTriangleStrip
end if
if used RLAPI.ImageDraw
	extrn 'ImageDraw' as RLAPI.ImageDraw
end if
if used RLAPI.ImageDrawText
	extrn 'ImageDrawText' as RLAPI.ImageDrawText
end if
if used RLAPI.ImageDrawTextEx
	extrn 'ImageDrawTextEx' as RLAPI.ImageDrawTextEx
end if
if used RLAPI.LoadTexture
	extrn 'LoadTexture' as RLAPI.LoadTexture
end if
if used RLAPI.LoadTextureFromImage
	extrn 'LoadTextureFromImage' as RLAPI.LoadTextureFromImage
end if
if used RLAPI.LoadTextureCubemap
	extrn 'LoadTextureCubemap' as RLAPI.LoadTextureCubemap
end if
if used RLAPI.LoadRenderTexture
	extrn 'LoadRenderTexture' as RLAPI.LoadRenderTexture
end if
if used RLAPI.IsTextureValid
	extrn 'IsTextureValid' as RLAPI.IsTextureValid
end if
if used RLAPI.UnloadTexture
	extrn 'UnloadTexture' as RLAPI.UnloadTexture
end if
if used RLAPI.IsRenderTextureValid
	extrn 'IsRenderTextureValid' as RLAPI.IsRenderTextureValid
end if
if used RLAPI.UnloadRenderTexture
	extrn 'UnloadRenderTexture' as RLAPI.UnloadRenderTexture
end if
if used RLAPI.UpdateTexture
	extrn 'UpdateTexture' as RLAPI.UpdateTexture
end if
if used RLAPI.UpdateTextureRec
	extrn 'UpdateTextureRec' as RLAPI.UpdateTextureRec
end if
if used RLAPI.GenTextureMipmaps
	extrn 'GenTextureMipmaps' as RLAPI.GenTextureMipmaps
end if
if used RLAPI.SetTextureFilter
	extrn 'SetTextureFilter' as RLAPI.SetTextureFilter
end if
if used RLAPI.SetTextureWrap
	extrn 'SetTextureWrap' as RLAPI.SetTextureWrap
end if
if used RLAPI.DrawTexture
	extrn 'DrawTexture' as RLAPI.DrawTexture
end if
if used RLAPI.DrawTextureV
	extrn 'DrawTextureV' as RLAPI.DrawTextureV
end if
if used RLAPI.DrawTextureEx
	extrn 'DrawTextureEx' as RLAPI.DrawTextureEx
end if
if used RLAPI.DrawTextureRec
	extrn 'DrawTextureRec' as RLAPI.DrawTextureRec
end if
if used RLAPI.DrawTexturePro
	extrn 'DrawTexturePro' as RLAPI.DrawTexturePro
end if
if used RLAPI.DrawTextureNPatch
	extrn 'DrawTextureNPatch' as RLAPI.DrawTextureNPatch
end if
if used RLAPI.ColorIsEqual
	extrn 'ColorIsEqual' as RLAPI.ColorIsEqual
end if
if used RLAPI.Fade
	extrn 'Fade' as RLAPI.Fade
end if
if used RLAPI.ColorToInt
	extrn 'ColorToInt' as RLAPI.ColorToInt
end if
if used RLAPI.ColorNormalize
	extrn 'ColorNormalize' as RLAPI.ColorNormalize
end if
if used RLAPI.ColorFromNormalized
	extrn 'ColorFromNormalized' as RLAPI.ColorFromNormalized
end if
if used RLAPI.ColorToHSV
	extrn 'ColorToHSV' as RLAPI.ColorToHSV
end if
if used RLAPI.ColorFromHSV
	extrn 'ColorFromHSV' as RLAPI.ColorFromHSV
end if
if used RLAPI.ColorTint
	extrn 'ColorTint' as RLAPI.ColorTint
end if
if used RLAPI.ColorBrightness
	extrn 'ColorBrightness' as RLAPI.ColorBrightness
end if
if used RLAPI.ColorContrast
	extrn 'ColorContrast' as RLAPI.ColorContrast
end if
if used RLAPI.ColorAlpha
	extrn 'ColorAlpha' as RLAPI.ColorAlpha
end if
if used RLAPI.ColorAlphaBlend
	extrn 'ColorAlphaBlend' as RLAPI.ColorAlphaBlend
end if
if used RLAPI.ColorLerp
	extrn 'ColorLerp' as RLAPI.ColorLerp
end if
if used RLAPI.GetColor
	extrn 'GetColor' as RLAPI.GetColor
end if
if used RLAPI.GetPixelColor
	extrn 'GetPixelColor' as RLAPI.GetPixelColor
end if
if used RLAPI.SetPixelColor
	extrn 'SetPixelColor' as RLAPI.SetPixelColor
end if
if used RLAPI.GetPixelDataSize
	extrn 'GetPixelDataSize' as RLAPI.GetPixelDataSize
end if
if used RLAPI.GetFontDefault
	extrn 'GetFontDefault' as RLAPI.GetFontDefault
end if
if used RLAPI.LoadFont
	extrn 'LoadFont' as RLAPI.LoadFont
end if
if used RLAPI.LoadFontEx
	extrn 'LoadFontEx' as RLAPI.LoadFontEx
end if
if used RLAPI.LoadFontFromImage
	extrn 'LoadFontFromImage' as RLAPI.LoadFontFromImage
end if
if used RLAPI.LoadFontFromMemory
	extrn 'LoadFontFromMemory' as RLAPI.LoadFontFromMemory
end if
if used RLAPI.IsFontValid
	extrn 'IsFontValid' as RLAPI.IsFontValid
end if
if used RLAPI.LoadFontData
	extrn 'LoadFontData' as RLAPI.LoadFontData
end if
if used RLAPI.GenImageFontAtlas
	extrn 'GenImageFontAtlas' as RLAPI.GenImageFontAtlas
end if
if used RLAPI.UnloadFontData
	extrn 'UnloadFontData' as RLAPI.UnloadFontData
end if
if used RLAPI.UnloadFont
	extrn 'UnloadFont' as RLAPI.UnloadFont
end if
if used RLAPI.ExportFontAsCode
	extrn 'ExportFontAsCode' as RLAPI.ExportFontAsCode
end if
if used RLAPI.DrawFPS
	extrn 'DrawFPS' as RLAPI.DrawFPS
end if
if used RLAPI.DrawText
	extrn 'DrawText' as RLAPI.DrawText
end if
if used RLAPI.DrawTextEx
	extrn 'DrawTextEx' as RLAPI.DrawTextEx
end if
if used RLAPI.DrawTextPro
	extrn 'DrawTextPro' as RLAPI.DrawTextPro
end if
if used RLAPI.DrawTextCodepoint
	extrn 'DrawTextCodepoint' as RLAPI.DrawTextCodepoint
end if
if used RLAPI.DrawTextCodepoints
	extrn 'DrawTextCodepoints' as RLAPI.DrawTextCodepoints
end if
if used RLAPI.SetTextLineSpacing
	extrn 'SetTextLineSpacing' as RLAPI.SetTextLineSpacing
end if
if used RLAPI.MeasureText
	extrn 'MeasureText' as RLAPI.MeasureText
end if
if used RLAPI.MeasureTextEx
	extrn 'MeasureTextEx' as RLAPI.MeasureTextEx
end if
if used RLAPI.MeasureTextCodepoints
	extrn 'MeasureTextCodepoints' as RLAPI.MeasureTextCodepoints
end if
if used RLAPI.GetGlyphIndex
	extrn 'GetGlyphIndex' as RLAPI.GetGlyphIndex
end if
if used RLAPI.GetGlyphInfo
	extrn 'GetGlyphInfo' as RLAPI.GetGlyphInfo
end if
if used RLAPI.GetGlyphAtlasRec
	extrn 'GetGlyphAtlasRec' as RLAPI.GetGlyphAtlasRec
end if
if used RLAPI.LoadUTF8
	extrn 'LoadUTF8' as RLAPI.LoadUTF8
end if
if used RLAPI.UnloadUTF8
	extrn 'UnloadUTF8' as RLAPI.UnloadUTF8
end if
if used RLAPI.LoadCodepoints
	extrn 'LoadCodepoints' as RLAPI.LoadCodepoints
end if
if used RLAPI.UnloadCodepoints
	extrn 'UnloadCodepoints' as RLAPI.UnloadCodepoints
end if
if used RLAPI.GetCodepointCount
	extrn 'GetCodepointCount' as RLAPI.GetCodepointCount
end if
if used RLAPI.GetCodepoint
	extrn 'GetCodepoint' as RLAPI.GetCodepoint
end if
if used RLAPI.GetCodepointNext
	extrn 'GetCodepointNext' as RLAPI.GetCodepointNext
end if
if used RLAPI.GetCodepointPrevious
	extrn 'GetCodepointPrevious' as RLAPI.GetCodepointPrevious
end if
if used RLAPI.CodepointToUTF8
	extrn 'CodepointToUTF8' as RLAPI.CodepointToUTF8
end if
if used RLAPI.LoadTextLines
	extrn 'LoadTextLines' as RLAPI.LoadTextLines
end if
if used RLAPI.UnloadTextLines
	extrn 'UnloadTextLines' as RLAPI.UnloadTextLines
end if
if used RLAPI.TextCopy
	extrn 'TextCopy' as RLAPI.TextCopy
end if
if used RLAPI.TextIsEqual
	extrn 'TextIsEqual' as RLAPI.TextIsEqual
end if
if used RLAPI.TextLength
	extrn 'TextLength' as RLAPI.TextLength
end if
if used RLAPI.TextFormat
	extrn 'TextFormat' as RLAPI.TextFormat
end if
if used RLAPI.TextSubtext
	extrn 'TextSubtext' as RLAPI.TextSubtext
end if
if used RLAPI.TextRemoveSpaces
	extrn 'TextRemoveSpaces' as RLAPI.TextRemoveSpaces
end if
if used RLAPI.GetTextBetween
	extrn 'GetTextBetween' as RLAPI.GetTextBetween
end if
if used RLAPI.TextReplace
	extrn 'TextReplace' as RLAPI.TextReplace
end if
if used RLAPI.TextReplaceAlloc
	extrn 'TextReplaceAlloc' as RLAPI.TextReplaceAlloc
end if
if used RLAPI.TextReplaceBetween
	extrn 'TextReplaceBetween' as RLAPI.TextReplaceBetween
end if
if used RLAPI.TextReplaceBetweenAlloc
	extrn 'TextReplaceBetweenAlloc' as RLAPI.TextReplaceBetweenAlloc
end if
if used RLAPI.TextInsert
	extrn 'TextInsert' as RLAPI.TextInsert
end if
if used RLAPI.TextInsertAlloc
	extrn 'TextInsertAlloc' as RLAPI.TextInsertAlloc
end if
if used RLAPI.TextJoin
	extrn 'TextJoin' as RLAPI.TextJoin
end if
if used RLAPI.TextSplit
	extrn 'TextSplit' as RLAPI.TextSplit
end if
if used RLAPI.TextAppend
	extrn 'TextAppend' as RLAPI.TextAppend
end if
if used RLAPI.TextFindIndex
	extrn 'TextFindIndex' as RLAPI.TextFindIndex
end if
if used RLAPI.TextToUpper
	extrn 'TextToUpper' as RLAPI.TextToUpper
end if
if used RLAPI.TextToLower
	extrn 'TextToLower' as RLAPI.TextToLower
end if
if used RLAPI.TextToPascal
	extrn 'TextToPascal' as RLAPI.TextToPascal
end if
if used RLAPI.TextToSnake
	extrn 'TextToSnake' as RLAPI.TextToSnake
end if
if used RLAPI.TextToCamel
	extrn 'TextToCamel' as RLAPI.TextToCamel
end if
if used RLAPI.TextToInteger
	extrn 'TextToInteger' as RLAPI.TextToInteger
end if
if used RLAPI.TextToFloat
	extrn 'TextToFloat' as RLAPI.TextToFloat
end if
if used RLAPI.DrawLine3D
	extrn 'DrawLine3D' as RLAPI.DrawLine3D
end if
if used RLAPI.DrawPoint3D
	extrn 'DrawPoint3D' as RLAPI.DrawPoint3D
end if
if used RLAPI.DrawCircle3D
	extrn 'DrawCircle3D' as RLAPI.DrawCircle3D
end if
if used RLAPI.DrawTriangle3D
	extrn 'DrawTriangle3D' as RLAPI.DrawTriangle3D
end if
if used RLAPI.DrawTriangleStrip3D
	extrn 'DrawTriangleStrip3D' as RLAPI.DrawTriangleStrip3D
end if
if used RLAPI.DrawCube
	extrn 'DrawCube' as RLAPI.DrawCube
end if
if used RLAPI.DrawCubeV
	extrn 'DrawCubeV' as RLAPI.DrawCubeV
end if
if used RLAPI.DrawCubeWires
	extrn 'DrawCubeWires' as RLAPI.DrawCubeWires
end if
if used RLAPI.DrawCubeWiresV
	extrn 'DrawCubeWiresV' as RLAPI.DrawCubeWiresV
end if
if used RLAPI.DrawSphere
	extrn 'DrawSphere' as RLAPI.DrawSphere
end if
if used RLAPI.DrawSphereEx
	extrn 'DrawSphereEx' as RLAPI.DrawSphereEx
end if
if used RLAPI.DrawSphereWires
	extrn 'DrawSphereWires' as RLAPI.DrawSphereWires
end if
if used RLAPI.DrawCylinder
	extrn 'DrawCylinder' as RLAPI.DrawCylinder
end if
if used RLAPI.DrawCylinderEx
	extrn 'DrawCylinderEx' as RLAPI.DrawCylinderEx
end if
if used RLAPI.DrawCylinderWires
	extrn 'DrawCylinderWires' as RLAPI.DrawCylinderWires
end if
if used RLAPI.DrawCylinderWiresEx
	extrn 'DrawCylinderWiresEx' as RLAPI.DrawCylinderWiresEx
end if
if used RLAPI.DrawCapsule
	extrn 'DrawCapsule' as RLAPI.DrawCapsule
end if
if used RLAPI.DrawCapsuleWires
	extrn 'DrawCapsuleWires' as RLAPI.DrawCapsuleWires
end if
if used RLAPI.DrawPlane
	extrn 'DrawPlane' as RLAPI.DrawPlane
end if
if used RLAPI.DrawRay
	extrn 'DrawRay' as RLAPI.DrawRay
end if
if used RLAPI.DrawGrid
	extrn 'DrawGrid' as RLAPI.DrawGrid
end if
if used RLAPI.LoadModel
	extrn 'LoadModel' as RLAPI.LoadModel
end if
if used RLAPI.LoadModelFromMesh
	extrn 'LoadModelFromMesh' as RLAPI.LoadModelFromMesh
end if
if used RLAPI.IsModelValid
	extrn 'IsModelValid' as RLAPI.IsModelValid
end if
if used RLAPI.UnloadModel
	extrn 'UnloadModel' as RLAPI.UnloadModel
end if
if used RLAPI.GetModelBoundingBox
	extrn 'GetModelBoundingBox' as RLAPI.GetModelBoundingBox
end if
if used RLAPI.DrawModel
	extrn 'DrawModel' as RLAPI.DrawModel
end if
if used RLAPI.DrawModelEx
	extrn 'DrawModelEx' as RLAPI.DrawModelEx
end if
if used RLAPI.DrawModelWires
	extrn 'DrawModelWires' as RLAPI.DrawModelWires
end if
if used RLAPI.DrawModelWiresEx
	extrn 'DrawModelWiresEx' as RLAPI.DrawModelWiresEx
end if
if used RLAPI.DrawBoundingBox
	extrn 'DrawBoundingBox' as RLAPI.DrawBoundingBox
end if
if used RLAPI.DrawBillboard
	extrn 'DrawBillboard' as RLAPI.DrawBillboard
end if
if used RLAPI.DrawBillboardRec
	extrn 'DrawBillboardRec' as RLAPI.DrawBillboardRec
end if
if used RLAPI.DrawBillboardPro
	extrn 'DrawBillboardPro' as RLAPI.DrawBillboardPro
end if
if used RLAPI.UploadMesh
	extrn 'UploadMesh' as RLAPI.UploadMesh
end if
if used RLAPI.UpdateMeshBuffer
	extrn 'UpdateMeshBuffer' as RLAPI.UpdateMeshBuffer
end if
if used RLAPI.UnloadMesh
	extrn 'UnloadMesh' as RLAPI.UnloadMesh
end if
if used RLAPI.DrawMesh
	extrn 'DrawMesh' as RLAPI.DrawMesh
end if
if used RLAPI.DrawMeshInstanced
	extrn 'DrawMeshInstanced' as RLAPI.DrawMeshInstanced
end if
if used RLAPI.GetMeshBoundingBox
	extrn 'GetMeshBoundingBox' as RLAPI.GetMeshBoundingBox
end if
if used RLAPI.GenMeshTangents
	extrn 'GenMeshTangents' as RLAPI.GenMeshTangents
end if
if used RLAPI.ExportMesh
	extrn 'ExportMesh' as RLAPI.ExportMesh
end if
if used RLAPI.ExportMeshAsCode
	extrn 'ExportMeshAsCode' as RLAPI.ExportMeshAsCode
end if
if used RLAPI.GenMeshPoly
	extrn 'GenMeshPoly' as RLAPI.GenMeshPoly
end if
if used RLAPI.GenMeshPlane
	extrn 'GenMeshPlane' as RLAPI.GenMeshPlane
end if
if used RLAPI.GenMeshCube
	extrn 'GenMeshCube' as RLAPI.GenMeshCube
end if
if used RLAPI.GenMeshSphere
	extrn 'GenMeshSphere' as RLAPI.GenMeshSphere
end if
if used RLAPI.GenMeshHemiSphere
	extrn 'GenMeshHemiSphere' as RLAPI.GenMeshHemiSphere
end if
if used RLAPI.GenMeshCylinder
	extrn 'GenMeshCylinder' as RLAPI.GenMeshCylinder
end if
if used RLAPI.GenMeshCone
	extrn 'GenMeshCone' as RLAPI.GenMeshCone
end if
if used RLAPI.GenMeshTorus
	extrn 'GenMeshTorus' as RLAPI.GenMeshTorus
end if
if used RLAPI.GenMeshKnot
	extrn 'GenMeshKnot' as RLAPI.GenMeshKnot
end if
if used RLAPI.GenMeshHeightmap
	extrn 'GenMeshHeightmap' as RLAPI.GenMeshHeightmap
end if
if used RLAPI.GenMeshCubicmap
	extrn 'GenMeshCubicmap' as RLAPI.GenMeshCubicmap
end if
if used RLAPI.LoadMaterials
	extrn 'LoadMaterials' as RLAPI.LoadMaterials
end if
if used RLAPI.LoadMaterialDefault
	extrn 'LoadMaterialDefault' as RLAPI.LoadMaterialDefault
end if
if used RLAPI.IsMaterialValid
	extrn 'IsMaterialValid' as RLAPI.IsMaterialValid
end if
if used RLAPI.UnloadMaterial
	extrn 'UnloadMaterial' as RLAPI.UnloadMaterial
end if
if used RLAPI.SetMaterialTexture
	extrn 'SetMaterialTexture' as RLAPI.SetMaterialTexture
end if
if used RLAPI.SetModelMeshMaterial
	extrn 'SetModelMeshMaterial' as RLAPI.SetModelMeshMaterial
end if
if used RLAPI.LoadModelAnimations
	extrn 'LoadModelAnimations' as RLAPI.LoadModelAnimations
end if
if used RLAPI.UpdateModelAnimation
	extrn 'UpdateModelAnimation' as RLAPI.UpdateModelAnimation
end if
if used RLAPI.UpdateModelAnimationEx
	extrn 'UpdateModelAnimationEx' as RLAPI.UpdateModelAnimationEx
end if
if used RLAPI.UnloadModelAnimations
	extrn 'UnloadModelAnimations' as RLAPI.UnloadModelAnimations
end if
if used RLAPI.IsModelAnimationValid
	extrn 'IsModelAnimationValid' as RLAPI.IsModelAnimationValid
end if
if used RLAPI.CheckCollisionSpheres
	extrn 'CheckCollisionSpheres' as RLAPI.CheckCollisionSpheres
end if
if used RLAPI.CheckCollisionBoxes
	extrn 'CheckCollisionBoxes' as RLAPI.CheckCollisionBoxes
end if
if used RLAPI.CheckCollisionBoxSphere
	extrn 'CheckCollisionBoxSphere' as RLAPI.CheckCollisionBoxSphere
end if
if used RLAPI.GetRayCollisionSphere
	extrn 'GetRayCollisionSphere' as RLAPI.GetRayCollisionSphere
end if
if used RLAPI.GetRayCollisionBox
	extrn 'GetRayCollisionBox' as RLAPI.GetRayCollisionBox
end if
if used RLAPI.GetRayCollisionMesh
	extrn 'GetRayCollisionMesh' as RLAPI.GetRayCollisionMesh
end if
if used RLAPI.GetRayCollisionTriangle
	extrn 'GetRayCollisionTriangle' as RLAPI.GetRayCollisionTriangle
end if
if used RLAPI.GetRayCollisionQuad
	extrn 'GetRayCollisionQuad' as RLAPI.GetRayCollisionQuad
end if
if used RLAPI.InitAudioDevice
	extrn 'InitAudioDevice' as RLAPI.InitAudioDevice
end if
if used RLAPI.CloseAudioDevice
	extrn 'CloseAudioDevice' as RLAPI.CloseAudioDevice
end if
if used RLAPI.IsAudioDeviceReady
	extrn 'IsAudioDeviceReady' as RLAPI.IsAudioDeviceReady
end if
if used RLAPI.SetMasterVolume
	extrn 'SetMasterVolume' as RLAPI.SetMasterVolume
end if
if used RLAPI.GetMasterVolume
	extrn 'GetMasterVolume' as RLAPI.GetMasterVolume
end if
if used RLAPI.LoadWave
	extrn 'LoadWave' as RLAPI.LoadWave
end if
if used RLAPI.LoadWaveFromMemory
	extrn 'LoadWaveFromMemory' as RLAPI.LoadWaveFromMemory
end if
if used RLAPI.IsWaveValid
	extrn 'IsWaveValid' as RLAPI.IsWaveValid
end if
if used RLAPI.LoadSound
	extrn 'LoadSound' as RLAPI.LoadSound
end if
if used RLAPI.LoadSoundFromWave
	extrn 'LoadSoundFromWave' as RLAPI.LoadSoundFromWave
end if
if used RLAPI.LoadSoundAlias
	extrn 'LoadSoundAlias' as RLAPI.LoadSoundAlias
end if
if used RLAPI.IsSoundValid
	extrn 'IsSoundValid' as RLAPI.IsSoundValid
end if
if used RLAPI.UpdateSound
	extrn 'UpdateSound' as RLAPI.UpdateSound
end if
if used RLAPI.UnloadWave
	extrn 'UnloadWave' as RLAPI.UnloadWave
end if
if used RLAPI.UnloadSound
	extrn 'UnloadSound' as RLAPI.UnloadSound
end if
if used RLAPI.UnloadSoundAlias
	extrn 'UnloadSoundAlias' as RLAPI.UnloadSoundAlias
end if
if used RLAPI.ExportWave
	extrn 'ExportWave' as RLAPI.ExportWave
end if
if used RLAPI.ExportWaveAsCode
	extrn 'ExportWaveAsCode' as RLAPI.ExportWaveAsCode
end if
if used RLAPI.PlaySound
	extrn 'PlaySound' as RLAPI.PlaySound
end if
if used RLAPI.StopSound
	extrn 'StopSound' as RLAPI.StopSound
end if
if used RLAPI.PauseSound
	extrn 'PauseSound' as RLAPI.PauseSound
end if
if used RLAPI.ResumeSound
	extrn 'ResumeSound' as RLAPI.ResumeSound
end if
if used RLAPI.IsSoundPlaying
	extrn 'IsSoundPlaying' as RLAPI.IsSoundPlaying
end if
if used RLAPI.SetSoundVolume
	extrn 'SetSoundVolume' as RLAPI.SetSoundVolume
end if
if used RLAPI.SetSoundPitch
	extrn 'SetSoundPitch' as RLAPI.SetSoundPitch
end if
if used RLAPI.SetSoundPan
	extrn 'SetSoundPan' as RLAPI.SetSoundPan
end if
if used RLAPI.WaveCopy
	extrn 'WaveCopy' as RLAPI.WaveCopy
end if
if used RLAPI.WaveCrop
	extrn 'WaveCrop' as RLAPI.WaveCrop
end if
if used RLAPI.WaveFormat
	extrn 'WaveFormat' as RLAPI.WaveFormat
end if
if used RLAPI.LoadWaveSamples
	extrn 'LoadWaveSamples' as RLAPI.LoadWaveSamples
end if
if used RLAPI.UnloadWaveSamples
	extrn 'UnloadWaveSamples' as RLAPI.UnloadWaveSamples
end if
if used RLAPI.LoadMusicStream
	extrn 'LoadMusicStream' as RLAPI.LoadMusicStream
end if
if used RLAPI.LoadMusicStreamFromMemory
	extrn 'LoadMusicStreamFromMemory' as RLAPI.LoadMusicStreamFromMemory
end if
if used RLAPI.IsMusicValid
	extrn 'IsMusicValid' as RLAPI.IsMusicValid
end if
if used RLAPI.UnloadMusicStream
	extrn 'UnloadMusicStream' as RLAPI.UnloadMusicStream
end if
if used RLAPI.PlayMusicStream
	extrn 'PlayMusicStream' as RLAPI.PlayMusicStream
end if
if used RLAPI.IsMusicStreamPlaying
	extrn 'IsMusicStreamPlaying' as RLAPI.IsMusicStreamPlaying
end if
if used RLAPI.UpdateMusicStream
	extrn 'UpdateMusicStream' as RLAPI.UpdateMusicStream
end if
if used RLAPI.StopMusicStream
	extrn 'StopMusicStream' as RLAPI.StopMusicStream
end if
if used RLAPI.PauseMusicStream
	extrn 'PauseMusicStream' as RLAPI.PauseMusicStream
end if
if used RLAPI.ResumeMusicStream
	extrn 'ResumeMusicStream' as RLAPI.ResumeMusicStream
end if
if used RLAPI.SeekMusicStream
	extrn 'SeekMusicStream' as RLAPI.SeekMusicStream
end if
if used RLAPI.SetMusicVolume
	extrn 'SetMusicVolume' as RLAPI.SetMusicVolume
end if
if used RLAPI.SetMusicPitch
	extrn 'SetMusicPitch' as RLAPI.SetMusicPitch
end if
if used RLAPI.SetMusicPan
	extrn 'SetMusicPan' as RLAPI.SetMusicPan
end if
if used RLAPI.GetMusicTimeLength
	extrn 'GetMusicTimeLength' as RLAPI.GetMusicTimeLength
end if
if used RLAPI.GetMusicTimePlayed
	extrn 'GetMusicTimePlayed' as RLAPI.GetMusicTimePlayed
end if
if used RLAPI.LoadAudioStream
	extrn 'LoadAudioStream' as RLAPI.LoadAudioStream
end if
if used RLAPI.IsAudioStreamValid
	extrn 'IsAudioStreamValid' as RLAPI.IsAudioStreamValid
end if
if used RLAPI.UnloadAudioStream
	extrn 'UnloadAudioStream' as RLAPI.UnloadAudioStream
end if
if used RLAPI.UpdateAudioStream
	extrn 'UpdateAudioStream' as RLAPI.UpdateAudioStream
end if
if used RLAPI.IsAudioStreamProcessed
	extrn 'IsAudioStreamProcessed' as RLAPI.IsAudioStreamProcessed
end if
if used RLAPI.PlayAudioStream
	extrn 'PlayAudioStream' as RLAPI.PlayAudioStream
end if
if used RLAPI.PauseAudioStream
	extrn 'PauseAudioStream' as RLAPI.PauseAudioStream
end if
if used RLAPI.ResumeAudioStream
	extrn 'ResumeAudioStream' as RLAPI.ResumeAudioStream
end if
if used RLAPI.IsAudioStreamPlaying
	extrn 'IsAudioStreamPlaying' as RLAPI.IsAudioStreamPlaying
end if
if used RLAPI.StopAudioStream
	extrn 'StopAudioStream' as RLAPI.StopAudioStream
end if
if used RLAPI.SetAudioStreamVolume
	extrn 'SetAudioStreamVolume' as RLAPI.SetAudioStreamVolume
end if
if used RLAPI.SetAudioStreamPitch
	extrn 'SetAudioStreamPitch' as RLAPI.SetAudioStreamPitch
end if
if used RLAPI.SetAudioStreamPan
	extrn 'SetAudioStreamPan' as RLAPI.SetAudioStreamPan
end if
if used RLAPI.SetAudioStreamBufferSizeDefault
	extrn 'SetAudioStreamBufferSizeDefault' as RLAPI.SetAudioStreamBufferSizeDefault
end if
if used RLAPI.SetAudioStreamCallback
	extrn 'SetAudioStreamCallback' as RLAPI.SetAudioStreamCallback
end if
if used RLAPI.AttachAudioStreamProcessor
	extrn 'AttachAudioStreamProcessor' as RLAPI.AttachAudioStreamProcessor
end if
if used RLAPI.DetachAudioStreamProcessor
	extrn 'DetachAudioStreamProcessor' as RLAPI.DetachAudioStreamProcessor
end if
if used RLAPI.AttachAudioMixedProcessor
	extrn 'AttachAudioMixedProcessor' as RLAPI.AttachAudioMixedProcessor
end if
if used RLAPI.DetachAudioMixedProcessor
	extrn 'DetachAudioMixedProcessor' as RLAPI.DetachAudioMixedProcessor
end if