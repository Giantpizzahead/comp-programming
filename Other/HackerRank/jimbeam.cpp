#include <iostream>
using ll = long long;
using namespace std;

int T;
int x1, y1, x2, y2, x3, y3, x4, y4;

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
    ll res = (ll) (x2-x1) * (y3-y1) - (ll) (y2-y1) * (x3-x1);
    if (res < 0) return -1;
    else if (res > 0) return 1;
    else return 0;
}

bool linesIntersect() {
    int ccw1 = ccw(x1, y1, x2, y2, x3, y3);
    int ccw2 = ccw(x1, y1, x2, y2, x4, y4);
    int ccw3 = ccw(x3, y3, x4, y4, x1, y1);
    int ccw4 = ccw(x3, y3, x4, y4, x2, y2);
    if (ccw1 == 0 && ccw2 == 0) {
        // Colinear; special case
        if (x1 == x2) {
            swap(x1, y1);
            swap(x2, y2);
            swap(x3, y3);
            swap(x4, y4);
        }
        // Check if x's are disjoint
        if (x1 < x3 && x1 < x4 && x2 < x3 && x2 < x4) return false;
        if (x1 > x3 && x1 > x4 && x2 > x3 && x2 > x4) return false;
        return true;
    }
    return ccw1 != ccw2 && ccw3 != ccw4;
}

int main() {
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        x4 = 0;
        y4 = 0;
        if (linesIntersect()) cout << "NO\n";
        else cout << "YES\n";
    }
    return 0;
}