#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5, MAXV = 2e6+1;

int N;
struct Point {
    int x, l, r;
    bool s;
    bool operator<(const Point& o) const {
        return x < o.x;
    }
};
Point points[MAXN*2];

struct SegmentTree {
    int minV[MAXV*4+1], cnt[MAXV*4+1], delta[MAXV*4+1];

    void merge(int n) {
        minV[n] = min(minV[n*2], minV[n*2+1]);
        if (minV[n*2] == minV[n*2+1]) {
            cnt[n] = cnt[n*2] + cnt[n*2+1];
        } else if (minV[n] == minV[n*2]) {
            cnt[n] = cnt[n*2];
        } else {
            cnt[n] = cnt[n*2+1];
        }
    }

    void prop(int n) {
        if (delta[n] != 0) {
            minV[n*2] += delta[n];
            minV[n*2+1] += delta[n];
            delta[n*2] += delta[n];
            delta[n*2+1] += delta[n];
            delta[n] = 0;
        }
    }

    void init(int n = 1, int lb = 0, int ub = MAXV-1) {
        if (lb == ub) {
            minV[n] = 0;
            cnt[n] = 1;
            delta[n] = 0;
            return;
        }
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    void upd(int l, int r, int v, int n = 1, int lb = 0, int ub = MAXV-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            minV[n] += v;
            delta[n] += v;
            return;
        }
        prop(n);
        upd(l, r, v, n*2, lb, (lb+ub)/2);
        upd(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    int queryArea() {
        return MAXV - cnt[1];
    }
};

SegmentTree segt;

void solve() {
    cin >> N;
    segt.init();
    int a, b, c, d;
    rep(i, 0, N) {
        cin >> a >> b >> c >> d;
        a += 1e6;
        b += 1e6;
        c += 1e6;
        d += 1e6;
        points[i*2] = {a, b, d, true};
        points[i*2+1] = {c, b, d, false};
    }
    N *= 2;
    sort(points, points+N);
    int lx = -1;
    ll answer = 0;
    rep(i, 0, N) {
        Point& p = points[i];
        // cout << segt.queryArea() << endl;
        answer += (ll) segt.queryArea() * (p.x - lx);
        lx = p.x;
        if (p.s) segt.upd(p.l, p.r-1, 1);
        else segt.upd(p.l, p.r-1, -1);
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}