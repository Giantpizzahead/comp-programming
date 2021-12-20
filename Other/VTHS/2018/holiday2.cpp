#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 20, AREA_ITERS = 8;
const double STEP = 0.00005;

int N;
double X[MAXN], Y[MAXN], dist[MAXN], angle[MAXN];
double angleV, initV, theta, wallX;
double centerX, centerY, horV, currT;

int ccw(double x1, double y1, double x2, double y2, double x3, double y3) {
    double result = (x1 - x3) * (y2 - y3) - (y1 - y3) * (x2 - x3);
    if (result < 0) return -1;
    else if (result == 0) return 0;
    else return 1;
}

bool linesIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    int a = ccw(x1, y1, x2, y2, x3, y3);
    int b = ccw(x1, y1, x2, y2, x4, y4);
    int c = ccw(x3, y3, x4, y4, x1, y1);
    int d = ccw(x3, y3, x4, y4, x2, y2);
    return a != b && c != d;
}

bool isPointInside(double x1, double y1) {
    double x2 = 10000, y2 = y1+0.01;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        int j = (i+1) % N;
        if (linesIntersect(x1, y1, x2, y2, X[i], Y[i], X[j], Y[j])) cnt++;
    }
    // cout << "cnt " << cnt << endl;
    return cnt % 2 == 1;
}

void solve() {
    cin >> N >> angleV >> initV >> theta >> wallX;
    // cout << "begin" << endl;
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
    }
    // Estimate area to determine center of mass
    double centerX = 0, centerY = 0;
    for (int k = 0; k < AREA_ITERS; k++) {
        int area = 500+rand()%500;
        int totalArea = 0;
        double ex = 0, ey = 0;
        for (int i = 0; i < area; i++) {
            for (int j = 0; j < area; j++) {
                double x = 40.0 * (i+0.5) / (area+1) - 20;
                double y = 40.0 * (j+0.5) / (area+1) - 20;
                // cout << x << " " << y << endl;
                if (isPointInside(x, y)) {
                    ex += x;
                    ey += y;
                    totalArea++;
                }
            }
        }
        ex /= totalArea;
        ey /= totalArea;
        centerX += ex;
        centerY += ey;
        // cout << ex << " " << ey << endl;
    }
    centerX /= AREA_ITERS;
    centerY /= AREA_ITERS;
    // cout << centerX << " " << centerY << endl;
    for (int i = 0; i < N; i++) {
        dist[i] = hypot(X[i] - centerX, Y[i] - centerY);
        angle[i] = atan2(Y[i] - centerY, X[i] - centerX);
        // cout << "angle " << angle[i] << endl;
    }
    horV = initV * cos(theta*M_PI/180);
    
    // Simulate cookie movement (skip first part)
    if (wallX > 40) {
        double skipT = (wallX - 40) / horV;
        currT = skipT;
        wallX = 40;
        for (int i = 0; i < N; i++) {
            angle[i] -= angleV * skipT;
        }
    }
    while (true) {
        currT += STEP;
        wallX -= horV * STEP;
        // Are any vertices in the wall?
        for (int i = 0; i < N; i++) {
            angle[i] -= angleV * STEP;
            double currX = centerX + dist[i] * cos(angle[i]);
            if (currX >= wallX) {
                // Vertex found
                cout << i+1 << ' ' << currT << endl;
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}