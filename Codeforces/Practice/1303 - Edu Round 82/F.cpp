#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int INF = 1e9, MAXN = 302, MAXG = 90005, MAXQ = 2e6+5;
const int cx[] = {1, 0, -1, 0}, cy[] = {0, 1, 0, -1};

int N, M, maxC, Q;
int X[MAXQ], Y[MAXQ], C[MAXQ], A[MAXQ];

inline int getI(int x, int y) {
    return x * M + y;
}

struct DisjointSet {
    int comps = 0;
    int V[MAXG];

    void reset() {
        rep(i, 0, N*M) V[i] = -INF;
        comps = 0;
    }

    int find(int i) {
        if (V[i] < 0) return i;
        int res = find(V[i]);
        V[i] = res;
        return res;
    }

    void merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b || V[a] == -INF || V[b] == -INF) return;
        comps--;
        if (V[a] < V[b]) {
            V[a] += V[b];
            V[b] = a;
        } else {
            V[b] += V[a];
            V[a] = b;
        }
    }

    void activate(int x, int y) {
        int i = find(getI(x, y));
        if (V[i] == -INF) {
            V[i] = -1;
            comps++;
        }
        rep(d, 0, 4) {
            int nx = x+cx[d], ny = y+cy[d];
            if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
            merge(i, getI(nx, ny));
        }
    }
};

DisjointSet ds;
struct Update {
    int x, y, t;
};
vector<Update> updateF[MAXQ], updateR[MAXQ];
int currC[MAXN][MAXN], ansPre[MAXQ];

void solve() {
    cin >> N >> M >> Q;
    rep(i, 0, Q) {
        cin >> X[i] >> Y[i] >> C[i];
        X[i]--;
        Y[i]--;
        if (C[i] != currC[X[i]][Y[i]]) {
            updateR[currC[X[i]][Y[i]]].push_back({X[i], Y[i], i});
            updateF[C[i]].push_back({X[i], Y[i], i});
        }
        currC[X[i]][Y[i]] = C[i];
    }
    rep(i, 0, N) {
        rep(j, 0, M) {
            updateR[currC[i][j]].push_back({i, j, Q});
        }
    }
    maxC = C[Q-1];
    rep(i, 0, maxC+1) {
        // Evaluate this component
        reverse(all(updateR[i]));

        ds.reset();
        int lastComp = 0;
        for (Update& u : updateF[i]) {
            ds.activate(u.x, u.y);
            ansPre[u.t] += ds.comps - lastComp;
            lastComp = ds.comps;
        }

        ds.reset();
        lastComp = 0;
        for (Update& u : updateR[i]) {
            ds.activate(u.x, u.y);
            ansPre[u.t] -= ds.comps - lastComp;
            lastComp = ds.comps;
        }

        // cout << i << ":\n";
        // for (Update& u : updateF[i]) {
        //     cout << "(" << u.x << ", " << u.y << ", " << u.t << ") ";
        // }
        // cout << endl;
        // for (Update& u : updateR[i]) {
        //     cout << "(" << u.x << ", " << u.y << ", " << u.t << ") ";
        // }
        // cout << endl;
    }
    // rep(i, 0, Q) cout << ansPre[i] << ' ';
    // cout << endl;

    A[0] = ansPre[0] + 1;
    rep(i, 1, Q) {
        A[i] = A[i-1] + ansPre[i];
    }
    rep(i, 0, Q) {
        cout << A[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}