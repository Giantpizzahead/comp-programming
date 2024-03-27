/*
https://szkopul.edu.pl/problemset/problem/iYVwsAcHHCRZzAtQh0QFKbsu/site/?key=statement

Solution: Convex hull trick.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 5e5+5;

int N;
int H[MAXN], ans[MAXN];
double sqrtCache[MAXN];

struct Trans {
    int h, j;
    int prevOvertakeI;

    double eval(int i) const {
        return h + sqrtCache[i-j];
    }

    // Returns the first i at which this transition overtakes the other one.
    int calcOvertake(const Trans& o, int currI) const {
        int low = currI, high = N;
        while (low < high) {
            int mid = (low + high) >> 1;
            if (eval(mid) >= o.eval(mid)) high = mid;
            else low = mid + 1;
        }
        return low;
    }
};

deque<Trans> hull;

// Assumes t starts later than everything else in the hull.
void addTrans(Trans t, int currI) {
    // Remove outdated from back
    int overtake = -1;
    while (!hull.empty()) {
        auto ptr = prev(hull.end());
        overtake = t.calcOvertake(*ptr, currI);
        if (overtake <= max(currI, ptr->prevOvertakeI)) hull.pop_back();
        else break;
    }
    // Insert new trans
    t.prevOvertakeI = overtake;
    hull.push_back(t);
}

// Gets the maximum trans value.
int getTrans(int currI) {
    if (hull.empty()) return 0;
    // Remove outdated from front
    if (sz(hull) > 1 && next(hull.begin())->prevOvertakeI == currI) hull.pop_front();
    // Return result;
    return ceil(hull.begin()->eval(currI));
}

void sweep() {
    rep(i, 0, N) {
        ans[i] = max(getTrans(i) - H[i], ans[i]);
        addTrans({H[i], i, -1}, i);
        // cout << "at i = " << i << ": ";
        // for (auto& t : hull) cout << "(" << t.h << ", " << t.j << ") ";
        // cout << endl;
    }
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> H[i];
    rep(i, 0, N) sqrtCache[i] = sqrt(i);

    // Solve in both directions
    sweep();
    hull.clear();
    reverse(H, H+N);
    reverse(ans, ans+N);
    sweep();
    reverse(ans, ans+N);
    rep(i, 0, N) cout << ans[i] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
