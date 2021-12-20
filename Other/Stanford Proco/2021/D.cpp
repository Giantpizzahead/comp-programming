#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 400, MAXS = 30;
const int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};

int N, M;
bool G[MAXN][MAXN];
int horPre[MAXN][MAXN], vertPre[MAXN][MAXN];
struct State {
    int i, j, d, s;
};
int cost[MAXN][MAXN][4][MAXS];

int getHash(int i, int j, int d, int s) {
    int h = i;
    h = 400 * h + j;
    h = 4 * h + d;
    h = 400 * h + s;
    return h;
}

void getState(int h, State& state) {
    state.s = h % 400; h /= 400;
    state.d = h % 4; h /= 4;
    state.j = h % 400; h /= 400;
    state.i = h;
}

queue<int> q;

bool validMove(int i, int j, int ni, int nj) {
    if (ni < 0 || ni >= N || nj < 0 || nj >= M) return false;
    else if (i == ni) {
        int j1 = min(j, nj), j2 = max(j, nj);
        return horPre[i][j2] - (j1 == 0 ? 0 : horPre[i][j1-1]) == 0;
    } else if (j == nj) {
        int i1 = min(i, ni), i2 = max(i, ni);
        return vertPre[i2][j] - (i1 == 0 ? 0 : vertPre[i1-1][j]) == 0;
    } else assert(false);
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        string str; cin >> str;
        rep(j, 0, M) {
            G[i][j] = (str[j] == '1');
        }
    }
    // Prefix sums
    rep(i, 0, N) {
        rep(j, 0, M) {
            horPre[i][j] = (j == 0 ? 0 : horPre[i][j-1]) + G[i][j];
            vertPre[i][j] = (i == 0 ? 0 : vertPre[i-1][j]) + G[i][j];
        }
    }

    cost[0][0][0][0] = 1;
    q.push(getHash(0, 0, 0, 0));
    State s;
    while (!q.empty()) {
        getState(q.front(), s); q.pop();
        int oc = cost[s.i][s.j][s.d][s.s];
        if (s.i == N-1 && s.j == M-1) {
            cout << oc - 1 << '\n';
            exit(0);
        }
        // Slow down or speed up
        rep(ns, s.s-1, s.s+2) {
            if (ns == s.s || ns < 0) continue;
            int ni = s.i + ns * ci[s.d];
            int nj = s.j + ns * cj[s.d];
            if (!validMove(s.i, s.j, ni, nj)) continue;
            if (cost[ni][nj][s.d][ns] != 0) continue;
            cost[ni][nj][s.d][ns] = oc + 1;
            q.push(getHash(ni, nj, s.d, ns));
        }
        // Change direction
        if (s.s == 0) {
            rep(nd, 0, 4) {
                if (cost[s.i][s.j][nd][s.s] != 0) continue;
                cost[s.i][s.j][nd][s.s] = oc + 1;
                q.push(getHash(s.i, s.j, nd, s.s));
            }
        }
    }

    cout << "-1\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}