#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

bool aboutEqual(double a, double b) {
    return abs(a-b) < 1e-8;
}

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const {
        if (!aboutEqual(x, p.x)) return x < p.x;
        else return y < p.y;
        // return tie(x, y) < tie(p.x, p.y);
    }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double) dist2()); }
    double angle() const { return atan2(y, x); }
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a)); 
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
typedef Point<double> PointD;

int N;
vector<PointD> A, B;

PointD findCentroid(vector<PointD>& points) {
    double sumX = 0, sumY = 0;
    for (PointD& p : points) {
        sumX += p.x, sumY += p.y;
    }
    sumX /= sz(points), sumY /= sz(points);
    return PointD(sumX, sumY);
}

const double INF = 1e9;
double ans;

// B[K] matches with A[0]
void tryRotation(int K) {
    // cout << A[0].dot(B[K]) << " " << (A[0].dist() * B[K].dist()) << endl;
    double arg = A[0].dot(B[K]) / (A[0].dist() * B[K].dist());
    arg = min(arg, 1.0); arg = max(arg, -1.0);
    double angle = acos(arg);
    bool isCCW = (A[0].cross(B[K]) > 0);
    if (isCCW) angle = -angle;
    
    // Rotate everything
    // cout << "trying rotation of " << angle << endl;
    vector<PointD> newB;
    rep(i, 0, N) {
        newB.push_back(B[i].rotate(angle));
        // cout << newB[i] << endl;
    }
    // Sort and check if the pairs match
    rep(i, 0, N) newB.push_back(A[i]);
    sort(all(newB));
    bool works = true;
    rep(i, 0, N) {
        PointD& p1 = newB[2*i], p2 = newB[2*i+1];
        // cout << p1 << " " << p2 << endl;
        if (!aboutEqual((p1-p2).dist(), 0)) {
            works = false;
            break;
        }
    }

    if (works) {
        // cout << "angle " << angle << " works";
        ans = min(abs(angle), ans);
    }
}

void solve() {
    cin >> N;
    cout << fixed << setprecision(9);
    if (N == 1) {
        cout << "0\n";
        return;
    }
    rep(i, 0, N) {
        PointD p; cin >> p.x >> p.y;
        A.push_back(p);
    }
    rep(i, 0, N) {
        PointD p; cin >> p.x >> p.y;
        B.push_back(p);
    }

    // Find centroid
    PointD centA = findCentroid(A);
    PointD centB = findCentroid(B);
    // Offset both sets of points
    rep(i, 0, N) {
        A[i] = A[i] - centA;
        B[i] = B[i] - centB;
    }

    // Remove zero point if it exists
    PointD zero = PointD(0, 0);
    rep(i, 0, N) {
        if (aboutEqual((A[i] - zero).dist(), 0)) {
            A.erase(A.begin()+i);
            break;
        }
    }
    rep(i, 0, N) {
        if (aboutEqual((B[i] - zero).dist(), 0)) {
            B.erase(B.begin()+i);
            break;
        }
    }

    // rep(i, 0, N) cout << A[i] << endl;
    // cout << endl;
    // rep(i, 0, N) cout << B[i] << endl;
    // cout << centA << " " << centB << endl;

    // Fix an arbitrary point P1 = A[0], find points in B with same distance
    ans = INF;
    double targetDist = A[0].dist();
    rep(i, 0, N) {
        if (aboutEqual(B[i].dist(), targetDist)) {
            // Candidate
            // cout << B[i] << " is a candidate" << endl;
            tryRotation(i);
        }
    }
    
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
