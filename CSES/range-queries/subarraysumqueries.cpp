#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, M;
int A[MAXN];

struct SegmentTree {
    ll L[MAXN*4+1], R[MAXN*4+1], W[MAXN*4+1], M[MAXN*4+1];

    void set(int n, int v) {
        L[n] = max(0, v);
        R[n] = max(0, v);
        W[n] = v;
        M[n] = max(0, v);
    }

    void merge(int n) {
        L[n] = max(L[n*2], W[n*2] + L[n*2+1]);
        R[n] = max(R[n*2+1], W[n*2+1] + R[n*2]);
        W[n] = W[n*2] + W[n*2+1];
        M[n] = max(max(M[n*2], M[n*2+1]), R[n*2] + L[n*2+1]);
    }

    void init(int n=1, int lb=0, int ub=N) {
        if (lb == ub-1) {
            set(n, A[lb]);
            return;
        }
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2, ub);
        merge(n);
    }

    void upd(int i, int v, int n=1, int lb=0, int ub=N) {
        if (lb == ub-1) {
            set(n, v);
            return;
        } else if (i < (lb+ub)/2) upd(i, v, n*2, lb, (lb+ub)/2);
        else upd(i, v, n*2+1, (lb+ub)/2, ub);
        merge(n);
    }

    ll query() {
        return M[1];
    }
} segt;

void solve() {
    cin >> N >> M;
    rep(i, 0, N) cin >> A[i];
    segt.init();
    int a, b;
    rep(i, 0, M) {
        cin >> a >> b;
        a--;
        segt.upd(a, b);
        cout << segt.query() << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}