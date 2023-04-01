#!/bin/bash
set echo on

# Get a list of all the .c++ files.
cFilenames=$(find . -type f -name "*.cpp")

assembly="launcher"
compilerFlags="-fdeclspec -fPIC -Wvarargs -Wall -Werror"
includeFlags="-Isrc -I../platform/src -I../engine/src"
linkerFlags="-L$OUT/ -lplatform -lengine -Wl,-rpath,$OUT/"
defines="-DIDL_API_SHARE -DXSIM_API_SHARE"

if [ $DEBUG == true ]
then
	compilerFlags="$compilerFlags -g"
	defines="$defines -D_DEBUG -DLOG_DEBUG_ENABLED"
fi

echo "Building $assembly..."

clang++ $cFilenames $compilerFlags -o $OUT/$assembly $defines $includeFlags $linkerFlags