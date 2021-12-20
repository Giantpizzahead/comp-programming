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

const int MAXN = 2e6+5;
const int MOD = 1e9+7;

int N, M;
struct Range {
    int a, b, x;
    bool operator<(const Range& o) const {
        if (a != o.a) return a < o.a;
        else return x < o.x;
    }
};
set<Range> ranges;

inline ll pairCount(ll x) {
    return x * (x-1) / 2;
}

struct DisjointSet {
    int V[MAXN], minV[MAXN], maxV[MAXN];
    ll numRoots, addedPairs;

    void init() {
        rep(i, 0, N) {
            V[i] = -1;
            minV[i] = i;
            maxV[i] = i;
        }
        numRoots = N;
        addedPairs = 0;
    }

    int find(int x) {
        if (V[x] < 0) return x;
        else {
            int r = find(V[x]);
            V[x] = r;
            return r;
        }
    }

    void merge(int a, int b) {
        a = find(a), b = find(b);
        int f;
        if (a == b) return;
        else if (V[a] < V[b]) {
            ranges.erase({minV[a], maxV[a], a});
            ranges.erase({minV[b], maxV[b], b});
            addedPairs -= pairCount(-V[a]);
            addedPairs -= pairCount(-V[b]);
            V[a] += V[b];
            addedPairs += pairCount(-V[a]);
            V[b] = a;
            minV[a] = min(minV[b], minV[a]);
            maxV[a] = max(maxV[b], maxV[a]);
            f = a;
        } else {
            ranges.erase({minV[b], maxV[b], b});
            ranges.erase({minV[a], maxV[a], a});
            addedPairs -= pairCount(-V[a]);
            addedPairs -= pairCount(-V[b]);
            V[b] += V[a];
            addedPairs += pairCount(-V[b]);
            V[a] = b;
            minV[b] = min(minV[a], minV[b]);
            maxV[b] = max(maxV[a], maxV[b]);
            f = b;
        }
        numRoots--;
        // Check for overlapping ranges
        auto ptr = ranges.lower_bound({minV[f], -1, -1});
        if (ptr != ranges.end() && ptr->b <= maxV[f]) {
            // Overlap
            merge(f, ptr->x);
            return;
        }
        if (ptr != ranges.begin()) {
            ptr = prev(ptr);
            if (ptr->b >= minV[f]) {
                // Overlap
                merge(f, ptr->x);
                return;
            }
        }
        // No overlaps
        ranges.insert({minV[f], maxV[f], f});
    }
} ds;

void solve() {
    cin >> N >> M;
    ds.init();
    ranges.clear();
    rep(i, 0, N) ranges.insert({i, i, i});
    vector<ll> S;
    rep(i, 0, M) {
        int a, b; cin >> a >> b;
        a--, b--;
        ds.merge(a, b);
        ll s = ds.addedPairs + (ll) N * (N-1) / 2;
        S.push_back(s % MOD);

        // cerr << s << endl;
        // cerr << "data: " << ds.addedPairs << " " << ds.numRoots << endl;
        // cerr << "ranges:\n";
        // for (const Range& r : ranges) cerr << r.a << " " << r.b << " " << r.x << endl;
    }
    ll r = 1;
    for (ll x : S) r = r*x % MOD;
    cout << r << '\n';
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