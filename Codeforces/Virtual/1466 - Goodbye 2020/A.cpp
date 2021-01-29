#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N;
int X[51];
unordered_set<int> vals;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> X[i];
    vals.clear();
    rep(i, 0, N) {
        rep(j, i+1, N) {
            vals.insert(X[j] - X[i]);
        }
    }
    cout << sz(vals) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}