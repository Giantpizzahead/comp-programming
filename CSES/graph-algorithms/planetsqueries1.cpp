#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5, MAXK = 31;

int N, Q;
int succ[MAXK][MAXN];

void solve() {
    cin >> N >> Q;
    rep(i, 0, N) {
        cin >> succ[0][i];
        succ[0][i]--;
    }
    rep(k, 1, MAXK) {
        rep(i, 0, N) {
            succ[k][i] = succ[k-1][succ[k-1][i]];
        }
    }
    int a, b;
    rep(i, 0, Q) {
        cin >> a >> b;
        a--;
        for (int k = MAXK-1; k >= 0; k--) {
            if (b >= (1 << k)) {
                b -= 1 << k;
                a = succ[k][a];
            }
        }
        cout << a+1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}