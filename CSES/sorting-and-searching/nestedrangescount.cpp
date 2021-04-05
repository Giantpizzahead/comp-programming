#include <iostream>
#include <vector>
#include <algorithm>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5, MAXC = 4e5+10;

int N;
int contains[MAXN], contained[MAXN];
pair<int, int> R[MAXN];
struct Point {
    int x, ox, id;
    bool s;
};
vector<Point> P;

struct BIT {
    int V[MAXC] = {0};

    void upd(int i, int v) {
        for (; i < MAXC; i+=i&-i) {
            V[i] += v;
        }
    }

    int query(int i) {
        int r = 0;
        for (; i > 0; i-=i&-i) {
            r += V[i];
        }
        return r;
    }

    int query(int l, int r) {
        return query(r) - query(l-1);
    }
};

BIT bitOn, bitOff;

void solve() {
    vector<int> compX;
    cin >> N;
    rep(i, 0, N) {
        cin >> R[i].first >> R[i].second;
        compX.push_back(R[i].first);
        compX.push_back(R[i].second);
    }
    // Compress coords
    sort(all(compX));
    compX.resize(distance(compX.begin(), unique(all(compX))));
    rep(i, 0, N) {
        R[i].first = distance(compX.begin(), lower_bound(all(compX), R[i].first)) + 1;
        R[i].second = distance(compX.begin(), lower_bound(all(compX), R[i].second)) + 1;
    }
    // Make points
    rep(i, 0, N) {
        P.push_back({R[i].first, R[i].second, i, true});
        P.push_back({R[i].second, R[i].first, i, false});
    }
    sort(all(P), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.s != b.s) return a.s < b.s;
        return abs(a.x - a.ox) < abs(b.x - b.ox);
    });

    for (Point& p : P) {
        if (p.s) {
            bitOn.upd(p.x, 1);
        } else {
            bitOn.upd(p.ox, -1);
            contained[p.id] = bitOn.query(p.ox);
            contains[p.id] = bitOff.query(p.ox, p.x);
            bitOff.upd(p.ox, 1);
        }
    }

    rep(i, 0, N) cout << contains[i] << (i == N-1 ? '\n' : ' ');
    rep(i, 0, N) cout << contained[i] << (i == N-1 ? '\n' : ' ');
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}