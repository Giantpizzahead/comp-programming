#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1001, INF = 9;
const int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};
const char cc[] = {'U', 'L', 'D', 'R'};

int N, M, si, sj;
int aDist[MAXN][MAXN], mDist[MAXN][MAXN], aFrom[MAXN][MAXN];
bool grid[MAXN][MAXN];

int qCurr = 0, qNext = 0, qDist = 0;
queue<pair<int, int>> q;

bool inBounds(int i, int j) {
    return i >= 0 && i < N && j >= 0 && j < M;
}

void trace(int i, int j) {
    cout << "YES\n" << aDist[i][j] << '\n';
    stack<char> dirs;
    while (i != si || j != sj) {
        int d = aFrom[i][j];
        dirs.push(cc[d]);
        i += ci[d], j += cj[d];
    }
    while (!dirs.empty()) {
        cout << dirs.top();
        dirs.pop();
    }
    cout << '\n';
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        string S; cin >> S;
        rep(j, 0, M) {
            aDist[i][j] = INF, mDist[i][j] = INF;
            grid[i][j] = (S[j] == '#');
            if (S[j] == 'A') si = i, sj = j;
            else if (S[j] == 'M') {
                mDist[i][j] = 0, qCurr++;
                q.emplace(i, j);
            }
        }
    }

    while (!q.empty()) {
        auto p = q.front(); q.pop();
        if (qCurr == 0) {
            qCurr = qNext, qNext = 0;
            qDist++;
        }
        qCurr--;

        int i = p.first, j = p.second;
        rep(d, 0, 4) {
            int ni = i+ci[d], nj = j+cj[d];
            if (!inBounds(ni, nj) || grid[ni][nj] || mDist[ni][nj] != INF) continue;
            mDist[ni][nj] = qDist+1;
            qNext++;
            q.emplace(ni, nj);
        }
    }

    aDist[si][sj] = 0;
    qCurr = 1, qNext = 0, qDist = 0;
    q.emplace(si, sj);
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        if (qCurr == 0) {
            qCurr = qNext, qNext = 0;
            qDist++;
        }
        qCurr--;

        int i = p.first, j = p.second;
        rep(d, 0, 4) {
            int ni = i+ci[d], nj = j+cj[d];
            if (!inBounds(ni, nj) || grid[ni][nj] || aDist[ni][nj] != INF || mDist[ni][nj] <= qDist+1) continue;
            aDist[ni][nj] = qDist+1;
            aFrom[ni][nj] = (d+2)%4;
            qNext++;
            q.emplace(ni, nj);
        }
    }

    rep(i, 0, N) {
        if (aDist[i][0] != INF) {
            trace(i, 0);
            return;
        }
        if (aDist[i][M-1] != INF) {
            trace(i, M-1);
            return;
        }
    }
    rep(j, 0, M) {
        if (aDist[0][j] != INF) {
            trace(0, j);
            return;
        }
        if (aDist[N-1][j] != INF) {
            trace(N-1, j);
            return;
        }
    }
    cout << "NO\n";

    // rep(i, 0, N) {
    //     rep(j, 0, M) cout << mDist[i][j] << ' ';
    //     cout << endl;
    // }

    // rep(i, 0, N) {
    //     rep(j, 0, M) cout << aDist[i][j] << ' ';
    //     cout << endl;
    // }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}