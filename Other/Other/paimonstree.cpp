/**
 * dp[i][a][b][m] = Max diameter when planning to use the path from node a to node b
 * i is the current weight in the integer sequence
 * m is a 2 bit mask representing whether the outermost edges have a weight assigned
 * 0 = Both, 1 = Not a, 2 = Not b, 3 = Neither
 * 
 * Base case: dp[0][a][b][1] = 0 for all a, b where dist(a, b) = 1
 * 
 * Transitions:
 * 
 * Extend endpoint a
 * dp[i][a][b][2] -> dp[i][adj(a)][b][3]
 * dp[i][a][b][0] -> dp[i][adj(a)][b][1]
 * Extend endpoint b, same thing
 * 
 * Throw away a weight
 * Can only be done if there is space, can be calculated from known info
 * dp[i][a][b][m] -> dp[i+1][a][b][m]
 * 
 * Use a weight at endpoint a
 * dp[i][a][b][1] + A[i] -> dp[i+1][a][b][0]
 * dp[i][a][b][3] + A[i] -> dp[i+1][a][b][2]
 * Use a weight at endpoint b, same thing
 * 
 * Answer: dp[a][b][0][0] for all a, b
 */

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;
using namespace std;

const int MAXN = 151;
const ll INF = 1e18;

int N;
int A[MAXN];
vector<int> adj[MAXN];

ll dp[MAXN][MAXN][MAXN][4];
// dist[a][b] = Number of edges on the path from a to b
int dist[MAXN][MAXN];
// from[a][b] = One node in the path from a to b (the one closest to b)
int from[MAXN][MAXN];
// between[a][b] = Number of edges between a and b, including branches off the path from a to b
int between[MAXN][MAXN];

void dfsDist(int n, int p, int r, int d) {
    dist[r][n] = d;
    from[r][n] = p;
    for (int e : adj[n]) {
        if (e == p) continue;
        dfsDist(e, n, r, d+1);
    }
}

bool blocked[MAXN];

void dfsBetween(int n, int p, int a, int b) {
    if (blocked[n]) return;
    between[a][b]++;
    for (int e : adj[n]) {
        if (e == p) continue;
        dfsBetween(e, n, a, b);
    }
}

void setMax(ll& a, ll b) {
    a = max(a, b);
}

void solve() {
    // Input parsing
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    N++;

    // Generate tree info
    rep(i, 0, N) dfsDist(i, i, i, 0);
    rep(a, 0, N) {
        rep(b, 0, N) {
            between[a][b] = 1;
            blocked[a] = true, blocked[b] = true;
            dfsBetween(from[a][b], from[a][b], a, b);
            blocked[a] = false, blocked[b] = false;
        }
    }

    // Do the DP
    rep(a, 0, N) {
        rep(b, 0, N) {
            rep(s, 0, N) {
                rep(m, 0, 4) {
                    dp[a][b][s][m] = -INF;
                }
            }
        }
    }
    // Base cases
    rep(a, 0, N) {
        rep(b, 0, N) {
            if (dist[a][b] == 1) dp[0][a][b][1] = 0;
        }
    }
    // Transitions
    rep(i, 0, N-1) {
        rep(m, 0, 4) {
            rep(a, 0, N) {
                rep(b, 0, N) {
                    if (dp[i][a][b][m] == -INF) continue;

                    // Extend endpoint a
                    if (!(m&1)) {
                        for (int e : adj[a]) {
                            if (dist[e][b] < dist[a][b]) continue;
                            setMax(dp[i][e][b][m^1], dp[i][a][b][m]);
                        }
                    }
                    // Extend endpoint b
                    if (!(m&2)) {
                        for (int e : adj[b]) {
                            if (dist[a][e] < dist[a][b]) continue;
                            setMax(dp[i][a][e][m^2], dp[i][a][b][m]);
                        }
                    }
                    // Throw away a weight
                    int numSpaces = between[a][b] - i;
                    if (m&1) numSpaces--;
                    if (m&2) numSpaces--;
                    if (numSpaces != 0) setMax(dp[i+1][a][b][m], dp[i][a][b][m]);

                    // Use a weight at endpoint a
                    if (m&1) setMax(dp[i+1][a][b][m^1], dp[i][a][b][m] + A[i]);
                    // Use a weight at endpoint b
                    if (m&2) setMax(dp[i+1][a][b][m^2], dp[i][a][b][m] + A[i]);

                    debug << "dp[" << i << "][" << a << "][" << b << "][" << m << "] = " << dp[i][a][b][m] << '\n';
                    debug << "numSpaces = " << numSpaces << '\n';
                }
            }
        }
    }

    debug << "between:\n";
    rep(a, 0, N) rep(b, 0, N) debug << between[a][b] << " \n"[b==N-1];

    // Answer
    ll ans = 0;
    rep(a, 0, N) rep(b, 0, N) setMax(ans, dp[N-1][a][b][0]);
    cout << ans << '\n';

    // Clear variables
    rep(i, 0, N) adj[i].clear();
    rep(i, 0, N) blocked[i] = false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}