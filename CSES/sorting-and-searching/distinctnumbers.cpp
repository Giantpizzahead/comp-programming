#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;

int N;
int X[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> X[i];
    sort(X, X+N);
    X[N] = 1e9+7;
    int ans = 0;
    rep(i, 0, N) {
        if (X[i] != X[i+1]) {
            ans++;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}