#!/bin/bash

Verify()
{
	ERRORLEVEL=$?
	if [ $ERRORLEVEL -ne 0 ]
	then
		echo "Error:"$ERRORLEVEL && exit
	fi
}

Platform()
{
	pushd "platform"
		source build.sh
	popd
	Verify
}

Engine()
{
	pushd "engine"
		source build.sh
	popd
	Verify
}

Launcher()
{
	pushd "launcher"
		source build.sh
	popd
	Verify
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
DEBUG=false

mkdir -p "$OUT"

while getopts :pela option;
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
		(\?) # no parameter
			echo "Error: Invalid option"
			exit;;
	esac
done