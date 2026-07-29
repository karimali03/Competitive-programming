#!/bin/bash
if [ $# -ne 1 ]; then echo "Usage: ./run.sh <file>"; exit 1; fi
g++ -std=c++17 -O2 -Wall "$1.cpp" -o "$1.out" && ./$1.out < in.txt > out.txt
rm -f "$1.out"
echo "Done."
