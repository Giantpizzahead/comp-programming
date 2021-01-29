#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

struct BIT {
    int V[MAXN];

    void upd(int i, int v) {
        i++;
        for (; i < MAXN; i += i & -i) V[i] += v;
    }

    int query(int i) {
        i++;
        int r = 0;
        for (; i > 0; i -= i & -i) r += V[i];
        return r;
    }

    int query(int l, int r) {
        int res = query(r) - query(l-1);
        // cerr << "query " << l << " " << r << " = " << res << endl;
        return res;
    }
} bit;

int N;
ll answer;
struct Point {
    int x, y;
};
Point P[MAXN];

void solve() {
    cin >> N;
    vi compX, compY;
    rep(i, 0, N) {
        cin >> P[i].x >> P[i].y;
        compX.push_back(P[i].x);
        compY.push_back(P[i].y);
    }
    sort(all(compX));
    sort(all(compY));
    compX.resize(distance(compX.begin(), unique(all(compX))));
    compY.resize(distance(compY.begin(), unique(all(compY))));
    rep(i, 0, N) {
        P[i].x = distance(compX.begin(), lower_bound(all(compX), P[i].x));
        P[i].y = distance(compY.begin(), lower_bound(all(compY), P[i].y));
    }

    // Sweep from top to bottom, ties broken by left to right
    sort(P, P+N, [](Point& a, Point& b) {
        if (a.y != b.y) return a.y > b.y;
        else return a.x < b.x;
    });
    int currY, lastX;
    for (int i = 0; i < N;) {
        currY = P[i].y;
        int j = i;
        while (j != N && P[j].y == currY) {
            Point& p = P[j];
            if (bit.query(p.x, p.x) == 0) bit.upd(p.x, 1);
            j++;
        }
        // Add all answers
        lastX = -1;
        while (i != N && P[i].y == currY) {
            Point& p = P[i];
            answer += (ll) bit.query(lastX+1, p.x) * bit.query(p.x, MAXN-2);
            lastX = p.x;
            i++;
        }
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}