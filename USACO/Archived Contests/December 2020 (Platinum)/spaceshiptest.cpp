#include <bits/stdc++.h>
using namespace std;

int moves[32];

void test(int i, int m, int x) {
    if (i >= x) {
        if (i == x) moves[m]++;
        return;
    }
    test(i+1, m+1, x);
    test(i+2, m+1, x);
    test(i+4, m+1, x);
    test(i+8, m+1, x);
    test(i+16, m+1, x);
}

int main() {
    for (int i = 1; i < 20; i++) {
        cout << "count " << i << " = ";
        for (int j = 0; j < 32; j++) moves[j] = 0;
        test(0, 0, i);
        for (int j = 1; j <= i; j++) cout << moves[j] << ' ';
        cout << endl;
    }
    return 0;
}