#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e6+5;

int N;

// Returns whether or not # of elements <= X is enough to reach the middle number
bool check(ll X) {
    ll cnt = 0;
    rep(i, 1, N+1) {
        ll numIn = min(X / i, (ll) N);
        cnt += numIn;
    }
    return cnt > (ll) N*N/2;
}

void solve() {
    cin >> N;
    ll low = 1, high = (ll) N*N;
    while (low < high) {
        ll mid = (low+high)/2;
        if (check(mid)) {
            high = mid;
        } else {
            low = mid+1;
        }
    }
    cout << low << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}