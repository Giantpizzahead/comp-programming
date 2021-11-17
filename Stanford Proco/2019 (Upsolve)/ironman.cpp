#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1000;

int N;
int A[MAXN][MAXN];
bool D[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        rep(j, 0, N) {
            cin >> A[i][j];
        }
    }
    // Rows
    rep(j, 0, N-1) D[j] = (A[0][j] > A[0][j+1]);
    rep(i, 1, N) {
        rep(j, 0, N-1) {
            if (D[j] != (A[i][j] > A[i][j+1])) {
                cout << "N\n";
                return;
            }
        }
    }
    // Columns
    rep(i, 0, N-1) D[i] = (A[i][0] > A[i+1][0]);
    rep(j, 1, N) {
        rep(i, 0, N-1) {
            if (D[i] != (A[i][j] > A[i+1][j])) {
                cout << "N\n";
                return;
            }
        }
    }
    cout << "Y\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}