@ECHO OFF
SetLocal EnableDelayedExpansion

@REM Get a list of all the .c++ files.
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

SET assembly=platform.dll
SET compilerFlags=-shared -Wvarargs -Wall -Werror
SET includeFlags=-I.
SET linkerFlags=
SET defines=-D_CRT_SECURE_NO_WARNINGS -DIDL_API_SHARED_LIB_BUILD

IF "%DEBUG%" == "true" (
	SET compilerFlags=!compilerFlags! -g
)

ECHO "Building %assembly%%..."

clang++ %cFilenames% %compilerFlags% -o %out%/%assembly% %defines% %includeFlags% %linkerFlags%