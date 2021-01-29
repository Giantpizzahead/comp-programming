#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

const int MAXN = 1000, INF = 1e9;

int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};
int N, D;
int rock[MAXN][MAXN];
int robot[MAXN][MAXN];

struct State {
    int i, j, t;
    State(int i, int j, int t) : i(i), j(j), t(t) {}
    bool operator<(const State& o) const {
        return t < o.t;
    }
};

queue<State> q1, q2;
priority_queue<State> q3;

inline bool inBounds(int i, int j) {
    return i >= 0 && j >= 0 && i < N && j < N;
}

void solve() {
    cin >> N >> D;
    rep(i, 0, N) {
        string str;
        cin >> str;
        rep(j, 0, N) {
            if (str[j] == '#') {
                rock[i][j] = 0;
                q1.emplace(i, j, D);
            } else {
                rock[i][j] = INF;
            }
            if (str[j] == 'S') {
                robot[i][j] = 0;
                q2.emplace(i, j, 0);
            } else {
                robot[i][j] = -1;
            }
        }
    }

    // Spread out rocks
    while (!q1.empty()) {
        State s = q1.front();
        q1.pop();
        if (s.t >= INF) continue;
        rep(d, 0, 4) {
            int ni = s.i + ci[d], nj = s.j + cj[d];
            if (!inBounds(ni, nj) || rock[ni][nj] != INF) continue;
            rock[ni][nj] = s.t;
            q1.emplace(ni, nj, s.t + D);
        }
    }

    // Spread out robots
    while (!q2.empty()) {
        State s = q2.front();
        q2.pop();
        rep(d, 0, 4) {
            int ni = s.i + ci[d], nj = s.j + cj[d];
            if (!inBounds(ni, nj) || rock[ni][nj] <= s.t || robot[ni][nj] != -1) continue;
            if (s.t + 1 != rock[ni][nj]) {
                robot[ni][nj] = s.t + 1;
                q2.emplace(ni, nj, s.t + 1);
            } else {
                // Can only move, not replicate
                robot[ni][nj] = s.t;
            }
        }
    }

    // Fill in visitable locations
    rep(i, 0, N) {
        rep(j, 0, N) {
            if (robot[i][j] != -1) q3.emplace(i, j, robot[i][j]);
        }
    }
    int answer = 0;
    while (!q3.empty()) {
        State s = q3.top();
        q3.pop();
        if (s.t < robot[s.i][s.j]) continue;
        answer++;
        rep(d, 0, 4) {
            int ni = s.i + ci[d], nj = s.j + cj[d];
            if (!inBounds(ni, nj) || rock[ni][nj] == 0 || robot[ni][nj] >= s.t - D) continue;
            robot[ni][nj] = s.t - D;
            q3.emplace(ni, nj, s.t - D);
        }
    }
    // rep(i, 0, N) {
    //     rep(j, 0, N) cout << robot[i][j] << ' ';
    //     cout << endl;
    // }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}