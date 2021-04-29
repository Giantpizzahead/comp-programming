#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr

const int MAXN = 2e5+5;

int N, M;
int n1[MAXN], n2[MAXN];
struct Edge {
    int n, id;
};
vector<Edge> adj[MAXN];

int curr = 0;
int disc[MAXN], ll[MAXN];
bool valid = true;

void dfs(int n, int lastID) {
    disc[n] = curr;
    ll[n] = curr++;
    for (Edge& e : adj[n]) {
        if (e.id == lastID) continue;
        if (n1[e.id] == -1) {
            // Set edge direction
            n1[e.id] = n;
            n2[e.id] = e.n;
        }
        if (disc[e.n] == -1) {
            dfs(e.n, e.id);
            if (ll[e.n] > disc[n]) valid = false;
            ll[n] = min(ll[e.n], ll[n]);
        } else {
            ll[n] = min(disc[e.n], ll[n]);
        }
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
        n1[i] = -1, n2[i] = -1;
    }
    rep(i, 0, N) disc[i] = -1;
    dfs(0, -1);
    rep(i, 0, N) if (disc[i] == -1) valid = false;
    // rep(i, 0, N) cout << disc[i] << " \n"[i==N-1];
    // rep(i, 0, N) cout << ll[i] << " \n"[i==N-1];
    if (!valid) cout << "IMPOSSIBLE\n";
    else {
        rep(i, 0, M) {
            cout << n1[i]+1 << ' ' << n2[i]+1 << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}