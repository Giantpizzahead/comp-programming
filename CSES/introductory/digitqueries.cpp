#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int Q;
ll K;

void solve(int d, ll num) {
    ll cnt = d * (num-num/10);
    if (K >= cnt) {
        K -= cnt;
        solve(d+1, num*10);
    } else {
        ll toAdd = K / d, digit = K % d;
        ll result = num/10+toAdd;
        // cout << result << ": ";
        rep(i, 0, d-1-digit) {
            result /= 10;
        }
        cout << result % 10 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> Q;
    rep(i, 0, Q) {
        cin >> K;
        K--;
        solve(1, 10);
    }
    return 0;
}