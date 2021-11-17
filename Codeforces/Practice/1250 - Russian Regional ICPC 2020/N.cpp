#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;

int N, S;
set<int> nodes;
struct Edge {
    int n, id;
};
map<int, vector<Edge>> adj;
map<int, bool> vis;

struct Answer {
    int w, a, b;
};
vector<Answer> ans;

bool soldered;
bool dfs(int n) {
    vis[n] = true;
    bool foundNew = false;
    for (Edge& e : adj[n]) {
        if (vis[e.n]) continue;
        foundNew = true;
        if (!dfs(e.n) && !soldered) {
            // This edge can be resoldered
            soldered = true;
            if (S == -1) {
                S = n;
            } else {
                ans.push_back({e.id, e.n, S});
            }
        }
    }
    return foundNew;
}

void solve() {
    cin >> N;
    S = -1;
    rep(i, 0, N) {
        int a, b;
        cin >> a >> b;
        nodes.insert(a);
        nodes.insert(b);
        adj[a].push_back({b, i+1});
        adj[b].push_back({a, i+1});
    }
    for (int n : nodes) {
        if (!vis[n]) {
            soldered = false;
            dfs(n);
        }
    }
    cout << sz(ans) << '\n';
    for (Answer& a : ans) cout << a.w << ' ' << a.a << ' ' << a.b << '\n';
    nodes.clear();
    adj.clear();
    vis.clear();
    ans.clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}