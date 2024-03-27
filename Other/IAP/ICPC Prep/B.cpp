/*
Solution: Geometry! Yay.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const double PI = acos(-1);

template<class T> struct Point3D {
    typedef Point3D P;
    typedef const P& R;
    T x, y, z;
    explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
    P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
    P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
    P operator*(T d) const { return P(x*d, y*d, z*d); }
    P operator/(T d) const { return P(x/d, y/d, z/d); }
    T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
    P cross(R p) const {
        return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
    }
    // In [-pi, pi]
    double phi() const { return atan2(y, x); }
    // In [0, pi]
    double theta() const { return atan2(sqrt(x*x+y*y), z); }
    T dist2() const { return x*x+y*y+z*z; }
    double dist() const { return sqrt((double)dist2()); }
    P unit() const { return *this/(T)dist(); }  // Makes dist() = 1
    // Returns unit vector normal to *this and p
    P normal(P p) const { return cross(p).unit(); }
    // Returns point rotated "angle" radians ccw around axis
    P rotate(double angle, P axis) const {
        double s = sin(angle), c = cos(angle); P u = axis.unit();
        return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
    }
};

const int MAXN = 25;
int N;
double R;
typedef Point3D<double> Point;
Point A[MAXN];

void printPoint(Point p) {
    cout << "(" << p.x << ", " << p.y << ", " << p.z << ")" << endl;
}

// Gets the tangent plane to the sphere going through point P.
// Returns the normal vector of the tangent plane.
// It's literally the point itself...
Point getTangentPlane(Point p) {
    return p;
}

// Gets any unit vector on the plane, with assumption that x != 0 or y != 0.
Point getPlaneUnitVector(Point p) {
    double z = 1;
    double x, y;
    if (p.x == 0) {
        x = 1;
        y = (-p.z - p.x) / p.y;
    } else {
        y = 1;
        x = (-p.z - p.y) / p.x;
    }
    return Point(x, y, z).unit();
}

// Gets a vector on the plane, in some direction (determined by angle).
Point getVectorInDir(pair<Point, Point>& basis, double angle) {
    double u1 = cos(angle);
    double u2 = sin(angle);
    return basis.first * u1 + basis.second * u2;
}

// Starting from curr, walk on the sphere to angle radians away in direction dir.
Point walkInDir(Point curr, Point dir, double angle) {
    double x = curr.x * cos(angle) + dir.x * sin(angle);
    double y = curr.y * cos(angle) + dir.y * sin(angle);
    double z = curr.z * cos(angle) + dir.z * sin(angle);
    return Point(x, y, z);
}

// Gets the distance on the sphere between a and b.
double sphericalDist(Point a, Point b) {
    double d = (b-a).dist();
    return 2*asin(d/2);
}

struct Event {
    double t;
    bool s;

    bool operator<(const Event& o) const {
        if (abs(t-o.t) < 1e-9) return s > o.s;
        else return t < o.t;
    }
};

bool checkBomb(int K) {
    // Get unit vectors for tangent plane
    Point plane = A[K];
    // double dPlane = A[K].dot(A[K]);
    pair<Point, Point> basis;
    basis.first = getPlaneUnitVector(plane);
    basis.second = plane.normal(basis.first);
    cout << "basis:" << endl;
    printPoint(basis.first);
    printPoint(basis.second);

    // For each bomb, find range where K is within that bomb's explosion
    vector<Event> events;
    rep(i, 0, N) {
        if (i == K) continue;
        if (sphericalDist(A[K], A[i]) >= 2*R) continue;  // No or one intersection

        // Find direction to other bomb
        Point directPath = A[i] - A[K];
        double distToPlane = plane.dot(directPath); // - dPlane;
        Point dirToBomb = (directPath - (plane * distToPlane)).unit();
        // printPoint(dirToBomb);
        assert(abs(dirToBomb.dot(plane)) < 1e-8);

        // Use this as the basis; now distance on both sides is the same!
        basis.first = dirToBomb;
        basis.second = plane.normal(basis.first);

        // Find location on the first half
        double low = 0, high = PI;
        while (high-low > 1e-9) {
            double mid = (low+high)/2;
            Point dir = walkInDir(plane, getVectorInDir(basis, mid), R);
            // assert(abs(sphericalDist(A[K], dir)-R) < 1e-9);
            if ((sphericalDist(A[i], dir) <= R)) high = mid;
            else low = mid;
        }
        double firstTime = (low+high)/2;
        double lastTime = 2*PI-firstTime;

        // Record the interval
        events.push_back({0, true});
        events.push_back({firstTime, false});
        events.push_back({2*PI-firstTime, true});
        cout << "For " << K << " against " << i << ": " << firstTime << " " << lastTime << endl;
    }
    events.push_back({2*PI, false});

    // Check if the whole circle is covered
    int numActive = 0;
    sort(all(events));
    for (Event& e : events) {
        if (numActive == 0 && abs(e.t) > 1e-9) return false;  // Not covered
        if (e.s) numActive++;
        else numActive--;
    }
    // All covered
    return true;
}

bool check() {
    cout << "check " << R << endl;
    // Check that each bomb is completely covered
    rep(i, 0, N) if (!checkBomb(i)) return false;
    // All covered
    return true;
}

void solve() {
    // Point plane = Point(1, 0, 0);
    // Point unit1 = getPlaneUnitVector(plane);
    // Point unit2 = plane.normal(unit1);
    // printPoint(unit1);
    // printPoint(unit2);
    // Point dir = getVectorInDir({unit1, unit2}, 3);
    // printPoint(dir);
    // printPoint(walkInDir(plane, dir, 1));

    cin >> N;
    rep(i, 0, N) {
        double f, t; cin >> t >> f;
        f = f*PI/180;
        t = t*PI/180 + PI/2;
        double x = sin(t) * cos(f);
        double y = sin(t) * sin(f);
        double z = cos(t);
        A[i] = Point(x, y, z);
    }
    rep(i, 0, N) cout << A[i].x << " " << A[i].y << " " << A[i].z << endl;

    // Try bomb radii
    double low = 0, high = PI;
    while (high-low > 1e-9*1000000) {
        R = (low + high) / 2;
        if (check()) high = R;
        else low = R;
    }
    cout << fixed << setprecision(9) << (low+high)/2 << "\n";

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
