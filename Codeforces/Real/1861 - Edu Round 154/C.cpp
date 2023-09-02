/*
Maintain the minimum and maximum possible sorted prefixes.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

string S;

void solve() {
    cin >> S;
    int N = 0, sortL = 0, sortR = 0;
    for (char c : S) {
        if (c == '+') {
            if (sortR == N) sortR++;
            if (sortL == 0) sortL++;
            N++;
        } else if (c == '-') {
            if (sortL == N) sortL--;
            if (sortR == N) sortR--;
            N--;
        } else if (c == '0') {
            if (sortL == N) {
                cout << "NO\n";
                return;
            }
            sortR = min(sortR, N-1);
        } else if (c == '1') {
            if (sortR != N) {
                cout << "NO\n";
                return;
            }
            sortL = N;
        }
        // cout << "N=" << N << ", sortL=" << sortL << ", sortR=" << sortR << endl;
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T; rep(i, 0, T) solve();
    return 0;
}
