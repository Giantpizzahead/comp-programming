#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
using ll = long long;

const int MAXN = 1e5;
const ll INF = 1e18;

int N;
char D[MAXN];
int X[MAXN];

struct Point {
    ll a, b;
    bool s;
    Point(ll a, ll b, bool s) : a(a), b(b), s(s) {}

    bool operator<(const Point& o) const {
        if (a != o.a) return a < o.a;
        else return s < o.s;
    }
};

struct Query {
    ll a, l, r;
    Query(ll a, ll l, ll r) : a(a), l(l), r(r) {}

    bool operator<(const Query& o) const {
        if (a != o.a) return a < o.a;
        else return l < o.l;
    }
};

vector<Point> points;
vector<Query> queries;
set<ll> active;

bool check(int M) {
    points.clear();
    queries.clear();
    active.clear();
    points.emplace_back(0, 0, true);
    points.emplace_back(1, 0, false);
    ll cx = 0, cy = 0;
    for (int i = 0; i < M; i++) {
        if (D[i] == 'U') {
            queries.emplace_back(cx, cy+1, cy+X[i]);
            cy += X[i];
        } else if (D[i] == 'D') {
            queries.emplace_back(cx, cy-X[i], cy-1);
            cy -= X[i];
        } else if (D[i] == 'R') {
            points.emplace_back(cx+1, cy, true);
            points.emplace_back(cx+X[i]+1, cy, false);
            cx += X[i];
        } else {
            points.emplace_back(cx-X[i], cy, true);
            points.emplace_back(cx-1+1, cy, false);
            cx -= X[i];
        }
    }
    sort(points.begin(), points.end());
    sort(queries.begin(), queries.end());

    // cout << "check " << M << endl;
    // cout << "points:\n";
    // for (Point& p : points) cout << p.a << " " << p.b << " " << p.s << endl;
    // cout << "queries:\n";
    // for (Query& q : queries) cout << q.a << " " << q.l << " " << q.r << endl;

    int pi = 0, qi = 0;
    while (pi != points.size() || qi != queries.size()) {
        ll ca = (qi == queries.size() ? INF : queries[qi].a);
        // Add points
        while (pi != points.size() && points[pi].a <= ca) {
            if (points[pi].s) {
                if (active.find(points[pi].b) != active.end()) return false;
                active.insert(points[pi].b);
            } else {
                active.erase(points[pi].b);
            }
            pi++;
        }
        // Handle queries
        ll maxR = -INF;
        while (qi != queries.size() && queries[qi].a == ca) {
            if (queries[qi].l <= maxR) return false;
            maxR = queries[qi].r;
            // Find any points within query range
            auto ptr = active.lower_bound(queries[qi].l);
            if (ptr != active.end() && *ptr <= queries[qi].r) return false;
            qi++;
        }
    }
    
    // All checks passed
    return true;
}

// Only checks if segment M intersects with any other segments before
struct Segment {
    ll a, l, r;
    bool h;
    Segment(ll a, ll l, ll r, bool h) : a(a), l(l), r(r), h(h) {}
};
vector<Segment> segments;
ll endx, endy;

void genSegs(int M) {
    segments.reserve(M);
    segments.emplace_back(0, 0, 0, true);
    ll cx = 0, cy = 0;
    for (int i = 0; i < M; i++) {
        if (D[i] == 'U') {
            segments.emplace_back(cx, cy+1, cy+X[i], false);
            cy += X[i];
        } else if (D[i] == 'D') {
            segments.emplace_back(cx, cy-X[i], cy-1, false);
            cy -= X[i];
        } else if (D[i] == 'R') {
            segments.emplace_back(cy, cx+1, cx+X[i], true);
            cx += X[i];
        } else {
            segments.emplace_back(cy, cx-X[i], cx-1, true);
            cx -= X[i];
        }
    }
    endx = cx;
    endy = cy;
}

bool check2(int M) {
    Segment seg(-1, -1, -1, -1);
    ll cx = endx, cy = endy;
    if (D[M] == 'U') {
        seg = Segment(cx, cy+1, cy+X[M], false);
        cy += X[M];
    } else if (D[M] == 'D') {
        seg = Segment(cx, cy-X[M], cy-1, false);
        cy -= X[M];
    } else if (D[M] == 'R') {
        seg = Segment(cy, cx+1, cx+X[M], true);
        cx += X[M];
    } else {
        seg = Segment(cy, cx-X[M], cx-1, true);
        cx -= X[M];
    }

    // Check all segments
    for (Segment& seg2 : segments) {
        if (seg.h == seg2.h) {
            if (seg.a == seg2.a && ((seg.l >= seg2.l && seg.l <= seg2.r) || (seg.r >= seg2.l && seg.r <= seg2.r))) return false;
        } else {
            if (seg.a >= seg2.l && seg.a <= seg2.r && seg.l <= seg2.a && seg.r >= seg2.a) return false;
        }
    }
    return true;
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> D[i] >> X[i];
    }
    points.reserve(2*N+3);
    queries.reserve(N+1);

    // Find instruction the robot stops on
    int low = 1, high = N;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }

    // cout << "stop on instruction " << low << endl;

    // Find location the robot stops on
    genSegs(low);
    ll answer = 0;
    for (int i = 0; i < low; i++) answer += X[i];
    if (low != N) {
        int lowD = 0, highD = X[low];
        while (lowD < highD) {
            int midD = (lowD + highD + 1) / 2;
            X[low] = midD;
            if (check2(low)) {
                lowD = midD;
            } else {
                highD = midD - 1;
            }
        }
        answer += lowD + 1;
        if ((D[low] == 'U' && D[low-1] == 'D') || (D[low] == 'D' && D[low-1] == 'U') ||
            (D[low] == 'R' && D[low-1] == 'L') || (D[low] == 'L' && D[low-1] == 'R')) answer--;
    }

    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}