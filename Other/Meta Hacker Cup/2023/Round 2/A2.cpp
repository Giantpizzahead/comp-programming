/*
Solution: BFS each group of white stones. Mark unique location that needs to be blocked, if there.
Take max of all.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 3005;

int R, C;
char A[MAXN][MAXN];
bool vis[MAXN][MAXN];
int numCapture[MAXN][MAXN];

int currCnt;
set<pair<int, int>> openLocs;

int ci[] = {1, 0, -1, 0};
int cj[] = {0, 1, 0, -1};

queue<pair<int, int>> q;

void bfs(int i, int j) {
    vis[i][j] = true;
    currCnt++;
    rep(d, 0, 4) {
        int ni = i + ci[d], nj = j + cj[d];
        if (ni < 0 || nj < 0 || ni >= R || nj >= C) continue;
        if (vis[ni][nj] || A[ni][nj] == 'B') continue;
        else if (A[ni][nj] == 'W') {
            vis[ni][nj] = true;
            q.push({ni, nj});
        } else {
            // Open square
            openLocs.insert({ni, nj});
        }
    }
}

void solve() {
    cin >> R >> C;
    rep(i, 0, R) {
        string s; cin >> s;
        rep(j, 0, C) A[i][j] = s[j];
    }

    // BFS through each group
    rep(i, 0, R) rep(j, 0, C) {
        vis[i][j] = false;
        numCapture[i][j] = 0;
    }
    rep(i, 0, R) rep(j, 0, C) {
        if (A[i][j] == 'W' && !vis[i][j]) {
            currCnt = 0;
            openLocs.clear();
            q.push({i, j});
            while (!q.empty()) {
                auto p = q.front(); q.pop();
                bfs(p.first, p.second);
            }
            // cerr << "group at " << i << " " << j << " = " << sz(openLocs) << " " << currCnt << endl;
            if (sz(openLocs) == 1) {
                numCapture[openLocs.begin()->first][openLocs.begin()->second] += currCnt;
            }
        }
    }

    int ans = 0;
    rep(i, 0, R) rep(j, 0, C) ans = max(numCapture[i][j], ans);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // For HackerCup
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
