#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;

int N, M;
int initArr[MAXN];

struct SegmentTree {
    double V[MAXN*4+1], D[MAXN*4+1];

    void merge(int n) {
        V[n] = V[n*2] + V[n*2+1];
    }

    void prop(int n, int lb, int ub) {
        if (D[n] >= 0) {
            V[n*2] = D[n] * ((lb+ub)/2-lb+1);
            V[n*2+1] = D[n] * (ub-(lb+ub)/2);
            D[n*2] = D[n];
            D[n*2+1] = D[n];
            D[n] = -1;
        }
    }

    void init(int n=1, int lb=0, int ub=N-1) {
        D[n] = -1;
        if (lb == ub) {
            V[n] = initArr[lb];
            return;
        }
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    void set(int l, int r, double v, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            V[n] = v * (ub-lb+1);
            D[n] = v;
            return;
        }
        prop(n, lb, ub);
        set(l, r, v, n*2, lb, (lb+ub)/2);
        set(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    double query(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return V[n];
        prop(n, lb, ub);
        return query(l, r, n*2, lb, (lb+ub)/2) + query(l, r, n*2+1, (lb+ub)/2+1, ub);
    }
} segt;

void solve() {
    cin >> N >> M;
    rep(i, 0, N) cin >> initArr[i];
    segt.init();
    int l, r;
    rep(i, 0, M) {
        cin >> l >> r;
        if (l == r) continue;
        l--, r--;
        double s = segt.query(l, r);
        segt.set(l, r, 0);
        segt.set(l, l, s/2);
        segt.set(r, r, s/2);
    }
    cout << fixed << setprecision(9);
    rep(i, 0, N) cout << segt.query(i, i) << " \n"[i==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}