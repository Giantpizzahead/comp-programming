/*
https://codeforces.com/contest/369/problem/E

Solution: Clever usage of offline range queries.
For each query, # of segments =
Sum over all segments: # of points contained in segment i
-
Sum over all segments: # of adjacent pairs of points contained in segment i
Since for each segment, # of points - # of adjacent pairs = 1 no matter how many points are contained.
Runtime: O(NlogN)
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

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
    ll query(int l, int r) { // sum of values in [l, r)
        ll res = query(r) - query(l);
        return res;
    }
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

const int MAXN = 3e5+5;
const int C = 1e6+5;

int N, M;
FT ft(C);
struct Point {
    int x, v;
    bool s;
};
vector<Point> points;
struct Query {
    int id, contrib;
    int l, r;
};
vector<Query> queries;
int ans[MAXN];

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        int a, b;
        cin >> a >> b;
        points.push_back({a, b, true});
        points.push_back({b+1, b, false});
    }
    rep(i, 0, M) {
        int k; cin >> k;
        vector<int> vals(k);
        rep(j, 0, k) cin >> vals[j];
        rep(j, 0, k) queries.push_back({i, 1, vals[j], vals[j]});
        rep(j, 0, k-1) queries.push_back({i, -1, vals[j], vals[j+1]});
    }
    sort(all(queries), [](const Query& a, const Query& b) {
        return a.l < b.l;
    });
    sort(all(points), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    int cq = 0, cp = 0;
    while (cq != sz(queries) && cp != sz(points)) {
        if (queries[cq].l < points[cp].x) {
            // Process query
            int res = ft.query(queries[cq].r, C-1);
            // cout << queries[cq].id << ": " << res * queries[cq].contrib << endl;
            ans[queries[cq].id] += res * queries[cq].contrib;
            cq++;
        } else {
            // Process point
            if (points[cp].s) ft.update(points[cp].v, 1);
            else ft.update(points[cp].v, -1);
            // cout << points[cp].x << " " << points[cp].v << " " << points[cp].s << endl;
            cp++;
        }
    }
    rep(i, 0, M) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}