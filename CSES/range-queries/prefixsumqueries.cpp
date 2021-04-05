#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;
const ll INF = 1e18;

int N, Q;
int A[MAXN];

struct SegmentTree {
    ll V[MAXN*4+1], D[MAXN*4+1];

    void merge(int n) {
        V[n] = max(V[n*2], V[n*2+1]);
    }

    void prop(int n) {
        if (D[n]) {
            V[n*2] += D[n];
            V[n*2+1] += D[n];
            D[n*2] += D[n];
            D[n*2+1] += D[n];
            D[n] = 0;
        }
    }

    void upd(int l, int r, ll v, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            V[n] += v;
            D[n] += v;
            return;
        }
        prop(n);
        upd(l, r, v, n*2, lb, (lb+ub)/2);
        upd(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    ll query(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return -INF;
        else if (lb >= l && ub <= r) return V[n];
        prop(n);
        return max(query(l, r, n*2, lb, (lb+ub)/2), query(l, r, n*2+1, (lb+ub)/2+1, ub));
    }
} segt;

void solve() {
    cin >> N >> Q;
    rep(i, 0, N) {
        cin >> A[i];
        segt.upd(i, N-1, A[i]);
    }
    int t, a, b;
    rep(i, 0, Q) {
        cin >> t >> a >> b;
        if (t == 1) {
            // Update
            a--;
            segt.upd(a, N-1, b-A[a]);
            A[a] = b;
        } else {
            // Query
            a--, b--;
            cout << max(segt.query(a, b) - (a == 0 ? 0 : segt.query(a-1, a-1)), 0LL) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}