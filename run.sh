#!/bin/bash
set -e

fail() {
    echo $1 >&2    
    exit 1
}

help() {
    echo "Incorrect use."
    echo "For building, run ./run.sh -b"
    echo "For running, run ./run.sh mode folder"
    echo "  where:"
    echo "      <mode>= -i, -d or -n"
    echo "      <folder>= the program folder in absolute path to be profiled"
    fail 
}

NUMBER_OF_ARGUMENTS=$#
BUILD_COMMAND="docker build -t arq ./docker"

if [ $NUMBER_OF_ARGUMENTS -eq 0 ]
then
    help
    # docker run -v "$PWD"/../linux:/home/student/src/linux -v "$PWD":/home/student/src/initramfs so
else
    if [ $NUMBER_OF_ARGUMENTS -gt 2 ]
    then
        fail "You must supply only one argument, run the command with --help or -h to see the options."
    else
        if [ $NUMBER_OF_ARGUMENTS -eq 1 ]
        then
            if [ $1 == "-b" ] || [ $1 == "--build" ]
            then
                echo "Running build command"
                eval $BUILD_COMMAND
            else
                help
            fi
        else
            PROGRAM_FOLDER=$2
            VOLUMES="-v $PROGRAM_FOLDER:/home/student/src"

            DEFAULT_COMMAND="docker run -ti $VOLUMES arq"
            INTERACTIVE_COMMAND="docker run -it $VOLUMES arq bash"
            case $1 in
                --interactive|-i) echo "Running in interactive"
                    eval $INTERACTIVE_COMMAND
                    ;;
               --help|-h) help
                    ;;
                --debuger|-d) echo "debug - to be developed"
                    eval $DEBUG_COMMAND
                    ;;
                --normal|-n) echo "normal"
                    eval $DEFAULT_COMMAND
                    ;;
                *)  fail "Unknown option" 
                    ;;
            esac
        fi
    fi
fi