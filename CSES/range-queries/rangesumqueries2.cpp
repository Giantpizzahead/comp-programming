#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+1;

struct BIT {
    ll V[MAXN];

    void upd(int i, int v) {
        while (i < MAXN) {
            V[i] += v;
            i += i & -i;
        }
    }

    ll query(int i) {
        ll R = 0;
        while (i > 0) {
            R += V[i];
            i -= i & -i;
        }
        return R;
    }

    ll query(int l, int r) {
        return query(r) - query(l-1);
    }
};

int N, Q;
int V[MAXN];
BIT bit;

void solve() {
    cin >> N >> Q;
    rep(i, 1, N+1) {
        cin >> V[i];
        bit.upd(i, V[i]);
    }
    rep(i, 0, Q) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            bit.upd(b, c - V[b]);
            V[b] = c;
        } else {
            cout << bit.query(b, c) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}