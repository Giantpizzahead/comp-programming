#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
vi adj[MAXN];

int dfs(int n, int p, int k) {
    if (sz(adj[n]) == 1 && n != p) return 1;  // Leaf node
    int smallest = N, cannot = -1;
    for (int e : adj[n]) {
        if (e == p) continue;
        int v = dfs(e, n, k);
        if (v == -1) return -1;
        smallest = min(v, smallest);
        if (v >= k) {
            if (n != p) {
                // Will not work
                return -1;
            } else {
                // Can only connect one directly
                if (cannot != -1) return -1;
                else cannot = v;
            }
        }
    }
    return smallest+1;
}

bool check(int k) {
    int v = dfs(0, 0, k);
    return v != -1;
}

void solve() {
    cin >> N;
    rep(i, 0, N) adj[i].clear();
    rep(i, 1, N) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int low = 1, high = N;
    while (low < high) {
        int mid = (low+high)/2;
        if (check(mid)) {
            high = mid;
        } else {
            low = mid+1;
        }
    }
    cout << low << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}