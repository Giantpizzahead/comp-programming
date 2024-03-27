/*
Solution: Simulation.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 31;

int N, M;
char grid[MAXN][MAXN];
int currMines[MAXN][MAXN];

int ci[] = {1, 1, 0, -1, -1, -1, 0, 1};
int cj[] = {0, 1, 1, 1, 0, -1, -1, -1};

int K;
struct Loc {
    int i, j;
    bool operator<(const Loc& l) const {
        return make_pair(i, j) < make_pair(l.i, l.j);
    }
};
set<Loc> setLocs;
vector<Loc> locs;
int cntValid;
vector<int> cntMine;

// See if the board is valid
bool tryCombo() {
    rep(i, 0, N) rep(j, 0, M) {
        if (grid[i][j] < '0' || grid[i][j] > '9') continue;
        int targetCnt = grid[i][j] - '0';
        // rep(d, 0, 8) {
        //     int ni = i + ci[d], nj = j + cj[d];
        //     if (ni < 0 || nj < 0 || ni >= N || nj >= M) continue;
        //     if (grid[ni][nj] == '*') targetCnt--;
        // }
        if (targetCnt != currMines[i][j]) return false;
    }
    return true;
}

void genCombos(int x) {
    if (x == K) {
        if (tryCombo()) {
            // Valid combo; record mine locations
            cntValid++;
            rep(i, 0, K) {
                if (grid[locs[i].i][locs[i].j] == '*') cntMine[i]++;
            }
        }
        return;
    }
    Loc& l = locs[x];
    grid[l.i][l.j] = '*';
    bool valid = true;
    rep(d, 0, 8) {
        int ni = l.i + ci[d], nj = l.j + cj[d];
        if (ni < 0 || nj < 0 || ni >= N || nj >= M) continue;
        currMines[ni][nj]++;
        if (grid[ni][nj] >= '0' && grid[ni][nj] <= '9' && grid[ni][nj]-'0' < currMines[ni][nj]) valid = false;
    }
    if (valid) genCombos(x+1);
    grid[l.i][l.j] = '.';
    rep(d, 0, 8) {
        int ni = l.i + ci[d], nj = l.j + cj[d];
        if (ni < 0 || nj < 0 || ni >= N || nj >= M) continue;
        currMines[ni][nj]--;
    }
    genCombos(x+1);
}

void solve() {
    cin >> M >> N;
    rep(i, 0, N) {
        string s; cin >> s;
        rep(j, 0, M) grid[i][j] = s[j];
    }

    // Find cells to check
    rep(i, 0, N) rep(j, 0, M) {
        if (grid[i][j] != '.') continue;
        rep(d, 0, 8) {
            int ni = i + ci[d], nj = j + cj[d];
            if (ni < 0 || nj < 0 || ni >= N || nj >= M) continue;
            if (grid[ni][nj] >= '0' && grid[ni][nj] <= '9') {
                // Next to a numeric cell
                setLocs.insert({i, j});
                break;
            }
        }
    }
    for (auto& l : setLocs) locs.push_back(l);

    // Generate all possible combos
    K = sz(locs);
    cntValid = 0;
    cntMine.resize(K);
    // assert(K < 14);
    genCombos(0);

    // Find set locations
    rep(i, 0, K) {
        if (cntMine[i] == cntValid) grid[locs[i].i][locs[i].j] = '*';
        else if (cntMine[i] == 0) grid[locs[i].i][locs[i].j] = ' ';
    }

    // Output the grid
    rep(i, 0, N) {
        rep(j, 0, M) cout << grid[i][j];
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
