echo "Compiling..."
g++ sugarrushbrute.cpp -O2 --std=c++17 -o brute
g++ sugarrushgen.cpp -O2 --std=c++17 -o gen
g++ sugarrushbutfast.cpp -O2 --std=c++17 -o sol
for((i = 1; ; ++i)); do
    ./gen $i > test.in
    ./sol < test.in > test.out
    ./brute < test.in > test.ans
    diff test.out test.ans > /dev/null || break
    echo "Passed test: "  $i
done
echo "WA on the following test:"
cat test.in
echo "Your answer is:"
cat test.out
echo "Correct answer is:"
cat test.ans