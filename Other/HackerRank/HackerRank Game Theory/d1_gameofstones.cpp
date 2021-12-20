#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 101;

int N;
bool W[MAXN];

void solve() {
    cin >> N;
    cout << (W[N] ? "First" : "Second") << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    rep(i, 2, MAXN) {
        W[i] = !W[i-2];
        if (i-3 >= 0) W[i] |= !W[i-3];
        if (i-5 >= 0) W[i] |= !W[i-5];
    }
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}