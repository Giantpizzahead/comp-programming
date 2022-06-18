#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXA = 1e4+5;

int N;
bool seen[MAXA];

void solve() {
    rep(i, 0, MAXA) seen[i] = false;
    int toRemove = 0;
    cin >> N;
    rep(i, 0, N) {
        int x; cin >> x;
        if (!seen[x]) seen[x] = true;
        else toRemove++;
    }
    if (toRemove % 2 == 1) toRemove++;
    cout << N - toRemove << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}