#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 800005;
const int C = 21;
const ll MOD = 1e9+7;

int N;
struct Edge {
    int n, c;
};
vector<Edge> adj[MAXN];

// numNodes includes the current node / everything in subtree
// upNodes includes everything else
int numNodes[MAXN][C], upNodes[MAXN][C];
ll sumInside[MAXN], finalSum[MAXN];

void dfs(int n, int p) {
    rep(i, 0, C) numNodes[n][i] = 0;
    numNodes[n][C-1] = 1;
    sumInside[n] = 0;

    // DFS children first
    for (Edge& e : adj[n]) {
        if (e.n == p) continue;
        dfs(e.n, n);
    }

    // Combine children
    int newNodes[C];
    ll newSuffSum[C+1], currSuffSum[C+1];
    for (Edge& e : adj[n]) {
        if (e.n == p) continue;
        // Take connecting edge capacity into account
        rep(c, 0, C) newNodes[c] = 0;
        rep(c, 0, C) {
            int nc = min(e.c, c);
            newNodes[nc] += numNodes[e.n][c];
        }
        // Generate suffix sums
        newSuffSum[C] = 0;
        for (int c = C-1; c >= 0; c--) newSuffSum[c] = newSuffSum[c+1] + newNodes[c];
        currSuffSum[C] = 0;
        for (int c = C-1; c >= 0; c--) currSuffSum[c] = currSuffSum[c+1] + numNodes[n][c];
        // Add to inside sum
        sumInside[n] += sumInside[e.n];
        rep(c, 0, C) {
            sumInside[n] += c * newNodes[c] * currSuffSum[c];
            sumInside[n] += c * numNodes[n][c] * newSuffSum[c+1];
        }
        // Add new nodes
        rep(c, 0, C) numNodes[n][c] += newNodes[c];
    }
    /*
    cout << n << ": " << sumInside[n] << endl;
    rep(c, 0, C) cout << numNodes[n][c] << " \n"[c==C-1];
    */
}

void dfsUp(int n, int p) {
    int newNodes[C];
    ll newSuffSum[C+1], currSuffSum[C+1];
    for (Edge& e : adj[n]) {
        if (e.n == p) continue;
        
        // Count number of up nodes
        rep(c, 0, C) newNodes[c] = 0;
        rep(c, 0, C) {
            int nc = min(e.c, c);
            newNodes[nc] += upNodes[n][c] + numNodes[n][c];
        }
        // Remove nodes from this child's subtree
        rep(c, 0, C) {
            int nc = min(e.c, c);
            newNodes[nc] -= numNodes[e.n][c];
        }
        /*
        int numIn = 0, numOut = 0;
        rep(c, 0, C) {
            numIn += numNodes[e.n][c];
            numOut += newNodes[c];
        }
        assert(numIn + numOut == N);
        */
        // Now newNodes has the correct upNode counts
        // Remove sum made using subtree nodes
        finalSum[e.n] = sumInside[0];
        newSuffSum[C] = 0;
        for (int c = C-1; c >= 0; c--) newSuffSum[c] = newSuffSum[c+1] + newNodes[c];
        currSuffSum[C] = 0;
        for (int c = C-1; c >= 0; c--) currSuffSum[c] = currSuffSum[c+1] + numNodes[e.n][c];
        rep(c, 0, C) {
            finalSum[e.n] -= c * newNodes[c] * currSuffSum[c];
            finalSum[e.n] -= c * numNodes[e.n][c] * newSuffSum[c+1];
        }
        rep(c, 0, C) upNodes[e.n][c] = newNodes[c];

        /*
        cout << e.n << ": " << endl;
        rep(c, 0, C) cout << numNodes[e.n][c] << " \n"[c==C-1];
        rep(c, 0, C) cout << upNodes[e.n][c] << " \n"[c==C-1];
        */
        dfsUp(e.n, n);
    }
}

void solve() {
    cin >> N;
    rep(i, 0, N) adj[i].clear();
    int a, b, c;
    rep(i, 1, N) {
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    dfs(0, 0);
    rep(i, 0, C) upNodes[0][i] = 0;
    finalSum[0] = 0;
    dfsUp(0, 0);

    ll answer = 1;
    rep(n, 1, N) {
        answer *= (finalSum[n] % MOD);
        answer %= MOD;
    }
    cout << answer << "\n";

    /*
    cout << endl;
    rep(n, 0, N) {
        cout << n+1 << ": " << sumInside[n] << " " << finalSum[n] << endl;
    }
    */

    /*
    ll answer = 1;
    rep(n, 0, N) {
        for (Edge& e : adj[n]) {
            if (e.n < n) continue;
            // Change this edge
            int saved = e.c;
            e.c = 0;
            for (Edge& f : adj[e.n]) if (f.n == n) f.c = 0;
            dfs(0, 0);
            e.c = saved;
            for (Edge& f : adj[e.n]) if (f.n == n) f.c = saved;
            cout << "\ntotal " << sumInside[0] << "\n";
        }
    }
    cout << endl;
    */
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}