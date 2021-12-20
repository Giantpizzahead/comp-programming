#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using namespace std;
using ll = long long;

const int MAXN = 40;
const ll MOD = 1e9+7;

int N;
int X[MAXN], Y[MAXN];

bool ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (x2-x1) * (y3-y1) - (y2-y1) * (x3-x1) > 0;
}

bool segmentsIntersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    bool a = ccw(x1, y1, x2, y2, x3, y3) != ccw(x1, y1, x2, y2, x4, y4);
    bool b = ccw(x3, y3, x4, y4, x1, y1) != ccw(x3, y3, x4, y4, x2, y2);
    return a && b;
}

bool pointInsideTri(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
    int xr = x+20000, yr = y+1;
    bool a = segmentsIntersect(x, y, xr, yr, x1, y1, x2, y2);
    bool b = segmentsIntersect(x, y, xr, yr, x2, y2, x3, y3);
    bool c = segmentsIntersect(x, y, xr, yr, x3, y3, x1, y1);
    int num = a + b + c;
    return num == 1;
}

int getArea(int x1, int y1, int x2, int y2, int x3, int y3) {
    int ans = abs(x1 * y2 + x2 * y3 + x3 * y1 - y1 * x2 - y2 * x3 - y3 * x1);
    return ans;
}

void plusMod(ll& a, ll b) {
    a = (a+b) % MOD;
}

ll dp[MAXN][MAXN][MAXN][MAXN];
bool canTrans[MAXN][MAXN][MAXN][MAXN];
int insidePoint[MAXN][MAXN][MAXN][MAXN];
int numInside[MAXN][MAXN][MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> X[i] >> Y[i];
    // Precompute info
    struct State {
        int a, b, c, area;
    };
    vector<State> states;
    rep(a, 0, N) {
        rep(b, 0, N) {
            rep(c, 0, N) {
                if (a == b || a == c || b == c) continue;
                int inside = 0;
                rep(d, 0, N) {
                    if (d == a || d == b || d == c) continue;
                    bool isInside = pointInsideTri(X[d], Y[d], X[a], Y[a], X[b], Y[b], X[c], Y[c]);
                    inside += isInside;
                    if (isInside) continue;
                    bool i = segmentsIntersect(X[a], Y[a], X[d], Y[d], X[b], Y[b], X[c], Y[c]);
                    bool j = segmentsIntersect(X[b], Y[b], X[d], Y[d], X[a], Y[a], X[c], Y[c]);
                    bool k = segmentsIntersect(X[c], Y[c], X[d], Y[d], X[a], Y[a], X[b], Y[b]);
                    canTrans[a][b][c][d] = !(i || j || k);
                    if (pointInsideTri(X[a], Y[a], X[d], Y[d], X[b], Y[b], X[c], Y[c])) insidePoint[a][b][c][d] = a;
                    if (pointInsideTri(X[b], Y[b], X[d], Y[d], X[a], Y[a], X[c], Y[c])) insidePoint[a][b][c][d] = b;
                    if (pointInsideTri(X[c], Y[c], X[d], Y[d], X[b], Y[b], X[a], Y[a])) insidePoint[a][b][c][d] = c;
                }
                numInside[a][b][c] = inside;
                dp[a][b][c][numInside[a][b][c]] = 1;
                states.push_back({a, b, c, getArea(X[a], Y[a], X[b], Y[b], X[c], Y[c])});
            }
        }
    }
    // Special case (no answer)
    int maxInside = 0;
    rep(a, 0, N) rep(b, 0, N) rep(c, 0, N) maxInside = max(numInside[a][b][c], maxInside);
    if (maxInside != N-3) {
        cout << "0\n";
        return;
    }
    // DP (process trans from smallest to largest area)
    sort(all(states), [](const State& a, const State& b) {
        return a.area < b.area;
    });
    int maxArea = states.back().area;
    ll ans = 0;
    for (State& s : states) {
        int a = s.a, b = s.b, c = s.c;
        for (int n = N-3; n >= 0; n--) {
            if (dp[a][b][c][n] == 0) continue;
            debug << "dp[" << a << "][" << b << "][" << c << "][" << n << "] = " << dp[a][b][c][n] << endl;
            // Use inner point
            if (n != 0) plusMod(dp[a][b][c][n-1], dp[a][b][c][n] * n % MOD);
            // Trans to new point
            rep(d, 0, N) {
                if (canTrans[a][b][c][d]) {
                    // Find new triangle
                    int newA = a, newB = b, newC = c;
                    if (insidePoint[a][b][c][d] == newA) newA = d;
                    if (insidePoint[a][b][c][d] == newB) newB = d;
                    if (insidePoint[a][b][c][d] == newC) newC = d;
                    int newN = n + numInside[newA][newB][newC] - numInside[a][b][c] - 1;
                    debug << "trans " << d << " " << newN << endl;
                    plusMod(dp[newA][newB][newC][newN], dp[a][b][c][n]);
                }
            }
            if (s.area == maxArea && n == 0) {
                // Add to answer
                plusMod(ans, dp[a][b][c][n]);
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}