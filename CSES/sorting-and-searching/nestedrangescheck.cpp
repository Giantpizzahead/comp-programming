#include <iostream>
#include <vector>
#include <algorithm>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
bool contains[MAXN], contained[MAXN];
struct Range {
    int l, r, id;
};
vector<Range> R;

void solve() {
    cin >> N;
    int x, y;
    rep(i, 0, N) {
        cin >> x >> y;
        R.push_back({x, y, i});
    }

    sort(all(R), [](const Range& a, const Range& b) {
        return make_pair(a.l, -a.r) < make_pair(b.l, -b.r);
    });
    int maxR = -1;
    for (Range& r : R) {
        if (r.r <= maxR) contained[r.id] = true;
        maxR = max(r.r, maxR); 
    }

    reverse(all(R));
    int minR = INT32_MAX;
    for (Range& r : R) {
        if (r.r >= minR) contains[r.id] = true;
        minR = min(r.r, minR);
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