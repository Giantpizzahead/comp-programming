/*
01010101111

Cannot have 0-0 followed by 1-1 in any case
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

void solve() {
    string A, B; cin >> A >> B;
    int N = sz(A);
    rep(i, 0, N-1) {
        if (A[i] == '0' && B[i] == '0' && A[i+1] == '1' && B[i+1] == '1') {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T; rep(i, 0, T) solve();
    return 0;
}
