@ECHO off
GOTO :init

REM command list
:help
	ECHO platform        build platform
	ECHO engine          build engine
	ECHO launcher        build launcher
	ECHO all             build all
	GOTO :EOF

:platform
	PUSHD "platform"
		CALL build.bat
	POPD
	GOTO :EOF

:engine
	PUSHD "engine"
		CALL build.bat
	POPD
	GOTO :EOF

:launcher
	PUSHD "launcher"
		CALL build.bat
	POPD
	GOTO :EOF

:all
	CALL :platform
	CALL :engine
	CALL :launcher
	IF %ERRORLEVEL% NEQ 0 (
		ECHO Error:%ERRORLEVEL%
	)	ELSE (
		ECHO "All assemblies built successfully. Output %OUT%"
	)	
	GOTO :EOF

REM main program
:init
	SET "WORKING_DIR=%~dp0"
	SET OUT=%WORKING_DIR%sdk
	SET BUILD=%WORKING_DIR%build
	SET "Commands[0]=1"
	SET /A "CommandIndex=0"
	SET EXT_LIB=".dll"
	SET "DEBUG=false"

	if not EXIST "%OUT%" (
		MKDIR "%OUT%"
	)
	if not EXIST "%BUILD%" (
		MKDIR "%BUILD%"
	)

:parse
	if "%~1"=="" GOTO :validate

	SET "Commands[%CommandIndex%]=%~1"
	SET /A "CommandIndex = %CommandIndex% + 1"

	shift
	GOTO :parse

:validate
	if %CommandIndex%==0 CALL :help & GOTO :end

:main
	setlocal enabledelayedexpansion

	SET /A "length = %CommandIndex% - 1"

	FOR /l %%n IN (0,1,%length%) DO (
		CALL :!Commands[%%n]!
	)

:end
	CALL :cleanup
	EXIT /B

:cleanup
	SET "__PROJECT_NAME="
	SET "Commands[0]="
	SET "CommandsIndex="

	GOTO :EOF	
REM end - main program