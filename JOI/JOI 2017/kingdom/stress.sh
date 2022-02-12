echo "Compiling..."
g++ --std=c++11 -o sol -O2 kingdomwrong.cpp
g++ --std=c++11 -o correct -O2 kingdombrute.cpp 
g++ --std=c++11 -o gen kingdomgen.cpp
chmod +x ./gen
chmod +x ./sol
chmod +x ./correct

for ((i = 2020; ; i++)); do
    echo $i
    ./gen $i > test.in
    ./sol < test.in > test.out
    ./correct < test.in > test.ans
    diff test.out test.ans || break
done

echo "Wrong test found!"
