/**
 * Each balanced set can be split into 3 parts, possibly empty: The "upper pyramid", "slide", and "bottom pyramid".
 * Ex:
 *      ##
 *    #####      Upper pyramid
 *    ######
 *    ######____________________
 *      ####
 *       ######  (Right) slide
 *        #####
 *        #####_________________
 *        ####
 *         ###   Bottom pyramid
 *          #
 * 
 * Do DP by rows, where dp[i][a][b] = # ways to form a balanced region with base row i, cells [a, b]. Have one DP for
 * each of the 4 "states" that the region could be in (think of it as "growing" from top to bottom).
 * To avoid ambiguity in the DP, start with upper pyramid, and only switch once it HAS to switch. So, upper->right when
 * left boundary moves to the right, right->bottom when right boundary moves to the left (similar for left slide).
 * The transitions take some care to get right. Once they're there, use 2D prefix sums to make it run fast enough.
 * Use 1D prefix sums to quickly tell if a region has all grass cells.
 * 
 * Runtime: O(8 * N^3)
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 150;
const ll MOD = 1e9+7;

int N;
int answer;
int gPre[MAXN][MAXN];
bool G[MAXN][MAXN];

inline bool isGrass(int i, int a, int b) {
    return (gPre[i][b] - (a == 0 ? 0 : gPre[i][a-1])) == 0;
}

inline void plusMod(int& a, ll b) {
    a = (a+b) % MOD;
}

// Upper pyramid
int U[MAXN][MAXN][MAXN];
ll preU[MAXN][MAXN][MAXN];
// Right slide
int R[MAXN][MAXN][MAXN];
ll preR[MAXN][MAXN][MAXN];
// Left slide
int L[MAXN][MAXN][MAXN];
ll preL[MAXN][MAXN][MAXN];
// Bottom pyramid
int B[MAXN][MAXN][MAXN];
ll preB[MAXN][MAXN][MAXN];

// BELOW ARE NOT IN MOD RANGE

ll getPrefixU(int i, int a1, int a2, int b1, int b2) {
    if (a1 > a2 || b1 > b2) return 0;
    ll res = preU[i][a2][b2] - (a1 == 0 ? 0 : preU[i][a1-1][b2]) - (b1 == 0 ? 0 : preU[i][a2][b1-1]) + (a1 == 0 || b1 == 0 ? 0 : preU[i][a1-1][b1-1]);
    res = (res % MOD) + MOD;
    return res;
}

ll getPrefixR(int i, int a1, int a2, int b1, int b2) {
    if (a1 > a2 || b1 > b2) return 0;
    ll res = preR[i][a2][b2] - (a1 == 0 ? 0 : preR[i][a1-1][b2]) - (b1 == 0 ? 0 : preR[i][a2][b1-1]) + (a1 == 0 || b1 == 0 ? 0 : preR[i][a1-1][b1-1]);
    res = (res % MOD) + MOD;
    return res;
}

ll getPrefixL(int i, int a1, int a2, int b1, int b2) {
    if (a1 > a2 || b1 > b2) return 0;
    ll res = preL[i][a2][b2] - (a1 == 0 ? 0 : preL[i][a1-1][b2]) - (b1 == 0 ? 0 : preL[i][a2][b1-1]) + (a1 == 0 || b1 == 0 ? 0 : preL[i][a1-1][b1-1]);
    res = (res % MOD) + MOD;
    return res;
}

ll getPrefixB(int i, int a1, int a2, int b1, int b2) {
    if (a1 > a2 || b1 > b2) return 0;
    ll res = preB[i][a2][b2] - (a1 == 0 ? 0 : preB[i][a1-1][b2]) - (b1 == 0 ? 0 : preB[i][a2][b1-1]) + (a1 == 0 || b1 == 0 ? 0 : preB[i][a1-1][b1-1]);
    res = (res % MOD) + MOD;
    return res;
}

void dpUpper(int i, int a, int b) {
    plusMod(U[i][a][b], getPrefixU(i-1, a, b, a, b));
    // for (int c = a; c <= b; c++) {
    //     for (int d = c; d <= b; d++) {
    //         plusMod(U[i][a][b], U[i-1][c][d]);
    //     }
    // }
}

void dpRight(int i, int a, int b) {
    // Transfer from upper pyramid *
    plusMod(R[i][a][b], getPrefixU(i-1, 0, a-1, a, b));
    // for (int c = 0; c < a; c++) {
    //     for (int d = a; d <= b; d++) {
    //         plusMod(R[i][a][b], U[i-1][c][d]);
    //     }
    // }
    plusMod(R[i][a][b], getPrefixR(i-1, 0, a, a, b));
    // for (int c = 0; c <= a; c++) {
    //     for (int d = a; d <= b; d++) {
    //         plusMod(R[i][a][b], R[i-1][c][d]);
    //     }
    // }
}

void dpLeft(int i, int a, int b) {
    // Transfer from upper pyramid *
    plusMod(L[i][a][b], getPrefixU(i-1, a, b, b+1, N-1));
    // for (int c = a; c <= b; c++) {
    //     for (int d = b+1; d <= N-1; d++) {
    //         plusMod(L[i][a][b], U[i-1][c][d]);
    //     }
    // }
    plusMod(L[i][a][b], getPrefixL(i-1, a, b, b, N-1));
    // for (int c = a; c <= b; c++) {
    //     for (int d = b; d <= N-1; d++) {
    //         plusMod(L[i][a][b], L[i-1][c][d]);
    //     }
    // }
}

void dpBottom(int i, int a, int b) {
    // Transfer from upper pyramid *
    plusMod(B[i][a][b], getPrefixU(i-1, 0, a-1, b+1, N-1));
    // for (int c = 0; c < a; c++) {
    //     for (int d = b+1; d <= N-1; d++) {
    //         plusMod(B[i][a][b], U[i-1][c][d]);
    //     }
    // }
    // Transfer from right slide *
    plusMod(B[i][a][b], getPrefixR(i-1, 0, a, b+1, N-1));
    // for (int c = 0; c <= a; c++) {
    //     for (int d = b+1; d <= N-1; d++) {
    //         plusMod(B[i][a][b], R[i-1][c][d]);
    //     }
    // }
    // Transfer from left slide *
    plusMod(B[i][a][b], getPrefixL(i-1, 0, a-1, b, N-1));
    // for (int c = 0; c < a; c++) {
    //     for (int d = b; d <= N-1; d++) {
    //         plusMod(B[i][a][b], L[i-1][c][d]);
    //     }
    // }
    plusMod(B[i][a][b], getPrefixB(i-1, 0, a, b, N-1));
    // for (int c = 0; c <= a; c++) {
    //     for (int d = b; d <= N-1; d++) {
    //         plusMod(B[i][a][b], B[i-1][c][d]);
    //     }
    // }
}

void doDP() {
    answer = 0;
    rep(i, 0, N) {
        rep(a, 0, N) {
            rep(b, a, N) {
                if (!isGrass(i, a, b)) continue;
                U[i][a][b] = 1;
                if (i != 0) {
                    dpUpper(i, a, b);
                    dpRight(i, a, b);
                    dpLeft(i, a, b);
                    dpBottom(i, a, b);
                }
                plusMod(answer, U[i][a][b]);
                plusMod(answer, R[i][a][b]);
                plusMod(answer, L[i][a][b]);
                plusMod(answer, B[i][a][b]);
            }
        }
        // Prefix sums
        rep(a, 0, N) {
            rep(b, 0, N) {
                preU[i][a][b] = U[i][a][b] + (a == 0 ? 0 : preU[i][a-1][b]) + (b == 0 ? 0 : preU[i][a][b-1]) - (a == 0 || b == 0 ? 0 : preU[i][a-1][b-1]);
                preR[i][a][b] = R[i][a][b] + (a == 0 ? 0 : preR[i][a-1][b]) + (b == 0 ? 0 : preR[i][a][b-1]) - (a == 0 || b == 0 ? 0 : preR[i][a-1][b-1]);
                preL[i][a][b] = L[i][a][b] + (a == 0 ? 0 : preL[i][a-1][b]) + (b == 0 ? 0 : preL[i][a][b-1]) - (a == 0 || b == 0 ? 0 : preL[i][a-1][b-1]);
                preB[i][a][b] = B[i][a][b] + (a == 0 ? 0 : preB[i][a-1][b]) + (b == 0 ? 0 : preB[i][a][b-1]) - (a == 0 || b == 0 ? 0 : preB[i][a-1][b-1]);
            }
        }
    }
    cout << answer << '\n';
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        string S; cin >> S;
        rep(j, 0, N) {
            G[i][j] = !(S[j] == 'G');
            gPre[i][j] = (j == 0 ? 0 : gPre[i][j-1]) + G[i][j];
        }
    }
    doDP();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}