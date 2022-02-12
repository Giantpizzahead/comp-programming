#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;

void solve() {
    int N = 100000;
    int K = 100000000;
    cout << N << " " << K << '\n';
    rep(i, 0, N) cout << rand() % 10000 + 8000 * i + 1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}