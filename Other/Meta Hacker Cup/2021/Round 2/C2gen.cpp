#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

void solve() {
    int R = 1400;
    int C = 1400;
    int S = 2000000;
    int K = 700;
    cout << 1 << '\n';
    cout << R << ' ' << C << ' ' << K << ' ' << S << '\n';
    rep(i, 0, R) {
        rep(j, 0, C) {
            cout << 'X';
        }
        cout << '\n';
    }
    rep(i, 0, S) {
        cout << "728 739" << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "w", stdout);
    solve();
    return 0;
}