#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 3005;

int N, M;
int reward[MAXN];
struct Edge {
    int n, c;
};
vector<Edge> adj[MAXN];

int numLeaves[MAXN];
const int INF = 1e9;

// dp[n][k] = Max money possible with k users watching
vector<int> dp[MAXN];

void dfs(int n) {
    if (sz(adj[n]) == 0) {
        // Leaf node
        dp[n].push_back(0);
        dp[n].push_back(reward[n]);
        numLeaves[n] = 1;
        return;
    }
    for (Edge& e : adj[n]) {
        dfs(e.n);
        numLeaves[n] += numLeaves[e.n];
    }

    // Knapsack
    dp[n].resize(numLeaves[n] + 1, -INF);
    dp[n][0] = 0;
    int currLeaves = 0;
    vector<int> newDP(numLeaves[n] + 1, -INF);
    for (Edge& e : adj[n]) {
        // Use items from here
        rep(i, 0, currLeaves+1) {
            rep(j, 0, numLeaves[e.n]+1) {
                int nc = dp[n][i] + dp[e.n][j];
                if (j != 0) nc -= e.c;
                newDP[i+j] = max(newDP[i+j], nc);
            }
        }
        currLeaves += numLeaves[e.n];
        // Record
        rep(i, 0, currLeaves+1) {
            dp[n][i] = newDP[i];
            newDP[i] = -INF;
        }
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N-M) {
        int k; cin >> k;
        rep(j, 0, k) {
            Edge e;
            cin >> e.n >> e.c;
            e.n--;
            adj[i].push_back(e);
        }
    }
    rep(i, 0, M) {
        cin >> reward[N-M+i];
    }
    dfs(0);

    // rep(i, 0, N) {
    //     cout << "dp " << i+1 << ": ";
    //     for (int x : dp[i]) cout << x << " ";
    //     cout << endl;
    // }

    int ans = 0;
    rep(i, 0, numLeaves[0] + 1) {
        if (dp[0][i] >= 0) ans = max(ans, i);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
