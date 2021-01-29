#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 60;

int R, C, numA;
bool rowsF[MAXN], colsF[MAXN], rowsA[MAXN], colsA[MAXN];
bool A[MAXN][MAXN];

void solve() {
    cin >> R >> C;
    numA = 0;
    rep(i, 0, R) {
        string S; cin >> S;
        rep(j, 0, C) {
            A[i][j] = (S[j] == 'A');
            if (A[i][j]) numA++;
        }
    }

    // Check -1 or 0
    if (numA == 0) {
        cout << "MORTAL\n";
        return;
    } else if (numA == R*C) {
        cout << 0 << "\n";
        return;
    }

    // Fill row info
    rep(i, 0, R) {
        rowsF[i] = true;
        rowsA[i] = false;
        rep(j, 0, C) {
            rowsF[i] &= A[i][j];
            rowsA[i] |= A[i][j];
        }
    }
    rep(j, 0, C) {
        colsF[j] = true;
        colsA[j] = false;
        rep(i, 0, R) {
            colsF[j] &= A[i][j];
            colsA[j] |= A[i][j];
        }
    }

    // Check 1
    if (rowsF[0] || rowsF[R-1] || colsF[0] || colsF[C-1]) {
        cout << 1 << "\n";
        return;
    }

    // Check 2
    bool works = A[0][0] || A[0][C-1] || A[R-1][0] || A[R-1][C-1];
    rep(i, 0, R) works |= rowsF[i];
    rep(j, 0, C) works |= colsF[j];
    if (works) {
        cout << 2 << "\n";
        return;
    }

    // Check 3
    if (rowsA[0] || rowsA[R-1] || colsA[0] || colsA[C-1]) {
        cout << 3 << "\n";
        return;
    }

    // Must be 4
    cout << 4 << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    rep(i, 0, T) solve();
    return 0;
}