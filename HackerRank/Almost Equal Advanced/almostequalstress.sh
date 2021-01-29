g++ -O2 -o gen almostequalgen.cpp
g++ -O2 -o solright almostequal.cpp
g++ -O2 -o soltest almostequal3.cpp

for i in {1..1000}
do
    echo $i
    ./gen $i > test.in
    ./solright < test.in > test.ans
    ./soltest < test.in > test.out
    diff test.ans test.out || exit
done