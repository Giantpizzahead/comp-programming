#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N[3];
vi nums[3], mins;
ll S[3];

void solve() {
    cin >> N[0] >> N[1] >> N[2];
    rep(i, 0, 3) {
        rep(j, 0, N[i]) {
            int x;
            cin >> x;
            S[i] += x;
            nums[i].push_back(x);
        }
        sort(all(nums[i]));
        mins.push_back(nums[i][0]);
    }
    sort(all(mins));
    ll ans = S[0] + S[1] + S[2] - mins[0] * 2 - mins[1] * 2;
    rep(i, 0, 3) {
        ans = max(S[0] + S[1] + S[2] - 2 * S[i], ans);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}