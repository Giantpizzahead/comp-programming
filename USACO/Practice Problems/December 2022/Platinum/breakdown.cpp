/*
http://usaco.org/index.php?page=viewproblem2&cpid=1260

Solution:
Process queries in reverse order (add edges instead of removing).
Maintain dp2[a][b] = Min cost path using 2 edges from a to b. Also maintain min cost paths from 1 to each node using
3 or 4 edges, and min cost paths from each node to N using 3 or 4 edges. Combine these values to get the min cost path
of length K (using a meet in the middle-like technique).
Can do this in O(N) amortized time per edge, for a runtime of O(N^3). See the code for details.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 305;
const int INF = 1e9;

int N, K;
int adj[MAXN][MAXN], W[MAXN][MAXN];
int A[MAXN*MAXN], B[MAXN*MAXN];
vector<int> ans;

// dp2[a][b] = Min cost path using 2 edges from a to b
int dp2[MAXN][MAXN];
// dp3From1[n] = Min cost path using 3 edges from 1 to n
int dp3From1[MAXN];
// dp3ToN[n] = Min cost path using 3 edges from n to N
int dp3ToN[MAXN];
// dp4From1[n] = Min cost path using 4 edges from 1 to n
int dp4From1[MAXN];
// dp4ToN[n] = Min cost path using 4 edges from n to N
int dp4ToN[MAXN];

void setMin(int& a, int b) {
    a = min(a, b);
}

int addEdge(int X, int Y) {
    adj[X][Y] = W[X][Y];

    // Update dp2
    // Using (X, Y) as first edge: X -> Y -> j
    rep(j, 1, N+1) setMin(dp2[X][j], adj[X][Y] + adj[Y][j]);
    // Using (X, Y) as second edge: i -> X -> Y
    rep(i, 1, N+1) setMin(dp2[i][Y], adj[i][X] + adj[X][Y]);

    // Update dp3From1
    // Using (X, Y) as first edge: (X = 1) -> Y -> ? -> n
    if (X == 1) rep(n, 1, N+1) setMin(dp3From1[n], adj[1][Y] + dp2[Y][n]);
    // Using (X, Y) as second edge: 1 -> X -> Y -> n
    rep(n, 1, N+1) setMin(dp3From1[n], adj[1][X] + adj[X][Y] + adj[Y][n]);
    // Using (X, Y) as third edge: 1 -> ? -> X -> (Y = n)
    setMin(dp3From1[Y], dp2[1][X] + adj[X][Y]);

    // Update dp3ToN
    // Using (X, Y) as first edge: (X = n) -> Y -> ? -> N
    setMin(dp3ToN[X], adj[X][Y] + dp2[Y][N]);
    // Using (X, Y) as second edge: n -> X -> Y -> N
    rep(n, 1, N+1) setMin(dp3ToN[n], adj[n][X] + adj[X][Y] + adj[Y][N]);
    // Using (X, Y) as third edge: n -> ? -> X -> (Y = N)
    if (Y == N) rep(n, 1, N+1) setMin(dp3ToN[n], dp2[n][X] + adj[X][N]);

    // dp4From1
    // 1st if X = 1: 1 ->-> ? ->-> n
    if (X == 1) rep(a, 1, N+1) rep(n, 1, N+1) setMin(dp4From1[n], dp2[1][a] + dp2[a][n]);
    // 2nd: 1 ->-> Y ->-> n
    rep(n, 1, N+1) setMin(dp4From1[n], dp2[1][Y] + dp2[Y][n]);
    // 3rd: 1 ->-> X ->-> n
    rep(n, 1, N+1) setMin(dp4From1[n], dp2[1][X] + dp2[X][n]);
    // 4th if Y = n: 1 ->->-> X -> Y
    setMin(dp4From1[Y], dp3From1[X] + adj[X][Y]);

    // dp4ToN
    // 1st if X = n: n -> Y ->->-> N
    setMin(dp4ToN[X], adj[X][Y] + dp3ToN[Y]);
    // 2nd: n ->-> Y ->-> N
    rep(n, 1, N+1) setMin(dp4ToN[n], dp2[n][Y] + dp2[Y][N]);
    // 3rd: n ->-> X ->-> N
    rep(n, 1, N+1) setMin(dp4ToN[n], dp2[n][X] + dp2[X][N]);
    // 4th if Y = N: n ->-> ? ->-> N
    if (Y == N) rep(a, 1, N+1) rep(n, 1, N+1) setMin(dp4ToN[n], dp2[n][a] + dp2[a][N]);

    // Calculate answer
    int ans = INF;
    if (K == 2) ans = dp2[1][N];
    else if (K == 3) ans = dp3From1[N];
    else if (K == 4) {
        // 1 -> ? -> ? -> n -> N
        rep(n, 1, N+1) setMin(ans, dp3From1[n] + adj[n][N]);
        return ans;
    } else if (K == 5) {
        // 1 -> ? -> ? -> n -> ? -> N
        rep(n, 1, N+1) setMin(ans, dp3From1[n] + dp2[n][N]);
    } else if (K == 6) {
        // 1 -> ? -> ? -> n -> ? -> ? -> N
        rep(n, 1, N+1) setMin(ans, dp3From1[n] + dp3ToN[n]);
    } else if (K == 7) {
        // 1 ->->->-> n ->->-> N
        rep(n, 1, N+1) setMin(ans, dp4From1[n] + dp3ToN[n]);
    } else {
        // 1 ->->->-> n ->->->-> N
        rep(n, 1, N+1) setMin(ans, dp4From1[n] + dp4ToN[n]);
    }
    return ans;
}

void solve() {
    cin >> N >> K;
    rep(i, 1, N+1) {
        rep(j, 1, N+1) {
            cin >> W[i][j];
            adj[i][j] = INF;
            dp2[i][j] = INF;
        }
        dp3From1[i] = INF;
        dp3ToN[i] = INF;
        dp4From1[i] = INF;
        dp4ToN[i] = INF;
    }
    rep(i, 0, N*N) {
        cin >> A[i] >> B[i];
    }

    ans.push_back(-1);
    for (int i = N*N-1; i > 0; i--) ans.push_back(addEdge(A[i], B[i]));
    reverse(all(ans));
    for (int a : ans) cout << (a < INF ? a : -1) << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
