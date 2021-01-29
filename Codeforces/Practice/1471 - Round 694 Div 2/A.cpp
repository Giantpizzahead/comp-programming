#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N, X;
ll sum;
int A[MAXN];

void solve() {
    cin >> N >> X;
    sum = 0;
    rep(i, 0, N) {
        cin >> A[i];
        sum += A[i];
    }
    cout << (sum + X - 1) / X << ' ';
    ll ans = 0;
    rep(i, 0, N) {
        ans += (A[i] + X - 1) / X;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}