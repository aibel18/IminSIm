@ECHO OFF
SetLocal EnableDelayedExpansion

@REM Get a list of all the .c++ files.
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

SET assembly=platform
SET includeFlags=-I%WORKING_DIR%/%assembly%/src
SET linkerFlags=-luser32
SET compilerFlags=-shared -Wvarargs -Wall -Werror
SET defines=-D_CRT_SECURE_NO_WARNINGS -DIDL_API_BUILD

IF "%DEBUG%" == "true" (
	SET compilerFlags=!compilerFlags! -g -llibcmtd -Xlinker /NODEFAULTLIB:libcmt
	SET defines=!defines! -D_DEBUG
)

ECHO Building %assembly%%EXT_LIB%...

clang++ %cFilenames% %compilerFlags% -o %OUT%/%assembly%%EXT_LIB% %defines% %includeFlags% %linkerFlags%