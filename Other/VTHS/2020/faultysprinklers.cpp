#include <bits/stdc++.h>
using namespace std;
using ll = long long;

double A, B, C, D;
int M;

struct Triangle {
    double x1, x2;
    double y1, y2, y3, y4;

    void print() {
        cout << x1 << " " << x2 << " " << y1 << " " << y2 << " " << y3 << " " << y4 << endl;
    }
    
    bool inRange(double x) {
        return x >= x1 && x <= x2;
    }

    double getTopY(double x) {
        double percent = (x-x1)/(x2-x1);
        double changeY = y4-y2;
        return y2 + changeY * percent;
    }

    double getBotY(double x) {
        double percent = (x-x1)/(x2-x1);
        double changeY = y3-y1;
        return y1 + changeY * percent;
    }
};

struct Point {
    double x;
    bool s;
};

Triangle triangles[8];
Point points[16];

void solve() {
    cin >> A >> B >> C >> D;
    cout << fixed << setprecision(9);
    if (A == 90 || B == 90 || C == 90 || D == 90) {
        cout << 1.0 << endl;
        return;
    }
    A *= M_PI / 180;
    B *= M_PI / 180;
    C *= M_PI / 180;
    D *= M_PI / 180;
    if (D > M_PI_4) {
        triangles[M++] = {0, 1/tan(D), 0, 0, 0, 1};
        triangles[M++] = {1/tan(D), 1, 0, 1, 0, 1};
    } else triangles[M++] = {0, 1, 0, 0, 0, tan(D)};
    if (C > M_PI_4) {
        triangles[M++] = {0, 1, 1-1/tan(C), 1, 1-1/tan(C), 1-1/tan(C)};
        triangles[M++] = {0, 1, 0, 1-1/tan(C), 0, 1-1/tan(C)};
    } else triangles[M++] = {0, tan(C), 0, 1, 0, 0};
    if (B > M_PI_4) {
        triangles[M++] = {1-1/tan(B), 1, 0, 1, 1, 1};
        triangles[M++] = {0, 1-1/tan(B), 0, 1, 0, 1};
    } else triangles[M++] = {0, 1, 1-tan(B), 1, 1, 1};
    if (A > M_PI_4) {
        triangles[M++] = {0, 1, 0, 0, 0, 1/tan(A)};
        triangles[M++] = {0, 1, 1/tan(A), 1, 1/tan(A), 1};
    } else triangles[M++] = {1-tan(A), 1, 1, 1, 0, 1};

    // for (int i = 0; i < M; i++) {
    //     triangles[i].print();
    // }
    double totalArea = 0;
    // double step = 0.0000005;
    double step = 1.0/8989375;
    double loc = 0;//step / 2;
    while (loc <= 1) {
        // Find loc of each triangle
        for (int i = 0; i < M; i++) {
            if (!triangles[i].inRange(loc)) {
                points[i*2].x = -1;
                points[i*2].s = true;
                points[i*2+1].x = -1;
                points[i*2+1].s = false;
                continue;
            }
            double bot = triangles[i].getBotY(loc);
            double top = triangles[i].getTopY(loc);
            // if (bot < 0 || top > 1) exit(-1);
            points[i*2].x = bot;
            points[i*2].s = true;
            points[i*2+1].x = top;
            points[i*2+1].s = false;
        }
        sort(points, points+M*2, [](const Point& a, const Point& b) {
            if (a.x == b.x) return a.s > b.s;
            return a.x < b.x;
        });
        // Sweep
        double area = 0, lastX = 0, active = 0;
        // cout << "sweep" << endl;
        for (int i = 0; i < M*2; i++) {
            Point& p = points[i];
            // cout << p.x << " " << p.s << endl;
            if (p.s) {
                if (active++ == 0) lastX = p.x;
            } else {
                if (active-- == 1) area += (p.x - lastX);
            }
        }
        totalArea += step * area;
        loc += step;
    }
    // if (totalArea > 1.0000001 || totalArea < 0) exit(-1);
    cout << totalArea << endl;
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