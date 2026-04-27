# Enum Parameter Inference

Generated from raylib public parser output plus source inspection.

- `SetWindowState(flags)` -> `RayLib.ConfigFlags` (rcore_android.c: parameter/constant expression)
- `ClearWindowState(flags)` -> `RayLib.ConfigFlags` (rcore_android.c: parameter/constant expression)
- `GetGamepadAxisMovement(axis)` -> `RayLib.GamepadAxis` (rcore.c: parameter/constant expression)
- `IsMouseButtonPressed(button)` -> `RayLib.MouseButton` (rcore.c: parameter/constant expression)
- `IsMouseButtonDown(button)` -> `RayLib.MouseButton` (rcore.c: parameter/constant expression)
- `IsMouseButtonReleased(button)` -> `RayLib.MouseButton` (rcore.c: parameter/constant expression)
- `IsMouseButtonUp(button)` -> `RayLib.MouseButton` (rcore.c: parameter/constant expression)
- `UpdateCamera(mode)` -> `RayLib.CameraMode` (rcamera.h: parameter/constant expression)
- `ImageFormat(newFormat)` -> `RayLib.PixelFormat` (rtextures.c: parameter/constant expression)
- `LoadTextureCubemap(layout)` -> `RayLib.CubemapLayout` (rtextures.c: parameter/constant expression)
- `SetTextureFilter(filter)` -> `RayLib.TextureFilter` (rtextures.c: switch(filter))
- `SetTextureWrap(wrap)` -> `RayLib.TextureWrap` (rtextures.c: switch(wrap))
- `GetPixelColor(format)` -> `RayLib.PixelFormat` (rtextures.c: switch(format))
- `SetPixelColor(format)` -> `RayLib.PixelFormat` (rtextures.c: switch(format))
- `GetPixelDataSize(format)` -> `RayLib.PixelFormat` (rtextures.c: switch(format))
- `LoadFontData(type)` -> `RayLib.FontType` (rtext.c: switch(type))
