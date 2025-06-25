#!/bin/bash

# Get the currently open .cpp file in VS Code
cppfile=$(basename "$(ls -t *.cpp | head -n 1)")

g++ -std=c++17 -O2 -Wall "$cppfile" -o main.out
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

if [ ! -f in.txt ]; then
    echo "in.txt not found."
    exit 1
fi

./main.out < in.txt > out.txt
rm -f main.out
echo "Output written to out.txt"