#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>

using namespace std;

const int MAXN = 20000;

bool isGood[MAXN];

void solve() {
    for (int i = 0; i < 0b1111111111; i++) {
        int num = 0, pow3 = 1;
        for (int j = 0; j < 10; j++) {
            if (i & (1 << j)) num += pow3;
            pow3 *= 3;
        }
        if (num < MAXN) isGood[num] = true;
    }
    int Q, N;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> N;
        for (int j = N;; j++) {
            if (isGood[j]) {
                cout << j << endl;
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}