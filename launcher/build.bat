@ECHO OFF
SetLocal EnableDelayedExpansion

@REM Get a list of all the .c++ files.
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

SET assembly=launcher.exe
SET compilerFlags=-Wvarargs -Wall -Werror
SET includeFlags=-Isrc -I../platform/src -I../engine/src
SET linkerFlags=-L"%OUT%" -lplatform.lib -lengine.lib
SET defines=-DIDL_API_SHARE -DXSIM_API_SHARE

IF "%DEBUG%" == "true" (
	SET compilerFlags=!compilerFlags! -g
	SET defines=!defines! -D_DEBUG -DLOG_DEBUG_ENABLED
)

ECHO "Building %assembly%%..."

clang++ %cFilenames% %compilerFlags% -o %OUT%/%assembly% %defines% %includeFlags% %linkerFlags%