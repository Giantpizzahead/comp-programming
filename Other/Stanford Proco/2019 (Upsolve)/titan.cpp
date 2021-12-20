#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 1000;
const double EPSILON = 1e-9;

int N;
struct Triple {
    double x, y, z;
};
Triple coords[MAXN];
double pairAngle[MAXN][MAXN];
double theta[MAXN], alpha[MAXN];

double tangentDist(double x1, double y1, double x2, double y2) {
    if (abs(x1-x2) < EPSILON) {
        // Vertical
        swap(x1, y1);
        swap(x2, y2);
    }
    if (abs(y1-y2) < EPSILON) {
        // Horizontal (or vertical)
        double dist = abs(y1);
        debug << x1 << " " << y1 << " " << x2 << " " << y2 << " = " << dist << " hor/vert\n";
        return dist;
    }
    double m = (y2 - y1) / (x2 - x1);
    double perpM = -1 / m;
    double ansX = (m * x1 - y1) / (m - perpM);
    double ansY = m * (ansX - x1) + y1;
    double dist = hypot(ansX, ansY);
    debug << x1 << " " << y1 << " " << x2 << " " << y2 << " = " << dist << " " << ansX << " " << ansY << "\n";
    return dist;
}

Triple getCoords(int a) {
    double T = theta[a] * M_PI / 180;
    double A = alpha[a] * M_PI / 180;
    double z = sin(T);
    double x, y;
    if (1-abs(z) < EPSILON) x = 0, y = 0;
    else {
        x = cos(A), y = sin(A);
        double adjust = sqrt(1-z*z);
        x *= adjust, y *= adjust;
    }
    assert(abs(x*x+y*y+z*z - 1) < EPSILON);
    return {x, y, z};
}

bool checkLine(int a, int b, double h) {
    // Gen points
    double x1 = 1 + h, y1 = 0;
    double x2 = cos(pairAngle[a][b]) * (1+h), y2 = sin(pairAngle[a][b]) * (1+h);
    return tangentDist(x1, y1, x2, y2) >= 1;
}

vector<int> adj[MAXN];
int currIter = 0;
int vis[MAXN];

int dfs(int n) {
    int cnt = 1;
    vis[n] = currIter;
    for (int e : adj[n]) {
        if (vis[e] == currIter) continue;
        cnt += dfs(e);
    }
    return cnt;
}

bool check(double H) {
    debug << "check " << H << '\n';
    rep(i, 0, N) adj[i].clear();
    rep(i, 0, N) {
        rep(j, i+1, N) {
            if (checkLine(i, j, H)) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
            debug << i << ' ' << j << " = " << checkLine(i, j, H) << '\n';
        }
    }
    currIter++;
    return (dfs(0) == N);
}

void solve() {
    // tangentDist(1, 0, 0, 1);
    // tangentDist(-5, 1, 3, 1);
    // tangentDist(5, 10.6602540378, -0.5773502692, 1);

    cin >> N;
    char c;
    rep(i, 0, N) {
        cin >> theta[i] >> c;
        if (c == 'S') theta[i] *= -1;
        cin >> alpha[i] >> c;
        if (c == 'W') alpha[i] *= -1;
    }

    // Precalculate info
    rep(i, 0, N) coords[i] = getCoords(i);
    rep(i, 0, N) {
        rep(j, i+1, N) {
            // Determine angle
            Triple loc1 = coords[i];
            Triple loc2 = coords[j];
            double dist = sqrt(pow(loc1.x-loc2.x, 2) + pow(loc1.y-loc2.y, 2) + pow(loc1.z-loc2.z, 2));
            double angle = asin(dist/2) * 2;
            pairAngle[i][j] = angle;
        }
    }

    // Binary search
    double low = 0, high = 1e5;
    while (abs(low-high) > 1e-7) {
        double mid = (low + high) / 2;
        if (check(mid)) {
            high = mid;
        } else {
            low = mid;
        }
    }
    cout << fixed << setprecision(9) << (low + high) / 2 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}