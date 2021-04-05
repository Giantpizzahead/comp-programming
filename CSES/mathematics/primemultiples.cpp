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
ll N;
__int128_t ans = 0;

void go(int i, int m, __int128_t p) {
    if (i == K) {
        ans += N / p * m;
        return;
    }
    go(i+1, m, p);
    p *= A[i];
    if (p <= N) go(i+1, -m, p);
}

void solve() {
    cin >> N >> K;
    rep(i, 0, K) cin >> A[i];
    go(0, -1, 1);
    cout << (ll) ans + N << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}