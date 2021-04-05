#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;
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
ll D[MAXN];
priority_queue<Pair> pq;

void solve() {
    cin >> N >> M;
    int a, b, c;
    rep(i, 0, M) {
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back({b, c});
    }
    rep(i, 0, N) D[i] = INF;
    D[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        Pair p = pq.top(); pq.pop();
        // cout << p.n << " " << p.c << endl;
        if (p.c != D[p.n]) continue;
        for (auto& e : adj[p.n]) {
            ll nd = p.c + e.c;
            if (nd < D[e.n]) {
                D[e.n] = nd;
                pq.push({e.n, nd});
            }
        }
    }
    rep(i, 0, N) cout << D[i] << " \n"[i == N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}