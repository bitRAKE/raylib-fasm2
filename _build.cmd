@echo off
setlocal EnableExtensions EnableDelayedExpansion
::	Direct PE build helper.
::	Common forms:
::		_build.cmd games\classics\snake.asm
::		_build.cmd games\classics\snake.asm games\classics\snake_test.exe
::		_build.cmd games\classics\*.asm
::		_build.cmd -iInclude('raylib_pe64.inc') games\classics\snake.asm
::
::	When no explicit output EXE is provided, each source builds next to the
::	source as <source-name>.exe. After assembly, the matching raylib.dll is
::	copied beside the output if it does not already exist there.

if "%~1"=="" goto :usage

if exist "%~dp0_local.cmd" call "%~dp0_local.cmd"

if not defined FASM2_PATH (
	echo error: FASM2_PATH is not set.
	echo        Example: set "FASM2_PATH=..\fasm2"
	exit /b 1
)
if not defined RAYLIB_ROOT (
	echo error: RAYLIB_ROOT is not set.
	echo        Example: set "RAYLIB_ROOT=..\raylib-build"
	exit /b 1
)

set "INCLUDE=%~dp0include;%FASM2_PATH%\include;%INCLUDE%"
set "USER_RAYLIB_ARCH=%RAYLIB_ARCH%"
set "fasmg_opts="
set "source_count=0"
set "explicit_out="

call :parse_args %*

if "%source_count%"=="0" goto :usage
if defined explicit_out if not "%source_count%"=="1" (
	echo error: explicit output can only be used with one source.
	exit /b 1
)

for /L %%i in (1,1,%source_count%) do (
	set "src=!source_%%i!"
	if defined explicit_out (
		set "out=!explicit_out!"
	) else (
		for %%s in ("!src!") do set "out=%%~dpns.exe"
	)
	call :build_one "!src!" "!out!"
	if errorlevel 1 exit /b !errorlevel!
)

exit /b 0

:build_one
set "source_path=%~f1"
set "out_path=%~f2"
set "out_dir=%~dp2"
if not exist "%out_dir%" mkdir "%out_dir%" || exit /b %errorlevel%

echo assembling "%source_path%" -^> "%out_path%"
set "asm_log=%TEMP%\%~n0_%RANDOM%_%RANDOM%.log"
"%FASM2_PATH%\fasmg" -iInclude('fasm2.inc') %fasmg_opts% "%source_path%" "%out_path%" >"%asm_log%" 2>&1
set "asm_status=%errorlevel%"
type "%asm_log%"
findstr /C:"Error:" "%asm_log%" >nul
if not errorlevel 1 (
	del "%asm_log%" >nul 2>nul
	exit /b 1
)
del "%asm_log%" >nul 2>nul
if not "%asm_status%"=="0" exit /b %asm_status%

set "RAYLIB_ARCH=%USER_RAYLIB_ARCH%"
call :detect_arch
if not defined RAYLIB_ARCH (
	echo error: could not determine Raylib DLL architecture for "%source_path%".
	echo        Set RAYLIB_ARCH=x64 or RAYLIB_ARCH=Win32, or use raylib_pe64.inc/raylib_pe32.inc.
	exit /b 1
)

set "dll_src=%RAYLIB_ROOT%\%RAYLIB_ARCH%\Release.DLL\raylib.dll"
if not exist "%dll_src%" (
	echo error: raylib.dll not found: "%dll_src%"
	exit /b 1
)

set "dll_dst=%out_dir%raylib.dll"
if not exist "%dll_dst%" (
	copy /Y "%dll_src%" "%dll_dst%" >nul || exit /b %errorlevel%
	echo copied "%dll_dst%"
) else (
	echo found "%dll_dst%"
)
exit /b 0

:parse_args
if "%~1"=="" exit /b 0
if /I "%~x1"==".asm" (
	for %%s in (%1) do (
		set /a source_count+=1
		set "source_!source_count!=%%~fs"
	)
) else if /I "%~x1"==".exe" (
	set "explicit_out=%~f1"
) else (
	set "fasmg_opts=!fasmg_opts! %~1"
)
shift
goto :parse_args

:detect_arch
if defined RAYLIB_ARCH goto :normalize_arch
echo(%fasmg_opts% | findstr /I /C:"raylib_pe64.inc" >nul && set "RAYLIB_ARCH=x64"
echo(%fasmg_opts% | findstr /I /C:"raylib_pe32.inc" >nul && set "RAYLIB_ARCH=Win32"
if defined RAYLIB_ARCH goto :normalize_arch

if not exist "%source_path%" goto :normalize_arch
findstr /I /C:"raylib_pe64.inc" "%source_path%" >nul 2>nul && set "RAYLIB_ARCH=x64"
findstr /I /C:"raylib_pe32.inc" "%source_path%" >nul 2>nul && set "RAYLIB_ARCH=Win32"
goto :normalize_arch

:normalize_arch
if /I "%RAYLIB_ARCH%"=="64" set "RAYLIB_ARCH=x64"
if /I "%RAYLIB_ARCH%"=="x64" set "RAYLIB_ARCH=x64"
if /I "%RAYLIB_ARCH%"=="amd64" set "RAYLIB_ARCH=x64"
if /I "%RAYLIB_ARCH%"=="32" set "RAYLIB_ARCH=Win32"
if /I "%RAYLIB_ARCH%"=="x86" set "RAYLIB_ARCH=Win32"
if /I "%RAYLIB_ARCH%"=="win32" set "RAYLIB_ARCH=Win32"
exit /b 0

:usage
echo usage: %~nx0 ^<fasmg-options^> ^<source.asm^|wildcard.asm^> [output.exe]
exit /b 1
