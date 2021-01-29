#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5;
const ll INF = 1e18;

int N, M;
struct Edge {
    int n, c;
};
vector<Edge> adj[MAXN];

priority_queue<pair<ll, int>> pq;
ll bestDist[MAXN];

void dijkstra() {
    for (int i = 0; i < N; i++) bestDist[i] = INF;
    pq.emplace(0, 0);
    bestDist[0] = 0;
    while (!pq.empty()) {
        int n = pq.top().second;
        ll c = -pq.top().first;
        pq.pop();
        if (c > bestDist[n]) continue;
        for (Edge& e : adj[n]) {
            ll nc = bestDist[n] + e.c;
            if (nc < bestDist[e.n]) {
                bestDist[e.n] = nc;
                pq.emplace(-nc, e.n);
            }
        }
    }
}

void solve() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        adj[a].push_back({b, c});
    }
    dijkstra();
    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ' ';
        cout << bestDist[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}