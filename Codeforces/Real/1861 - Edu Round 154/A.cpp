#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

void solve() {
    string S; cin >> S;
    rep(i, 0, sz(S)) {
        if (S[i] == '1') {
            cout << "13\n";
            return;
        } else if (S[i] == '3') {
            cout << "31\n";
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T; rep(i, 0, T) solve();
    return 0;
}
