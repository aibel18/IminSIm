@ECHO OFF
SetLocal EnableDelayedExpansion

@REM Get a list of all the .c++ files.
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

SET assembly=launcher.exe
SET compilerFlags=-Wvarargs -Wall -Werror
SET includeFlags=-I. -I../platform/ -I../engine/
SET linkerFlags=-L"%OUT%" -lplatform.lib -lengine.lib
SET defines=-D_DEBUG -DIDL_API_SHARED_LIB -DIMINSIM_API_SHARED_LIB

IF "%DEBUG%" == "true" (
	SET compilerFlags=!compilerFlags! -g
)

ECHO "Building %assembly%%..."

clang++ %cFilenames% %compilerFlags% -o %out%/%assembly% %defines% %includeFlags% %linkerFlags%