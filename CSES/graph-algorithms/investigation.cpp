#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5, MOD = 1e9+7;
const ll INF = 1e18;

int N, M;
struct Pair {
    int n;
    ll c;
    bool operator<(const Pair& o) const {
        return c > o.c;
    }
};
vector<Pair> adj[MAXN];

priority_queue<Pair> pq;
ll dist[MAXN];
int ways[MAXN], minF[MAXN], maxF[MAXN];

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back({b, c});
    }

    rep(i, 0, N) {
        dist[i] = INF;
    }
    dist[0] = 0;
    ways[0] = 1;
    pq.push({0, 0});
    while (!pq.empty()) {
        Pair p = pq.top(); pq.pop();
        if (p.c > dist[p.n]) continue;
        for (Pair& e : adj[p.n]) {
            ll nc = p.c + e.c;
            if (nc < dist[e.n]) {
                dist[e.n] = nc;
                ways[e.n] = 0;
                minF[e.n] = N;
                maxF[e.n] = -1;
                pq.push({e.n, nc});
            }
            if (nc == dist[e.n]) {
                ways[e.n] += ways[p.n];
                if (ways[e.n] >= MOD) ways[e.n] -= MOD;
                minF[e.n] = min(minF[p.n]+1, minF[e.n]);
                maxF[e.n] = max(maxF[p.n]+1, maxF[e.n]);
            }
        }
    }

    cout << dist[N-1] << " " << ways[N-1] << " " << minF[N-1] << " " << maxF[N-1] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}