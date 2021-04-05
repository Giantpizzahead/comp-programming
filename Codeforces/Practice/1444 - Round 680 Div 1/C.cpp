#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;
#define debug if (false) cerr

const int MAXN = 5e5+5;

int N, M, K;
int C[MAXN], G[MAXN], L[MAXN];
bool valid[MAXN];
vi adj[MAXN];
vector<pair<int, int>> E;
struct Edge {
    int n, l;
};
vector<Edge> adjG[MAXN];

int currG = 0;
void dfsGroup(int n) {
    G[n] = currG;
    for (int e : adj[n]) {
        if (C[e] != C[n] || G[e] != -1) continue;
        dfsGroup(e);
    }
}

void dfsBipartite(int n, int g, int v) {
    L[n] = v;
    for (int e : adj[n]) {
        if (G[e] != g || L[e] == 1-L[n]) continue;
        if (L[e] == L[n]) {
            // Invalid
            valid[C[n]] = false;
        }
        if (L[e] == -1) dfsBipartite(e, g, 1-v);
    }
}

bool isValid;
int color[MAXN];

void dfsCheck(int n, int v) {
    debug << "dfs " << n << " " << v << endl;
    color[n] = v;
    for (auto& e : adjG[G[n]]) {
        debug << e.n << " " << (e.l==L[n] ? 'y' : 'n') << endl;
        int av;
        if (e.l == L[n]) av = v;
        else av = 1-v;
        // Transition to opposite
        int nv = 1-av;
        if (color[e.n] == -1) {
            dfsCheck(e.n, nv);
        } else if (color[e.n] != nv) {
            isValid = false;
        }
    }
}

void solve() {
    cin >> N >> M >> K;
    rep(i, 0, N) {
        cin >> C[i];
        C[i]--;
        G[i] = -1;
        L[i] = -1;
    }
    rep(i, 0, M) {
        int a, b; cin >> a >> b;
        a--, b--;
        if (C[a] != C[b]) E.push_back({a, b});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    rep(i, 0, K) valid[i] = true;
    rep(i, 0, N) {
        if (G[i] == -1) {
            dfsGroup(i);
            dfsBipartite(i, G[i], 0);
            currG++;
        }
    }

    rep(i, 0, N) debug << G[i] << " \n"[i == N-1];
    rep(i, 0, N) debug << L[i] << " \n"[i == N-1];
    rep(i, 0, K) debug << valid[i] << " \n"[i == K-1];

    ll answer = 0;
    int validG = 0;
    rep(i, 0, K) if (valid[i]) validG++;
    answer += (ll) validG * (validG-1) / 2;

    sort(all(E), [](const pair<int, int>& p1, const pair<int, int>& p2) {
        int a1 = C[p1.first], a2 = C[p1.second];
        if (a1 > a2) swap(a1, a2);
        int b1 = C[p2.first], b2 = C[p2.second];
        if (b1 > b2) swap(b1, b2);
        return make_pair(a1, a2) < make_pair(b1, b2);
    });

    // Handle overcounted pairs
    int ei = 0;
    rep(i, 0, N) color[i] = -1;
    while (ei != sz(E)) {
        // Find all edges to add
        int a = C[E[ei].first], b = C[E[ei].second];
        if (a > b) swap(a, b);
        int ej = ei;
        while (ej != sz(E)) {
            int a2 = C[E[ej].first], b2 = C[E[ej].second];
            if (a2 > b2) swap(a2, b2);
            if (a == a2 && b == b2) ej++;
            else break;
        }
        debug << "check " << a << ' ' << b << endl;
        // Add all edges to temp graph
        set<int> nodes;
        rep(i, ei, ej) {
            int a = E[i].first, b = E[i].second;
            nodes.insert(a);
            nodes.insert(b);
            debug << "add " << L[a] << " " << L[b] << endl;
            adjG[G[a]].push_back({b, L[a]});
            adjG[G[b]].push_back({a, L[b]});
        }

        // Search through graph
        isValid = true;
        for (int n : nodes) {
            debug << n << endl;
            if (color[n] == -1) dfsCheck(n, 0);
        }
        if (!isValid && valid[a] && valid[b]) {
            debug << "invalid" << endl;
            answer--;
        }

        // Remove all edges & backtrack
        rep(i, ei, ej) {
            int a = E[i].first, b = E[i].second;
            adjG[G[a]].clear();
            adjG[G[b]].clear();
        }
        for (int n : nodes) color[n] = -1;
        ei = ej;
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}