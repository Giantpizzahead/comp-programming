#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int X;

void solve() {
    cin >> X;
    int L = 0, J = 0;
    while (L < X) {
        J++;
        L += J;
    }
    if (L - 1 == X) cout << J + 1 << endl;
    else cout << J << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}