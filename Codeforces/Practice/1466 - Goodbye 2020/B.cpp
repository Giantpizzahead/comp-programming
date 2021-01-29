#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N;
int X[MAXN];
unordered_set<int> vals;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> X[i];
    sort(X, X+N);
    vals.clear();
    vals.insert(X[0]);
    rep(i, 1, N) {
        if (X[i] <= X[i-1]) {
            X[i]++;
        }
        vals.insert(X[i]);
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