echo "Compiling files..."
g++ -o sol1 NKMARSsegt.cpp -O2
g++ -o sol2 NKMARSsegt2.cpp -O2
g++ -o gen NKMARSgen.cpp -O2
echo "Starting stress test..."
for i in {1..100}
do
    echo "$i"
    ./gen $(($i)) $(($i)) > test.in
    ./sol1 < test.in > test1.out
    ./sol2 < test.in > test2.out
    diff test1.out test2.out || exit
done
echo "Stress test passed!"