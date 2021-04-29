#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 151;
const ll MOD = 1e9+7;

int N;
ll answer;
int gPre[MAXN][MAXN];
bool G[MAXN][MAXN];

inline bool isGrass(int i, int a, int b) {
    return (gPre[i][b] - (a == 0 ? 0 : gPre[i][a-1])) == 0;
}

inline void plusMod(ll& a, ll b) {
    a = (a+b) % MOD;
}

// Upper pyramid
ll U[MAXN][MAXN][MAXN], preU[MAXN][MAXN][MAXN];
// Right slide
ll R[MAXN][MAXN][MAXN], preR[MAXN][MAXN][MAXN];
// Left slide
ll L[MAXN][MAXN][MAXN], preL[MAXN][MAXN][MAXN];
// Bottom pyramid
ll B[MAXN][MAXN][MAXN], preB[MAXN][MAXN][MAXN];

// BELOW ARE NOT IN MOD RANGE

ll getPrefixU(int i, int a1, int a2, int b1, int b2) {
    ll res = preU[i][a2][b2] - (a1 == 0 ? 0 : preU[i][a1-1][b2]) - (b1 == 0 ? 0 : preU[i][a2][b1-1]) + (a1 == 0 || b1 == 0 ? 0 : preU[i][a1-1][b1-1]);
    res = (res % MOD) + MOD;
    return res;
}

ll getPrefixR(int i, int a1, int a2, int b1, int b2) {
    ll res = preR[i][a2][b2] - (a1 == 0 ? 0 : preR[i][a1-1][b2]) - (b1 == 0 ? 0 : preR[i][a2][b1-1]) + (a1 == 0 || b1 == 0 ? 0 : preR[i][a1-1][b1-1]);
    res = (res % MOD) + MOD;
    return res;
}

ll getPrefixL(int i, int a1, int a2, int b1, int b2) {
    ll res = preL[i][a2][b2] - (a1 == 0 ? 0 : preL[i][a1-1][b2]) - (b1 == 0 ? 0 : preL[i][a2][b1-1]) + (a1 == 0 || b1 == 0 ? 0 : preL[i][a1-1][b1-1]);
    res = (res % MOD) + MOD;
    return res;
}

ll getPrefixB(int i, int a1, int a2, int b1, int b2) {
    ll res = preB[i][a2][b2] - (a1 == 0 ? 0 : preB[i][a1-1][b2]) - (b1 == 0 ? 0 : preB[i][a2][b1-1]) + (a1 == 0 || b1 == 0 ? 0 : preB[i][a1-1][b1-1]);
    res = (res % MOD) + MOD;
    return res;
}

void dpUpper(int i, int a, int b) {
    for (int c = a; c <= b; c++) {
        for (int d = c; d <= b; d++) {
            plusMod(U[i][a][b], U[i-1][c][d]);
        }
    }
}

void dpRight(int i, int a, int b) {
    // Transfer from upper pyramid *
    for (int c = 0; c < a; c++) {
        for (int d = a; d <= b; d++) {
            plusMod(R[i][a][b], U[i-1][c][d]);
        }
    }
    for (int c = 0; c <= a; c++) {
        for (int d = a; d <= b; d++) {
            plusMod(R[i][a][b], R[i-1][c][d]);
        }
    }
}

void dpLeft(int i, int a, int b) {
    // Transfer from upper pyramid *
    for (int c = a; c <= b; c++) {
        for (int d = b+1; d <= N-1; d++) {
            plusMod(L[i][a][b], U[i-1][c][d]);
        }
    }
    for (int c = a; c <= b; c++) {
        for (int d = b; d <= N-1; d++) {
            plusMod(L[i][a][b], L[i-1][c][d]);
        }
    }
}

void dpBottom(int i, int a, int b) {
    // Transfer from upper pyramid *
    for (int c = 0; c < a; c++) {
        for (int d = b+1; d <= N-1; d++) {
            plusMod(B[i][a][b], U[i-1][c][d]);
        }
    }
    // Transfer from right slide ?
    for (int c = 0; c <= a; c++) {
        for (int d = b+1; d <= N-1; d++) {
            plusMod(B[i][a][b], R[i-1][c][d]);
        }
    }
    // Transfer from left slide ?
    for (int c = 0; c < a; c++) {
        for (int d = b; d <= N-1; d++) {
            plusMod(B[i][a][b], L[i-1][c][d]);
        }
    }
    for (int c = 0; c <= a; c++) {
        for (int d = b; d <= N-1; d++) {
            plusMod(B[i][a][b], B[i-1][c][d]);
        }
    }
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