#!/bin/sh

echo "Compiling files..."
g++ -o solmodel CHANGE.cpp -O2
g++ -o soltest CHANGE.cpp -O2
g++ -o gen CHANGE.cpp -O2
echo "Starting stress test..."
for i in {1..1000}
do
    echo "$i"
    ./gen $(($i)) $(($i)) > test.in
    ./solmodel < test.in > test1.out
    ./soltest < test.in > test2.out
    diff test1.out test2.out || exit
done
echo "Stress test passed!"