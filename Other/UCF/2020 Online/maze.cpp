#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 102;

int N, M;
int cx[] = {1, 0, -1, 0};
int cy[] = {0, 1, 0, -1};
char grid[MAXN][MAXN];
bool visited[MAXN][MAXN][10];

struct State {
    int i, j, h;
    State(int ii, int jj, int hh) : i(ii), j(jj), h(hh) {}
};

deque<State> Q;

inline bool inBounds(int i, int j) {
    return i >= 0 && i < N && j >= 0 && j < M;
}

void solve() {
    cin >> N >> M;
    Q.clear();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int h = 0; h < 10; h++) {
                visited[i][j][h] = false;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < M; j++) {
            grid[i][j] = str[j];
            if ((i == 0 || j == 0 || i == N-1 || j == M-1) && grid[i][j] == '1') {
                Q.emplace_back(i, j, 1);
                visited[i][j][1] = true;
            }
        }
    }
    
    while (!Q.empty()) {
        auto p = Q.front();
        int i = p.i, j = p.j, h = p.h;
        Q.pop_front();
        // cout << i << " " << j << " " << h << endl;
        // Gas check
        bool isValid = true;
        for (int d = 0; d < 4; d++) {
            int ni = i+cx[d], nj = j+cy[d];
            if (inBounds(ni, nj) && grid[ni][nj] == 'G') {
                // Cannot go here
                isValid = false;
                break;
            }
        }
        if (!isValid) continue;

        if (grid[i][j] == '*') {
            cout << "You've got this!\n";
            return;
        }

        for (int d = 0; d < 4; d++) {
            int ni = i+cx[d], nj = j+cy[d], nh = h;
            if (!inBounds(ni, nj)) continue;
            // Can we transfer here?
            bool canGo = false;
            if ((grid[ni][nj] >= '1' && grid[ni][nj] <= '9') || grid[ni][nj] == '*') {
                if (grid[ni][nj] == '*') nh = 9;
                else nh = grid[ni][nj] - '0';
                if (grid[i][j] == 'E') canGo = true;
                if (grid[i][j] == 'F' && nh > h) canGo = true;
                if (grid[i][j] == 'P' && nh < h) canGo = true;
                if (grid[i][j] >= '1' && grid[i][j] <= '9' && abs(h-nh) <= 1) canGo = true;
            } else canGo = true;
            if (!canGo || visited[ni][nj][nh]) continue;
            // Transfer here
            Q.emplace_back(ni, nj, nh);
            visited[ni][nj][nh] = true;
        }
    }

    cout << "Find another way\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}