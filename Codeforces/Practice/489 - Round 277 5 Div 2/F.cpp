/*
https://codeforces.com/contest/489/problem/F

Solution:
7 so far
zero: 3, one: 4, two: 5, rows left: 5
dp[i][j][k] = # of ways to fill i rows with j columns at 0, k columns at 1
dp[i][j][k] = sum of...
Place both 1s in columns with 0
dp[i-1][j+2][k-2] * (j+2)(j+1)/2
Place both 1s in columns with 1
dp[i-1][j][k+2] * (k+2)(k+1)/2
Place one 1 in each type
dp[i-1][j+1][k] * (j+1) * (k)

With fixed i and j, k can be derived, so only N^2 states matter
Runtime: O(N^2)
Memory: O(N^2)
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 505;

int N, M;
ll mod;
ll dp[2][MAXN][MAXN];
int upd[2][MAXN][MAXN];
int cnt[MAXN];

inline void plusMod(ll& a, ll b) {
    a = (a + b) % mod;
}

void solve() {
    cin >> N >> M >> mod;
    rep(i, 0, M) {
        string s; cin >> s;
        rep(j, 0, N) {
            if (s[j] == '1') cnt[j]++;
        }
    }
    int num0 = 0, num1 = 0;
    rep(i, 0, N) {
        if (cnt[i] == 0) num0++;
        else if (cnt[i] == 1) num1++;
    }
    int cr = 0;
    dp[cr][num0][num1] = 1;
    upd[cr][num0][num1] = M;
    rep(i, M, N) {
        cr = 1 - cr;
        rep(j, 0, N+1) {
            int k = 2*(N-j-i-1);
            if (k < 0 || k > N) continue;
            dp[cr][j][k] = 0;
            upd[cr][j][k] = i+1;
            if (j <= N-2 && k >= 2 && upd[1-cr][j+2][k-2] == i) plusMod(dp[cr][j][k], dp[1-cr][j+2][k-2] * (j+2)*(j+1)/2);
            if (k <= N-2 && upd[1-cr][j][k+2] == i) plusMod(dp[cr][j][k], dp[1-cr][j][k+2] * (k+2)*(k+1)/2);
            if (j <= N-1 && k >= 1 && upd[1-cr][j+1][k] == i) plusMod(dp[cr][j][k], dp[1-cr][j+1][k] * (j+1)*k);
            // if (dp[cr][j][k] != 0) debug << "dp[" << i << "][" << j << "][" << k << "] = " << dp[cr][j][k] << "\n";
        }
    }
    cout << dp[cr][0][0] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}