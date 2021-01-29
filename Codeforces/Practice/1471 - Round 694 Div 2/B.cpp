#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N, X;
queue<pair<int, int>> nums;

void solve() {
    cin >> N >> X;
    ll answer = 0;
    while (!nums.empty()) nums.pop();
    rep(i, 0, N) {
        int x; cin >> x;
        answer += x;
        nums.emplace(x, 1);
    }
    while (!nums.empty()) {
        auto p = nums.front();
        if (p.first % X != 0) break;
        answer += (ll) p.first * p.second;
        nums.emplace(p.first / X, p.second * X);
        nums.pop();
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