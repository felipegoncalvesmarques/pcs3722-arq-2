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
cd jpeg-6a
make clean
make all
cd ..

JPEG=./jpeg-6a/cjpeg 

# Linha de Execução do Programa
$JPEG -dct int -progressive -opt -outfile output_small_encode.jpeg input_small.ppm
# Execução com Gprof
gprof $JPEG gmon.out > profile-data.txt

