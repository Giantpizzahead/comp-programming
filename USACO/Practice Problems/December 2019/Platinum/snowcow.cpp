#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

const int MAXN = 1e5+5, INF = 1e9;

int N, Q;
vector<int> adj[MAXN];
set<pair<int, int>> colors[MAXN];

struct SegmentTree {
    ll V[MAXN*4+1], D[MAXN*4+1];

    SegmentTree() {
        rep(i, 0, MAXN*4+1) {
            V[i] = 0;
            D[i] = 0;
        }
    }

    void prop(int n, int lb, int ub) {
        int ls = (lb+ub)/2-lb+1;
        int rs = ub-lb+1-ls;
        V[n*2] += D[n] * ls;
        V[n*2+1] += D[n] * rs;
        D[n*2] += D[n];
        D[n*2+1] += D[n];
        D[n] = 0;
    }

    void merge(int n) {
        V[n] = V[n*2] + V[n*2+1];
    }

    void update(int l, int r, ll v, int lb = 0, int ub = N-1, int n = 1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            V[n] += (ub-lb+1)*v;
            D[n] += v;
            return;
        }
        prop(n, lb, ub);
        update(l, r, v, lb, (lb+ub)/2, n*2);
        update(l, r, v, (lb+ub)/2+1, ub, n*2+1);
        merge(n);
    }

    ll query(int l, int r, int lb = 0, int ub = N-1, int n = 1) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return V[n];
        prop(n, lb, ub);
        return query(l, r, lb, (lb+ub)/2, n*2) + query(l, r, (lb+ub)/2+1, ub, n*2+1);
    }
};
SegmentTree segt;

int currL = 0;
int labelS[MAXN], labelE[MAXN];
void dfsLabels(int n, int p) {
    labelS[n] = currL++;
    for (int e : adj[n]) {
        if (e != p) dfsLabels(e, n);
    }
    labelE[n] = currL-1;
}

void handleUpdate(int n, int c) {
    // Is this already splashed?
    auto ptr = colors[c].upper_bound({labelS[n], INF});
    if (ptr != colors[c].begin()) {
        ptr = prev(ptr);
        if (ptr->second >= labelE[n]) return;  // Covered
    }
    // Remove outdated splashes
    while (true) {
        ptr = colors[c].lower_bound({labelS[n], -1});
        if (ptr == colors[c].end() || ptr->first > labelE[n]) break;
        // Remove this
        segt.update(ptr->first, ptr->second, -1);
        colors[c].erase(ptr);
    }
    // Add this
    segt.update(labelS[n], labelE[n], 1);
    colors[c].emplace(labelS[n], labelE[n]);
}

void solve() {
    cin >> N >> Q;
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfsLabels(0, 0);
    int t, x, c;
    rep(i, 0, Q) {
        cin >> t;
        if (t == 1) {
            // Update
            cin >> x >> c;
            x--, c--;
            handleUpdate(x, c);
        } else {
            // Query
            cin >> x;
            x--;
            cout << segt.query(labelS[x], labelE[x]) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);
    solve();
    cout.flush();
    fclose(stdin);
    fclose(stdout);
    return 0;
}