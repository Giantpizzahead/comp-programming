#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 300;

int N, M;
vector<int> startGrid[MAXN][MAXN], endGrid[MAXN][MAXN];
deque<int> grid[MAXN][MAXN];
struct Move {
    int x1, y1, x2, y2;
};
vector<Move> moves;

void move(int x1, int y1, int x2, int y2) {
    // cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    assert(x1 >= 0 && x2 < N && y1 >= 0 && y1 < M);
    assert(x1 != x2 || y1 != y2);
    assert(x1 == x2 || y1 == y2);
    assert(!grid[x1][y1].empty());
    grid[x2][y2].push_front(grid[x1][y1].back());
    grid[x1][y1].pop_back();
    moves.push_back({x1+1, y1+1, x2+1, y2+1});
}

void printGrid() {
    rep(i, 0, N) {
        rep(j, 0, M) {
            for (int k : grid[i][j]) cout << k;
            if (grid[i][j].empty()) cout << '_';
            cout << ' ';
        }
        cout << endl;
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        rep(j, 0, M) {
            string str; cin >> str;
            rep(k, 0, sz(str)) {
                startGrid[i][j].push_back(str[k] - '0');
                grid[i][j].push_back(str[k] - '0');
            }
        }
    }
    rep(i, 0, N) {
        rep(j, 0, M) {
            string str; cin >> str;
            rep(k, 0, sz(str)) {
                endGrid[i][j].push_back(str[k] - '0');
            }
        }
    }

    // Move 0s to top-left, 1s to bot-right
    for (int i = 0; i < N; i++) {
        for (int j = M-1; j >= 0; j--) {
            if (i == 0 && j == 0) {
                for (int k = 0; k < sz(startGrid[i][j]); k++) move(0, 0, N-1, 0);
                continue;
            } else if (i == N-1 && j == M-1) {
                for (int k = 0; k < sz(startGrid[i][j]); k++) move(N-1, M-1, N-1, 0);
                continue;
            }
            while (!grid[i][j].empty()) {
                int b = grid[i][j].back();
                if (b == 0) {
                    // Go to top left
                    if (j == 0) {
                        // On left column
                        move(i, 0, 0, 0);
                    } else {
                        move(i, j, i, 0);
                    }
                } else {
                    // Go to bot right
                    if (i == N-1) {
                        // On bot row
                        move(N-1, j, N-1, M-1);
                    } else {
                        move(i, j, N-1, j);
                    }
                }
            }
        }
    }
    // printGrid();

    // Fill top-right square
    rep(i, 0, N-1) {
        rep(j, 1, M) {
            for (int k = sz(endGrid[i][j])-1; k >= 0; k--) {
                if (endGrid[i][j][k] == 0) {
                    // Move 0 here
                    if (i != 0) move(0, 0, i, 0);
                    move(i, 0, i, j);
                } else {
                    // Move 1 here
                    if (j != M-1) move(N-1, M-1, N-1, j);
                    move(N-1, j, i, j);
                }
            }
        }
    }
    // printGrid();

    // Fill sides
    rep(i, 0, N-1) {
        for (int k = sz(endGrid[i][0])-1; k >= 0; k--) {
            if (endGrid[i][0][k] == 0) {
                move(0, 0, N-1, 0);
                move(N-1, 0, i, 0);
            } else {
                move(N-1, M-1, N-1, 0);
                move(N-1, 0, i, 0);
            }
        }
    }
    rep(j, 1, M) {
        for (int k = sz(endGrid[N-1][j])-1; k >= 0; k--) {
            if (endGrid[N-1][j][k] == 0) {
                move(0, 0, N-1, 0);
                move(N-1, 0, N-1, j);
            } else {
                move(N-1, M-1, N-1, 0);
                move(N-1, 0, N-1, j);
            }
        }
    }
    // printGrid();

    // Fill corner
    for (int k = sz(endGrid[N-1][0])-1; k >= 0; k--) {
        if (endGrid[N-1][0][k] == 0) {
            move(0, 0, N-1, 0);
        } else {
            move(N-1, M-1, N-1, 0);
        }
    }
    // printGrid();

    cout << moves.size() << '\n';
    for (Move& m : moves) cout << m.x1 << " " << m.y1 << " " << m.x2 << " " << m.y2 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}