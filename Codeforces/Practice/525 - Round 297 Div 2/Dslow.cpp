/*
https://codeforces.com/contest/525/problem/D

Solution: DSU, choosing the room with the least expansion space needed when merging.
Runtime: O(NM)

This takes too long to code... taking a peek at the editorial, I know that there's a better way involving 2x2 squares.
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXD = 2e3+5;
const int MAXV = MAXD*MAXD;

int N, M;
char C[MAXD][MAXD];

int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};

inline int getID(int i, int j) {
    return M*i+j;
}

struct Info {
    int z;
    int i1, j1, i2, j2;
    int ci1, cj1, ci2, cj2;

    int getCurrArea() {
        return (ci2-ci1+1)*(cj2-cj1+1);
    }
};

struct DisjointSet {
    int V[MAXV];
    Info* I[MAXV];
    bool active[MAXV];

    DisjointSet() {
        rep(i, 0, MAXV) {
            V[i] = -1;
            active[i] = false;
            I[i] = new Info();
        }
    }

    int find(int n) {
        if (V[n] < 0) return n;
        int r = find(V[n]);
        V[n] = r;
        return r;
    }

    int merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return a;
        if (V[a] > V[b]) swap(a, b);
        V[a] += V[b];
        V[b] = a;
        if (I[a]->getCurrArea() < I[b]->getCurrArea()) swap(I[a], I[b]);
        I[a]->i1 = min(I[b]->i1, I[a]->i1);
        I[a]->j1 = min(I[b]->j1, I[a]->j1);
        I[a]->i2 = max(I[b]->i2, I[a]->i2);
        I[a]->j2 = max(I[b]->j2, I[a]->j2);
        return a;
    }

    void activate(int i, int j) {
        C[i][j] = '.';
        int id = find(getID(i, j));
        if (!active[id]) {
            I[id]->z = getID(i, j);
            I[id]->i1 = i, I[id]->i2 = i, I[id]->ci1 = i, I[id]->ci2 = i;
            I[id]->j1 = j, I[id]->j2 = j, I[id]->cj1 = j, I[id]->cj2 = j;
            active[id] = true;
        }
        // Merge with adjacent cells
        rep(d, 0, 4) {
            int ni = i + ci[d], nj = j + cj[d];
            if (ni < 0 || nj < 0 || ni >= N || nj >= M) continue;
            int nid = find(getID(ni, nj));
            if (active[nid]) id = merge(id, nid);
        }
    }
} ds;

void expand(int id) {
    while (true) {
        Info* infoP = ds.I[id];
        Info& info = *infoP;
        int z = info.z;
        if (info.ci1 != info.i1) {
            // Expand up
            int i = info.ci1-1;
            rep(j, info.cj1, info.cj2+1) ds.activate(i, j);
            info.ci1--;
        } else if (info.ci2 != info.i2) {
            // Expand down
            int i = info.ci2+1;
            rep(j, info.cj1, info.cj2+1) ds.activate(i, j);
            info.ci2++;
        } else if (info.cj1 != info.j1) {
            // Expand left
            int j = info.cj1-1;
            rep(i, info.ci1, info.ci2+1) ds.activate(i, j);
            info.cj1--;
        } else if (info.cj2 != info.j2) {
            // Expand right
            int j = info.cj2+1;
            rep(i, info.ci1, info.ci2+1) ds.activate(i, j);
            info.cj2++;
        } else {
            // Nowhere to expand
            break;
        }
        assert(info.z == z);
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        string S; cin >> S;
        rep(j, 0, M) {
            C[i][j] = S[j];
            if (C[i][j] == '.') {
                ds.activate(i, j);
            }
        }
    }
    // Fully expand everything
    rep(i, 0, N) rep(j, 0, M) if (C[i][j] == '.') expand(ds.find(getID(i, j)));
    rep(i, 0, N) {
        rep(j, 0, M) cout << C[i][j];
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}