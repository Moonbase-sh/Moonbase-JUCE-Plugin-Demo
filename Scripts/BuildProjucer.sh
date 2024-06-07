#!/bin/bash

BASEDIR="$(dirname "$0")/.."


if [[ "$OSTYPE" == "darwin"* ]]; then

    echo "Running on macOS"

    cd "$BASEDIR/Submodules/JUCE/extras/Projucer/Builds/MacOSX"
    BINARY="./build/Release/Projucer.app/Contents/MacOS/Projucer"
    BUILD_CMD="xcodebuild -project Projucer.xcodeproj -configuration Release -target \"Projucer - App\""

elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]]; then
    source "$BASEDIR/Scripts/SetupDevEnv.sh" || exit $?
    echo "Running on Windows"
    echo "(If you're running on a Github hosted runner, this step may appear to hang for 5-15minutes :( it's a bug in the action runner images, see issue https://github.com/actions/runner-images/issues/5301 for more info)"
    cd "$BASEDIR/Submodules/JUCE/extras/Projucer/Builds/VisualStudio2022"
    BINARY="./x64/Release/App/Projucer.exe"
    
    JUCER_LOG_FILE=$(realpath "./jucerbuildlog.txt")
    if [ -f "$JUCER_LOG_FILE" ]; then
        rm "$JUCER_LOG_FILE"
    fi
    touch "$JUCER_LOG_FILE"
    # Start a background process to tail the log file
    tail -f "$JUCER_LOG_FILE" &

    # Store the PID of the tail process
    JUCER_TAIL_PID=$!
    function killJucerLogTail() {
        kill $JUCER_TAIL_PID
        rm "$JUCER_LOG_FILE"
    }

    if [ -z "$DEV_ENV_EXE" ]; then
        DEV_ENV_EXE="C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/devenv.exe"
    fi

    BUILD_CMD="\"$DEV_ENV_EXE\" \"Projucer.sln\" -Build \"Release|x64\" -Out \"$JUCER_LOG_FILE\""

else
  echo "Error: This script can only be run on macOS or Windows"
  exit 1
fi

function projucerbuild_death() {
    if [ $1 -ne 0 ]; then
        echo "Error: Projucer build failed"
    fi
    if [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]]; then
        killJucerLogTail
    fi
    exit $1
}

if [ -f "$BINARY" ]; then

    if [[ "$OSTYPE" == "darwin"* ]]; then
        # macOS
        CURRENT_JUCER_VERSION=$(strings $BINARY | grep -o 'juce_version_[0-9]\+_[0-9]\+_[0-9]\+' | head -n 1 | awk -F_ '{print $3"."$4"."$5}')
    elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "win32" ]]; then
        # Windows
        CURRENT_JUCER_VERSION=$(powershell.exe -Command "(Get-Command $BINARY).FileVersionInfo.FileVersion")
    else
        echo "Unsupported OS"
        projucerbuild_death 1
    fi
    echo "Current Projucer Version: $CURRENT_JUCER_VERSION"

    JUCE_CMAKELISTS="../../../../CMakeLists.txt"
    if [ -f "$JUCE_CMAKELISTS" ]; then
        CMAKELISTS_VERSION=$(grep -o 'project(JUCE VERSION [0-9]\+\.[0-9]\+\.[0-9]\+' $JUCE_CMAKELISTS | awk '{print $3}')
    else
        echo "Error: JUCE CMakeLists.txt not found for version comparison..."
        projucerbuild_death 2
    fi
    echo "Current JUCE Version: $CMAKELISTS_VERSION"

    if [ "$CURRENT_JUCER_VERSION" == "$CMAKELISTS_VERSION" ]; then
        echo "Projucer is up to date"

        # check if any arg is a --force flag in one line
        if [[ "$@" == *--force* ]]; then
            echo "Forcing build..."
        else
            projucerbuild_death 0
        fi
    fi

    echo "Projucer version is out of sync, building..."
fi

eval $BUILD_CMD

if [ ! -f "$BINARY" ]; then
    echo "Error, Projucer binary not found after build..."
    projucerbuild_death 1
fi

projucerbuild_death 0