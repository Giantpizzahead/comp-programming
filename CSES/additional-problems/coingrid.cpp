#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 205;
const int INF = 1e9;

int N, S, T;
struct Edge {
    int n, f, c;
};
vector<Edge> adj[MAXN];

int level[MAXN], ptr[MAXN], cut[MAXN];

bool bfs() {
    rep(i, 0, N) level[i] = -1;
    level[S] = 0;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int n = q.front(); q.pop();
        for (Edge& e : adj[n]) {
            if (level[e.n] != -1 || e.c == 0) continue;
            level[e.n] = level[n] + 1;
            q.push(e.n);
        }
    }
    return (level[T] != -1);
}

int dfs(int n, int f) {
    if (n == T) return f;
    for (; ptr[n] < sz(adj[n]); ptr[n]++) {
        Edge& e = adj[n][ptr[n]];
        if (level[n] + 1 != level[e.n] || e.c == 0) continue;
        int ret = dfs(e.n, min(e.c, f));
        if (ret != 0) {
            e.c -= ret;
            adj[e.n][e.f].c += ret;
            return ret;
        }
    }
    return 0;
}

void maxFlow() {
    int flow = 0;
    while (bfs()) {
        rep(i, 0, N) ptr[i] = 0;
        while (dfs(S, INF)) flow++;
    }
    // cout << flow << endl;
}

void dfsCut(int n) {
    cut[n] = 1;
    for (Edge& e : adj[n]) {
        if (cut[e.n] == 1 || e.c == 0) continue;
        dfsCut(e.n);
    }
}

void addEdge(int a, int b, int c) {
    adj[a].push_back({b, sz(adj[b]), c});
    adj[b].push_back({a, sz(adj[a])-1, 0});
}

void solve() {
    int gridN;
    cin >> gridN;
    N = 2*gridN+2;
    S = 2*gridN, T = 2*gridN+1;
    rep(i, 0, gridN) {
        string str; cin >> str;
        rep(j, 0, gridN) {
            if (str[j] == 'o') addEdge(i, gridN+j, INF);
        }
    }
    rep(i, 0, gridN) {
        addEdge(S, i, 1);
        addEdge(gridN+i, T, 1);
    }
    maxFlow();

    vector<pair<int, int>> answer;
    dfsCut(S);
    rep(n, 0, N) {
        if (cut[n] == 0) continue;
        for (Edge& e : adj[n]) {
            if (cut[e.n] == 0 && e.c == 0) {
                if (n == S) answer.emplace_back(1, e.n);
                else if (e.n == T) answer.emplace_back(2, n-gridN);
            }
        }
    }

    cout << sz(answer) << '\n';
    for (pair<int, int>& p : answer) cout << p.first << ' ' << p.second+1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}