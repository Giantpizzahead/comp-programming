g++ -O2 -o gen almostequalgen.cpp
g++ -O2 -o sol almostequal5.cpp
./gen 1 > test.in
time ./sol < test.in > test.out