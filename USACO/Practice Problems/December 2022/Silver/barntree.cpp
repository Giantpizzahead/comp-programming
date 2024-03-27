/*
http://usaco.org/index.php?page=viewproblem2&cpid=1254
Solution: I believe the number of haybales needed to move in/out of each edge is uniquely determined.
So, we just need to figure out the # of haybales in each subtree, and the # of nodes.
Order? I think we can just do some sort of topo order? For silver?
I guess, go down to subtrees with more haybales than needed first.
Then, process subtrees with less.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 5e5+5;

int N;
ll K;
ll H[MAXN], stSize[MAXN];
ll sumH[MAXN];
vector<int> adj[MAXN];
struct Move {
    int a, b;
    ll c;
};
vector<Move> ans;

void dfs(int n, int p) {
    // Fill out initial values
    stSize[n] = 1;
    sumH[n] = H[n];
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs(e, n);
        stSize[n] += stSize[e];
        sumH[n] += sumH[e];
    }
}

void dfs2(int n, int p) {
    // Generate sequence of moves; first, process all subtrees with too many haybales
    for (int e : adj[n]) {
        if (e == p || sumH[e] <= K * stSize[e]) continue;
        dfs2(e, n);
        ans.push_back({e, n, sumH[e] - K * stSize[e]});
    }

    // Then, process subtrees with too little haybales
    for (int e : adj[n]) {
        if (e == p || sumH[e] > K * stSize[e]) continue;
        if (sumH[e] != K * stSize[e]) ans.push_back({n, e, K * stSize[e] - sumH[e]});
        dfs2(e, n);
    }
}

void solve() {
    cin >> N;
    K = 0;
    rep(i, 0, N) {
        cin >> H[i];
        K += H[i];
    }
    K /= N;
    rep(i, 1, N) {
        int a, b; cin >> a >> b; a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, 0);
    dfs2(0, 0);
    cout << sz(ans) << "\n";
    for (Move& m : ans) cout << m.a+1 << " " << m.b+1 << " " << m.c << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("test.in", "r", stdin);
    solve();
    return 0;
}
