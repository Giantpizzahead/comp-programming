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
const int MAXK = 20;

int N, Q;
vi S;
int A[MAXN][MAXK];

int combine(int a, int b) {
    if (a > b) swap(a, b);
    int c = -1;
    if (a == b) c = -1;
    else if (a == 0 && b == 1) c = 2;
    else if (a == 1 && b == 2) c = 0;
    else if (a == 0 && b == 2) c = 1;
    else c = b;
    return c;
}

bool solveQuery(int l, int r) {
    // Binary lift
    int c = -1;
    for (int k = MAXK-1; k >= 0; k--) {
        if (l + (1 << k) <= r) {
            c = combine(c, A[k][l]);
            l += (1 << k);
        }
    }
    return c == 0;
}

void solve() {
    string strS;
    cin >> strS;
    for (char c : strS) {
        if (c == 'C') S.push_back(0);
        else if (c == 'O') S.push_back(1);
        else S.push_back(2);
    }
    N = sz(S);
    // Generate binary lift table
    rep(i, 0, N) A[0][i] = S[i];
    rep(k, 1, MAXK) {
        rep(i, 0, N) {
            int i2 = i + (1 << (k-1));
            if (i2 >= N) {
                A[k][i] = A[k-1][i];
                continue;
            }
            int a = A[k-1][i], b = A[k-1][i2];
            A[k][i] = combine(a, b);
        }
    }
    // rep(k, 0, MAXK) rep(i, 0, N) cout << A[k][i] << " \n"[i==N-1];
    // Solve queries
    cin >> Q;
    rep(i, 0, Q) {
        int l, r; cin >> l >> r;
        l--;
        cout << (solveQuery(l, r) ? 'Y' : 'N');
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