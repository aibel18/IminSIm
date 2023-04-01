@ECHO OFF
SetLocal EnableDelayedExpansion

@REM Get a list of all the .c++ files.
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

SET assembly=launcher
SET includeFlags=-I%WORKING_DIR%/%assembly%/src -I%WORKING_DIR%/platform/src -I%WORKING_DIR%/engine/src
SET linkerFlags=-L"%OUT%" -lplatform.lib -lengine.lib
SET compilerFlags=-Wvarargs -Wall -Werror
SET defines=-DIDL_API_SHARE -DXSIM_API_SHARE

IF "%DEBUG%" == "true" (
	SET compilerFlags=!compilerFlags! -g
	SET defines=!defines! -D_DEBUG -DLOG_DEBUG_ENABLED
)

ECHO Building %assembly%.exe...

clang++ %cFilenames% %compilerFlags% -o %OUT%/%assembly%.exe %defines% %includeFlags% %linkerFlags%