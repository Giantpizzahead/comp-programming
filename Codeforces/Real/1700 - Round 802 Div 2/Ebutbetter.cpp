#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

int N, M, currMax;
vector<vector<int>> A;
vector<vector<bool>> isMax;

struct State {
    int i, j, v;
    bool operator<(const State& o) const {
        return v > o.v;
    }
};
priority_queue<State> pq;
int ci[] = {1, 0, -1, 0, 0}, cj[] = {0, 1, 0, -1, 0};

inline bool inBounds(int i, int j) {
    return i >= 0 && j >= 0 && i < N && j < M;
}

void updateIsMax(int i, int j) {
    if (isMax[i][j]) {
        isMax[i][j] = false;
        currMax--;
    }
    bool allGreater = true;
    rep(d, 0, 4) {
        int ni = i + ci[d], nj = j + cj[d];
        if (!inBounds(ni, nj)) continue;
        if (A[ni][nj] < A[i][j]) {
            allGreater = false;
            break;
        }
    }
    if (allGreater && A[i][j] != 1) {
        isMax[i][j] = true;
        currMax++;
    }
}

bool trySwap(int i1, int j1, int i2, int j2) {
    swap(A[i1][j1], A[i2][j2]);
    int ni, nj;
    rep(d, 0, 5) {
        ni = i1 + ci[d], nj = j1 + cj[d];
        if (inBounds(ni, nj)) updateIsMax(ni, nj);
        ni = i2 + ci[d], nj = j2 + cj[d];
        if (inBounds(ni, nj)) updateIsMax(ni, nj);
    }
    bool res = (currMax == 0);
    // Backtrack
    swap(A[i1][j1], A[i2][j2]);
    rep(d, 0, 5) {
        ni = i1 + ci[d], nj = j1 + cj[d];
        if (inBounds(ni, nj)) updateIsMax(ni, nj);
        ni = i2 + ci[d], nj = j2 + cj[d];
        if (inBounds(ni, nj)) updateIsMax(ni, nj);
    }
    return res;
}

void solve() {
    cin >> N >> M;
    currMax = 0;
    A.resize(N, vector<int>(M));
    isMax.resize(N, vector<bool>(M));
    rep(i, 0, N) {
        rep(j, 0, M) {
            cin >> A[i][j];
        }
    }
    rep(i, 0, N) rep(j, 0, M) updateIsMax(i, j);
    if (currMax == 0) cout << "0\n";
    else {
        // Find the first maximum, and try swapping everything
        int maxI, maxJ;
        rep(i, 0, N) rep(j, 0, M) {
            if (isMax[i][j]) {
                maxI = i, maxJ = j;
                break;
            }
        }
        int numWays = 0;
        rep(d, 0, 5) {
            int si = maxI + ci[d], sj = maxJ + cj[d];
            if (!inBounds(si, sj)) continue;
            // Try swapping this with everything
            rep(i, 0, N) rep(j, 0, M) {
                if (si == i && sj == j) continue;
                if (d != 4 && i == maxI && j == maxJ) continue;  // Avoid overcounting
                if (trySwap(si, sj, i, j)) numWays++;
            }
        }
        if (numWays == 0) cout << "2\n";
        else cout << "1 " << numWays << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}