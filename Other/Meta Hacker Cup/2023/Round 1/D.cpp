/*
Solution: Lazy segment tree that stores mins and maxes, along with whether the range should be flipped.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 1e6+10;
const int MOD = 1e9+7;
 
int N, Q;
int A[MAXN];

struct SegmentTree {
    int rMin[MAXN*4+1], rMax[MAXN*4+1];
    bool rFlip[MAXN*4+1];
 
    void init(int n=1, int lb=0, int ub=N-1) {
        if (lb == ub) {
            rMin[n] = A[lb], rMax[n] = A[lb];
            rFlip[n] = false;
            return;
        }
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }
 
    void prop(int n, int lb, int ub) {
        if (rFlip[n]) {
            // Flip range
            swap(rMin[n*2], rMax[n*2]);
            swap(rMin[n*2+1], rMax[n*2+1]);
            rMin[n*2] = MOD - rMin[n*2];
            rMax[n*2] = MOD - rMax[n*2];
            rMin[n*2+1] = MOD - rMin[n*2+1];
            rMax[n*2+1] = MOD - rMax[n*2+1];
            rFlip[n*2] = !rFlip[n*2];
            rFlip[n*2+1] = !rFlip[n*2+1];

            rFlip[n] = false;
        }
    }

    void merge(int n) {
        rMin[n] = min(rMin[n*2], rMin[n*2+1]);
        rMax[n] = max(rMax[n*2], rMax[n*2+1]);
        rFlip[n] = false;
    }
 
    void rangeFlip(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            rFlip[n] = !rFlip[n];
            swap(rMin[n], rMax[n]);
            rMin[n] = MOD - rMin[n];
            rMax[n] = MOD - rMax[n];
            return;
        }
        prop(n, lb, ub);
        rangeFlip(l, r, n*2, lb, (lb+ub)/2);
        rangeFlip(l, r, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }
 
    int getMaxIndex(int n=1, int lb=0, int ub=N-1) {
        if (lb == ub) return lb;
        prop(n, lb, ub);
        if (rMax[n*2] >= rMax[n*2+1]) return getMaxIndex(n*2, lb, (lb+ub)/2);
        else return getMaxIndex(n*2+1, (lb+ub)/2+1, ub);
    }

    void debug(int n=1, int lb=0, int ub=N-1) {
        if (lb == ub) cerr << lb << " = " << rMax[n] << endl;
        else {
            prop(n, lb, ub);
            debug(n*2, lb, (lb+ub)/2);
            debug(n*2+1, (lb+ub)/2+1, ub);
        }

        if (n == 1) {
            cerr << "rMax: ";
            rep(i, 0, 4*N+1) cerr << rMax[i] << " ";
            cerr << endl;
        }
    }
} segt;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    segt.init();
    // segt.debug();
    // cerr << endl;

    cin >> Q;
    ll ans = 0;
    rep(i, 0, Q) {
        int l, r; cin >> l >> r; l--, r--;
        segt.rangeFlip(l, r);
        // segt.debug();
        // cerr << endl;
        ans += segt.getMaxIndex() + 1;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("d.txt", "r", stdin);
    freopen("d.out", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
