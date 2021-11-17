#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 3e5+5;

int N, M;
int U[MAXN], V[MAXN];
ll A[MAXN];
ll X;
struct Edge {
    int n, id;
};
vector<Edge> adj[MAXN];
bool edgeUsed[MAXN], vis[MAXN];

// struct DisjointSet {
//     int S[MAXN];
//     ll A[MAXN];

//     DisjointSet() {
//         rep(i, 0, MAXN) {
//             S[i] = -1;
//             A[i] = 0;
//         }
//     }

//     int find(int n) {
//         if (S[n] < 0) return n;
//         int r = find(S[n]);
//         S[n] = r;
//         return r;
//     }

//     int merge(int a, int b) {
//         a = find(a), b = find(b);
//         if (a == b) return a;
//         if (S[a] < S[b]) {
//             A[a] += A[b];
//             A[b] = 0;
//             S[a] += S[b];
//             S[b] = a;
//             return a;
//         } else {
//             A[b] += A[a];
//             A[a] = 0;
//             S[b] += S[a];
//             S[a] = b;
//             return b;
//         }
//     }
// } ds;

bool dfsInitial(int n, int p) {
    vis[n] = true;
    for (auto& e : adj[n]) {
        if (vis[e.n]) continue;
        if (dfsInitial(e.n, n)) {
            edgeUsed[e.id] = true;
            cout << e.id+1 << '\n';
        }
    }
    if (A[n] >= X && n != p) {
        // Bring asphalt "up"
        A[p] += A[n] - X;
        A[n] = 0;
        return true;
    }
    return false;
}

vector<int> remaining;

ll dfsFinal(int n, ll a) {
    vis[n] = true;
    a += A[n];
    A[n] = 0;
    for (auto& e : adj[n]) {
        if (vis[e.n]) continue;
        if (!edgeUsed[e.id]) {
            if (a >= X) {
                edgeUsed[e.id] = true;
                cout << e.id+1 << '\n';
                a -= X;
            } else remaining.push_back(e.id);
        }
        a = dfsFinal(e.n, a);
    }
    return a;
}

void solve() {
    cin >> N >> M >> X;
    ll needed = (N-1) * X;
    rep(i, 0, N) {
        cin >> A[i];
        needed -= A[i];
    }
    if (needed > 0) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    rep(i, 0, M) {
        cin >> U[i] >> V[i];
        U[i]--, V[i]--;
        adj[U[i]].push_back({V[i], i});
        adj[V[i]].push_back({U[i], i});
    }

    // Bring lots of asphalt up
    dfsInitial(0, 0);
    rep(i, 0, N) debug << A[i] << " \n"[i==N-1];

    // Use all the asphalt
    rep(i, 0, N) vis[i] = false;
    dfsFinal(0, 0);
    rep(i, 0, N) debug << A[i] << " \n"[i==N-1];

    // Remaining edges can be arbitrarily chosen
    for (int id : remaining) {
        cout << id+1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}