#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MOD = 1e9+7;

int N;

void solve() {
    cin >> N;
    int R = 1;
    rep(i, 0, N) {
        R = R * 2 % MOD;
    }
    cout << R << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}