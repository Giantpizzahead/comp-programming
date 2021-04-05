#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;
const ll INF = 1e18;

int N, M, K;
struct Pair {
    int n;
    ll c;
    bool operator<(const Pair& o) const {
        return c > o.c;
    }
};
vector<Pair> adj[MAXN];

priority_queue<Pair> pq;
int vis[MAXN];
ll dist[MAXN][11];

void solve() {
    cin >> N >> M >> K;
    int a, b, c;
    rep(i, 0, M) {
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back({b, c});
    }

    rep(i, 0, N) {
        rep(j, 0, K) {
            dist[i][j] = INF;
        }
    }
    pq.push({0, 0});
    while (!pq.empty()) {
        Pair p = pq.top(); pq.pop();
        if (vis[p.n] == K) continue;
        vis[p.n]++;

        for (Pair& e : adj[p.n]) {
            ll nc = p.c + e.c;
            rep(j, 0, K) {
                if (nc < dist[e.n][j]) {
                    for (int k = K-1; k > j; k--) swap(dist[e.n][k-1], dist[e.n][k]);
                    dist[e.n][j] = nc;
                    pq.push({e.n, nc});
                    break;
                }
            }
        }
    }

    rep(i, 0, K) cout << dist[N-1][i] << (i == K-1 ? '\n' : ' ');
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}