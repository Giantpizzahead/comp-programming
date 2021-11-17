#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 3e5+5;

int N;
ll A[MAXN];
map<ll, int> cnt;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    ll ans = 0, sum = 0;
    cnt[0]++;
    rep(i, 0, N) {
        if (i % 2 == 0) sum += A[i];
        else sum -= A[i];
        ans += cnt[sum]++;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}