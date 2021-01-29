#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
int K[MAXN];
set<int> active;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> K[i];
    int ans = 0;
    int l = 0;
    rep(r, 0, N) {
        while (active.count(K[r]) != 0) {
            active.erase(K[l]);
            l++;
        }
        active.insert(K[r]);
        ans = max(r-l+1, ans);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}