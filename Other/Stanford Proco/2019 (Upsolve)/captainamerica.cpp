#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2e5+5;

int Q;
bool active[MAXN];
vector<int> T[MAXN];
set<pair<int, int>> adj[MAXN];

void solve() {
    cin >> Q;
    int M = 0, K = 0;
    int t, u, v, ans = 0;
    rep(n, 1, Q+1) {
        cin >> t >> u >> v;
        if (t == 1) {
            // Process existing triangles
            int e = adj[u].lower_bound({v, -1})->second;
            for (int k : T[e]) {
                if (active[k]) {
                    active[k] = false;
                    ans--;
                }
            }
            // Delete this edge
            adj[u].erase(adj[u].lower_bound({v, -1}));
            adj[v].erase(adj[v].lower_bound({u, -1}));
        }
        
        // Add new edge(s)
        if (u == v) {
            adj[u].insert({n, M});
            adj[n].insert({u, M});
            M++;
        } else {
            adj[u].insert({n, M});
            adj[n].insert({u, M});
            M++;
            adj[v].insert({n, M});
            adj[n].insert({v, M});
            M++;
            // Check for new triangle
            auto ptr = adj[u].lower_bound({v, -1});
            if (ptr != adj[u].end() && ptr->first == v) {
                active[K] = true;
                T[M-2].push_back(K);
                T[M-1].push_back(K);
                T[ptr->second].push_back(K);
                ans++, K++;
            }
        }

        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}