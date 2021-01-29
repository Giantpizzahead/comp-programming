#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MOD = 1e9+7, MAXN = 2e5+2;

struct BIT {
    int V[MAXN];

    void upd(int i, int v) {
        while (i < MAXN) {
            V[i] = (V[i] + v) % MOD;
            i += i & -i;
        }
    }

    int query(int i) {
        int r = 0;
        while (i > 0) {
            r = (r + V[i]) % MOD;
            i -= i & -i;
        }
        return r;
    }
};

int N;
pair<int, int> X[MAXN];
BIT bit;

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> X[i].first;
        X[i].second = -(i+2);
    }
    sort(X, X+N);
    bit.upd(1, 1);
    rep(i, 0, N) {
        // cout << -X[i].second << endl;
        bit.upd(-X[i].second, bit.query(-X[i].second) % MOD);
    }
    int ans = bit.query(N+1) - 1;
    if (ans < 0) ans += MOD;
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}