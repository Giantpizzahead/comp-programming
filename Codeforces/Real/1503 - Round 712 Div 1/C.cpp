#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;
struct City {
    int a, c;
    bool operator<(const City& o) const {
        return a < o.a;
    }
};

int N;
City C[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> C[i].a >> C[i].c;
    sort(C, C+N);
    ll ans = 0;
    rep(i, 0, N) ans += C[i].c;
    int currC = C[0].c;
    rep(i, 1, N) {
        int diff = C[i].a - C[i-1].a;
        ans += max(0, -(currC - diff));
        currC = max(currC - diff, C[i].c);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}