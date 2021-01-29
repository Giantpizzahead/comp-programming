#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
multiset<int> S;

void solve() {
    cin >> N;
    rep(i, 0, N) {
        int k; cin >> k;
        auto ptr = S.upper_bound(k);
        if (ptr != S.end()) S.erase(ptr);
        S.insert(k);
    }
    cout << S.size() << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}