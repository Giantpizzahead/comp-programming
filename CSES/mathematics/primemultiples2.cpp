#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXK = 20;

int K;
ll A[MAXK];
ll N, ans = 0;

void go(int i, int m, ll d) {
    if (i == K) {
        if (m) ans += d;
        else ans -= d;
        return;
    }
    go(i+1, m, d);
    d /= A[i];
    if (d != 0) go(i+1, !m, d);
}

void solve() {
    cin >> N >> K;
    rep(i, 0, K) cin >> A[i];
    go(0, false, N);
    cout << ans + N << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}