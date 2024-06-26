#!/bin/bash

Verify()
{
	ERRORLEVEL=$?
	if [ $ERRORLEVEL -ne 0 ]
	then
		echo "Error: "$ERRORLEVEL && exit
	fi
}

Platform()
{
	pushd "platform" > /dev/null
		source build.sh
	popd > /dev/null
}

Engine()
{
	pushd "engine" > /dev/null
		source build.sh
	popd > /dev/null
}

Launcher()
{
	pushd "launcher" > /dev/null
		source build.sh
	popd > /dev/null
}

Run()
{
    $OUT/launcher
}

All()
{
	Platform
	Engine
	Launcher
	echo "All assemblies built successfully. Output $OUT"
}

WORKING_DIR=$(pwd)
OUT=$WORKING_DIR/sdk
BUILD=$WORKING_DIR/build
EXT_LIB=".so"
DEBUG=false

mkdir -p "$OUT"
mkdir -p "$BUILD"

while getopts :pelar option;
do
	case "$option" in
		p) # build platform
			Platform
			exit;;
		e) # build engine
			Engine
			exit;;
		l) # build launcher
			Launcher
			exit;;
		a) # build all
			All
			exit;;
        r) # run
			Run
			exit;;
		(\?) # no parameter
			echo "Error: Invalid option"
			exit;;
	esac
done