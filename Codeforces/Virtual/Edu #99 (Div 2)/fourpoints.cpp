#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 5;

struct Point {
    int x, y;
};

Point P[MAXN], P2[MAXN];
int centerX, centerY;

inline ll dist(Point& a, Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

ll trySquare(int s) {
    P2[0].x = centerX - s/2;
    P2[0].y = centerY - s/2;
    P2[1].x = centerX + (s+1)/2;
    P2[1].y = centerY - s/2;
    P2[2].x = centerX - s/2;
    P2[2].y = centerY + (s+1)/2;
    P2[3].x = centerX + (s+1)/2;
    P2[3].y = centerY + (s+1)/2;
    ll best = 1e18;
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (a == b) continue;
            for (int c = 0; c < 4; c++) {
                if (a == c || b == c) continue;
                for (int d = 0; d < 4; d++) {
                    if (a == d || b == d || c == d) continue;
                    // Try this combo
                    best = min(dist(P[a], P2[0]) + dist(P[b], P2[1]) + dist(P[c], P2[2]) + dist(P[d], P2[3]), best);
                }
            }
        }
    }
    return best;
}

ll tryCenter() {
    // Ternary search on square size
    int low = 0, high = 1e9;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        ll left = trySquare(mid-1);
        ll cent = trySquare(mid);
        ll right = trySquare(mid+1);
        if (cent <= left && cent <= right) {
            low = mid;
            high = mid;
        } else if (left < cent) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return trySquare(low);
}

void solve() {
    cin >> P[0].x >> P[0].y >> P[1].x >> P[1].y >> P[2].x >> P[2].y >> P[3].x >> P[3].y;
    sort(P, P+4, [](const Point& a, const Point& b) { return a.x < b.x; });
    if (P[1].x == P[2].x && (P[0].x == P[1].x || P[2].x == P[3].x)) {
        // Flip
        for (int i = 0; i < 4; i++) swap(P[i].x, P[i].y);
        sort(P, P+4, [](const Point& a, const Point& b) { return a.x < b.x; });
    }
    ll answer = 1e18;
    centerX = (P[0].x + P[1].x + P[2].x + P[3].x) / 4;
    centerY = (P[0].y + P[1].y + P[2].y + P[3].y) / 4;
    answer = min(tryCenter(), answer);
    centerX++;
    answer = min(tryCenter(), answer);
    centerX--;
    centerY++;
    answer = min(tryCenter(), answer);
    centerX++;
    answer = min(tryCenter(), answer);

    centerX = (P[1].x + P[2].x) / 2;
    sort(P, P+4, [](const Point& a, const Point& b) { return a.y < b.y; });
    centerY = (P[1].y + P[2].y) / 2;
    answer = min(tryCenter(), answer);
    centerX++;
    answer = min(tryCenter(), answer);
    centerX--;
    centerY++;
    answer = min(tryCenter(), answer);
    centerX++;
    answer = min(tryCenter(), answer);

    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}