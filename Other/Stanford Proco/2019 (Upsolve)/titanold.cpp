#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1000;
const double EPSILON = 1e-9;

int N;
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

bool checkLine(int a, int b, double h) {
    // "Turn" the globe until a is at (0, 0)
    double B = alpha[b] - alpha[a];
    if (B > 180) B -= 360;
    if (B < -180) B += 360;
    double T = abs(theta[b] - theta[a]);
    if (T > 90) {
        T = 180 - T;
        B += 180;
    }
    if (T < -90) {
        T = -180 - T;
        B += 180;
    }
    if (B > 180) B -= 360;
    B = abs(B);
    T = abs(T);

    // Get angle between the towers
    double angle = B;
    double diff = 90 - angle;
    angle += diff * (T / 90);
    assert(B >= 0 && B <= 180);
    assert(T >= 0 && T <= 90);
    assert(angle >= 0 && angle <= 180);
    debug << B << ' ' << T << ' ' << angle << "\n";
    angle = angle * M_PI / 180;

    // Gen points
    double x1 = 1 + h, y1 = 0;
    double x2 = cos(angle) * (1+h), y2 = sin(angle) * (1+h);
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

    double low = 0, high = 1e12;
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