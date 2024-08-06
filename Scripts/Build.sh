#!/bin/bash

DO_STANDALONE_BUILD=1

BUILD_CONF="Debug"
PRODUCTNAME="Moonbase Plugin Demo"


BASEDIR="$(realpath $(dirname "$0")/..)"
JUCERPROJ="$BASEDIR/$PRODUCTNAME.jucer"

"$BASEDIR/Scripts/BuildProjucer.sh" || exit $?
"$BASEDIR/Submodules/moonbase_JUCEClient/Assets/Build.sh" || exit $?


if [[ "$OSTYPE" == "darwin"* ]]; then
    PROJUCER="$BASEDIR/Submodules/JUCE/extras/Projucer/Builds/MacOSX/build/Release/Projucer.app/Contents/MacOS/Projucer"
    BUILD_CMD="xcodebuild \
                -project \"$PRODUCTNAME.xcodeproj\" \
                -configuration $BUILD_CONF \
                -target \"$PRODUCTNAME - Shared Code\" \
                -target \"$PRODUCTNAME - AU\" \
                -target \"$PRODUCTNAME - VST3\""

    if [ $DO_STANDALONE_BUILD -eq 1 ]; then
        BUILD_CMD="$BUILD_CMD -target \"$PRODUCTNAME - Standalone Plugin\""
    fi

elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]]; then

    powershell -ExecutionPolicy Bypass -File "$BASEDIR/Scripts/InstallWebview2.ps1" || exit $?

    source "$BASEDIR/Scripts/SetupDevEnv.sh" || exit $?
    PROJUCER="$BASEDIR/Submodules/JUCE/extras/Projucer/Builds/VisualStudio2022/x64/Release/App/Projucer.exe"
    
    LOG_FILE="$BASEDIR/buildlog.txt"
    if [ -f "$LOG_FILE" ]; then
        rm "$LOG_FILE"
    fi
    touch "$LOG_FILE"
    # Start a background process to tail the log file
    tail -f "$LOG_FILE" &


    # Store the PID of the tail process
    TAIL_PID=$!

    function killLogTail() {
        echo "Killing log tail process $TAIL_PID and removing log file $LOG_FILE"
        kill $TAIL_PID
        rm "$LOG_FILE"
    }

    BUILD_CMD="\"$DEV_ENV_EXE\" \"${PRODUCTNAME}.sln\" -Build \"$BUILD_CONF|x64\" -Out \"$LOG_FILE\""
else
  echo "Error: This script can only be run on macOS or Windows"
  exit 1
fi

if [ ! -f "$PROJUCER" ]; then
    echo "Error: Projucer binary not found at $PROJUCER"
    exit 1
fi

"$PROJUCER" --resave "$JUCERPROJ" || prematureExit $?

if [[ "$OSTYPE" == "darwin"* ]]; then
    cd "$BASEDIR/Builds/MacOSX"
elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]]; then
    cd "$BASEDIR/Builds/VisualStudio2022"
fi

eval "$BUILD_CMD" 
returnVal=$?

cd "$BASEDIR"

RED=$(tput setaf 9; tput bold)
GREEN=$(tput setaf {10}; tput bold)
RESET=$(tput sgr0)

if [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]]; then
    killLogTail
fi

if [ $returnVal -eq 0 ]; then
	echo "$GREEN**************** BUILD SUCCESSFUL ****************$RESET"
else
	echo "$RED!!! **************** BUILD FAILED **************** !!!$RESET"
    echo "Build failed on exit code: $returnVal"
fi

exit $returnVal