g++ -O2 gen.cpp -o gen

for i in {1..1000}
do
    echo $i
    ./gen "ldfol$i" > test.in
    ./keys < test.in > test.ans
    ./keysfast < test.in > test.out
    diff test.out test.ans || exit
done