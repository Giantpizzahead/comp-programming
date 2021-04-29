#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;

const int MAXN = 2e5+5;

int N;
struct Point {
    int x, y;
    double comp;
};
Point P[MAXN];
bool on[MAXN];
vector<Point> H;

int ccw(Point& a, Point& b, Point& c) {
    ll res = (ll)(b.x-a.x)*(c.y-a.y) - (ll)(b.y-a.y)*(c.x-a.x);
    if (res < 0) return -1;
    else if (res > 0) return 1;
    else return 0;
}

bool onSeg(Point& a, Point& b, Point& c) {
    if (ccw(a, b, c) != 0) return false;
    if (a.x == c.x && a.y == c.y) return true;
    if (b.x == c.x && b.y == c.y) return true;
    if (a.x == b.x) return ((a.y < c.y) == (c.y < b.y));
    else return ((a.x < c.x) == (c.x < b.x));
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> P[i].x >> P[i].y;
        if (make_pair(P[i].y, P[i].x) < make_pair(P[0].y, P[0].x)) {
            swap(P[i], P[0]);
        }
    }
    rep(i, 1, N) P[i].comp = atan2(P[i].y-P[0].y, P[i].x-P[0].x);
    sort(P+1, P+N, [](const Point& a, const Point& b) {
        return a.comp < b.comp;
    });
    P[N].x = P[0].x;
    P[N].y = P[0].y;
    rep(i, 0, N+1) {
        while (sz(H) >= 2) {
            int res = ccw(H[sz(H)-2], H[sz(H)-1], P[i]);
            if (res < 0) H.pop_back();
            else if (res == 0) {
                // Either don't add this one, or remove the other one
                if (onSeg(H[sz(H)-2], H[sz(H)-1], P[i])) break;
                else H.pop_back();
            } else {
                H.push_back(P[i]);
                break;
            }
        }
        if (sz(H) < 2) H.push_back(P[i]);
    }
    // Mark points on the hull
    // cout << "hull:\n";
    // for (Point& p : H) cout << p.x << ' ' << p.y << '\n';
    int currSeg = 0, ans = 0;
    rep(i, 0, N) {
        // cout << "i " << i << " seg " << currSeg << endl;
        if (H[currSeg+1].x == P[i].x && H[currSeg+1].y == P[i].y) {
            // Next segment
            on[i] = true;
            ans++;
            currSeg++;
            // cout << "next\n";
        } else if (onSeg(H[currSeg], H[currSeg+1], P[i]) ||
                   (currSeg != 0 && onSeg(H[currSeg-1], H[currSeg], P[i])) ||
                   (currSeg != sz(H)-2 && onSeg(H[currSeg+1], H[currSeg+2], P[i]))) {
            on[i] = true;
            ans++;
        }
    }
    cout << ans << '\n';
    rep(i, 0, N) if (on[i]) cout << P[i].x << ' ' << P[i].y << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}