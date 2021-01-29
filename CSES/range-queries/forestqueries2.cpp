#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1001;

struct BIT {
    int V[MAXN];

    void upd(int i, int v) {
        while (i < MAXN) {
            V[i] += v;
            i += i & -i;
        }
    }

    int query(int i) {
        int R = 0;
        while (i > 0) {
            R += V[i];
            i -= i & -i;
        }
        return R;
    }

    int query(int l, int r) {
        return query(r) - query(l-1);
    }
};

struct BIT2D {
    BIT V[MAXN];

    void upd(int i, int j, int v) {
        while (i < MAXN) {
            V[i].upd(j, v);
            i += i & -i;
        }
    }

    int query(int i, int j1, int j2) {
        int R = 0;
        while (i > 0) {
            R += V[i].query(j1, j2);
            i -= i & -i;
        }
        return R;
    }

    int query(int i1, int j1, int i2, int j2) {
        return query(i2, j1, j2) - query(i1-1, j1, j2);
    }
};

int N, Q;
bool state[MAXN][MAXN];
BIT2D bit;

void solve() {
    cin >> N >> Q;
    rep(i, 1, N+1) {
        string str;
        cin >> str;
        rep(j, 1, N+1) {
            state[i][j] = str[j-1] == '*';
            if (state[i][j]) bit.upd(i, j, 1);
        }
    }
    int a, b, c, d, e;
    rep(i, 0, Q) {
        cin >> a >> b >> c;
        if (a == 1) {
            if (state[b][c]) bit.upd(b, c, -1);
            else bit.upd(b, c, 1);
            state[b][c] = !state[b][c];
        } else {
            cin >> d >> e;
            cout << bit.query(b, c, d, e) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}