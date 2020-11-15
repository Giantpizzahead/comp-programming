#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
using namespace std;

int genRand(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, const char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <seed> <MAXN>" << endl;
        return -1;
    }
    
    srand(hash<string>{}(argv[1]));
    int N = genRand(1, stoi(argv[2]));
    cout << N << endl;
    for (int i = 0; i < N; i++) {
        while (true) {
            int x1 = genRand(0, N);
            int y1 = genRand(0, N);
            int x2 = genRand(0, N);
            int y2 = genRand(0, N);
            if (x1 == x2 || y1 == y2) continue;
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
            break;
        }
    }
    return 0;
}