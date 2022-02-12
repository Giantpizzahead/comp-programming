/*
Must solve using some form of modified Dijkstra
If A >= C, never makes sense to kick the ball, special case
Now guaranteed A < C

When a player has the ball, they can either kick to any square in their row / column (Ap + B), or move to a different square (C)

It may be optimal to move before getting the ball, but it's never optimal to have the same player get the ball twice (they could just move with the ball instead).

BFS to find shortest distance from each cell to the nearest player. If the ball is at that cell, players can get to the ball with that distance.

When kicking the ball, don't transition to all cells immediately; treat it as another state to reach.

So each cell location has states of: Player has the ball (4), no one has the ball (5), ball is currently being kicked in any of 4 directions (0-1-2-3).

Trans: 5 -> 4, 4 -> 0-1-2-3, 0-1-2-3 -> 5

This works because even though it doesn't correctly consider the "move back" cost for a player, it's never optimal for the same player to get the ball twice, and any state that uses the same player twice will be greater cost than the correct, optimal path. (Although some paths will have incorrect cost, they won't be the ones the algorithm chooses.)

Runtime: O(HW * log(HW))
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXD = 505;
const ll INF = 1e18;

int H, W, N;
int si, sj, ei, ej;
ll A, B, C;
ll costP[MAXD][MAXD];

int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};

inline bool inBounds(int i, int j) {
    return i >= 0 && i < H && j >= 0 && j < W;
}

// 0-3 = Being kicked, 4 = Player has the ball
ll bestC[MAXD][MAXD][5];
struct Loc {
    int i, j, k;
    ll c;
    bool operator<(const Loc& o) const {
        return c > o.c;
    }
};
priority_queue<Loc> pq;

void tryTrans(int i, int j, int k, ll c) {
    if (!inBounds(i, j) || bestC[i][j][k] <= c) return;
    bestC[i][j][k] = c;
    pq.push({i, j, k, c});
}

void bfs1() {
    while (!pq.empty()) {
        Loc l = pq.top(); pq.pop();
        int i = l.i, j = l.j;
        ll c = l.c;
        if (c != costP[i][j]) continue;
        // Move to adjacent square
        rep(d, 0, 4) {
            int ni = i + ci[d], nj = j + cj[d];
            ll nc = c + C;
            if (!inBounds(ni, nj) || costP[ni][nj] <= nc) continue;
            costP[ni][nj] = nc;
            pq.push({ni, nj, -1, nc});
        }
    }
}

void bfs2() {
    bestC[si][sj][4] = 0;
    pq.push({si, sj, 4, 0});
    while (!pq.empty()) {
        Loc l = pq.top(); pq.pop();
        int i = l.i, j = l.j, k = l.k;
        ll c = l.c;
        if (c != bestC[i][j][k]) continue;
        if (k == 4) {
            // Player has the ball
            rep(d, 0, 4) {
                tryTrans(i + ci[d], j + cj[d], 4, c + C);  // Move with the ball
                tryTrans(i, j, d, c + B);  // Kick the ball in a direction
            }
        } else {
            // Ball is being kicked
            // Continue moving the ball
            tryTrans(i + ci[k], j + cj[k], k, c + A);
            // Stop moving and have a player pick up the ball
            tryTrans(i, j, 4, c + costP[i][j]);
        }
    }
}

void solve() {
    cin >> H >> W;
    H++, W++;
    cin >> A >> B >> C;
    cin >> N;
    rep(i, 0, H) rep(j, 0, W) {
        costP[i][j] = INF;
        rep(k, 0, 5) bestC[i][j][k] = INF;
    }
    rep(k, 0, N) {
        int i, j; cin >> i >> j;
        if (k == 0) si = i, sj = j;
        else if (k == N-1) ei = i, ej = j;
        costP[i][j] = 0;
        pq.push({i, j, -1, 0});
    }
    bfs1();
    bfs2();
    ll ans = INF;
    rep(i, 0, H) rep(j, 0, W) rep(k, 0, 5) {
        ll cost = bestC[i][j][k] + C * (abs(ei-i) + abs(ej-j));
        ans = min(cost, ans);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}