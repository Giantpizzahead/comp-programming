#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e6+5, MAXK = 102;

int N, K;
int P[MAXK];
bool win[MAXN];

void solve() {
    cin >> N >> K;
    rep(i, 0, K) {
        cin >> P[i];
    }
    win[0] = false;
    win[1] = true;
    rep(i, 2, N+1) {
        rep(k, 0, K) {
            if (P[k] <= i && !win[i-P[k]]) {
                win[i] = true;
                break;
            }
        }
    }
    rep(i, 1, N+1) cout << (win[i] ? 'W' : 'L');
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}