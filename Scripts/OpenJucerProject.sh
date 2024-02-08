#!/bin/bash

BASEDIR="$(dirname "$0")/.."

"$BASEDIR/Scripts/BuildProjucer.sh" || exit $?

if [[ "$OSTYPE" == "darwin"* ]]; then
  PROJUCER="$BASEDIR/Submodules/JUCE/extras/Projucer/Builds/MacOSX/build/Release/Projucer.app/Contents/MacOS/Projucer"
elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]]; then
  PROJUCER="$BASEDIR/Submodules/JUCE/extras/Projucer/Builds/VisualStudio2022/x64/Release/App/Projucer.exe"
else
  echo "Error: This script can only be run on macOS or Windows"
  exit 1
fi

if [ ! -f "$PROJUCER" ]; then
    echo "Error: Projucer binary not found"
    exit 1
fi

"$PROJUCER" "$BASEDIR/Moonbase Plugin Demo.jucer" || exit $?

exit 0