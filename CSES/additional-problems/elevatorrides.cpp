#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 20;
const int INF = 1e9+7;

int N, X;
int W[MAXN];
int dp[1 << MAXN];

int rec(int mask, int w, int skip, int i);
int go(int mask);

int go(int mask) {
    if (dp[mask] != -1) return dp[mask];

    // Must use first unused person
    rep(i, 0, N) {
        if ((mask & (1 << i)) == 0) {
            int w = X - W[i];
            int newMask = mask | (1 << i);
            int res = rec(newMask, w, INF, i+1) + 1;
            return dp[mask] = res;
        }
    }

    return -INF;
}

int rec(int mask, int w, int skip, int i) {
    // cout << mask << " " << w << " " << skip << " " << i << endl;
    if (i == N || w < W[i]) {
        if (w < skip) return go(mask);
        else return INF;
    }

    if (mask & (1 << i)) return rec(mask, w, skip, i+1);

    int res = rec(mask | (1 << i), w-W[i], skip, i+1);
    if (res > 1) res = min(rec(mask, w, W[i], i+1), res);
    return res;
}

void solve() {
    cin >> N >> X;
    rep(i, 0, N) cin >> W[i];
    sort(W, W+N);
    rep(i, 0, 1 << N) dp[i] = -1;
    dp[(1 << N)-1] = 0;
    cout << go(0) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}