#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 250, MAXM = 5000;
const int INF = 1e9;

int N, M, S, T;
int pi[MAXN];
struct Edge {
    int n, f, c, w;
};;
vector<Edge> edgeList;
vector<Edge> adj[MAXN];

void addEdge(int u, int v, int c, int w) {
    adj[u].push_back({v, sz(adj[v]), c, w});
    adj[v].push_back({u, sz(adj[u])-1, 0, -w});
}

int dist[MAXN];
void prepJohnson() {
    rep(i, 0, N) dist[i] = INF;
    dist[S] = 0;
    rep(i, 0, N-1) {
        for (Edge& e : edgeList) {
            dist[e.f] = min(dist[e.n] + e.w, dist[e.f]);
        }
    }
    rep(i, 0, N) pi[i] = dist[i];
}

// Dijkstra using adjusted edge costs
struct State {
    int n, w;
    bool operator<(const State& o) const {
        return w > o.w;
    }
};
priority_queue<State> pq;
int bestW[MAXN], fromN[MAXN], fromI[MAXN];

pair<int, ll> findPath() {
    rep(i, 0, N) {
        bestW[i] = INF;
        fromN[i] = -1;
        fromI[i] = -1;
    }
    bestW[S] = 0;
    pq.push({S, 0});
    while (!pq.empty()) {
        State s = pq.top(); pq.pop();
        if (s.w != bestW[s.n]) continue;
        rep(i, 0, sz(adj[s.n])) {
            Edge& e = adj[s.n][i];
            int realW = e.w + pi[s.n] - pi[e.n];
            // debug << realW << endl;
            if (s.w + realW >= bestW[e.n] || e.c == 0) continue;
            // assert(realW >= 0);
            bestW[e.n] = s.w + realW;
            fromN[e.n] = s.n, fromI[e.n] = i;
            pq.push({e.n, bestW[e.n]});
        }
    }

    if (bestW[T] == INF) return {0, 0};
    // Backtrace
    int flow = INF;
    int n = T;
    while (fromN[n] != -1) {
        flow = min(adj[fromN[n]][fromI[n]].c, flow);
        n = fromN[n];
    }
    // Update costs
    ll cost = 0;
    n = T;
    while (fromN[n] != -1) {
        Edge& e = adj[fromN[n]][fromI[n]];
        cost += flow * e.w;
        e.c -= flow;
        adj[e.n][e.f].c += flow;
        n = fromN[n];
    }
    return {flow, cost};
}

pair<int, ll> minCostMaxFlow() {
    int flow = 0;
    ll cost = 0;
    prepJohnson();
    while (true) {
        // debug << "iteration" << endl;
        pair<int, ll> p = findPath();
        if (p.first == 0) break;
        flow += p.first;
        cost += p.second;
        rep(i, 0, N) {
            pi[i] = bestW[i] - pi[S] + pi[i];
        }
    }
    return {flow, cost};
}

void solve() {
    int tempM;
    cin >> N >> tempM >> S >> T;
    M = 0;
    int u, v, c, w;
    rep(i, 0, tempM) {
        cin >> u >> v >> c >> w;
        addEdge(u, v, c, w);
        edgeList.push_back({u, v, c, w});
    }
    pair<int, ll> answer = minCostMaxFlow();

    // debug << "potentials:" << endl;
    // rep(i, 0, N) debug << pi[i] << " \n"[i==N-1];
    cout << answer.first << ' ' << answer.second << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}