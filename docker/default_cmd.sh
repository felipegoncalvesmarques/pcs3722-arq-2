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
make all

JPEG=./jpec 

# Linha de Execução do Programa
$JPEG input_large2.png

# Execução com Gprof
gprof $JPEG gmon.out > profile-data.txt

