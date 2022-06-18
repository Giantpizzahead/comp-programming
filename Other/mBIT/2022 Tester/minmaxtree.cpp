#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;

int N, K, V;
int A[MAXN];
vector<int> adj[MAXN];

// Returns min number of >=V leafs needed for this value to be >=V, or -1 if impossible
int dfs(int n, int p) {
    if (A[n] == 0) return 1;
    else if (A[n] >= V) return 0;
    else if (A[n] > 0) return -1;
    else if (A[n] == -2) {
        // Max
        int res = MAXN;
        for (int e : adj[n]) {
            if (e == p) continue;
            int v = dfs(e, n);
            if (v != -1) res = min(v, res);
        }
        return res;
    } else {
        // Min
        int res = 0;
        for (int e : adj[n]) {
            if (e == p) continue;
            int v = dfs(e, n);
            if (v == -1) return -1;
            else res += v;
        }
        return res;
    }
}

bool check(int v) {
    V = v;
    int numAvailable = K - V + 1;
    rep(i, 0, N) if (A[i] >= V) numAvailable--;
    int res = dfs(0, 0);
    return (res != -1 && res <= numAvailable);
}

void solve() {
    cin >> N >> K;
    rep(i, 0, N) {
        string s;
        cin >> s;
        if (s == "max") A[i] = -2;
        else if (s == "min") A[i] = -1;
        else A[i] = stoi(s);
    }
    rep(i, 1, N) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if (A[0] >= 0) {
        // Root is a leaf
        cout << 0 << '\n';
        return;
    }
    // Binary search for the answer
    int low = 1, high = K;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) {
            low = mid;
        } else {
            high = mid-1;
        }
    }
    cout << low << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}