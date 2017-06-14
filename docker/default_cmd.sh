#!/bin/bash
set -ex

fail() {
    echo $1 >&2
    exit 1
}

SRC=/home/student/src
# Program compilation
if ! cd $SRC; then
    fail "Mount a volume with the program being to be profiled under $SRC"
fi
make clean
make 
./program
gprof program gmon.out > profile-data.txt

