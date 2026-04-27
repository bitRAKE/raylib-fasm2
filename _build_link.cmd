@echo off
setlocal
::	This script assumes machine-type matching MS tools environment.
::	Must execute with fasmg expected command line.
::		fasm <source>
::		fasm <source> <output>
::		fasm <options> <source> <output>
::
::	How to link when we don't know where the object file is?
::	Loop through all arguments to get the last:
for %%a in (%*) do (set "last=%%a")
call :get_path_name "%last%"

if exist "%~dp0_local.cmd" call "%~dp0_local.cmd"

REM	Configure these for your environment before invoking:
if not defined FASM2_PATH (
	echo error: FASM2_PATH is not set.
	echo        Example: set "FASM2_PATH=..\fasm2"
	exit /b 1
)
if not defined RAYLIB_LIBPATH (
	echo error: RAYLIB_LIBPATH is not set.
	echo        Example: set "RAYLIB_LIBPATH=..\raylib-build"
	exit /b 1
)
REM	Win32\Release\raylib.lib	-- static 32-bit linking
REM	Win32\Release.DLL\raylib.lib	-- dynamic 32-bit linking
REM	x64\Release\raylib.lib		-- static 64-bit linking
REM	x64\Release.DLL\raylib.lib	-- dynamic 64-bit linking

if defined RAYLIB_LINKER (
	set "linker=%RAYLIB_LINKER%"
) else (
	where lld-link.exe >nul 2>nul
	if not errorlevel 1 (
		set "linker=lld-link.exe"
	) else (
		set "linker=link.exe"
	)
)

REM	Local includes can bypass fasm2 includes:
set "INCLUDE=%~dp0include;%FASM2_PATH%\include;%INCLUDE%"

"%FASM2_PATH%\fasmg" -iInclude('fasm2.inc') %* || exit /b %errorlevel%

::	Note: response files do NOT expand environment variables.
::	Now we can use the response file created:
echo linker: "%linker%"
"%linker%" /LIBPATH:"%RAYLIB_LIBPATH%" @%path_name%.response || exit /b %errorlevel%
goto :eof

:get_path_name
set "path_name=%~dpn1"
goto :eof
