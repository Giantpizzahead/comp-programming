#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 32;

int N, M, E, spx, spy, scx, scy, ex, ey;
char grid[MAXN][MAXN];
bool visited[MAXN][MAXN][MAXN][MAXN];
int cx[] = {1, 0, -1, 0, 0}, cy[] = {0, 1, 0, -1, 0};

struct State {
    int px, py, cx, cy;
    State(int px, int py, int cx, int cy) : px(px), py(py), cx(cx), cy(cy) {}
};

queue<State> q;
int currLeft, nextLeft, currM;

void solve() {
    cin >> N >> M >> E;
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < M; j++) {
            grid[i][j] = str[j];
            if (grid[i][j] == 'P') {
                spx = i;
                spy = j;
                grid[i][j] = '.';
            } else if (grid[i][j] == 'C') {
                scx = i;
                scy = j;
                grid[i][j] = '.';
            } else if (grid[i][j] == 'E') {
                ex = i;
                ey = j;
                grid[i][j] = '.';
            }
        }
    }
    visited[spx][spy][scx][scy] = true;
    q.emplace(spx, spy, scx, scy);
    currLeft++;
    while (!q.empty()) {
        auto s = q.front();
        // cout << s.px << " " << s.py << " " << s.cx << " " << s.cy << endl;
        if (currLeft == 0) {
            currLeft = nextLeft;
            nextLeft = 0;
            currM++;
            // cout << currLeft << endl;
        }
        currLeft--;
        // Check exit
        if (s.px == ex && s.py == ey) {
            cout << currM << endl;
            return;
        }
        for (int i = 0; i < 5; i++) {
            int nx = s.px;
            int ny = s.py;
            // Move the creeper
            int ncx = s.cx;
            int ncy = s.cy;
            int horDist = abs(nx - ncx);
            if (nx < ncx && grid[ncx-1][ncy] != '.') horDist = 0;
            if (nx > ncx && grid[ncx+1][ncy] != '.') horDist = 0;
            // if (nx + 1 == ncx && cx[i] == 1) horDist = 0;
            // if (nx - 1 == ncx && cx[i] == -1) horDist = 0;
            int vertDist = abs(ny - ncy);
            if (ny < ncy && grid[ncx][ncy-1] != '.') vertDist = 0;
            if (ny > ncy && grid[ncx][ncy+1] != '.') vertDist = 0;
            // if (ny + 1 == ncy && cy[i] == 1) vertDist = 0;
            // if (ny - 1 == ncy && cy[i] == -1) vertDist = 0;
            if (vertDist >= horDist && vertDist != 0) {
                if (ny < ncy) ncy--;
                else ncy++;
            } else if (horDist > vertDist && horDist != 0) {
                if (nx < ncx) ncx--;
                else ncx++;
            }
            nx += cx[i];
            ny += cy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= M || grid[nx][ny] != '.') continue;
            // New state
            // Check creeper
            int dist = max(abs(ncx - nx), abs(ncy - ny));
            if (dist <= E) continue;
            if (visited[nx][ny][ncx][ncy]) continue;
            q.emplace(nx, ny, ncx, ncy);
            nextLeft++;
            visited[nx][ny][ncx][ncy] = true;
        }
        q.pop();
        // cout << q.size() << endl;
    }
    cout << "you're toast" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}