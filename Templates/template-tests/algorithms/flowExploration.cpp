#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 1205, MAXM = 120005;
const bool SHUFFLE = false;

int N, M, S, T, E;
int perm[MAXM];
int A[MAXM*2], B[MAXM*2], C[MAXM*2];
vector<int> adj[MAXN];

/*
Impl difficulty: 2/5
Impl time: 3/5
LOJ unshuffled: 88/100, 11432 ms
LOJ shuffled: 88/100, 11280 ms
*/
class DinicScaling {
    int maxC;
    int level[MAXN], ptr[MAXN];
    queue<int> q;
    
    bool bfs() {
        rep(i, 0, N) level[i] = -1;
        level[S] = 0;
        q.push(S);
        while (!q.empty()) {
            int n = q.front(); q.pop();
            for (int id : adj[n]) {
                if (level[B[id]] != -1 || C[id] < maxC) continue;
                level[B[id]] = level[n] + 1;
                q.push(B[id]);
            }
        }
        return (level[T] != -1);
    }
    
    int dfs(int n, int f = INT32_MAX) {
        if (n == T) return f;
        for (; ptr[n] < sz(adj[n]); ptr[n]++) {
            int id = adj[n][ptr[n]];
            if (level[B[id]] != level[n] + 1 || C[id] < maxC) continue;
            int ret = dfs(B[id], min(f, C[id]));
            if (ret != 0) {
                C[id] -= ret;
                C[id^1] += ret;
                return ret;
            }
        }
        return 0;
    }
    
public:
    ll maxFlow() {
        ll flow = 0;
        maxC = INT32_MAX;
        while (maxC > 0) {
            while (bfs()) {
                rep(i, 0, N) ptr[i] = 0;
                while (int ret = dfs(S)) {
                    flow += ret;
                }
            }
            maxC /= 2;
        }
        return flow;
    }
};

/*
Impl difficulty: 2/5
Impl time: 2/5
LOJ unshuffled: 36/100, 27301 ms
LOJ shuffled: 36/100, 27643 ms
*/
class Dinic {
    int level[MAXN], ptr[MAXN];
    queue<int> q;
    
    bool bfs() {
        rep(i, 0, N) level[i] = -1;
        level[S] = 0;
        q.push(S);
        while (!q.empty()) {
            int n = q.front(); q.pop();
            for (int id : adj[n]) {
                if (level[B[id]] != -1 || C[id] == 0) continue;
                level[B[id]] = level[n] + 1;
                q.push(B[id]);
            }
        }
        return (level[T] != -1);
    }
    
    int dfs(int n, int f = INT32_MAX) {
        if (n == T) return f;
        for (; ptr[n] < sz(adj[n]); ptr[n]++) {
            int id = adj[n][ptr[n]];
            if (level[B[id]] != level[n] + 1 || C[id] == 0) continue;
            int ret = dfs(B[id], min(f, C[id]));
            if (ret != 0) {
                C[id] -= ret;
                C[id^1] += ret;
                return ret;
            }
        }
        return 0;
    }
    
public:
    ll maxFlow() {
        ll flow = 0;
        while (bfs()) {
            rep(i, 0, N) ptr[i] = 0;
            while (int ret = dfs(S)) {
                flow += ret;
            }
        }
        return flow;
    }
};

/*
Impl difficulty: 2/5
Impl time: 3/5
LOJ unshuffled: 36/100, 27126 ms
LOJ shuffled: 36/100, 27485 ms
*/
class PFS {
    int from[MAXN], amount[MAXN];
    priority_queue<pair<int, int>> pq;

    int findFlow() {
        pq.emplace(INT32_MAX, S);
        while (!pq.empty()) {
            auto& topPair = pq.top();
            int n = topPair.second, f = topPair.first;
            if (amount[n] != f) continue;
            pq.pop();
            if (n == T) {
                // Backtrack
                while (from[n] != -2) {
                    C[from[n]] -= f;
                    C[from[n]^1] += f;
                    n = A[from[n]];
                }
                break;
            }
            for (int id : adj[n]) {
                int nf = min(f, C[id]);
                if (amount[B[id]] >= nf) continue;
                from[B[id]] = id, amount[B[id]] = nf;
                pq.emplace(nf, B[id]);
            }
        }
        while (!pq.empty()) pq.pop();
        return (from[T] == -1 ? 0 : amount[T]);
    }

public:
    ll maxFlow() {
        ll flow = 0;
        while (true) {
            rep(i, 0, N) {
                from[i] = -1;
                amount[i] = 0;
            }
            from[S] = -2, amount[S] = INT32_MAX;
            int ret = findFlow();
            if (ret != 0) flow += ret;
            else break;
        }
        return flow;
    }
};

/*
Impl difficulty: 2/5
Impl time: 3/5
LOJ unshuffled: 36/100, 27748 ms
LOJ shuffled: 32/100, 28152 ms
*/
class EdmondsKarpScaling {
    int maxC;
    int from[MAXN], amount[MAXN];
    queue<int> q;

    int findFlow() {
        q.push(S);
        while (!q.empty()) {
            int n = q.front(); q.pop();
            if (n == T) {
                // Backtrack
                while (from[n] != -2) {
                    C[from[n]] -= amount[T];
                    C[from[n]^1] += amount[T];
                    n = A[from[n]];
                }
                break;
            }
            for (int id : adj[n]) {
                if (from[B[id]] != -1 || C[id] < maxC) continue;
                from[B[id]] = id;
                amount[B[id]] = min(amount[n], C[id]);
                q.push(B[id]);
            }
        }
        while (!q.empty()) q.pop();
        return (from[T] == -1 ? 0 : amount[T]);
    }

public:
    ll maxFlow() {
        ll flow = 0;
        maxC = INT32_MAX;
        while (maxC > 0) {
            rep(i, 0, N) from[i] = -1;
            from[S] = -2, amount[S] = INT32_MAX;
            int ret = findFlow();
            if (ret != 0) flow += ret;
            else maxC /= 2;
        }
        return flow;
    }
};

/*
Impl difficulty: 2/5
Impl time: 2/5
LOJ unshuffled: 20/100, 32192 ms
LOJ shuffled: 20/100, 32692 ms
*/
class EdmondsKarp {
    int from[MAXN], amount[MAXN];
    queue<int> q;

    int findFlow() {
        q.push(S);
        while (!q.empty()) {
            int n = q.front(); q.pop();
            if (n == T) {
                // Backtrack
                while (from[n] != -2) {
                    C[from[n]] -= amount[T];
                    C[from[n]^1] += amount[T];
                    n = A[from[n]];
                }
                break;
            }
            for (int id : adj[n]) {
                if (from[B[id]] != -1 || C[id] == 0) continue;
                from[B[id]] = id;
                amount[B[id]] = min(amount[n], C[id]);
                q.push(B[id]);
            }
        }
        while (!q.empty()) q.pop();
        return (from[T] == -1 ? 0 : amount[T]);
    }

public:
    ll maxFlow() {
        ll flow = 0;
        while (true) {
            rep(i, 0, N) from[i] = -1;
            from[S] = -2, amount[S] = INT32_MAX;
            int ret = findFlow();
            if (ret != 0) flow += ret;
            else break;
        }
        return flow;
    }
};

/*
Impl difficulty: 2/5
Impl time: 1/5
LOJ unshuffled: 32/100, 28372 ms
LOJ shuffled: 32/100, 28823 ms
*/
class CapacityScaling {
    int iter = 0, maxC;
    int vis[MAXN];

    int pushFlow(int n, int f = INT32_MAX) {
        // debug << "pushFlow(" << n << ", " << f << ")" << endl;
        vis[n] = iter;
        if (n == T) return f;
        for (int id : adj[n]) {
            if (vis[B[id]] == iter || C[id] < maxC) continue;
            int ret = pushFlow(B[id], min(f, C[id]));
            if (ret > 0) {
                C[id] -= ret;
                C[id^1] += ret;
                return ret;
            }
        }
        return 0;
    }

public:
    CapacityScaling() {
        rep(i, 0, MAXN) vis[i] = 0;
    }

    ll maxFlow() {
        ll flow = 0;
        maxC = INT32_MAX;
        while (maxC > 0) {
            iter++;
            int ret = pushFlow(S);
            if (ret != 0) flow += ret;
            else maxC /= 2;
        }
        return flow;
    }
};

/*
Impl difficulty: 1/5
Impl time: 1/5
LOJ unshuffled: 16/100, 32742 ms
LOJ shuffled: 16/100, 32860 ms
*/
class FordFulkerson {
    int iter = 0;
    int vis[MAXN];

    int pushFlow(int n, int f = INT32_MAX) {
        // debug << "pushFlow(" << n << ", " << f << ")" << endl;
        vis[n] = iter;
        if (n == T) return f;
        for (int id : adj[n]) {
            if (vis[B[id]] == iter || C[id] == 0) continue;
            int ret = pushFlow(B[id], min(f, C[id]));
            if (ret > 0) {
                C[id] -= ret;
                C[id^1] += ret;
                return ret;
            }
        }
        return 0;
    }

public:
    FordFulkerson() {
        rep(i, 0, MAXN) vis[i] = 0;
    }

    ll maxFlow() {
        ll flow = 0;
        while (true) {
            iter++;
            int ret = pushFlow(S);
            if (ret != 0) flow += ret;
            else break;
        }
        return flow;
    }
};

EdmondsKarpScaling flowSolver;

void addEdge(int a, int b, int c) {
    int e = perm[E];
    adj[a].push_back(e);
    A[e] = a, B[e] = b, C[e] = c;
    e++;
    adj[b].push_back(e);
    A[e] = b, B[e] = a, C[e] = 0;
    E++;
}

void solve() {
    cin >> N >> M >> S >> T;
    S--, T--;
    E = 0;
    int a, b, c;
    rep(i, 0, M) {
        cin >> a >> b >> c;
        a--, b--;
        addEdge(a, b, c);
    }
    cout << flowSolver.maxFlow() << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // Shuffle to eliminate some types of worst cases
    rep(i, 0, MAXM) perm[i] = 2*i;
    if (SHUFFLE) {
        srand(913746283);
        random_shuffle(perm, perm+MAXM);
    }
    solve();
    return 0;
}