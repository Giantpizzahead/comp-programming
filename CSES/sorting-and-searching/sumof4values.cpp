#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1000;

int N, X;
struct Pair {
    int v, a, b;
    bool operator<(const Pair& o) const {
        return make_pair(v, a*N+b) < make_pair(o.v, o.a*N+o.b);
    }
};
vector<Pair> pairs;
int A[MAXN];

void solve() {
    cin >> N >> X;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) {
        rep(j, i+1, N) {
            pairs.push_back({A[i] + A[j], i+1, j+1});
        }
    }
    sort(all(pairs));

    Pair currP;
    for (Pair& p : pairs) {
        currP.v = X - p.v;
        currP.a = p.b+1;
        currP.b = 1;
        auto ptr = lower_bound(all(pairs), currP);
        if (ptr == pairs.end() || ptr->v != currP.v) continue;
        cout << p.a << " " << p.b << " " << ptr->a << " " << ptr->b << '\n';
        return;
    }
    cout << "IMPOSSIBLE\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}