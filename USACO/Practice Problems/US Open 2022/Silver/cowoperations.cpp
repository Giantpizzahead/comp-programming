#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, Q;
vi S;
int pre[3][MAXN];

void solve() {
    string strS;
    cin >> strS;
    for (char c : strS) {
        if (c == 'C') S.push_back(0);
        else if (c == 'O') S.push_back(1);
        else S.push_back(2);
    }
    N = sz(S);
    // Generate prefix sums
    rep(i, 0, 3) rep(j, 0, N) {
        pre[i][j] = (j == 0 ? 0 : pre[i][j-1]);
        if (S[j] == i) pre[i][j]++;
    }
    // Solve queries
    cin >> Q;
    rep(i, 0, Q) {
        int l, r; cin >> l >> r;
        l--, r--;
        int a = pre[0][r] - (l == 0 ? 0 : pre[0][l-1]);
        int b = pre[1][r] - (l == 0 ? 0 : pre[1][l-1]);
        int c = pre[2][r] - (l == 0 ? 0 : pre[2][l-1]);
        // EOO or OEE works
        if ((a % 2) != (b % 2) && (b % 2) == (c % 2)) cout << 'Y';
        else cout << 'N';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}