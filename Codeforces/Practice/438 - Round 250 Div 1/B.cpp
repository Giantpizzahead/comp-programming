#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5, INF = 1e9;

int N, M;
pair<int, int> order[MAXN];
int A[MAXN];
vi adj[MAXN];
ll answer = 0;

struct DisjointSet {
    int V[MAXN];

    DisjointSet() {
        fill(V, V+MAXN, -INF);
    }

    int find(int i) {
        if (V[i] < 0) return i;
        int r = find(V[i]);
        V[i] = r;
        return r;
    }

    void activate(int i) {
        V[i] = -1;
    }

    void merge(int a, int b, int v) {
        a = find(a), b = find(b);
        if (a == b || V[a] == -INF || V[b] == -INF) return;
        answer += (ll) v * -V[a] * -V[b];
        if (V[a] < V[b]) {
            V[a] += V[b];
            V[b] = a;
        } else {
            V[b] += V[a];
            V[a] = b;
        }
    }
} ds;

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        cin >> A[i];
        order[i].first = A[i];
        order[i].second = i;
    }
    sort(order, order+N, greater<pair<int, int>>());
    int a, b;
    rep(i, 0, M) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    rep(i, 0, N) {
        int n = order[i].second;
        ds.activate(n);
        for (int e : adj[n]) {
            ds.merge(n, e, A[n]);
        }
    }

    cout << fixed << setprecision(12) << (double) answer / N / (N-1) * 2 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}