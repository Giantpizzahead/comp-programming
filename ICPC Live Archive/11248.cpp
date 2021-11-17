#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 101;

int N, E, S, T;
ll C;
struct Edge {
    int n, r;
    ll c;
    bool f;
};
vector<Edge> adj[MAXN];

ll flow;
int level[MAXN], ptr[MAXN];
bool trackChanges;
stack<pair<Edge&, ll>> changes;

void addEdge(int a, int b, ll c) {
    adj[a].push_back({b, sz(adj[b]), c, true});
    adj[b].push_back({a, sz(adj[a])-1, 0, false});
}

bool bfs() {
    rep(i, 0, N) level[i] = -1;
    level[S] = 0;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int n = q.front(); q.pop();
        for (Edge& e : adj[n]) {
            if (level[e.n] != -1 || !e.c) continue;
            level[e.n] = level[n] + 1;
            q.push(e.n);
        }
    }
    return (level[T] != -1);
}

ll dfs(int n, ll f) {
    if (n == T) return f;
    for (; ptr[n] < sz(adj[n]); ptr[n]++) {
        Edge& e = adj[n][ptr[n]];
        if (level[n] + 1 != level[e.n] || e.c == 0) continue;
        if (ll ret = dfs(e.n, min(f, e.c))) {
            e.c -= ret;
            adj[e.n][e.r].c += ret;
            if (trackChanges) {
                changes.emplace(e, ret);
                changes.emplace(adj[e.n][e.r], -ret);
            }
            return ret;
        }
    }
    return 0;
}

bool findFlow() {
    while (bfs()) {
        rep(i, 0, N) ptr[i] = 0;
        while (ll ret = dfs(0, C)) {
            flow += ret;
            if (flow >= C) return true;
        }
    }
    return false;
}

bool solve(int tn) {
    cin >> N >> E >> C;
    if (N == 0) return false;
    cout << "Case " << tn << ": ";
    S = 0, T = N-1;
    rep(i, 0, N) adj[i].clear();
    int a, b;
    ll c;
    rep(i, 0, E) {
        cin >> a >> b >> c;
        a--, b--;
        addEdge(a, b, c);
    }
    // Possible without increasing anything
    flow = 0;
    trackChanges = false;
    if (C == 0 || findFlow()) {
        cout << "possible\n";
        return true;
    }
    // Try all edges
    vector<pair<int, int>> answer;
    rep(n, 0, N) {
        for (Edge& e : adj[n]) {
            if (!e.f || e.c != 0) continue;
            // Try this edge
            e.c += C;
            ll oldFlow = flow;
            trackChanges = true;
            if (findFlow()) answer.emplace_back(n, e.n);
            // Revert changes
            flow = oldFlow;
            while (!changes.empty()) {
                changes.top().first.c += changes.top().second;
                changes.pop();
            }
            e.c -= C;
        }
    }
    sort(all(answer));
    if (answer.empty()) cout << "not possible\n";
    else {
        cout << "possible option:";
        rep(i, 0, sz(answer)) {
            cout << "(" << answer[i].first+1 << "," << answer[i].second+1 << ")" << ",\n"[i==sz(answer)-1];
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int t = 1; solve(t); t++);
    return 0;
}