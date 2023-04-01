@ECHO OFF
SetLocal EnableDelayedExpansion

@REM Get a list of all the .c++ files.
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

SET assembly=engine
SET includeFlags=-I%WORKING_DIR%/%assembly%/src -I%WORKING_DIR%/platform/src
SET linkerFlags=-L"%OUT%" -lplatform.lib
SET compilerFlags=-c -Wvarargs -Wall -Werror
SET defines=-D_CRT_SECURE_NO_WARNINGS

IF "%DEBUG%" == "true" (
	SET compilerFlags=!compilerFlags! -g
	SET defines=!defines! -D_DEBUG -DLOG_DEBUG_ENABLED
)

ECHO Building %assembly%%EXT_LIB%...

@REM clang++ %cFilenames% %compilerFlags% -o %OUT%/%assembly%%EXT_LIB% %defines% %includeFlags% %linkerFlags%

if not EXIST "%BUILD%/%assembly%" (
	MKDIR "%BUILD%/%assembly%"
)
CD %BUILD%/%assembly%
clang++ %cFilenames% %compilerFlags% %defines% %includeFlags%
llvm-ar rc %OUT%/%assembly%%EXT_LIB% %BUILD%/%assembly%/*.o