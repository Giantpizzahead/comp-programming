/*
Notes go here.
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e6+5;

int R, C;
struct Loc {
    int i, j, v;
};
vector<Loc> H, S;

struct DisjointSet {
    int n;
    int V[MAXN];
    bool robot[MAXN], active[MAXN];

    void init(int n) {
        this->n = n;
        rep(i, 0, n) {
            V[i] = -1;
            robot[i] = false;
            active[i] = false;
        }
    }

    int find(int x) {
        if (V[x] < 0) return x;
        else {
            int r = find(V[x]);
            V[x] = r;
            return r;
        }
    }

    // a must be active!
    int merge(int a, int b) {
        if (b < 0 || b >= n) return a;
        a = find(a), b = find(b);
        if (a == b || !active[b]) return a;
        else if (V[a] < V[b]) {
            V[a] += V[b];
            V[b] = a;
            robot[a] |= robot[b];
            return a;
        } else {
            V[b] += V[a];
            V[a] = b;
            robot[b] |= robot[a];
            return b;
        }
    }
} ds;

void solve() {
    cin >> R >> C;
    H.clear();
    S.clear();
    rep(i, 0, R) {
        rep(j, 0, C) {
            int h; cin >> h;
            H.push_back({i, j, h});
        }
    }
    rep(i, 0, R) {
        rep(j, 0, C) {
            int s; cin >> s;
            S.push_back({i, j, s});
        }
    }
    ds.init(R*C);

    sort(all(H), [](const Loc& a, const Loc& b) {
        return a.v > b.v;
    });
    sort(all(S), [](const Loc& a, const Loc& b) {
        return a.v > b.v;
    });
    int hi = 0, si = 0;
    int numSamples = 0, numRobots = 0;
    while (hi != R*C || si != R*C) {
        if (hi != R*C && (si == R*C || H[hi].v > S[si].v)) {
            // Process platform
            Loc& l = H[hi++];
            // cout << "p " << l.i << " " << l.j << endl;
            int x = l.i * C + l.j;
            ds.active[x] = true;
            if (l.j != C-1) ds.merge(x, x+1);
            if (l.j != 0) ds.merge(x, x-1);
            if (l.i != R-1) ds.merge(x, x+C);
            if (l.i != 0) ds.merge(x, x-C);
        } else {
            // Process sample
            Loc& l = S[si++];
            // cout << "s " << l.i << " " << l.j << endl;
            int x = l.i * C + l.j;
            if (!ds.active[x]) continue;
            x = ds.find(x);
            if (!ds.robot[x]) {
                numSamples++;
                numRobots++;
                ds.robot[x] = true;
            } else {
                numSamples++;
            }
        }
    }
    cout << numSamples << " " << numRobots << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}