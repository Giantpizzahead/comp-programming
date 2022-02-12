/*
Solution: Floodfill to find the islands. Then, find APSP using N BFSs. Finally, use bitwise DP to get the answer.
DP state - dp[mask][j] = Min distance to visit mask nodes, currently on node j
Runtime: O(NRC + 2^N * N^2)
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 15;
const int MAXD = 50;
const int INF = 1e9;

int R, C, N;
int adj[MAXN][MAXN];

int X[MAXD][MAXD];
char A[MAXD][MAXD];

int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};

void dfsIsland(int i, int j) {
    X[i][j] = N;
    rep(d, 0, 4) {
        int ni = i + ci[d], nj = j + cj[d];
        if (ni < 0 || nj < 0 || ni >= R || nj >= C || A[ni][nj] != 'X' || X[ni][nj] != -1) continue;
        dfsIsland(ni, nj);
    }
}

int dist[MAXD][MAXD];

void bfsIsland(int si, int sj) {
    // Visited distances
    rep(i, 0, R) rep(j, 0, C) dist[i][j] = INF;
    dist[si][sj] = 0;
    // Main BFS loop
    struct Loc {
        int i, j;
    };
    deque<Loc> q;
    q.push_back({si, sj});
    while (!q.empty()) {
        Loc l = q.front(); q.pop_front();
        if (A[l.i][l.j] == 'X') adj[X[si][sj]][X[l.i][l.j]] = dist[l.i][l.j];
        rep(d, 0, 4) {
            int ni = l.i + ci[d], nj = l.j + cj[d];
            if (ni < 0 || nj < 0 || ni >= R || nj >= C || A[ni][nj] == '.' || dist[ni][nj] != INF) continue;
            if (A[ni][nj] == 'X') {
                dist[ni][nj] = dist[l.i][l.j];
                q.push_front({ni, nj});
            } else {
                dist[ni][nj] = dist[l.i][l.j] + 1;
                q.push_back({ni, nj});
            }
        }
    }
}

int dp[1 << MAXN][MAXN];

void doDP() {
    rep(i, 0, 1 << N) rep(j, 0, N) dp[i][j] = INF;
    rep(j, 0, N) dp[1 << j][j] = 0;
    rep(i, 0, 1 << N) {
        rep(j, 0, N) {
            // Transitions
            int oldI = i ^ (1 << j);
            rep(k, 0, N) {
                if (j == k || (i & (1 << k)) == 0) continue;
                dp[i][j] = min(dp[oldI][k] + adj[k][j], dp[i][j]);
            }
            // bitset<3> bs(i);
            // debug << bs << " " << j << " = " << dp[i][j] << '\n';
        }
    }
}

void solve() {
    cin >> R >> C;
    rep(i, 0, R) {
        string s; cin >> s;
        rep(j, 0, C) {
            A[i][j] = s[j];
            X[i][j] = -1;
        }
    }

    // Find islands
    N = 0;
    rep(i, 0, R) {
        rep(j, 0, C) {
            if (A[i][j] != 'X' || X[i][j] != -1) continue;
            dfsIsland(i, j);
            N++;
        }
    }

    // Find APSP
    rep(i, 0, N) adj[i][i] = -1;
    rep(i, 0, R) {
        rep(j, 0, C) {
            if (A[i][j] != 'X' || adj[X[i][j]][X[i][j]] != -1) continue;
            adj[X[i][j]][X[i][j]] = 0;
            bfsIsland(i, j);
        }
    }

    // Do DP
    doDP();
    int ans = INF;
    rep(j, 0, N) ans = min(dp[(1 << N) - 1][j], ans);
    cout << ans << '\n';

    // rep(i, 0, N) {
    //     rep(j, 0, N) {
    //         debug << adj[i][j] << ' ';
    //     }
    //     debug << endl;
    // }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);
    solve();
    return 0;
}