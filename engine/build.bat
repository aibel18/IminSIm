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
SET compilerFlags=-shared -Wvarargs -Wall -Werror
SET defines=-D_CRT_SECURE_NO_WARNINGS -DIDL_API_SHARE -DXSIM_API_BUILD

IF "%DEBUG%" == "true" (
	SET compilerFlags=!compilerFlags! -g
	SET defines=!defines! -D_DEBUG -DLOG_DEBUG_ENABLED
)

ECHO Building %assembly%%EXT_LIB%...

clang++ %cFilenames% %compilerFlags% -o %OUT%/%assembly%%EXT_LIB% %defines% %includeFlags% %linkerFlags%