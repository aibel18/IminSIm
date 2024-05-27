#!/bin/bash
set echo on

# Get a list of all the .c++ files.
cFilenames=$(find . -type f -name "*.cpp")

assembly="launcher"
includeFlags="-I$WORKING_DIR/$assembly/src -I$WORKING_DIR//platform/src -I$WORKING_DIR/engine/src"
linkerFlags="-L$OUT/ -lplatform -lengine -Wl,-rpath,$OUT/"
compilerFlags="-fdeclspec -fPIC -Wvarargs -Wall -Werror -Wno-missing-braces"
defines="-DIDL_API_SHARE -DXSIM_API_SHARE"

if [ $DEBUG == true ]
then
	compilerFlags="$compilerFlags -g"
	defines="$defines -D_DEBUG -DLOG_DEBUG_ENABLED"
fi

echo "Building $assembly..."

clang++ $cFilenames $compilerFlags -o $OUT/$assembly $defines $includeFlags $linkerFlags

Verify