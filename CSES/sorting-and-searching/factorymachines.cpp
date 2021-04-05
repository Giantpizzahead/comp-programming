#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, T;
int K[MAXN];

bool check(ll time) {
    ll currT = T;
    rep(i, 0, N) {
        currT -= time / K[i];
        if (currT <= 0) return true;  
    }
    return false;
}

void solve() {
    cin >> N >> T;
    rep(i, 0, N) cin >> K[i];
    ll low = 0, high = 1e18;
    while (low < high) {
        ll mid = (low+high)/2;
        if (check(mid)) high = mid;
        else low = mid+1;
    }
    cout << low << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}