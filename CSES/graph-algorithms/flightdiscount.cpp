#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5;
const ll INF = 1e18;

int N, M;
vector<pair<int, int>> adj[MAXN];

struct State {
    int n;
    ll c;
    bool u;
    bool operator<(const State& o) const {
        return c > o.c;
    }
};
priority_queue<State> pq;
ll bestDist[MAXN][2];

void solve() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c; a--; b--;
        adj[a].emplace_back(c, b);
    }
    for (int i = 0; i < N; i++) {
        bestDist[i][0] = INF;
        bestDist[i][1] = INF;
    }
    pq.push({0, 0, false});
    while (!pq.empty()) {
        State s = pq.top();
        pq.pop();
        if (s.c > bestDist[s.n][s.u]) continue;
        for (auto e : adj[s.n]) {
            if (!s.u) {
                ll nc = s.c + e.first / 2;
                if (nc < bestDist[e.second][1]) {
                    bestDist[e.second][1] = nc;
                    pq.push({e.second, nc, 1});
                }
            }
            ll nc = s.c + e.first;
            if (nc < bestDist[e.second][s.u]) {
                bestDist[e.second][s.u] = nc;
                pq.push({e.second, nc, s.u});
            }
        }
    }

    cout << min(bestDist[N-1][0], bestDist[N-1][1]) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}