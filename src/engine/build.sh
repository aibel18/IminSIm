#!/bin/bash
set echo on

# Get a list of all the .c++ files.
cFilenames=$(find . -type f -name "*.cpp")

assembly="libengine.so"
compilerFlags="-shared -fdeclspec -fPIC -Wvarargs -Wall -Werror"
includeFlags="-I. -I../platform"
linkerFlags="-L$OUT/ -lplatform -Wl,-rpath,$OUT/"
defines="-D_CRT_SECURE_NO_WARNINGS -DIDL_API_SHARED_LIB -DIMINSIM_API_SHARED_LIB_BUILD"

if [ $DEBUG == true ]
then
	compilerFlags="$compilerFlags -g"
	defines="$defines -D_DEBUG -DLOG_DEBUG_ENABLED"
fi

echo "Building $assembly..."

clang++ $cFilenames $compilerFlags -o $OUT/$assembly $defines $includeFlags $linkerFlags