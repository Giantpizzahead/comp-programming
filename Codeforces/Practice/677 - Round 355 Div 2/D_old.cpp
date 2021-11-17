#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 301, MAXP = 90005;
const int INF = 1e9+7;

int N, M, P;
int A[MAXN][MAXN], C[MAXN][MAXN];

int D[MAXN][MAXN];
struct Point {
    int i, j;
    bool operator<(const Point& o) const {
        return D[i][j] > D[o.i][o.j];
    }
};
vector<Point> points[MAXP];
Point point2D[MAXN][MAXN];
int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};
priority_queue<Point> toEval;

void transBFS(int L) {
    rep(i, 0, N) {
        rep(j, 0, M) {
            D[i][j] = INF;
        }
    }
    for (Point& p : points[L]) {
        D[p.i][p.j] = C[p.i][p.j];
        toEval.push(p);
    }
    while (!toEval.empty()) {
        auto ptr = toEval.top();
        int i = ptr.i, j = ptr.j;
        int c = D[i][j];
        toEval.pop();
        if (D[i][j] != c) continue;
        rep(d, 0, 4) {
            int ni = i + ci[d], nj = j + cj[d];
            if (ni < 0 || ni >= N || nj < 0 || nj >= M || D[ni][nj] <= c) continue;
            D[ni][nj] = c+1;
            toEval.push(point2D[ni][nj]);
        }
    }
    for (Point& p : points[L+1]) {
        C[p.i][p.j] = D[p.i][p.j];
    }
}

void transPairs(int L) {
    for (Point& a : points[L]) {
        for (Point& b : points[L+1]) {
            C[b.i][b.j] = min(C[a.i][a.j] + abs(a.i-b.i) + abs(a.j-b.j), C[b.i][b.j]);
        }
    }
}

void solve() {
    cin >> N >> M >> P;
    rep(i, 0, N) {
        rep(j, 0, M) {
            cin >> A[i][j];
            points[A[i][j]].push_back({i, j});
            point2D[i][j] = points[A[i][j]].back();
            if (A[i][j] != 1) C[i][j] = INF;
            else C[i][j] = i+j;
        }
    }
    // Transition between "layers"
    int maxS = 3000;
    rep(i, 1, P) {
        if (sz(points[i]) >= maxS || sz(points[i+1]) >= maxS) {
            // BFS
            transBFS(i);
        } else {
            // Pairs
            transPairs(i);
        }
        /*
        debug << "at layer " << i << endl;
        rep(a, 0, N) {
            rep(b, 0, M) {
                debug << C[a][b] << " \n"[b==M-1];
            }
        }
        */
    }
    cout << C[points[P][0].i][points[P][0].j] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}