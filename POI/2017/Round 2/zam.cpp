/*
Solution: When representing each chamber as a node and adjacent chambers as edges, it can be shown that the # of edges
is bounded by a small constant of N (maybe 4?). Think about the number of full sides for each chamber (not touching
other chambers), along with the number of contiguous, partially occupied sides. Messing around with these, along with
some intuition, reveals this property.
To efficiently find these edges, use a sorted vector to "sweep" through the chambers that are adjacent. See code for
more details.
Runtime: O(N * log(N) * C) where C is a small constant
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e6+5;
const int INF = 1e9;

int W, H, N, M, A, B;
int X1[MAXN], Y1[MAXN], X2[MAXN], Y2[MAXN];
bool marked[MAXN];

struct Point {
    int x, y, i;
    bool operator<(const Point& o) const {
        return make_pair(x, y) < make_pair(o.x, o.y);
    }
};

struct Pair {
    int x, i;
    bool operator<(const Pair& o) const {
        return x < o.x;
    }
};

unordered_map<int, vector<Pair>> adjT, adjR, adjB, adjL;
int dist[MAXN];
queue<int> q;

void addAdj(int d, int l, int r, vector<Pair>& v) {
    auto ptr = upper_bound(all(v), Pair{l, -1});
    if (ptr != v.begin()) ptr = prev(ptr);
    while (ptr != v.end() && ptr->x < r) {
        int n = ptr->i;
        if (!marked[n] && dist[n] == INF) {
            dist[n] = d+1;
            q.push(n);
        }
        ptr = next(ptr);
    }
}

int bfs() {
    rep(i, 0, N) {
        adjT[Y1[i]].push_back({X1[i], i});
        adjB[Y2[i]].push_back({X1[i], i});
        adjR[X1[i]].push_back({Y1[i], i});
        adjL[X2[i]].push_back({Y1[i], i});
        dist[i] = INF;
    }
    for (auto& v : adjT) sort(all(v.second));
    for (auto& v : adjR) sort(all(v.second));
    for (auto& v : adjB) sort(all(v.second));
    for (auto& v : adjL) sort(all(v.second));

    q.push(A);
    dist[A] = 1;
    while (!q.empty()) {
        int n = q.front(); q.pop();
        if (n == B) return dist[n];
        addAdj(dist[n], X1[n], X2[n], adjT[Y2[n]]);
        addAdj(dist[n], X1[n], X2[n], adjB[Y1[n]]);
        addAdj(dist[n], Y1[n], Y2[n], adjR[X2[n]]);
        addAdj(dist[n], Y1[n], Y2[n], adjL[X1[n]]);
    }
    return -1;
}

void solve() {
    cin >> W >> H >> N >> M;
    int xp, yp, xs, ys;
    cin >> xp >> yp >> xs >> ys;
    rep(i, 0, N) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        X1[i] = min(x1, x2);
        Y1[i] = min(y1, y2);
        X2[i] = max(x1, x2);
        Y2[i] = max(y1, y2);
    }

    // Process marks
    vector<Point> events;
    events.push_back({xp, yp, 2*N});
    events.push_back({xs, ys, 2*N+1});
    rep(i, 0, N) {
        events.push_back({X1[i], Y1[i], i});
        events.push_back({X2[i], Y1[i], N+i});
    }
    rep(i, 0, M) {
        int x, y;
        cin >> x >> y;
        events.push_back({x, y, -1});
    }
    sort(all(events));
    set<pair<int, int>> activeRects;
    for (Point& p : events) {
        // debug << p.x << " " << p.y << " " << p.i << endl;
        if (p.i == -1 || p.i >= 2*N) {
            // Point
            int n = prev(activeRects.lower_bound({p.y, -1}))->second;
            if (p.i == -1) marked[n] = true;
            else if (p.i == 2*N) A = n;
            else B = n;
        } else if (p.i < N) {
            // Rectangle start
            activeRects.insert({p.y, p.i});
        } else {
            // Rectangle end
            activeRects.erase({p.y, p.i-N});
        }
    }

    // BFS
    int ans = bfs();
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}