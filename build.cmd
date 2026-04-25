@echo off
setlocal

rem Unified build wrapper for raylib-fasm2 examples.
rem
rem Usage:
rem   build.cmd pe64        examples\pe64\<name>.asm
rem   build.cmd obj-dll     examples\obj\<name>.asm
rem   build.cmd obj-static  examples\obj\<name>.asm
rem
rem Required env:
rem   FASM2_PATH    directory containing fasm2.cmd (https://github.com/tgrysztar/fasm2)
rem
rem Required runtime artifacts (not committed to the repo — fetch a
rem raylib release from https://github.com/raysan5/raylib/releases and
rem extract the lib/dll set into the matching directories):
rem   bin64\raylib.dll, bin64\raylib.lib    (PE64 + obj-dll modes)
rem   lib64\raylib.lib                       (obj-static mode)
rem
rem OBJ modes additionally need the VS dev shell envs (LIB, INCLUDE) in
rem scope so link.exe can resolve kernel32.lib / ucrt.lib / etc.

if "%~1"=="" goto :usage
if "%~2"=="" goto :usage
if "%FASM2_PATH%"=="" goto :no_fasm2

set MODE=%~1
set SRC=%~2
set ROOT=%~dp0
set NAME=%~n2
set OUTDIR=%ROOT%examples\build\%MODE%

rem Prepend our generated includes so fasm2's `include 'raylib.inc'`
rem resolves. fasm2.cmd will further prepend its own include dir.
set INCLUDE=%ROOT%inc;%INCLUDE%

if not exist "%OUTDIR%" mkdir "%OUTDIR%"

if /I "%MODE%"=="pe64" goto :pe64
if /I "%MODE%"=="obj-dll" goto :obj_dll
if /I "%MODE%"=="obj-static" goto :obj_static
echo unknown mode: %MODE%
goto :usage

:pe64
set EXE=%OUTDIR%\%NAME%.exe
call "%FASM2_PATH%\fasm2.cmd" "%SRC%" "%EXE%" || exit /b %errorlevel%
if exist "%ROOT%bin64\raylib.dll" copy /Y "%ROOT%bin64\raylib.dll" "%OUTDIR%\raylib.dll" >nul
echo built %EXE%
goto :eof

:obj_dll
set OBJ=%OUTDIR%\%NAME%.obj
set EXE=%OUTDIR%\%NAME%.exe
call "%FASM2_PATH%\fasm2.cmd" "%SRC%" "%OBJ%" || exit /b %errorlevel%
if not exist "%ROOT%bin64\raylib.lib" goto :no_dll_lib
link /nologo /entry:mainCRTStartup /subsystem:console ^
     /out:"%EXE%" "%OBJ%" ^
     "%ROOT%bin64\raylib.lib" ^
     kernel32.lib ucrt.lib msvcrt.lib vcruntime.lib || exit /b %errorlevel%
copy /Y "%ROOT%bin64\raylib.dll" "%OUTDIR%\raylib.dll" >nul
echo built %EXE%
goto :eof

:obj_static
set OBJ=%OUTDIR%\%NAME%.obj
set EXE=%OUTDIR%\%NAME%.exe
call "%FASM2_PATH%\fasm2.cmd" "%SRC%" "%OBJ%" || exit /b %errorlevel%
if not exist "%ROOT%lib64\raylib.lib" goto :no_static_lib
rem Static raylib was built against the dynamic MSVC CRT (__imp_ refs),
rem so we link against the import-stub CRT libs (ucrt + msvcrt +
rem vcruntime), not the all-static ones. Plus the Win32 / GL libs
rem raylib's GLFW backend needs.
link /nologo /entry:mainCRTStartup /subsystem:console ^
     /out:"%EXE%" "%OBJ%" ^
     "%ROOT%lib64\raylib.lib" ^
     user32.lib gdi32.lib shell32.lib winmm.lib opengl32.lib ^
     kernel32.lib ucrt.lib msvcrt.lib vcruntime.lib || exit /b %errorlevel%
echo built %EXE%
goto :eof

:no_fasm2
echo error: FASM2_PATH is not set.
echo Set it to your fasm2 install directory before running this script:
echo   set "FASM2_PATH=C:\path\to\fasm2"
echo Get fasm2 from https://github.com/tgrysztar/fasm2
exit /b 2

:no_dll_lib
echo error: missing bin64\raylib.lib (and probably bin64\raylib.dll).
echo Download a raylib release from https://github.com/raysan5/raylib/releases
echo and extract the contents of `raylib_msvc16/` (or equivalent) into bin64\.
exit /b 2

:no_static_lib
echo error: missing lib64\raylib.lib (the fully-static archive).
echo Download a raylib release from https://github.com/raysan5/raylib/releases
echo and extract the static lib into lib64\.
exit /b 2

:usage
echo usage: %~nx0 ^<pe64^|obj-dll^|obj-static^> ^<source.asm^>
echo.
echo   pe64        examples/pe64/foo.asm     -^> build/pe64/foo.exe + raylib.dll
echo   obj-dll     examples/obj/foo.asm      -^> build/obj-dll/foo.{obj,exe} + raylib.dll
echo   obj-static  examples/obj/foo.asm      -^> build/obj-static/foo.{obj,exe} (self-contained)
echo.
echo Required env:    FASM2_PATH   path to your fasm2 install
echo OBJ modes also need a VS dev shell active (LIB / INCLUDE).
exit /b 2
