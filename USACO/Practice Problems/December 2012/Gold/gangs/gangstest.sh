g++ -o main --std=c++11 -O2 -DNDEBUG gangsOn.cpp
echo "\nO(n)"
time ./main

# g++ -o main --std=c++11 -O2 -DNDEBUG gangsOn2.cpp
# echo "\nO(n^2)"
# time ./main

# g++ -o main --std=c++11 -O2 -DNDEBUG gangsOn3.cpp
# echo "\nO(n^3)"
# time ./main

# diff gangs.out2 gangs.out || exit
# diff gangs.out3 gangs.out2 || exit
# echo "\nAll answers match!"
