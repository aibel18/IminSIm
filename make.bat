@echo off
goto :init

REM command list
:help
	echo down    		    		clean project
	echo generate    		    generate project
	echo build              build project
	goto :eof

:down
	call rm -r build
	call rm -r sdk
	goto :eof

:generate
	call cmake -B build -G "NMake Makefiles" .
	goto :eof
	
:build
	call cd "%WORKING_DIR%build"
	call nmake
	goto :eof

REM main program
:init
	set "WORKING_DIR=%~dp0"
	set "Commands[0]=1"
	set /A "CommandIndex=0"

:parse
	if "%~1"=="" goto :validate

	set "Commands[%CommandIndex%]=%~1"
	set /A "CommandIndex = %CommandIndex% + 1"

	shift
	goto :parse

:validate
	if %CommandIndex%==0 call :help & goto :end

:main
	setlocal enabledelayedexpansion

	set /A "length = %CommandIndex% - 1"

	for /l %%n in (0,1,%length%) do (
		call :!Commands[%%n]!
	)

:end
	call :cleanup
	exit /B

:cleanup
	set "__PROJECT_NAME="
	set "Commands[0]="
	set "CommandsIndex="

	goto :eof	
REM end - main program