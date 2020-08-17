#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int N, K, D;

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> K >> D;
    K = min(N, K);

    if (K == 1 && N != 1) {
        // Impossible
        cout << -1 << endl;
        return 0;
    }

    ll pow = K;
    int cycleLength = 1;
    while (pow < N) {
        pow *= K;
        cycleLength++;
    }

    if (cycleLength - 1 >= D) {
        cout << -1 << endl;
        return 0;
    }

    for (int i = 0; i < cycleLength; i++) {
        pow /= K;
        for (int j = 0; j < N; j++) {
            if (j != 0) cout << ' ';
            cout << (j / pow % K) + 1;
        }
        cout << endl;
    }
    // Fill in remaining
    for (int i = cycleLength; i < D; i++) {
        for (int j = 0; j < N; j++) {
            if (j != 0) cout << ' ';
            cout << 1;
        }
        cout << endl;
    }
}