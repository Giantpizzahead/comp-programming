#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;

const int MAXN = 1000;

int N, M;
bool G[MAXN][MAXN], vis[MAXN][MAXN];

int comps = 0;
const int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};
void dfs(int i, int j) {
    vis[i][j] = true;
    rep(d, 0, 4) {
        int ni = i + ci[d], nj = j + cj[d];
        if (ni < 0 || ni >= N || nj < 0 || nj >= M || vis[ni][nj] || !G[ni][nj]) continue;
        dfs(ni, nj);
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        string S; cin >> S;
        rep(j, 0, M) {
            G[i][j] = (S[j] == '#');
        }
    }
    bool emptyRow = false;
    rep(i, 0, N) {
        int state = 0;
        rep(j, 0, M) {
            if (G[i][j]) {
                if (state == 0) state = 1;
                else if (state == 2) {
                    cout << "-1\n";
                    return;
                }
            } else {
                if (state == 1) state = 2;
            }
        }
        if (state == 0) emptyRow = true;
    }
    bool emptyCol = false;
    rep(j, 0, M) {
        int state = 0;
        rep(i, 0, N) {
            if (G[i][j]) {
                if (state == 0) state = 1;
                else if (state == 2) {
                    cout << "-1\n";
                    return;
                }
            } else {
                if (state == 1) state = 2;
            }
        }
        if (state == 0) emptyCol = true;
    }
    if (emptyRow != emptyCol) {
        cout << "-1\n";
        return;
    }
    // Answer is just number of components
    rep(i, 0, N) {
        rep(j, 0, M) {
            if (G[i][j] && !vis[i][j]) {
                comps++;
                dfs(i, j);
            }
        }
    }
    cout << comps << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}