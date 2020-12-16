#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAXN = 2e5 + 10;
const ll MOD = 1e9 + 7;

int N;
int A[MAXN], L[MAXN], R[MAXN];
pair<int, int> S[MAXN];

struct SegmentTree {
    ll vals[MAXN * 8 + 20], lazy[MAXN * 8 + 20];

    void init() {
        for (int i = 0; i < MAXN * 8 + 20; i++) lazy[i] = 1;
    }

    void prop(int n) {
        if (lazy[n] != 1) {
            lazy[n*2] = lazy[n*2] * lazy[n] % MOD;
            lazy[n*2+1] = lazy[n*2+1] * lazy[n] % MOD;
            vals[n*2] = vals[n*2] * lazy[n] % MOD;
            vals[n*2+1] = vals[n*2+1] * lazy[n] % MOD;
            lazy[n] = 1;
        }
    }

    void merge(int n) {
        vals[n] = (vals[n*2] + vals[n*2+1]) % MOD;
    }

    void mult(int l, int r, int n = 1, int lb = 0, int ub = 2 * N) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            lazy[n] = lazy[n] * 2 % MOD;
            vals[n] = vals[n] * 2 % MOD;
            return;
        }
        prop(n);
        mult(l, r, n*2, lb, (lb+ub)/2);
        mult(l, r, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    void pointAdd(int i, ll v, int n = 1, int lb = 0, int ub = 2 * N) {
        if (lb == ub) {
            vals[n] = (vals[n] + v) % MOD;
            return;
        }
        prop(n);
        if (i > (lb+ub)/2) pointAdd(i, v, n*2+1, (lb+ub)/2+1, ub);
        else pointAdd(i, v, n*2, lb, (lb+ub)/2);
        merge(n);
    }

    ll query(int l, int r, int n = 1, int lb = 0, int ub = 2 * N) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return vals[n];
        prop(n);
        return (query(l, r, n*2, lb, (lb+ub)/2) + query(l, r, n*2+1, (lb+ub)/2+1, ub)) % MOD;
    }
};

SegmentTree dp, dp2;

void solve() {
    dp.init();
    dp2.init();
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> L[i] >> R[i];
        S[i] = {L[i], R[i]};
    }
    sort(S, S+N);

    dp2.pointAdd(0, 1);
    for (int x = 0; x < N; x++) {
        int l = S[x].first, r = S[x].second;
        ll toAdd = dp.query(0, r-1) + dp2.query(0, l-1);
        toAdd %= MOD;
        dp.pointAdd(r, toAdd);
        dp2.pointAdd(r, dp2.query(0, r-1));
        dp.mult(r+1, 2*N);
        dp2.mult(r+1, 2*N);
    }

    // for (int i = 0; i <= 2 * N; i++) cout << dp.query(i, i) << ' ';
    // cout << endl;
    // for (int i = 0; i <= 2 * N; i++) cout << dp2.query(i, i) << ' ';
    // cout << endl;

    int answer = dp.query(0, 2 * N);

    cout << answer << endl;
}

int main() {
    freopen("help.in", "r", stdin);
    freopen("help.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}