#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

const int MAXN = 2505;
const ll INF = 1e18;

int N, M;
struct State {
    int n, e;
    ll v;
    bool operator<(const State& o) const {
        return v < o.v;
    }
};
vector<State> adj[MAXN];

ll score[MAXN];
priority_queue<State> pq;

ll dijkstra(int a, int b) {
    rep(i, 0, N) score[i] = -INF;
    score[a] = 0;
    pq.push({a, 0, 0});

    while (!pq.empty()) {
        State s = pq.top(); pq.pop();
        if (score[s.n] > s.v) continue;
        if (s.e >= N) {
            // Must be a cycle
            s.v = INF;
            score[s.n] = INF;
        }
        for (State& e : adj[s.n]) {
            ll nv = min(s.v + e.v, INF);
            if (nv > score[e.n]) {
                score[e.n] = nv;
                pq.push({e.n, s.e+1, nv});
            }
        }
    }
    
    return (score[b] >= INF ? -1 : score[b]);
}

void solve() {
    cin >> N >> M;
    int a, b, x;
    rep(i, 0, M) {
        cin >> a >> b >> x;
        a--, b--;
        adj[a].push_back({b, -1, x});
    }
    cout << dijkstra(0, N-1) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}