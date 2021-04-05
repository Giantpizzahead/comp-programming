#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5, MAXL = 18;

int N, Q;
int P[MAXL][MAXN], D[MAXN];

void solve() {
    cin >> N >> Q;
    P[0][1] = 1;
    rep(i, 2, N+1) {
        cin >> P[0][i];
    }
    rep(i, 1, MAXL) {
        rep(j, 1, N+1) {
            P[i][j] = P[i-1][P[i-1][j]];
        }
    }
    D[1] = -1;
    rep(i, 2, N+1) {
        int n = i;
        for (int j = MAXL-1; j >= 0; j--) {
            if (P[j][n] != 1) {
                D[i] += 1 << j;
                n = P[j][n];
            }
        }
    }
    int a, b;
    rep(i, 0, Q) {
        cin >> a >> b;
        if (D[a] < D[b]) swap(a, b);
        for (int j = MAXL-1; j >= 0; j--) {
            if (D[P[j][a]] >= D[b]) {
                a = P[j][a];
            }
        }
        if (a == b) cout << a << '\n';
        else {
            for (int j = MAXL-1; j >= 0; j--) {
                if (P[j][a] != P[j][b]) {
                    a = P[j][a];
                    b = P[j][b];
                }
            }
            cout << P[0][a] << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}