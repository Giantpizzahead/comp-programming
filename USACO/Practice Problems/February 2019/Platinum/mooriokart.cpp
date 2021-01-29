#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2505;
const ll MOD = 1e9+7;

int N, M, X, Y, compN;
struct Edge {
    int n, c;
};
vector<Edge> adj[MAXN];
vector<int> comps[MAXN];
unordered_map<int, int> compPaths[MAXN];
int compOverCnt[MAXN], compOverSum[MAXN];
bool vis[MAXN];

void dfsComp(int n) {
    vis[n] = true;
    comps[compN].push_back(n);
    for (Edge& e : adj[n]) {
        if (vis[e.n]) continue;
        dfsComp(e.n);
    }
}

int sn;
void dfsPaths(int n, int p, int c, int comp) {
    if (n > sn) {
        if (c >= Y) {
            compOverCnt[comp]++;
            compOverSum[comp] += c;
            compOverSum[comp] %= MOD;
        } else compPaths[comp][c]++;
    }

    for (Edge& e : adj[n]) {
        if (e.n == p) continue;
        dfsPaths(e.n, n, c + e.c, comp);
    }
}

ll dp[2][MAXN], dpOld[2][MAXN];

void solve() {
    cin >> N >> M >> X >> Y;
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            dfsComp(i);
            compN++;
        }
    }

    for (int i = 0; i < compN; i++) {
        for (int n : comps[i]) {
            sn = n;
            dfsPaths(n, n, 0, i);
        }
        // cout << i << ": ";
        // for (auto x : compPaths[i]) {
        //     cout << "(" << x.first << ", " << x.second << ") ";
        // }
        // cout << compOverCnt[i] << " " << compOverSum[i] << endl;
    }

    dpOld[0][0] = 1;
    for (int i = 0; i < compN; i++) {
        for (auto p : compPaths[i]) {
            int cost = p.first, cnt = p.second;
            for (int j = 0; j <= Y; j++) {
                // Use this path
                int newJ = min(j + cost, Y);
                dp[0][newJ] += dpOld[0][j] * cnt;
                dp[0][newJ] %= MOD;
                dp[1][newJ] += dpOld[1][j] * cnt + dpOld[0][j] * cost % MOD * cnt;
                dp[1][newJ] %= MOD;
            }
        }
        // Use over paths
        for (int j = 0; j <= Y; j++) {
            // Use this path
            dp[0][Y] += dpOld[0][j] * compOverCnt[i];
            dp[0][Y] %= MOD;
            dp[1][Y] += dpOld[1][j] * compOverCnt[i] + dpOld[0][j] * compOverSum[i];
            dp[1][Y] %= MOD;
        }
        swap(dp, dpOld);
        for (int j = 0; j <= Y; j++) {
            dp[0][j] = 0;
            dp[1][j] = 0;
        }
        // cout << endl;
        // for (int j = 0; j <= Y; j++) cout << dpOld[0][j] << ' ';
        // cout << endl;
        // for (int j = 0; j <= Y; j++) cout << dpOld[1][j] << ' ';
        // cout << endl;
    }

    // Merge paths together
    ll mergeWays = 1, mergeSides = 1;
    for (int i = 2; i <= compN; i++) {
        mergeSides *= 2;
        mergeSides %= MOD;
    }
    for (int i = 2; i < compN; i++) {
        mergeWays *= i;
        mergeWays %= MOD;
    }
    mergeWays = mergeWays * mergeSides % MOD;

    ll answer = 0;
    int costNeeded = max(Y - X * compN, 0);
    for (int j = costNeeded; j <= Y; j++) {
        answer += mergeWays * dpOld[1][j];
        answer %= MOD;
        answer += X * compN * dpOld[0][j] % MOD * mergeWays;
        answer %= MOD;
    }
    cout << answer << '\n';
}

int main() {
    freopen("mooriokart.in", "r", stdin);
    freopen("mooriokart.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    cout.flush();
    fclose(stdin);
    fclose(stdout);
    return 0;
}