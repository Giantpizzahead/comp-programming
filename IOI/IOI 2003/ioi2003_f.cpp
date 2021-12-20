/**
 * Solution: Do a circular sweep. Because each rock is convex, it blocks a contiguous range of angles. Use this
 * property to count the # of rocks covering an angle, and the # of fence posts that are visible (covered by 0 rocks).
 * 
 * When implmenting, be careful about rocks that touch and/or cross the left side of the x-axis (-PI or PI with atan2).
 * Treat them as two separate rocks, splitting at the x-axis.
 * 
 * Runtime: O((4N+3R) * log(N))
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 500005;
const int MAXR = 30005;
const double EPSILON = 1e-14;

int N, R;
int fx, fy;
double fenceA[MAXN*4];
struct Event {
    // 0 = Rock start, 1 = Fence post, 2 = Rock end
    int type;
    double angle;

    bool operator<(const Event& o) const {
        if (abs(angle-o.angle) >= EPSILON) return angle < o.angle;
        else return type < o.type;
    }
};
vector<Event> events;

void solve() {
    cin >> N >> R;
    cin >> fx >> fy;
    // Add rocks
    rep(i, 0, R) {
        vector<double> angles;
        int p; cin >> p;
        double minA = MAXR, maxA = -MAXR;
        rep(j, 0, p) {
            int x, y; cin >> x >> y;
            double angle = atan2(y-fy, x-fx);
            if (abs(angle-M_PI) < EPSILON) angle = -M_PI;
            angles.push_back(angle);
            minA = min(angle, minA);
            maxA = max(angle, maxA);
        }
        if (maxA - minA <= M_PI) {
            // Does not cross over
            events.push_back({0, minA});
            events.push_back({2, maxA});
        } else {
            // Crosses over; need different approach
            minA = MAXR;
            maxA = -MAXR;
            for (double angle : angles) {
                if (angle < 0) maxA = max(angle, maxA);
                else minA = min(angle, minA);
            }
            // 
            events.push_back({0, -M_PI});
            events.push_back({2, maxA});
            events.push_back({0, minA});
        }
    }
    // Add fence posts
    rep(i, 0, N+1) {
        int x = i, y = 0;
        double angle = atan2(y-fy, x-fx);
        events.push_back({1, angle});
        y = N;
        angle = atan2(y-fy, x-fx);
        events.push_back({1, angle});
        if (i != 0 && i != N) {
            x = 0, y = i;
            double angle = atan2(y-fy, x-fx);
            if (abs(angle-M_PI) < EPSILON) angle = -M_PI;
            events.push_back({1, angle});
            x = N;
            angle = atan2(y-fy, x-fx);
            events.push_back({1, angle});
        }
    }
    sort(all(events));
    // Sweep
    int answer = 0, currRocks = 0;
    for (Event& e : events) {
        if (e.type == 0) currRocks++;
        else if (e.type == 2) currRocks--;
        else if (currRocks == 0) answer++;
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}