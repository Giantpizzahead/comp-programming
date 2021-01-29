#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1000;

int N, M;
int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};
bool visited[MAXN][MAXN];
char grid[MAXN][MAXN];

void dfs(int i, int j) {
    visited[i][j] = true;
    for (int d = 0; d < 4; d++) {
        int ni = i+ci[d], nj = j+cj[d];
        if (ni < 0 || nj < 0 || ni >= N || nj >= M || grid[ni][nj] == '#' || visited[ni][nj]) continue;
        dfs(ni, nj);
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        string str;
        cin >> str;
        rep(j, 0, M) {
            grid[i][j] = str[j];
        }
    }
    int answer = 0;
    rep(i, 0, N) {
        rep(j, 0, M) {
            if (!visited[i][j] && grid[i][j] == '.') {
                answer++;
                dfs(i, j);
            }
        }
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}