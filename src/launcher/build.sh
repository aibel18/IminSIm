#!/bin/bash
set echo on

# Get a list of all the .c++ files.
cFilenames=$(find . -type f -name "*.cpp")

assembly="launcher"
compilerFlags="-fdeclspec -fPIC -Wvarargs -Wall -Werror"
includeFlags="-I. -I../platform/ -I../engine/"
linkerFlags="-L$OUT/ -lplatform -lengine -Wl,-rpath,$OUT/"
defines="-D_DEBUG -DIDL_API_SHARED_LIB -DIMINSIM_API_SHARED_LIB"

if [ $DEBUG == true ]
then
	compilerFlags="$compilerFlags -g"
	defines="$defines -DLOG_DEBUG_ENABLED"
fi

echo "Building $assembly..."

clang++ $cFilenames $compilerFlags -o $OUT/$assembly $defines $includeFlags $linkerFlags