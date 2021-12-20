#include <iostream>
using namespace std;
using ll = long long;

const int MOD = 20201227;

ll pow7[MOD];

void precalc(ll x) {
    ll b = 1;
    for (int e = 0; e < MOD; e++) {
        pow7[e] = b;
        b = b * x % MOD;
    }
}

int C, D;

bool testLoopSize(int L, int X) {
    return pow7[L] == X;
}

int main() {
    precalc(7);
    cin >> C >> D;
    int A, B;
    for (int i = 0; i < MOD-1; i++) {
        if (testLoopSize(i, C)) A = i;
        if (testLoopSize(i, D)) B = i;
    }
    precalc(D);
    cout << "Card Key: " << pow7[A] << endl;
    precalc(C);
    cout << "Door Key: " << pow7[B] << endl;
    return 0;
}