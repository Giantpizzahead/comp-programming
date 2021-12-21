#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using namespace std;
using ll = long long;

const int MAXN = 5005;
const int INF = 1e9;

int T, N, K;
bool B[MAXN];
int X[MAXN], Y[MAXN];
int mustPair[MAXN];

// dp[i][j][k][l] = Max weight of unpaired cows, currently on G(i), H(j)
// Must pair (G or H) until index k to be maximal
const int MAXDP = 305;
int dp[MAXDP][MAXDP][MAXDP*2];

void setMax(int& a, int b) {
    a = max(a, b);
}

void setMin(int& a, int b) {
    a = min(a, b);
}

vector<vector<int>> dp2;

void solve1() {
    // dp[a][b] = Min weight of unpaired cows, currently on G(i), H(j)
    dp2.resize(N+1, vector<int>(N+1));
    rep(i, 0, N+1) {
        rep(j, 0, N+1) {
            dp2[i][j] = INF;
        }
    }
    dp2[0][0] = 0;
    rep(i, 0, N+1) {
        rep(j, 0, N+1) {
            if (dp2[i][j] == INF) continue;
            else if (i != N && !B[i]) {
                // Incorrect breed
                setMin(dp2[i+1][j], dp2[i][j]);
            } else if (j != N && B[j]) {
                // Incorrect breed
                setMin(dp2[i][j+1], dp2[i][j]);
            } else {
                // Don't pair
                if (i != N) setMin(dp2[i+1][j], dp2[i][j] + Y[i]);
                if (j != N) setMin(dp2[i][j+1], dp2[i][j] + Y[j]);
                // Pair
                if (i != N && j != N && abs(X[i] - X[j]) <= K) {
                    setMin(dp2[i+1][j+1], dp2[i][j]);
                }
            }
        }
    }
    cout << dp2[N][N] << '\n';
}

void solve() {
    cin >> T >> N >> K;
    rep(i, 0, N) {
        char c;
        cin >> c >> X[i] >> Y[i];
        B[i] = (c == 'G');
    }
    if (T == 1) {
        solve1();
        return;
    }
    rep(i, 0, N) {
        mustPair[i] = i;
        while (true) {
            if (mustPair[i] == N || X[mustPair[i]] - X[i] > K) {
                // Out of range; this cow does not need to be paired
                // Find last cow that did need to be paired
                while (mustPair[i] == N || B[i] == B[mustPair[i]] || X[mustPair[i]] - X[i] > K) {
                    mustPair[i]--;
                    if (mustPair[i] == i) break;
                }
                break;
            }
            mustPair[i]++;
        }
    }
    // rep(i, 0, N) cout << mustPair[i] << " \n"[i==N-1];

    rep(i, 0, N+1) rep(j, 0, N+1) rep(k, 0, N*2+1) dp[i][j][k] = -INF;
    dp[0][0][0] = 0;
    rep(i, 0, N+1) {
        rep(j, 0, N+1) {
            rep(k, 0, N*2+1) {
                if (dp[i][j][k] == -INF) continue;
                else if (i != N && !B[i]) {
                    // Incorrect breed
                    setMax(dp[i+1][j][k], dp[i][j][k]);
                } else if (j != N && B[j]) {
                    // Incorrect breed
                    setMax(dp[i][j+1][k], dp[i][j][k]);
                } else {
                    // Pair the cows
                    if (i != N && j != N && abs(X[i] - X[j]) <= K) {
                        // cout << "trans pair\n";
                        setMax(dp[i+1][j+1][k], dp[i][j][k]);
                    }
                    // Leave i unpaired
                    bool b = (k <= N);
                    int loc = k-1;
                    if (!b) loc -= N;
                    if (i != N && (loc == -1 || i > loc || B[i] != b)) {
                        // cout << "trans i " << loc << "\n";
                        setMax(dp[i+1][j][mustPair[i]+N+1], dp[i][j][k] + Y[i]);
                    }
                    // Leave j unpaired
                    if (j != N && (loc == -1 || j > loc || B[j] != b)) {
                        // cout << "trans j " << loc << "\n";
                        setMax(dp[i][j+1][mustPair[j]+1], dp[i][j][k] + Y[j]);
                    }
                }
                // cout << "dp[" << i << "][" << j << "][" << k << "] = " << dp[i][j][k] << "\n";
            }
        }
    }

    int ans = 0;
    rep(k, 0, N*2+1) ans = max(dp[N][N][k], ans);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}