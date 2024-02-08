#!/bin/bash

BASEDIR="$(dirname "$0")/.."

if [[ "$OSTYPE" == "darwin"* ]]; then

  echo "Running on macOS"
  cd "$BASEDIR/Submodules/JUCE/extras/Projucer/Builds/MacOSX"
  BINARY="./build/Release/Projucer.app/Contents/MacOS/Projucer"
  BUILD_CMD="xcodebuild -project Projucer.xcodeproj -configuration Release -target \"Projucer - App\""

elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]]; then

  echo "Running on Windows"
  cd "$BASEDIR/Submodules/JUCE/extras/Projucer/Builds/VisualStudio2022"
  BINARY="./x64/Release/App/Projucer.exe"
  BUILD_CMD="MSBuild.exe Projucer_App.vcxproj -p:Configuration=Release -p:Platform=x64"

else
  echo "Error: This script can only be run on macOS or Windows"
  exit 1
fi

if [ -f "$BINARY" ]; then
    echo "Projucer binary found, skipping Projucer build..."
    exit 0
fi

eval $BUILD_CMD || exit $?

if [ ! -f "$BINARY" ]; then
    echo "Error, Projucer binary not found after build..."
    exit 1
fi

exit 0