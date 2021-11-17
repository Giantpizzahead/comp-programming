#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2000;

int N, S = 0, C = 0;
bool A[MAXN][MAXN], B[MAXN][MAXN];

void setColor(int i, int j) {
    int zero = 0, one = 0;
    rep(a, -2, 3) {
        rep(b, -2, 3) {
            int ni = i+a, nj = j+b;
            if (ni < 0 || ni >= N || nj < 0 || nj >= N) continue;
            else if (A[ni][nj]) one++;
            else zero++;
        }
    }
    B[i][j] = (one >= zero);
}

struct Point {
    int i, j;
};
vector<Point> locs;
bool vis[MAXN][MAXN];

void dfsComp(int i, int j) {
    if (i < 0 || i >= N || j < 0 || j >= N) return;
    if (vis[i][j] || !B[i][j]) return;
    vis[i][j] = true;
    locs.push_back({i, j});
    dfsComp(i-1, j);
    dfsComp(i+1, j);
    dfsComp(i, j-1);
    dfsComp(i, j+1);
}

void checkComp(int a, int b) {
    locs.clear();
    dfsComp(a, b);

    // Check for big enough shape
    if (sz(locs) <= 75) return;

    // Find center loc
    double ci = 0, cj = 0;
    for (Point& p : locs) {
        ci += p.i, cj += p.j;
    }
    ci /= sz(locs), cj /= sz(locs);

    // Find distances from center
    double averageDist = 0, maxDist = 0;
    // map<int, int> dists;
    for (Point& p : locs) {
        double dist = hypot(p.i - ci, p.j - cj);
        averageDist += dist;
        maxDist = max(dist, maxDist);
        // int intDist = (int) round(dist);
        // dists[intDist]++;
    }
    averageDist /= sz(locs);

    // Mean distance is different for squares and circles
    double squareRatio = (0.57863+0.59232)/2;
    double circleRatio = 0.66503;
    double currRatio = averageDist / maxDist;
    if (abs(currRatio - squareRatio) < abs(currRatio - circleRatio)) S++;
    else C++;

    // debug << "center " << ci << " " << cj << "\n";
    // debug << "maxDist " << maxDist << "\n";
    // debug << "averageDist " << averageDist << "\n";
    // debug << "sDist " << abs(currRatio - squareRatio);
    // debug << ", cDist " << abs(currRatio - circleRatio) << "\n\n";

    // // Find max dist and mode dist
    // int maxDist = 0, modeDist = 0, modeCnt = 0;
    // for (auto& p : dists) {
    //     if (p.second < 5) continue;  // Ignore outliers
    //     if (p.first > maxDist) maxDist = p.first;
    //     if (p.second > modeCnt) {
    //         modeCnt = p.second;
    //         modeDist = p.first;
    //     }
    // }
    // // Circles have modeDist near maxDist
    // // Squares have modeDist somewhere in between
    // int outerDist = maxDist * 4 / 5;
    // if (modeDist > outerDist) C++;
    // else S++;

    // debug << "center " << ci << " " << cj << "\n";
    // debug << "dists\n";
    // for (auto& p : dists) {
    //     if (p.second < 5) continue;
    //     debug << p.first << ' ' << p.second << '\n';
    // }
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        rep(j, 0, N) {
            cin >> A[i][j];
        }
    }

    // Remove some noise
    rep(i, 0, N) {
        rep(j, 0, N) {
            setColor(i, j);
        }
    }

    // Find components
    rep(i, 0, N) {
        rep(j, 0, N) {
            if (!vis[i][j] && B[i][j]) {
                checkComp(i, j);
            }
        }
    }
    cout << C << ' ' << S << '\n';

    // cout << N << '\n';
    // rep(i, 0, N) {
    //     rep(j, 0, N) {
    //         cout << B[i][j] << " \n"[j==N-1];
    //     }
    // }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}