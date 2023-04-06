#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 5e5+5;

int N;
int B[MAXN], A[MAXN];
struct Range {
    int l, r, i;
};
vector<Range> R;
set<pair<int, int>> toFill;

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> B[i];
        R.push_back({(i+1) / (B[i]+1) + 1, (B[i] == 0 ? N : (i+1) / B[i]), i});
    }
    sort(all(R), [](const Range& a, const Range& b) { return a.l < b.l; });
    int cr = 0;
    rep(i, 1, N+1) {
        while (cr != N && R[cr].l <= i) {
            toFill.insert({R[cr].r, R[cr].i});
            cr++;
        }
        // Fill the most urgent one first (smallest range)
        auto p = toFill.begin();
        A[p->second] = i;
        toFill.erase(p);
    }

    // for (auto& r : R) cout << r.l << " " << r.r << " " << r.i << "\n";
    rep(i, 0, N) cout << A[i] << " \n"[i==N-1];
    R.clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}