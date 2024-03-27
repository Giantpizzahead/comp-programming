#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

int N;
vector<int> ans;

void solve() {
    cin >> N;
    rep(i, 0, N/2) {
        ans.push_back(N/2+(i+1));
        ans.push_back(i+1);
    }
    if (N % 2 == 1) ans.push_back(N);
    rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i==sz(ans)-1];
    ans.clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    // int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
