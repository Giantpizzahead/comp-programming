#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
#define x first
#define y second
using namespace std;
using ll = long long;
using vi = vector<int>;

pair<int, int> P[4];
vector<pair<int, int>> temp;

pair<int, int> getMaxes(int y1, int y2, int y3, int y4) {
    temp.clear();
    temp.emplace_back(y1, 1);
    temp.emplace_back(y2, 2);
    temp.emplace_back(y3, 3);
    temp.emplace_back(y4, 4);
    sort(all(temp));
    int ymin, ymax;
    if (temp[0].second % 2 == 1 && temp[1].second % 2 == 1) {
        ymin = 0;
        if (temp[0].second / 2 == temp[2].second / 2) {
            ymax = temp[3].first - temp[0].first;
        } else {
            ymax = max(temp[3].first - temp[1].first, temp[2].first - temp[0].first);
        }
    } else {
        ymin = temp[2].first - temp[1].first;
        ymax = temp[3].first - temp[0].first;
    }
    return {ymin, ymax};
}

ll makeSquare() {
    int y1 = min(P[0].y, P[1].y), y2 = max(P[0].y, P[1].y);
    int x1 = min(P[1].x, P[2].x), x2 = max(P[1].x, P[2].x);
    int y3 = min(P[2].y, P[3].y), y4 = max(P[2].y, P[3].y);
    int x3 = min(P[3].x, P[0].x), x4 = max(P[3].x, P[0].x);
    pair<int, int> p = getMaxes(y1, y2, y3, y4);
    int ymin = p.first, ymax = p.second;
    p = getMaxes(x1, x2, x3, x4);
    int xmin = p.first, xmax = p.second;
    // cout << ymin << " " << xmin << " " << ymax << " " << xmax << endl;

    // Optimal cost
    ll bestCost = (ll) y2-y1 + y4-y3 + x2-x1 + x4-x3;
    // Can a square be formed?
    if (ymin > xmin) {
        swap(ymin, xmin);
        swap(ymax, xmax);
    }
    if (ymax >= xmin) return bestCost;  // Yes!
    // Grow square by as little as possible
    int diff = xmin - ymax;
    return bestCost + 2 * diff;
}

void solve() {
    rep(i, 0, 4) cin >> P[i].x >> P[i].y;
    ll answer = 1e18;
    rep(i, 0, 24) {
        answer = min(makeSquare(), answer);
        next_permutation(P, P+4);
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}