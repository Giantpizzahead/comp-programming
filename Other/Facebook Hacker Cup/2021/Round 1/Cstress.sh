#!/bin/sh

echo Compiling...
g++ -O2 -o sol_test C.cpp
g++ -O2 -o sol_naive Cnaive.cpp
g++ -O2 -o gen Cgen.cpp

i=0
while true; do
    i=$((i+1))
    echo $i
    ./gen > input.txt
    ./sol_naive
    mv output.txt correct.txt
    ./sol_test
    mv output.txt unknown.txt
    diff correct.txt unknown.txt || exit
done