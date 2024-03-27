/*
Solution: Fix each point, and do a radial sweep.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

int N, M;

struct Point {
    int x, y;
    bool isG;
};

vector<Point> P;

struct Angle {
    int x, y;
    int t, id;
    bool flipped;
    int half() const {
        assert(x || y);
        return y < 0 || (y == 0 && x < 0);
    }
    Angle t180() const { return {-x, -y, t, id, flipped}; }
};
bool operator<(Angle a, Angle b) {
    return make_tuple(a.t, a.half(), a.y * (ll)b.x) <
           make_tuple(b.t, b.half(), a.x * (ll)b.y);
}

void doSweep(Point O, vector<Point>& points) {
    vector<Angle> angles;  // Angle is from KACTL
    rep(i, 0, sz(points)) {
        Point& p = points[i];
        Angle a = {p.x - O.x, p.y - O.y, 0, i, false};
        Angle a2 = a.t180();  a2.flipped = true;
        angles.push_back(a); angles.push_back(a2);
    }
    sort(all(angles));
    int rightG = 0, rightR = 0;
    // Origin is always above (left of) the line
    // Find location of other points, assuming starting line right below the origin
    rep(i, 0, sz(points)) {
        if (points[i].y - O.y < 0) { if (points[i].isG) rightG++; else rightR++; }
    }
    // Go through 360 degree loop once
    for (Angle a : angles) {
        if (!a.flipped && rightG == N/2 && rightR == M/2) {
            // Solution: both points are barely above the line
        }
        if (!a.flipped) { // Right before crossing from left to right
            if (points[a.id].isG) rightG++; else rightR++;
        } else { // Right before crossing from right to left
            if (points[a.id].isG) rightG--; else rightR--;
        }
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        Point p; cin >> p.x >> p.y;
        p.isG = true;
        P.push_back(p);
    }
    rep(i, 0, M) {
        Point p; cin >> p.x >> p.y;
        p.isG = false;
        P.push_back(p);
    }

    rep(i, 0, N+M) {
        // Do polar sweep around P[i]
        vector<Point> points;
        rep(j, 0, N+M) {
            if (i == j) continue;
            points.push_back(P[j]);
        }
        doSweep(P[i], points);
    }
    // If got here, no solution
    cout << "0 0 0\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
