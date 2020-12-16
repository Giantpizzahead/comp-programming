#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N;

void solve() {
    cin >> N;
    double P = 1;
    int S;
    for (int i = 0; i < N; i++) {
        cin >> S;
        S += 100;
        P *= S / 100.0;
    }
    cout << P * 100 - 100 << endl;
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