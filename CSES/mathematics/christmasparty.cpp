#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e6+5;
const ll MOD = 1e9+7;

int N;
ll D[MAXN];

void solve() {
    cin >> N;
    D[0] = 1, D[1] = 0;
    rep(i, 2, N+1) D[i] = (i-1) * (D[i-2] + D[i-1]) % MOD;
    cout << D[N] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}