#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, Q;

struct SegmentTree {
    int V[MAXN*4+1];

    void merge(int n) {
        V[n] = min(V[n*2], V[n*2+1]);
    }

    void upd(int i, int v, int n=1, int lb=0, int ub=N-1) {
        if (lb == ub) {
            V[n] = v;
            return;
        } else if (i > (lb+ub)/2) upd(i, v, n*2+1, (lb+ub)/2+1, ub);
        else upd(i, v, n*2, lb, (lb+ub)/2);
        merge(n);
    }

    int query(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return INT32_MAX;
        else if (lb >= l && ub <= r) return V[n];
        return min(query(l, r, n*2, lb, (lb+ub)/2), query(l, r, n*2+1, (lb+ub)/2+1, ub));
    }
};

SegmentTree segLow, segHigh;

void solve() {
    cin >> N >> Q;
    int p;
    rep(i, 0, N) {
        cin >> p;
        segLow.upd(i, p-i);
        segHigh.upd(i, p+i);
    }
    int t, a, b;
    rep(i, 0, Q) {
        cin >> t;
        if (t == 1) {
            // Update
            cin >> a >> b; a--;
            segLow.upd(a, b-a);
            segHigh.upd(a, b+a);
        } else {
            // Query
            cin >> a; a--;
            int cost = min(segLow.query(0, a)+a, segHigh.query(a, N-1)-a);
            cout << cost << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}