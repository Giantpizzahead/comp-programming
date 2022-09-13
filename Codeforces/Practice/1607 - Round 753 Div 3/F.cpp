/*
https://codeforces.com/contest/1607/problem/F

Solution: Standard DFS with cycles. Record the length of a cycle when one is found to avoid dfs-ing it twice.
Runtime: O(NM)
Memory: O(NM), needed to be optimized a lot to get AC
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 2e3+5;

int N, M;
int D[MAXN][MAXN];
int C[MAXN][MAXN];
char A[MAXN][MAXN];
int currT;

int dfs(int i, int j) {
    D[i][j] = -(currT++);
    int ni = i, nj = j;
    if (A[i][j] == 'U') ni--;
    else if (A[i][j] == 'D') ni++;
    else if (A[i][j] == 'L') nj--;
    else nj++;
    if (ni < 0 || ni >= N || nj < 0 || nj >= M) {
        // Out of bounds
        D[i][j] = 1;
        return -1;
    } else if (D[ni][nj] == 0) {
        // Unvisited
        int res = dfs(ni, nj);
        if (res != -1 && res <= -D[i][j]) D[i][j] = D[ni][nj];  // In cycle
        else D[i][j] = D[ni][nj] + 1;
        return res;
    } else if (D[ni][nj] > 0) {
        // Seen before
        D[i][j] = D[ni][nj] + 1;
        return -1;
    } else {
        // Visited before in this dfs; find cycle length
        int cycleLen = currT - (-D[ni][nj]);
        D[i][j] = cycleLen;
        return -D[ni][nj];
    }
}

void solve() {
    cin >> N >> M;
    currT = 1;
    rep(i, 0, N) rep(j, 0, M) {
        D[i][j] = 0;
        C[i][j] = 0;
    }
    string S;
    rep(i, 0, N) {
        cin >> S;
        rep(j, 0, M) A[i][j] = S[j];
    }
    int ar = 0, ac = 0, ad = -1;
    rep(i, 0, N) rep(j, 0, M) {
        if (D[i][j] != 0) continue;
        dfs(i, j);
        if (D[i][j] > ad) ar = i, ac = j, ad = D[i][j];
    }
    cout << ar+1 << " " << ac+1 << " " << ad << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}