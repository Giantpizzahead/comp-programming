#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1000;

int N, M, si, sj;
char grid[MAXN][MAXN];
int visited[MAXN][MAXN];
int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};
char cs[] = {'D', 'R', 'U', 'L'};

queue<pair<int, int>> q;
int currLeft, nextLeft, currCost;

void solve() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < M; j++) {
            visited[i][j] = -1;
            grid[i][j] = str[j];
            if (str[j] == 'A') {
                grid[i][j] = '.';
                si = i;
                sj = j;
            }
        }
    }

    q.emplace(si, sj);
    visited[si][sj] = 5;
    currLeft++;
    while (!q.empty()) {
        auto ptr = q.front();
        int i = ptr.first, j = ptr.second;
        q.pop();
        if (currLeft == 0) {
            currLeft = nextLeft;
            nextLeft = 0;
            currCost++;
        }
        currLeft--;

        if (grid[i][j] == 'B') {
            // Answer found
            cout << "YES\n";
            cout << currCost << "\n";
            string str;
            while (visited[i][j] != 5) {
                int d = visited[i][j];
                str += cs[d];
                i -= ci[d];
                j -= cj[d];
            }
            reverse(str.begin(), str.end());
            cout << str << '\n';
            return;
        }

        for (int d = 0; d < 4; d++) {
            int ni = i + ci[d], nj = j + cj[d];
            if (ni < 0 || nj < 0 || ni >= N || nj >= M || grid[ni][nj] == '#' || visited[ni][nj] != -1) continue;
            q.emplace(ni, nj);
            visited[ni][nj] = d;
            nextLeft++;
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}