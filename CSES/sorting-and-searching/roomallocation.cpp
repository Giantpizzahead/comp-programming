#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, K;
int ans[MAXN];
stack<int> isOpen;
struct Point {
    int x, id;
    bool s;
};
Point P[MAXN*2];

void solve() {
    cin >> N;
    int a, b;
    rep(i, 0, N) {
        cin >> a >> b;
        P[i*2] = {a, i, true};
        P[i*2+1] = {b+1, i, false};
    }
    sort(P, P+2*N, [](const Point& a, const Point& b) {
        return make_pair(a.x, a.s) < make_pair(b.x, b.s);
    });

    K = 0;
    rep(i, 0, 2*N) {
        Point& p = P[i];
        if (p.s) {
            if (isOpen.empty()) isOpen.push(K++);
            ans[p.id] = isOpen.top(); isOpen.pop();
        } else {
            isOpen.push(ans[p.id]);
        }
    }

    cout << K << '\n';
    rep(i, 0, N) cout << ans[i]+1 << (i == N-1 ? '\n' : ' ');
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}