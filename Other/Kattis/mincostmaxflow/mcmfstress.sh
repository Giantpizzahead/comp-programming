echo "Compiling code..."
g++ -o gen -O2 mcmfgen.cpp
g++ -o sol -O2 mincostmaxflow.cpp

i=0
while true
do
    let i=i+1
    echo $i
    ./gen $i > test.in
    ./sol < test.in > test.out
    if [ ! $? -eq 0 ]
    then
        exit
    fi
done