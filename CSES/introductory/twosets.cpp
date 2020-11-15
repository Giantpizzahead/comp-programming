#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
using namespace std;
using ll = long long;

const int MAXN = 1000005;

int N;
bool used[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> N;
    if ((N+1)/2 % 2 == 1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        ll targetSum = (ll) N * (N+1) / 4;
        int numUsed = 0;
        for (int i = N; targetSum != 0; i--) {
            if (targetSum >= i) {
                targetSum -= i;
                used[i] = true;
                numUsed++;
            }
        }
        cout << numUsed << '\n';
        numUsed = 0;
        for (int i = 1; i <= N; i++) {
            if (used[i]) {
                if (numUsed++ != 0) cout << ' ';
                cout << i;
            }
        }
        cout << '\n' << N - numUsed << '\n';
        numUsed = 0;
        for (int i = 1; i <= N; i++) {
            if (!used[i]) {
                if (numUsed++ != 0) cout << ' ';
                cout << i;
            }
        }
        cout << '\n';
    }
    return 0;
}