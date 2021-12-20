/*
Solution:
dp[i][j] = Min area of a i x j slab that must be wasted
Base cases -> dp[i][j] = i*j, dp[desired w][desired h] = 0
Trans -> Cut vertically or horizontally

Runtime: Fast O(N^3)
*/ 

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 205;
const int MAXW = 605;
const int INF = 1e9;

int W, H, N;
int A[MAXN], B[MAXN];
int dp[MAXW][MAXW];

void solve() {
    cin >> W >> H >> N;
    rep(i, 0, N) cin >> A[i] >> B[i];
    rep(i, 0, W+1) {
        rep(j, 0, H+1) {
            dp[i][j] = i * j;
        }
    }
    rep(i, 0, N) dp[A[i]][B[i]] = 0;
    rep(i, 1, W+1) {
        rep(j, 1, H+1) {
            // Cut vertically
            rep(k, 1, i) dp[i][j] = min(dp[k][j] + dp[i-k][j], dp[i][j]);
            // Cut horizontally
            rep(k, 1, j) dp[i][j] = min(dp[i][k] + dp[i][j-k], dp[i][j]);
        }
    }
    cout << dp[W][H] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}