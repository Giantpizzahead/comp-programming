/*
Solution: 
Runtime: 
*/

#include "railroad.h"
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2e5+5;
const int INF = 1e9+7;

int N;

struct DisjointSet {
    int V[MAXN];

    void init() {
        rep(i, 0, N) V[i] = -1;
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
        else if (V[a] < V[b]) {
            V[a] += V[b];
            V[b] = a;
            return a;
        } else {
            V[b] += V[a];
            V[a] = b;
            return b;
        }
    }

    bool inSameComp(int a, int b) {
        return find(a) == find(b);
    }
} ds;

struct Loc {
    int x, i;
    bool isS;
    bool operator<(const Loc& o) const {
        if (x != o.x) return x < o.x;
        else if (i != o.i) return i < o.i;
        else return isS < o.isS;
    }
};
vector<Loc> locs;
set<Loc> onS, onT;

ll plan_roller_coaster(vector<int> s, vector<int> t) {
    N = sz(s);
    rep(i, 0, N) {
        locs.push_back({s[i], i, true});
        locs.push_back({t[i], i, false});
    }
    locs.push_back({0, N++, false});
    locs.push_back({INF, N++, true});
    sort(all(locs));
    reverse(all(locs));
    ds.init();

    // Sweep
    ll ans = 0;
    for (Loc& a : locs) {
        // cout << "loc " << a.i << " " << a.isS << " " << a.x << endl;
        if (a.isS) {
            // Check for t to pair with
            bool paired = true;
            if (!onT.empty()) {
                auto b = onT.begin();
                if (ds.inSameComp(a.i, b->i)) {
                    // Can't pair with this
                    if (sz(onT) >= 2) {
                        // Pair with the next t
                        b = next(b);
                        assert(!ds.inSameComp(a.i, b->i));
                    } else {
                        paired = false;
                    }
                }
                if (paired) {
                    // Pair these
                    // cout << "pair " << a.x << " " << b->x << endl;
                    ds.merge(a.i, b->i);
                    ans += max(0, b->x - a.x);
                    onT.erase(b);
                }
            } else paired = false;
            if (!paired) {
                // Save for later
                onS.insert(a);
            }
        } else {
            // Check for s to pair with
            bool paired = true;
            if (!onS.empty()) {
                auto b = onS.begin();
                if (ds.inSameComp(a.i, b->i)) {
                    // Can't pair with this
                    if (sz(onS) >= 2) {
                        // Pair with the next s
                        b = next(b);
                        assert(!ds.inSameComp(a.i, b->i));
                    } else {
                        paired = false;
                    }
                }
                if (paired) {
                    // Pair these
                    // cout << "pair " << a.x << " " << b->x << endl;
                    ds.merge(a.i, b->i);
                    ans += max(0, a.x - b->x);
                    onS.erase(b);
                }
            } else paired = false;
            if (!paired) {
                // Save for later
                onT.insert(a);
            }
        }
    }
    assert(onS.empty());
    assert(onT.empty());
    return ans;
}
