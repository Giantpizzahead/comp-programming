#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, Q;
int T[MAXN];

struct SegmentTree {
    ll V[MAXN*4+1], D[MAXN*4+1];

    void init(int n=1, int lb=0, int ub=N-1) {
        if (lb == ub) {
            V[n] = T[lb];
            D[n] = 0;
            return;
        }
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2+1, ub);
        V[n] = V[n*2] + V[n*2+1];
        D[n] = 0;
    }

    void prop(int n, int lb, int ub) {
        if (D[n] >= 0) {
            // Add
            V[n*2] += D[n] * ((lb+ub)/2-lb+1);
            V[n*2+1] += D[n] * (ub-(lb+ub)/2);
            if (D[n*2] >= 0) D[n*2] += D[n];
            else D[n*2] -= D[n];
            if (D[n*2+1] >= 0) D[n*2+1] += D[n];
            else D[n*2+1] -= D[n];
        } else {
            // Set
            V[n*2] = -D[n] * ((lb+ub)/2-lb+1);
            V[n*2+1] = -D[n] * (ub-(lb+ub)/2);
            D[n*2] = D[n];
            D[n*2+1] = D[n];
        }
        D[n] = 0;
    }

    void rangeAdd(int l, int r, ll v, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            V[n] += v * (ub-lb+1);
            if (D[n] >= 0) D[n] += v;
            else D[n] -= v;
            return;
        }
        prop(n, lb, ub);
        rangeAdd(l, r, v, n*2, lb, (lb+ub)/2);
        rangeAdd(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        V[n] = V[n*2] + V[n*2+1];
    }

    void rangeSet(int l, int r, ll v, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            V[n] = v * (ub-lb+1);
            D[n] = -v;
            return;
        }
        prop(n, lb, ub);
        rangeSet(l, r, v, n*2, lb, (lb+ub)/2);
        rangeSet(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        V[n] = V[n*2] + V[n*2+1];
    }

    ll rangeSum(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return V[n];
        prop(n, lb, ub);
        return rangeSum(l, r, n*2, lb, (lb+ub)/2) + rangeSum(l, r, n*2+1, (lb+ub)/2+1, ub);
    }
} segt;

void solve() {
    cin >> N >> Q;
    rep(i, 0, N) cin >> T[i];
    segt.init();
    int t, a, b, x;
    rep(i, 0, Q) {
        cin >> t >> a >> b;
        a--, b--;
        if (t == 1) {
            // Range add
            cin >> x;
            segt.rangeAdd(a, b, x);
        } else if (t == 2) {
            // Range set
            cin >> x;
            segt.rangeSet(a, b, x);
        } else {
            // Range sum
            cout << segt.rangeSum(a, b) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}