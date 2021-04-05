#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, Q;

struct BIT {
    ll V[MAXN];

    void upd(int i, ll v) {
        for (; i < MAXN; i+=i&-i) V[i] += v;
    }

    void upd(int l, int r, ll v) {
        upd(l, v);
        upd(r+1, -v);
    }

    ll query(int i) {
        ll r = 0;
        for (; i > 0; i-=i&-i) r += V[i];
        return r;
    }
} bit;

void solve() {
    cin >> N >> Q;
    int t, a, b, c;
    rep(i, 1, N+1) {
        cin >> a;
        bit.upd(i, i, a);
    }
    rep(i, 0, Q) {
        cin >> t;
        if (t == 1) {
            cin >> a >> b >> c;
            bit.upd(a, b, c);
        } else {
            cin >> a;
            cout << bit.query(a) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}