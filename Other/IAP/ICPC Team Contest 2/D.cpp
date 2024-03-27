#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int maxn = 1005;

template<typename T>
struct point {
    T x, y;
    point() {}
    point(T x, T y) : x(x), y(y) {}
};
double mem[maxn];
bool vis[maxn];
point <int> p[maxn];
int n;
int v_w, v_c;
vector <pair <int, double>> g[maxn]; 
const double INF = 1e16;

double get_X(point<int> a, point<int> b, int y) {
    if(a.y == b.y) {
        assert(y == a.y);
        return min(a.x, b.x);
    }
    double m = double(b.y - a.y) / (b.x - a.x);
    double c = a.y - m * a.x;
    return (y - c) / m;
} 
double get_X_rev(point<int> a, point<int> b, int y) {
    if(a.y == b.y) {
        assert(y == a.y);
        return max(a.x, b.x);
    }
    double m = double(b.y - a.y) / (b.x - a.x);
    double c = a.y - m * a.x;
    return (y - c) / m;
} 

double dist(point<double>a, point<double>b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

point<double> to_double(point<int> p) {
    return point<double>(p.x, p.y);
}

pair <int, double> hor(int l) {
    int y = p[l].y;
    for(int i = l + 1; i < n; i++) {
        if(p[i].y <= y) {
            double x = get_X(p[i-1], p[i], y);
            point<double> interx (x, y);
            double hor_d = dist(to_double(p[l]), interx);
            double nor_d = dist(interx, to_double(p[i])); 
            return make_pair(i, hor_d / v_c + nor_d / v_w);
        } 
    }
    return make_pair(-1, -1);
}
pair <int, double> hor_rev(int l) {
    int y = p[l].y;
    for(int i = l - 1; i >= 0; i--) {
        if(p[i].y <= y) {
            double x = get_X_rev(p[i], p[i+1], y);
            point<double> interx (x, y);
            double hor_d = dist(to_double(p[l]), interx);
            double nor_d = dist(interx, to_double(p[i])); 
            return make_pair(i, hor_d / v_c + nor_d / v_w);
        } 
    }
    return make_pair(-1, -1);
}

double dp(int i) {
    if(i == n-1) {
        return 0;
    }
    if(vis[i]) {
        return mem[i];
    }
    vis[i] = true;
    double ans = INF;
    for(auto x : g[i]) {
        ans = min(ans, x.second + dp(x.first));
    }
    return mem[i] = ans;
}

void solve() {
    // cout << dist(point<double>(50, 50), point<double>(100, 100)) << endl;
    cin >> n;
    cin >> v_w >> v_c;
    for(int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
        g[i].clear();
    }
    for(int i = 0; i < n; i++) {
        auto r = hor(i);
        auto l = hor_rev(i);
        if(l.first != -1) g[l.first].emplace_back(i, l.second);
        if(r.first != -1) g[i].emplace_back(r.first, r.second);
        if(i < n-1) {
            g[i].emplace_back(i+1, dist(to_double(p[i]), to_double(p[i+1])) / v_w);
        } 
    }
    memset(vis, false, sizeof(vis));
    cout << setprecision(10) << fixed << dp(0) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
