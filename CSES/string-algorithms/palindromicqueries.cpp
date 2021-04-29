#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int NUMH = 2, MAXN = 2e5+5, MOD = 1e9+7;

int randint(int a, int b) {
    return rand() % (b-a+1) + a;
}

int N, M;

struct SegmentTree {
    int V[MAXN*4+1], P[MAXN], H;

    void genP() {
        P[0] = 1;
        rep(i, 1, MAXN) P[i] = (ll) P[i-1] * H % MOD;
    }

    void upd(int i, int v, int n=1, int lb=0, int ub=N-1) {
        if (lb == ub) {
            V[n] = v;
            return;
        } else if (i > (lb+ub)/2) {
            upd(i, v, n*2+1, (lb+ub)/2+1, ub);
        } else {
            upd(i, v, n*2, lb, (lb+ub)/2);
        }
        int rs = ub-(lb+ub)/2;
        V[n] = ((ll) P[rs] * V[n*2] + V[n*2+1]) % MOD;
    }

    int query(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > r) return 0;
        else if (lb >= l && ub <= r) return V[n];
        int lp = query(l, min(r, (lb+ub)/2), n*2, lb, (lb+ub)/2), rp = query(max(l, (lb+ub)/2+1), r, n*2+1, (lb+ub)/2+1, ub);
        int rs = max(r-max(l, (lb+ub)/2+1)+1, 0);
        return ((ll) P[rs] * lp + rp) % MOD;
    }
};
SegmentTree segtF[NUMH], segtB[NUMH];

void solve() {
    // Gen hashes
    srand(time(NULL));
    rep(h, 0, NUMH) {
        segtF[h].H = randint(500000000, 1000000000);
        segtF[h].genP();
        segtB[h].H = segtF[h].H;
        segtB[h].genP();
    }

    string str;
    cin >> N >> M >> str;
    rep(h, 0, NUMH) {
        rep(i, 0, N) {
            segtF[h].upd(i, str[i]);
            segtB[h].upd(N-1-i, str[i]);
        }
    }
    int a, b;
    char c;
    rep(i, 0, M) {
        cin >> a;
        if (a == 1) {
            cin >> a >> c;
            a--;
            rep(h, 0, NUMH) {
                segtF[h].upd(a, c);
                segtB[h].upd(N-1-a, c);
            }
        } else {
            cin >> a >> b;
            a--, b--;
            int ra = N-1-a, rb = N-1-b;
            bool match = true;
            rep(h, 0, NUMH) {
                if (segtF[h].query(a, b) != segtB[h].query(rb, ra)) {
                    match = false;
                    break;
                }
            }
            cout << (match ? "YES\n" : "NO\n");
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}