#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 4;

int N, M;
int G[MAXN][MAXN];
int A[MAXN*MAXN];
bool used[MAXN*MAXN];

int cntBruteDiag1 = 0;
int cntBruteDiag2 = 0;
int cntBruteTopBot = 0;
int cntBruteLeftRight = 0;

void printAndExit(int s) {
    cout << s << '\n';
    rep(i, 0, N) {
        rep(j, 0, N) {
            cout << G[i][j] << " \n"[j==N-1];
        }
    }
    exit(0);
}

void bruteSmall(int i, int j) {
    if (i == N) {
        // Check for correct sums
        int s = 0;
        rep(k, 0, N) s += G[0][k];
        rep(k, 0, N) {
            int r = 0, c = 0;
            rep(l, 0, N) {
                r += G[k][l];
                c += G[l][k];
            }
            if (r != s || c != s) return;
        }
        int d1 = 0, d2 = 0;
        rep(k, 0, N) {
            d1 += G[k][k];
            d2 += G[N-1-k][k];
        }
        if (d1 != s || d2 != s) return;
        printAndExit(s);
    }
    rep(x, 0, M) {
        if (!used[x]) {
            G[i][j] = A[x];
            used[x] = true;
            if (j == N-1) bruteSmall(i+1, 0);
            else bruteSmall(i, j+1);
            used[x] = false;
        }
    }
}

bool usedD[MAXN*MAXN], usedO[MAXN*MAXN];
vector<int> D, O;
ll S;

void bruteLeftRight(int n) {
    if (n == 0) {
        // cntBruteLeftRight++;
        set<int> u;
        rep(k, 0, 8) {
            if (usedO[k] || u.count(O[k])) continue;
            usedO[k] = true;
            u.insert(O[k]);
            G[1][0] = O[k];
            // Fill G[2][0]
            int target = S - (G[0][0] + G[1][0] + G[3][0]);
            rep(l, 0, 8) {
                if (usedO[l] || O[l] != target) continue;
                usedO[l] = true;
                G[2][0] = O[l];
                bruteLeftRight(1);
                usedO[l] = false;
                break;
            }
            usedO[k] = false;
        }
    } else if (n == 1) {
        // Fill G[1][3]
        int target = S - (G[1][0] + G[1][1] + G[1][2]);
        rep(l, 0, 8) {
            if (usedO[l] || O[l] != target) continue;
            usedO[l] = true;
            G[1][3] = O[l];
            bruteLeftRight(2);
            usedO[l] = false;
            break;
        }
    } else if (n == 2) {
        // Fill G[2][3]
        int target = S - (G[2][0] + G[2][1] + G[2][2]);
        rep(l, 0, 8) {
            if (usedO[l] || O[l] != target) continue;
            usedO[l] = true;
            G[2][3] = O[l];
            printAndExit(S);
        }
    }
}

void bruteTopBot(int n) {
    // if (G[0][0] == 7 && G[1][1] == 13 && G[2][2] == 10 && G[3][3] == 4 &&
    //     G[3][0] == 9 && G[2][1] == 3 && G[1][2] == 8 && G[0][3] == 14) {
    //     debug << "correct into topbot " << n << endl;
    //     rep(l, 0, 8) if (!usedO[l]) debug << O[l] << ' ';
    //     debug << endl;
    // }
    if (n == 0) {
        // cntBruteTopBot++;
        set<int> u;
        rep(k, 0, 8) {
            if (usedO[k] || u.count(O[k])) continue;
            usedO[k] = true;
            u.insert(O[k]);
            G[0][1] = O[k];
            // Fill G[0][2]
            int target = S - (G[0][0] + G[0][1] + G[0][3]);
            rep(l, 0, 8) {
                if (usedO[l] || O[l] != target) continue;
                usedO[l] = true;
                G[0][2] = O[l];
                bruteTopBot(1);
                usedO[l] = false;
                break;
            }
            usedO[k] = false;
        }
    } else if (n == 1) {
        // Fill G[3][1]
        int target = S - (G[0][1] + G[1][1] + G[2][1]);
        rep(l, 0, 8) {
            if (usedO[l] || O[l] != target) continue;
            usedO[l] = true;
            G[3][1] = O[l];
            bruteTopBot(2);
            usedO[l] = false;
            break;
        }
    } else if (n == 2) {
        // Fill G[3][2]
        int target = S - (G[0][2] + G[1][2] + G[2][2]);
        rep(l, 0, 8) {
            if (usedO[l] || O[l] != target) continue;
            usedO[l] = true;
            G[3][2] = O[l];
            bruteLeftRight(0);
            usedO[l] = false;
            break;
        }
    }
}

void bruteDiag2(int n) {
    // if (n == 0) cntBruteDiag2++;
    set<int> u;
    rep(k, 0, 8) {
        if (usedD[k] || u.count(D[k])) continue;
        usedD[k] = true;
        u.insert(D[k]);
        if (n == 0) {
            G[3][0] = D[k];
            bruteDiag2(n+1);
        } else if (n == 1) {
            G[2][1] = D[k];
            bruteDiag2(n+1);
        } else if (n == 2) {
            // Fill G[0][3]
            G[1][2] = D[k];
            int target = S - (G[3][0] + G[2][1] + G[1][2]);
            rep(l, 0, 8) {
                if (usedD[l] || D[l] != target) continue;
                usedD[l] = true;
                G[0][3] = D[l];
                bruteTopBot(0);
                usedD[l] = false;
                break;
            }
        }
        usedD[k] = false;
    }
}

void bruteDiag1(int n) {
    // if (n == 0) cntBruteDiag1++;
    set<int> u;
    rep(k, 0, 8) {
        if (usedD[k] || u.count(D[k])) continue;
        usedD[k] = true;
        u.insert(D[k]);
        if (n == 0) {
            G[0][0] = D[k];
            bruteDiag1(n+1);
        } else if (n == 1) {
            G[1][1] = D[k];
            bruteDiag1(n+1);
        } else if (n == 2) {
            // Fill G[3][3]
            G[2][2] = D[k];
            int target = S - (G[0][0] + G[1][1] + G[2][2]);
            rep(l, 0, 8) {
                if (usedD[l] || D[l] != target) continue;
                usedD[l] = true;
                G[3][3] = D[l];
                bruteDiag2(0);
                usedD[l] = false;
                break;
            }
        }
        usedD[k] = false;
    }
}

void genDiags(int n) {
    if (n == 16) {
        if (sz(D) != 8) return;
        // Check sum
        S = 0;
        for (int x : D) S += 3 * x;
        for (int x : O) S += 2 * x;
        if (S % 10 != 0) return;
        S /= 10;
        // debug << "diag sum: " << S << '\n';
        // Use these as diagonals
        bruteDiag1(0);
    } else {
        D.push_back(A[n]);
        genDiags(n+1);
        D.pop_back();
        O.push_back(A[n]);
        genDiags(n+1);
        O.pop_back();
    }
}

void solve() {
    cin >> N;
    M = N*N;
    rep(i, 0, M) cin >> A[i];
    random_shuffle(A, A+M);
    if (N <= 3) {
        bruteSmall(0, 0);
    } else {
        genDiags(0);
        // debug << "diag1: " << cntBruteDiag1 << endl;
        // debug << "diag2: " << cntBruteDiag2 << endl;
        // debug << "topbot: " << cntBruteTopBot << endl;
        // debug << "leftright: " << cntBruteLeftRight << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(time(NULL));
    solve();
    return 0;
}