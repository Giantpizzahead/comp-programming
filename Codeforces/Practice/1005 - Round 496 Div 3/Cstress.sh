#!/bin/sh

i=0
while true
do
    echo $i
    i=$((i+1))
    node Agen > test.in
    node Abrute < test.in > test.ans
    node A < test.in > test.out
    diff test.out test.ans || exit
done