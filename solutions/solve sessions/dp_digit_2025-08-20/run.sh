#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: ./run.sh <filename_without_extension>"
    exit 1
fi

file="$1.cpp"
exe="$1.out"

if [ ! -f "$file" ]; then
    echo "$file not found!"
    exit 1
fi

g++ -std=c++17 -O2 -Wall "$file" -o "$exe"
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

./"$exe" < in.txt > out.txt
echo "Execution finished. Output is in out.txt"

rm -f "$exe"
