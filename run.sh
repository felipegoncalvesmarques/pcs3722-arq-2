#!/bin/bash
set -e

fail() {
    echo $1 >&2    
    exit 1
}

NUMBER_OF_ARGUMENTS=$#
PROGRAM_FOLDER="$PWD/hello-world"
VOLUMES="-v $PROGRAM_FOLDER:/home/student/src"

BUILD_COMMAND="docker build -t arq ./docker"
DEFAULT_COMMAND="docker run -ti $VOLUMES arq"
INTERACTIVE_COMMAND="docker run -it $VOLUMES arq bash"

if [ $NUMBER_OF_ARGUMENTS -eq 0 ]
then
    echo "Running default program..."
    eval $DEFAULT_COMMAND
    # docker run -v "$PWD"/../linux:/home/student/src/linux -v "$PWD":/home/student/src/initramfs so
else
    if [ $NUMBER_OF_ARGUMENTS -gt 1 ]
    then
        fail "You must supply only one argument, run the command with --help or -h to see the options."
    else
        case $1 in
            --interactive|-i) echo "Running in interactive"
                eval $INTERACTIVE_COMMAND
                ;;
            --build|-b) echo "Building image"
                eval $BUILD_COMMAND
                ;;
            --help|-h) echo "help - to be developed"
                ;;
            --debuger|-d) echo "debug - to be developed"
                eval $DEBUG_COMMAND
                ;;
            *)  fail "Unknown option" 
                ;;
        esac
    fi
fi