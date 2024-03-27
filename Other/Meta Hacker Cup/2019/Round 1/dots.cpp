#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 800000;
using ll = long long;

struct Point {
    int x, y;
};

Point points[MAXN];
int maxX[MAXN];
int N, H, V;
// Ordered by increasing X coordinate, then decreasing Y coordinate
auto cmp = [](const Point& a, const Point& b) {
    if (a.x == b.x) return a.y > b.y;
    else return a.x < b.x;
};
set<Point, decltype(cmp)> pointSet(cmp);

void solve(int tn) {
    fin >> N >> H >> V;
    int X0, Y0, X1, Y1;
    ll Ax, Bx, Cx, Dx, Ay, By, Cy, Dy;
    fin >> X0 >> X1 >> Ax >> Bx >> Cx >> Dx;
    fin >> Y0 >> Y1 >> Ay >> By >> Cy >> Dy;
    points[0] = {X0, Y0};
    points[1] = {X1, Y1};
    for (int i = 2; i < N; i++) {
        X0 = ((Ax * points[i-2].x + Bx * points[i-1].x + Cx) % Dx) + 1;
        Y0 = ((Ay * points[i-2].y + By * points[i-1].y + Cy) % Dy) + 1;
        points[i] = {X0, Y0};
    }
    // Impossible check
    if (H + V < N) {
        fout << "Case #" << tn << ": -1" << endl;
        return;
    }
    // Sort points by increasing Y coordinate, then decreasing X coordinate
    sort(points, points+N, [](const Point& a, const Point& b) {
        if (a.y == b.y) return a.x > b.x;
        else return a.y < b.y;
    });
    int currMaxX = 0;
    for (int i = N - 1; i >= 0; i--) {
        currMaxX = max(points[i].x, currMaxX);
        maxX[i] = currMaxX;
    }
    /*
    for (int i = 0; i < N; i++) {
        cout << "(" << points[i].x << ", " << points[i].y << ")" << endl;
    }
    */
    
    // Add initial points
    pointSet.clear();
    for (int i = 0; i < N - H; i++) {
        pointSet.insert(points[i]);
    }
    currMaxX = (H == 0 ? 0 : maxX[N - H]);
    int currMaxPointX = 0;
    int answer = (N - H == 0 ? 0 : points[N - H - 1].y) + currMaxX;
    // Sweep
    for (int i = N - H; i < N; i++) {
        pointSet.insert(points[i]);
        currMaxX = (i == N-1 ? 0 : maxX[i+1]);
        // Switch points to horizontal lines when needed
        if (pointSet.size() > V) {
            // cout << "switching" << endl;
            const Point& point = *pointSet.begin();
            currMaxPointX = max(point.x, currMaxPointX);
            pointSet.erase(pointSet.begin());
        }
        answer = min((V == 0 ? 0 : points[i].y) + max(currMaxX, currMaxPointX), answer);
        // cout << (V == 0 ? 0 : points[i].y) + max(currMaxX, currMaxPointX) << endl;
    }
    /*
    for (auto x : pointSet) {
        cout << x.x << ' ' << x.y << endl;
    }
    */
    // cout << endl;
    fout << "Case #" << tn << ": " << answer << endl;
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}