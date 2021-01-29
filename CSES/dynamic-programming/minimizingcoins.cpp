#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define repinc(i, a, b) for (int i = (a); i <= (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 100, MAXX = 1e6+1, INF = 1e9;

int N, X;
int C[MAXN];
int dp[MAXX];

void solve() {
    cin >> N >> X;
    rep(i,0,N) cin >> C[i];
    repinc(i,0,X) dp[i] = INF;
    dp[0] = 0;
    rep(i,0,N) {
        repinc(j,C[i],X) {
            dp[j] = min(dp[j-C[i]]+1, dp[j]);
        }
    }
    cout << (dp[X] == INF ? -1 : dp[X]) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}