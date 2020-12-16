#include <iostream>
using namespace std;

int calcA(int n) {
    int k = 1, m = 1;
    while (m != 0) {
        m = (m * 10 + 1) % n;
        k++;
    }
    return k;
}

int main() {
    for (int i = 1000000; i < 1000100; i++) {
        if (i % 2 == 0 || i % 5 == 0) continue;
        if (calcA(i) > 1000000) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}