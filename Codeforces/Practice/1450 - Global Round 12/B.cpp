#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 102;

int N, K;
int X[MAXN], Y[MAXN];

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
    }
    for (int i = 0; i < N; i++) {
        bool allWorks = true;
        for (int j = 0; j < N; j++) {
            if (abs(X[i] - X[j]) + abs(Y[i] - Y[j]) > K) {
                allWorks = false;
                break;
            }
        }
        if (allWorks) {
            cout << 1 << '\n';
            return;
        }
    }
    cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}