#!/bin/bash

if [ $OSTYPE == "msys" ] || [ $OSTYPE == "cygwin" ]; then
    export DEV_ENV_EXE="$(which devenv.exe)"
    if [ -z "$DEV_ENV_EXE" ]; then
        echo "dev env not found, trying default path"
        export DEV_ENV_EXE="C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/devenv.exe" #devenv.exe is the cli version of visual studio
    fi

    if [ ! -f "$DEV_ENV_EXE" ]; then
        echo "Error: Visual Studio devenv.exe not found in PATH or at: $DEV_ENV_EXE"
        return 1
    fi
    echo "Visual Studio found at: $DEV_ENV_EXE"
fi

return 0