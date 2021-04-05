#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5, MAXL = 31;

int N;
int A[MAXN], num1[MAXL], num0[MAXL];

// int W[MAXL][MAXL][4];
bool firstWins(int c1, int c0) {
    if (c1 % 4 == 1) return true;
    else if (c0 % 2 == 1) return true;
    return false;
    // // DP
    // W[0][0][0b00] = 0;
    // W[0][0][0b01] = -1;
    // W[0][0][0b10] = 1;
    // W[0][0][0b11] = 0;
    // rep(i, 0, MAXL) {
    //     rep(j, 0, MAXL) {
    //         if (i == 0 && j == 0) continue;
    //         rep(k, 0, 4) {
    //             W[i][j][k] = -1;
    //             // Take 1
    //             if (i != 0) {
    //                 int nk = k^2;
    //                 if (nk == 0b01) nk = 0b10;
    //                 else if (nk == 0b10) nk = 0b01;
    //                 W[i][j][k] = max(-W[i-1][j][nk], W[i][j][k]);
    //             }
    //             // Take 0
    //             if (j != 0) {
    //                 int nk = k;
    //                 if (nk == 0b01) nk = 0b10;
    //                 else if (nk == 0b10) nk = 0b01;
    //                 W[i][j][k] = max(-W[i][j-1][nk], W[i][j][k]);
    //             }
    //         }
    //     }
    // }

    // rep(i, 0, MAXL) {
    //     rep(j, 0, MAXL) {
    //         rep(k, 0, 1) {
    //             if (W[i][j][k] == -1) cout << 'X';
    //             else if (W[i][j][k] == 0) cout << '-';
    //             else cout << 'O';
    //         }
    //         // cout << " ";
    //     }
    //     cout << endl;
    // }
    // return true;
}

void solve() {
    rep(j, 0, MAXL) {
        num0[j] = 0;
        num1[j] = 0;
    }
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i];
        rep(j, 0, MAXL) {
            if (A[i] & (1 << j)) num1[j]++;
            else num0[j]++;
        }
    }
    int winner = -1;
    for (int j = MAXL-1; j >= 0; j--) {
        if (num1[j] % 2 != 0) {
            // This bit decides the winner
            winner = firstWins(num1[j], num0[j]);
            break;
        }
    }
    if (winner == -1) cout << "DRAW\n";
    else if (winner == 1) cout << "WIN\n";
    else cout << "LOSE\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}