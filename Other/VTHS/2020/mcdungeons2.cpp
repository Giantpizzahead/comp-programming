#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 31;

int N, M, E, spi, spj, sci, scj;
char grid[MAXN][MAXN];
bool visited[MAXN][MAXN][MAXN][MAXN];

struct State {
    int pi, pj, ci, cj;
    State(int a, int b, int c, int d) : pi(a), pj(b), ci(c), cj(d) {}
};

int chgi[] = {1, 0, -1, 0, 0}, chgj[] = {0, 1, 0, -1, 0};

queue<State> q;
int currLeft = 0, nextLeft = 0, currMoves = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> E;
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < M; j++) {
            grid[i][j] = str[j];
            if (grid[i][j] == 'P') {
                spi = i;
                spj = j;
                grid[i][j] = '.';
            } else if (grid[i][j] == 'C') {
                sci = i;
                scj = j;
                grid[i][j] = '.';
            }
        }
    }

    q.emplace(spi, spj, sci, scj);
    currLeft++;
    while (!q.empty()) {
        auto ptr = q.front();
        int pi = ptr.pi, pj = ptr.pj, ci = ptr.ci, cj = ptr.cj;
        q.pop();
        if (currLeft == 0) {
            currLeft = nextLeft;
            nextLeft = 0;
            currMoves++;
        }
        currLeft--;

        // Exit check
        if (grid[pi][pj] == 'E') {
            cout << currMoves << endl;
            return 0;
        }

        // Creeper move
        int iDist = abs(pi-ci), jDist = abs(pj-cj);
        if (pi < ci && grid[ci-1][cj] == 'X') iDist = 0;
        if (pi > ci && grid[ci+1][cj] == 'X') iDist = 0;
        if (pj < cj && grid[ci][cj-1] == 'X') jDist = 0;
        if (pj > cj && grid[ci][cj+1] == 'X') jDist = 0;
        if (iDist >= jDist && iDist != 0) {
            if (pi < ci) ci--;
            else ci++;
        } else if (jDist > iDist && jDist != 0) {
            if (pj < cj) cj--;
            else cj++;
        }

        // Player move
        for (int d = 0; d < 5; d++) {
            int ni = pi + chgi[d], nj = pj + chgj[d];
            if (ni < 0 || ni >= N || nj < 0 || nj >= M || grid[ni][nj] == 'X') continue;
            if (visited[ni][nj][ci][cj]) continue;
            visited[ni][nj][ci][cj] = true;

            // Creeper check
            int dist = max(abs(ni-ci), abs(nj-cj));
            if (dist <= E) continue;  // BOOM
            q.emplace(ni, nj, ci, cj);
            nextLeft++;
        }
    }

    cout << "you're toast" << endl;
    return 0;
}