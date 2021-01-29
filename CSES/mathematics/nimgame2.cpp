#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5;

int N, x, currXOR;

void solve() {
    cin >> N;
    currXOR = 0;
    rep(i, 0, N) {
        cin >> x;
        currXOR ^= x;
    }
    if (currXOR % 4) cout << "first\n";
    else cout << "second\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}