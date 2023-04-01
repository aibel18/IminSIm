@ECHO OFF
SetLocal EnableDelayedExpansion

@REM Get a list of all the .c++ files.
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

SET assembly=engine.dll
SET compilerFlags=-shared -Wvarargs -Wall -Werror
SET includeFlags=-Isrc -I../platform/src
SET linkerFlags=-L"%OUT%" -lplatform.lib
SET defines=-D_CRT_SECURE_NO_WARNINGS -DIDL_API_SHARE -DXSIM_API_BUILD

IF "%DEBUG%" == "true" (
	SET compilerFlags=!compilerFlags! -g
	SET defines=!defines! -D_DEBUG -DLOG_DEBUG_ENABLED
)

ECHO "Building %assembly%%..."

clang++ %cFilenames% %compilerFlags% -o %OUT%/%assembly% %defines% %includeFlags% %linkerFlags%