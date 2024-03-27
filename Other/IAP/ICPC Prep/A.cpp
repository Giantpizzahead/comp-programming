/*
Solution: Get a system of equations from the board.
Solve this system efficiently using elimination, and use the result to determine mine
See KACTL template for it!
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 31;

typedef bitset<480> bs;
typedef vector<int> vi;

map<int, int> forced;

int solveLinear(vector<bs>& A, vi& b, bs& x, int m) {
    // Gaussian elimination
    int n = sz(A), rank = 0, br;
    assert(m <= sz(x));
    vi col(m); iota(all(col), 0);
    rep(i, 0, n) {
        for (br=i; br<n; ++br) if (A[br].any()) break;
        if (br == n) {
            rep(j, i, n) if (b[j]) return -1;
            break;
        }
        int bc = (int) A[br]._Find_next(i-1);
        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        rep(j, 0, n) if (A[j][i] != A[j][bc]) {
            A[j].flip(i); A[j].flip(bc);
        }
        rep(j, i+1, n) if (A[j][i]) {
            b[j] ^= b[i];
            A[j] ^= A[i];
        }
        rank++;
    }

    x = bs();
    for (int i = rank; i--;) {
        if (!b[i]) {
            x[col[i]] = 0;
            forced[col[i]] = 0;
        } else {
            x[col[i]] = 1;
            forced[col[i]] = 1;
            rep(j, 0, i) b[j] ^= A[j][i];
        }
    }
    return rank;
}

int R, C;
char grid[MAXN][MAXN];
vector<bs> A;
vector<int> B;

int ci[] = {1, 1, 0, -1, -1, -1, 0, 1};
int cj[] = {0, 1, 1, 1, 0, -1, -1, -1};

int getID(int i, int j) {
    return i*C+j;
}

void solve() {
    cin >> C >> R;
    rep(i, 0, R) {
        string s; cin >> s;
        rep(j, 0, C) {
            grid[i][j] = s[j];
        }
    }

    // Setup matrix
    rep(i, 0, R) {
        rep(j, 0, C) {
            if (grid[i][j] < '0' || grid[i][j] > '9') continue;
            // Add equation
            B.push_back(grid[i][j] - '0');
            bs currRow;
            rep(d, 0, 8) {
                int ni = i + ci[d], nj = j + cj[d];
                if (ni < 0 || nj < 0 || ni >= R || nj >= C) continue;
                if (grid[ni][nj] != '.') continue;
                currRow.flip(getID(ni, nj));
            }
            A.push_back(currRow);
        }
    }

    rep(i, 0, sz(B)) {
        if (B[i] == 0) continue;
        rep(j, 0, R*C) cout << A[i][j] << " ";
        cout << " = " << B[i] << endl;
    }

    bs x;
    int rank = solveLinear(A, B, x, R*C);
    cout << "rank: " << rank << endl;
    cout << "x: ";
    rep(i, 0, R) rep(j, 0, C) {
        if (forced.find(i*C+j) != forced.end()) {
            grid[i][j] = (forced[i*C+j] == 0 ? ' ' : '*');
        }
        if (x[i*C+j]) cout << "(" << i << "," << j << ") ";
    }
    cout << endl;

    rep(i, 0, R) {
        rep(j, 0, C) cout << grid[i][j];
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
