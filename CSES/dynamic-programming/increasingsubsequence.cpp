#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
map<int, int> dp;
pair<int, int> A[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i].first;
        A[i].second = -i;
    }
    sort(A, A+N);
    rep(i, 0, N) A[i].second *= -1;

    dp[-1] = 0;
    rep(i, 0, N) {
        auto ptr = prev(dp.lower_bound(A[i].second));
        int v = ptr->second + 1;
        dp[A[i].second] = v;
        // Maintain monotonicity
        while (true) {
            ptr = dp.lower_bound(A[i].second+1);
            if (ptr == dp.end() || ptr->second > v) break;
            dp.erase(ptr);
        }
    }

    cout << prev(dp.end())->second << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}