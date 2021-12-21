#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;

int N, M, K;
int C[MAXN], P[MAXN], A[MAXN], B[MAXN];

const ll INF = 1e18;
// 0 = Visit left, 1 = Visit right, 2 = Visit both
ll bestP[MAXN][3];
bool vis[MAXN][3];
struct State {
    int n, t;
    ll c;
    bool operator<(const State& o) const {
        return c > o.c;
    }
};
priority_queue<State> pq;

// Key: Once a range is transitioned to, no need to consider it again
struct SegmentTree {
    vector<int> V[MAXN*4+1];

    void addSeg(int l, int r, int v, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            V[n].push_back(v);
            return;
        }
        addSeg(l, r, v, n*2, lb, (lb+ub)/2);
        addSeg(l, r, v, n*2+1, (lb+ub)/2+1, ub);
    }

    void transToSegs(int v, vector<int>& trans, int n=1, int lb=0, int ub=N-1) {
        if (v > ub || v < lb) return;
        // Segments cover this node
        trans.insert(trans.end(), all(V[n]));
        V[n].clear();
        if (lb != ub) {
            transToSegs(v, trans, n*2, lb, (lb+ub)/2);
            transToSegs(v, trans, n*2+1, (lb+ub)/2+1, ub);
        }
    }
};

SegmentTree segt[3];

void dijkstra() {
    rep(i, 0, M) rep(j, 0, 3) bestP[i][j] = INF;
    bestP[0][0] = 0;
    pq.push({0, 0, 0});
    bestP[N-1][1] = 0;
    pq.push({N-1, 1, 0});

    while (!pq.empty()) {
        State s = pq.top(); pq.pop();
        int n = s.n, t = s.t;
        ll c = s.c;
        if (vis[n][t]) continue;
        vis[n][t] = true;
        // Combine costs from left and right
        if (t != 2) {
            ll nc = bestP[n][0] + bestP[n][1];
            if (nc < bestP[n][2]) {
                bestP[n][2] = nc;
                pq.push({n, 2, nc});
            }
        }
        // Transition
        if (n < N) {
            // Node to range
            vector<int> trans;
            segt[t].transToSegs(n, trans);
            for (int x : trans) {
                int i = x + N;
                if (!vis[i][t] && c < bestP[i][t]) {
                    bestP[i][t] = c;
                    pq.push({i, t, c});
                }
            }
            // TODO: Efficiency
            /*
            rep(x, 0, K) {
                if (n < A[x] || n > B[x]) continue;
                int i = x + N;
                if (!vis[i][t] && c < bestP[i][t]) {
                    bestP[i][t] = c;
                    pq.push({i, t, c});
                }
            }
            */
        } else {
            // Range to node
            int x = n - N;
            if (!vis[C[x]][t] && c + P[x] < bestP[C[x]][t]) {
                bestP[C[x]][t] = c + P[x];
                pq.push({C[x], t, c + P[x]});
            }
        }
    }
}

void solve() {
    cin >> N >> K;
    M = N + K;
    rep(i, 0, K) {
        cin >> C[i] >> P[i] >> A[i] >> B[i];
        C[i]--;
        A[i]--;
        B[i]--;
    }
    rep(i, 0, 3) {
        rep(j, 0, K) segt[i].addSeg(A[j], B[j], j);
    }
    dijkstra();
    rep(i, 0, N) {
        if (bestP[i][2] == INF) cout << "-1\n";
        else cout << bestP[i][2] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}