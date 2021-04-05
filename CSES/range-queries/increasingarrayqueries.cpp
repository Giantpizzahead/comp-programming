#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, Q;
int A[MAXN];
ll pre[MAXN], ans[MAXN];
struct Query {
    int l, r, id;
};
Query queries[MAXN];

struct SegmentTree {
    ll V[MAXN*4+1], D[MAXN*4+1];

    void set(int n, ll v, int lb, int ub) {
        V[n] = v * (ub-lb);
        D[n] = v;
    }

    void merge(int n) {
        V[n] = V[n*2] + V[n*2+1];
    }

    void prop(int n, int lb, int ub) {
        if (D[n]) {
            set(n*2, D[n], lb, (lb+ub)>>1);
            set(n*2+1, D[n], (lb+ub)>>1, ub);
            D[n] = 0;
        }
    }

    void init(int n=1, int lb=0, int ub=N) {
        if (lb == ub-1) {
            set(n, A[lb], lb, ub);
            return;
        }
        init(n*2, lb, (lb+ub)>>1);
        init(n*2+1, (lb+ub)>>1, ub);
        merge(n);
    }

    void upd(int l, int r, ll v, int n=1, int lb=0, int ub=N) {
        if (l >= ub || r <= lb) return;
        else if (lb >= l && ub <= r) {
            set(n, v, lb, ub);
            return;
        }
        prop(n, lb, ub);
        upd(l, r, v, n*2, lb, (lb+ub)>>1);
        upd(l, r, v, n*2+1, (lb+ub)>>1, ub);
        merge(n);
    }

    ll query(int l, int r, int n=1, int lb=0, int ub=N) {
        // cout << l << " " << r << " " << n << " " << lb << " " << ub << endl;
        if (l >= ub || r <= lb) return 0;
        else if (lb >= l && ub <= r) return V[n];
        prop(n, lb, ub);
        return query(l, r, n*2, lb, (lb+ub)>>1) + query(l, r, n*2+1, (lb+ub)>>1, ub);
    }
} segt;

stack<pair<int, int>> locs;

void solve() {
    cin >> N >> Q;
    rep(i, 0, N) cin >> A[i];
    pre[0] = A[0];
    rep(i, 1, N) pre[i] = pre[i-1] + A[i];
    rep(i, 0, Q) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--, queries[i].r--;
        queries[i].id = i;
    }
    sort(queries, queries+Q, [](const Query& a, const Query& b) {
        return a.l > b.l;
    });

    segt.init();
    int qi = 0;
    for (int i = N-1; i >= 0; i--) {
        int currNext = i;
        while (!locs.empty() && locs.top().second < A[i]) {
            currNext = locs.top().first;
            segt.upd(i+1, locs.top().first+1, A[i]);
            locs.pop();
        }
        locs.push({currNext, A[i]});
        for (; qi != Q && queries[qi].l == i; qi++) {
            Query& q = queries[qi];
            ans[q.id] = segt.query(q.l, q.r+1) - pre[q.r] + (q.l == 0 ? 0 : pre[q.l-1]);
        }
    }

    rep(i, 0, Q) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}