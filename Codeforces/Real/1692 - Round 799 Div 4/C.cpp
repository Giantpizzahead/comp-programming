#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

char A[8][8];
char B[8][8];

bool testLoc(int a, int b) {
    rep(i, 0, 8) rep(j, 0, 8) B[i][j] = (abs(a-i) == abs(b-j) ? '#' : '.');
    bool same = true;
    rep(i, 0, 8) rep(j, 0, 8) if (A[i][j] != B[i][j]) same = false;
    return same;
}

void solve() {
    rep(i, 0, 8) {
        string s; cin >> s;
        rep(j, 0, 8) A[i][j] = s[j];
    }
    rep(i, 0, 8) {
        rep(j, 0, 8) {
            if (testLoc(i, j)) {
                cout << i+1 << " " << j+1 << "\n";
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}