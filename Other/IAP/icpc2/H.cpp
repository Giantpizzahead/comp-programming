/**
 * Problem link:
 * https://codeforces.com/group/hosRkEuluH/contest/423073/problem/H
 * 
 * Solution:
 * Sort by angle, and sweep. Each warehouse is active in a contiguous range.
 * When a new warehouse becomes visible, quickly determine the two points that the goggles
 * intersect the convex shape at to find the area.
 * Many edge cases to worry about... might be messy to implement.
 */

// ============================== BEGIN TEMPLATE ==============================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#ifdef LOCAL
    #include "pprint.hpp"
#else
    #define debug(...) 42
    #define dumpVars(...) 42
#endif

void solve();

int runTests(bool multiple_tests) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (multiple_tests) {
        int T; cin >> T;
        rep(i, 0, T) solve();
    } else solve();
    return 0;
}

// KACTL

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
	auto a = (e-s).cross(p-s);
	double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}

#define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
template <class P> int extrVertex(vector<P>& poly, P dir) {
	int n = sz(poly), lo = 0, hi = n;
	if (extr(0)) return 0;
	while (lo + 1 < hi) {
		int m = (lo + hi) / 2;
		if (extr(m)) return m;
		int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
		(ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
	}
	return lo;
}

#define cmpL(i) sgn(a.cross(poly[i], b))
template <class P>
array<int, 2> lineHull(P a, P b, vector<P>& poly) {
	int endA = extrVertex(poly, (a - b).perp());
	int endB = extrVertex(poly, (b - a).perp());
	if (cmpL(endA) < 0 || cmpL(endB) > 0)
		return {-1, -1};
	array<int, 2> res;
	rep(i,0,2) {
		int lo = endB, hi = endA, n = sz(poly);
		while ((lo + 1) % n != hi) {
			int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
			(cmpL(m) == cmpL(endB) ? lo : hi) = m;
		}
		res[i] = (lo + !cmpL(hi)) % n;
		swap(endA, endB);
	}
	if (res[0] == res[1]) return {res[0], -1};
	if (!cmpL(res[0]) && !cmpL(res[1]))
		switch ((res[0] - res[1] + sz(poly) + 1) % sz(poly)) {
			case 0: return {res[0], res[0]};
			case 2: return {res[1], res[1]};
		}
	return res;
}

typedef Point<ll> Pl;
typedef Point<double> P;
vector<Pl> convexHull(vector<Pl> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<Pl> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (Pl p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
	return a;
}

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {all(s)};
}

// =============================== END TEMPLATE ===============================

#define M_PI       3.14159265358979323846
double BIG = 1e6;
double EPS = 1e-12;

int N;
P origin;
struct Warehouse {
    int c;
    vector<P> hull;
    bool countArea;
};
vector<Warehouse> W;
vector<Warehouse> toSweep;

struct Loc {
    int id, w, i;
    double angle;
    bool countArea;
};
vector<Loc> locs;
double angle;
map<pair<int, int>, bool> distCompCache;

P getIntersection(vector<P>& hull, int i, P& q1, P& q2) {
    vector<P> p = segInter(hull[i], hull[(i+1)%sz(hull)], q1, q2);
    assert(sz(p) == 1);
    return p[0];
}

void solve() {
    cin >> N;
    W.resize(N);
    origin = P(0, 0);
    rep(i, 0, N) {
        vector<Pl> points;
        int C; cin >> C;
        rep(j, 0, C) {
            int x, y; cin >> x >> y;
            points.push_back(Pl(x, y));
        }
        vector<Pl> hull = convexHull(points);
        W[i].hull.resize(sz(hull));
        rep(j, 0, sz(hull)) {
            W[i].hull[j] = P(hull[j].x, hull[j].y);
        }

        W[i].c = sz(W[i].hull);
    }

    // Push polygons away from the center to (hopefully) avoid edge cases
    // rep(i, 0, N) {
    //     P delta = P(W[i].center.x / W[i].dist * EPS, W[i].center.y / W[i].dist * EPS);
    //     rep(j, 0, W[i].c) {
    //         W[i].hull[j] = W[i].hull[j] + delta;
    //     }
    // }
    
    // Prepare sweeping
    rep(i, 0, N) {
        // Does this hull cross the x-axis (angle edge case)?
        double minAngle = BIG, maxAngle = -BIG;
        rep(j, 0, W[i].c) {
            minAngle = min(W[i].hull[j].angle(), minAngle);
            maxAngle = max(W[i].hull[j].angle(), maxAngle);
        }
        bool crossesX = (maxAngle - minAngle > M_PI);
        // Add sweep points
        rep(j, 0, W[i].c) {
            angle = atan2(W[i].hull[j].y, W[i].hull[j].x);
            dumpVars(angle);
            if (crossesX && angle < 0) angle += 2*M_PI;
            locs.push_back({i, i, j, angle - 2*M_PI, false});
            locs.push_back({i+N, i, j, angle, true});
            locs.push_back({i+2*N, i, j, angle + 2*M_PI, false});
        }
        dumpVars(i, crossesX);
    }
    sort(all(locs), [](const Loc& a, const Loc& b) { return a.angle < b.angle; });

    // Sweep
    angle = -1;
    double ans = 0;
    struct Active {
        int id, w, pointsLeft;
        bool countArea;

        double getDist() const {
            // Get current polygon location
            P ray1 = P(cos(angle+EPS)*BIG, sin(angle+EPS)*BIG);
            array<int, 2> res1 = lineHull(origin, ray1, W[w].hull);
            int segI = res1[0];
            P& ray = ray1;
            if (res1[0] == -1) {
                P ray2 = P(cos(angle-EPS)*BIG, sin(angle-EPS)*BIG);
                array<int, 2> res2 = lineHull(origin, ray2, W[w].hull);
                assert(res2[0] != -1);
                segI = res2[0];
                ray = ray2;
            }
            P p1 = getIntersection(W[w].hull, segI, origin, ray);
            return hypot(p1.x, p1.y);
        }

        bool operator<(const Active& o) const {
            if (w == o.w) return false;
            int a = min(w, o.w), b = max(w, o.w);
            // Find in cache
            auto ptr = distCompCache.find({a, b});
            if (ptr != distCompCache.end()) {
                bool res = ptr->second;
                if (w > o.w) res = !res;
                return res;
            }
            // Do the calculation and save result to cache
            bool rawRes = getDist() < o.getDist();
            bool res = rawRes;
            if (w > o.w) res = !res;
            distCompCache[{a, b}] = res;
            return rawRes;
        }
    };
    map<int, Active> wToActive;
    set<Active> active;
    double lastAngle = -1;
    for (Loc& l : locs) {
        int id = l.id, w = l.w; //, i = l.i;
        angle = l.angle;
        bool countArea = l.countArea;

        // Update area as needed
        if (!active.empty()) {
            // Get the closest polygon
            Warehouse& warehouse = W[begin(active)->w];

            // Does this contribute to the area?
            if (countArea && abs(angle - lastAngle) > EPS) {
                debug("adding area from " << begin(active)->w << "\n");
                // Count area between last and current update
                P lastRay = P(cos(lastAngle+EPS)*BIG, sin(lastAngle+EPS)*BIG);
                array<int, 2> lastRes = lineHull(origin, lastRay, warehouse.hull);
                dumpVars(lastRes);
                P p1 = getIntersection(warehouse.hull, lastRes[0], origin, lastRay);
                P p2 = getIntersection(warehouse.hull, lastRes[1], origin, lastRay);
                if (p2.dist() < p1.dist()) swap(p1, p2);

                P currRay = P(cos(angle-EPS)*BIG, sin(angle-EPS)*BIG);
                array<int, 2> currRes = lineHull(origin, currRay, warehouse.hull);
                dumpVars(currRes);
                P q1 = getIntersection(warehouse.hull, currRes[0], origin, currRay);
                P q2 = getIntersection(warehouse.hull, currRes[1], origin, currRay);
                if (q2.dist() > q1.dist()) swap(q1, q2);

                dumpVars(lastAngle, angle, lastRes, currRes);

                vector<P> poly = {p1, p2, q1, q2};
                double area = abs(polygonArea2(poly)) / 2;
                debug("area added: ");
                dumpVars(area, p1, p2, q1, q2);
                ans += area;
            }
        }

        // Handle this location
        // dumpVars(id, w, angle, countArea);
        Warehouse& warehouse = W[w];
        if (!wToActive.count(w)) {
            // Activate new warehouse
            Active curr = {id, w, warehouse.c-1, countArea};
            active.insert(curr);
            wToActive[w] = curr;
            debug("inserted " << w << "\n");
        } else {
            Active& curr = wToActive[w];
            // End of polygon?
            if (--curr.pointsLeft == 0) {
                active.erase(curr);
                wToActive.erase(w);
                debug("erased " << w << "\n");
            }
        }
        lastAngle = angle;
    }
    rep(i, 0, N) {
        dumpVars(W[i].hull);
    }

    cout << fixed << setprecision(9) << ans << "\n";
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
