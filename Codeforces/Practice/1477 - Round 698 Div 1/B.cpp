#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;
int N, Q;
int L[MAXN], R[MAXN];
string S, F;

struct SegmentTree {
    int num0[MAXN*4+1], num1[MAXN*4+1], rs[MAXN*4+1], delta[MAXN*4+1];

    void merge(int n) {
        num0[n] = num0[n*2] + num0[n*2+1];
        num1[n] = num1[n*2] + num1[n*2+1];
        rs[n] = rs[n*2] + rs[n*2+1];
    }

    void prop(int n) {
        if (delta[n] != -1) {
            delta[n*2] = delta[n];
            delta[n*2+1] = delta[n];
            if (delta[n] == 0) {
                num0[n*2] = rs[n*2];
                num0[n*2+1] = rs[n*2+1];
                num1[n*2] = 0;
                num1[n*2+1] = 0;
            } else {
                num1[n*2] = rs[n*2];
                num1[n*2+1] = rs[n*2+1];
                num0[n*2] = 0;
                num0[n*2+1] = 0;
            }
            delta[n] = -1;
        }
    }

    void init(int n = 1, int lb = 0, int ub = N-1) {
        delta[n] = -1;
        if (lb == ub) {
            num0[n] = F[lb] == '0';
            num1[n] = F[ub] == '1';
            rs[n] = 1;
            return;
        }
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    void set(int l, int r, int v, int n = 1, int lb = 0, int ub = N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            if (v == 0) {
                num0[n] = rs[n];
                num1[n] = 0;
            } else {
                num0[n] = 0;
                num1[n] = rs[n];
            }
            delta[n] = v;
            return;
        }
        prop(n);
        set(l, r, v, n*2, lb, (lb+ub)/2);
        set(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    int query1(int l, int r, int n = 1, int lb = 0, int ub = N-1) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return num1[n];
        prop(n);
        return query1(l, r, n*2, lb, (lb+ub)/2) + query1(l, r, n*2+1, (lb+ub)/2+1, ub);
    }
} segt;

void solve() {
    cin >> N >> Q;
    cin >> S >> F;
    segt.init();
    rep(i, 0, Q) {
        cin >> L[i] >> R[i];
        L[i]--, R[i]--;
    }
    //rep(i, 0, N) cout << segt.query1(i, i);
    //cout << endl;

    for (int i = Q-1; i >= 0; i--) {
        int l = L[i], r = R[i];
        int oneCnt = segt.query1(l, r);
        int zeroCnt = r-l+1-oneCnt;
        if (zeroCnt > oneCnt) {
            // Must've been zeros before
            segt.set(l, r, 0);
        } else if (oneCnt > zeroCnt) {
            // Must've been ones before
            segt.set(l, r, 1);
        } else {
            // Not possible
            cout << "NO\n";
            return;
        }
        //rep(i, 0, N) cout << segt.query1(i, i);
        //cout << endl;
    }

    rep(i, 0, N) {
        int v = segt.query1(i, i);
        if (S[i] - '0' != v) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}