#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int B, D, C, L;

void solve() {
    cin >> B >> D >> C >> L;
    bool possible = false;
    for (int i = 0; i <= L; i++) {
        for (int j = 0; j <= L; j++) {
            for (int k = 0; k <= L; k++) {
                if (i*B+j*D+k*C == L) {
                    possible = true;
                    cout << i << ' ' << j << ' ' << k << '\n';
                }
            }
        }
    }
    if (!possible) cout << "impossible\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}