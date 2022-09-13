/*
https://codeforces.com/contest/1613/problem/E

Solution: Simple DFS, spreading to a cell once you're sure the robot can reach the lab.
Runtime: O(NM)
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

int N, M;
vector<vector<char>> A;
vector<vector<int>> numOpen;
queue<pii> q;

int ci[] = {0, 1, 0, -1}, cj[] = {1, 0, -1, 0};

inline bool inBounds(int i, int j) {
    return i >= 0 && i < N && j >= 0 && j < M;
}

void solve() {
    cin >> N >> M;
    A.resize(N, vector<char>(M));
    numOpen.resize(N, vector<int>(M));
    rep(i, 0, N) {
        string s; cin >> s;
        rep(j, 0, M) A[i][j] = s[j];
    }
    rep(i, 0, N) rep(j, 0, M) {
        if (A[i][j] == 'L') q.push({i, j});
        rep(d, 0, 4) {
            int ni = i + ci[d], nj = j + cj[d];
            if (inBounds(ni, nj) && A[ni][nj] != '#') numOpen[i][j]++;
        }
    }

    while (!q.empty()) {
        pii c = q.front(); q.pop();
        rep(d, 0, 4) {
            int ni = c.first + ci[d], nj = c.second + cj[d];
            if (!inBounds(ni, nj) || A[ni][nj] != '.') continue;
            else if (--numOpen[ni][nj] <= 1) {
                A[ni][nj] = '+';
                q.push({ni, nj});
            }
        }
    }

    rep(i, 0, N) {
        rep(j, 0, M) cout << A[i][j];
        cout << '\n';
    }
    A.clear();
    numOpen.clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}