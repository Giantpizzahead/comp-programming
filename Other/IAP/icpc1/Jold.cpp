// ============================== BEGIN TEMPLATE ==============================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

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
// =============================== END TEMPLATE ===============================

// =============================== KACTL ===============================

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
	ld dist() const { return sqrt((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ld> P;

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, ld eps) {
	auto a = (e-s).cross(p-s);
	ld l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

bool inHull(const vector<P>& l, P p, bool strict = false) {
	int a = 1, b = sz(l) - 1, r = !strict;
	if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
	if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
		return false;
	while (abs(a - b) > 1) {
		int c = (a + b) / 2;
		(sideOf(l[0], l[c], p) > 0 ? b : a) = c;
	}
	return sgn(l[a].cross(l[b], p)) < r;
}

typedef pair<int, int> pii;
typedef vector<int> vi;

struct PushRelabel {
	struct Edge {
		int dest, back;
		ll f, c;
	};
	vector<vector<Edge>> g;
	vector<ll> ec;
	vector<Edge*> cur;
	vector<vi> hs; vi H;
	PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

	void addEdge(int s, int t, ll cap, ll rcap=0) {
		if (s == t) return;
		g[s].push_back({t, sz(g[t]), 0, cap});
		g[t].push_back({s, sz(g[s])-1, 0, rcap});
        // debug(s << " " << t << " " << cap << endl);
	}

	void addFlow(Edge& e, ll f) {
		Edge &back = g[e.dest][e.back];
		if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
		e.f += f; e.c -= f; ec[e.dest] += f;
		back.f -= f; back.c += f; ec[back.dest] -= f;
	}
	ll calc(int s, int t) {
		int v = sz(g); H[s] = v; ec[t] = 1;
		vi co(2*v); co[0] = v-1;
		rep(i,0,v) cur[i] = g[i].data();
		for (Edge& e : g[s]) addFlow(e, e.c);

		for (int hi = 0;;) {
			while (hs[hi].empty()) if (!hi--) return -ec[s];
			int u = hs[hi].back(); hs[hi].pop_back();
			while (ec[u] > 0)  // discharge u
				if (cur[u] == g[u].data() + sz(g[u])) {
					H[u] = 1e9;
					for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest]+1)
						H[u] = H[e.dest]+1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] && hi < v)
						rep(i,0,v) if (hi < H[i] && H[i] < v)
							--co[H[i]], H[i] = v + 1;
					hi = H[u];
				} else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
					addFlow(*cur[u], min(ec[u], cur[u]->c));
				else ++cur[u];
		}
	}
	bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

// =============================== KACTL ===============================

int N, W, M;
vector<vector<int>> adj;
vector<P> hull;
struct Fish {
    int x, y, r;
};
vector<Fish> fish;

const int INF = 1e9;
const ld SMALL_CHANGE = 1e-9;
const ld EPSILON = 1e-14;
const ld TERNARY_EPS = 1e-12;

ld findHorLength(vector<P>& newHull, ld y, ld minX, ld maxX) {
    // Find the leftmost point
    ld lowX = minX, highX = maxX;
    while (highX-lowX > EPSILON) {
        ld midX = (lowX + highX) / 2;
        if (inHull(newHull, P(midX, y))) highX = midX;
        else lowX = midX;
    }
    ld leftX = (lowX + highX) / 2;
    // Find the rightmost point
    lowX = minX, highX = maxX;
    while (highX-lowX > EPSILON) {
        ld midX = (lowX + highX) / 2;
        if (inHull(newHull, P(midX, y))) lowX = midX;
        else highX = midX;
    }
    ld rightX = (lowX + highX) / 2;
    // Answer
    return rightX - leftX;
}

void solve() {
    cin >> N >> W;
    rep(i, 0, N) {
        int x, y; cin >> x >> y;
        hull.push_back(P(x, y));
    }
    cin >> M;
    rep(i, 0, M) {
        int x, y, r; cin >> x >> y >> r;
        fish.push_back({x, y, r});
    }
    // Special fish for the edges
    fish.push_back({0, -1, -1});
    fish.push_back({W, -1, -1});
    M += 2;

    // Generate graph
    // Our way of checking if the polygon "fits" between the circles is wrong, need to rethink it... :/
    adj = vector<vector<int>>(M, vector<int>());
    rep(i, 0, M) {
        rep(j, i+1, M) {
            if (fish[i].r == -1 && fish[j].r == -1) continue;
            bool edgeIsJ = (fish[j].r == -1);
            // Rotate the hull
            ld angle;
            if (!edgeIsJ) angle = atan2(fish[j].y - fish[i].y, fish[j].x - fish[i].x);
            else angle = atan2(0, 1);
            vector<P> newHull;
            rep(k, 0, N) newHull.push_back(hull[k].rotate(-angle));
            dumpVars(newHull);
            // Find min and max coordinates
            ld minX = INF, maxX = -INF, minY = INF, maxY = -INF;
            rep(k, 0, N) {
                minX = min(newHull[k].x, minX);
                maxX = max(newHull[k].x, maxX);
                minY = min(newHull[k].y, minY);
                maxY = max(newHull[k].y, maxY);
            }
            // Find y coordinate with longest line length in the hull
            // Use a form of ternary search
            ld lowY = minY, highY = maxY;
            while (highY-lowY > TERNARY_EPS*3) {
                ld midY = (lowY + highY) / 2;
                ld lenBelow = findHorLength(newHull, midY-TERNARY_EPS, minX, maxX);
                ld lenAbove = findHorLength(newHull, midY+TERNARY_EPS, minX, maxX);
                if (lenBelow < lenAbove) lowY = midY-TERNARY_EPS;
                else highY = midY+TERNARY_EPS;
            }
            ld lineLen = findHorLength(newHull, (lowY+highY)/2, minX, maxX);
            // Determine if this edge exists in the graph
            ld openDist;
            if (!edgeIsJ) {
                openDist = hypot(fish[j].x - fish[i].x, fish[j].y - fish[i].y);
                openDist -= fish[i].r + fish[j].r;
            } else {
                openDist = abs(fish[j].x - fish[i].x);
                openDist -= fish[i].r;
            }
            debug("(" << i << ", " << j << "): ");
            dumpVars(lineLen, openDist);
            if (lineLen - SMALL_CHANGE > openDist) {
                // Bob is blocked by this
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    dumpVars(adj);

    // Calculate min cut by constructing a flow graph
    PushRelabel flow = PushRelabel(2*M-2);
    rep(n, 0, M-2) flow.addEdge(n, M+n, 1);
    rep(n, 0, M) {
        for (int e : adj[n]) {
            flow.addEdge((n >= M-2 ? n : M+n), e, INF);
            flow.addEdge((e >= M-2 ? e : M+e), n, INF);
        }
    }
    ll ans = flow.calc(M-2, M-1);
    cout << ans << '\n';
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
