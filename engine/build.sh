#!/bin/bash
set echo on

# Get a list of all the .c++ files.
cFilenames=$(find . -type f -name "*.cpp")

assembly="libengine"
includeFlags="-I$WORKING_DIR/$name/src -I$WORKING_DIR/platform/src"
linkerFlags="-L$OUT/ -lplatform -Wl,-rpath,$OUT/"
compilerFlags="-shared -fdeclspec -fPIC -Wvarargs -Wall -Werror"
defines="-D_CRT_SECURE_NO_WARNINGS -DIDL_API_SHARE -DXSIM_API_BUILD"

if [ $DEBUG == true ]
then
	compilerFlags="$compilerFlags -g"
	defines="$defines -D_DEBUG -DLOG_DEBUG_ENABLED"
fi

echo "Building $assembly$EXT_LIB..."

clang++ $cFilenames $compilerFlags -o $OUT/$assembly$EXT_LIB $defines $includeFlags $linkerFlags