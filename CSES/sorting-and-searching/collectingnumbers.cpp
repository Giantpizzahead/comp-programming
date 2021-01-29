#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
pair<int, int> X[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> X[i].first;
        X[i].second = i;
    }
    sort(X, X+N);
    int ans = 1;
    rep(i, 1, N) {
        if (X[i-1].second > X[i].second) ans++;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}