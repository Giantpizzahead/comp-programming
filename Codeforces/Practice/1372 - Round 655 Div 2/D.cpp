#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
int A[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    ll ans = 0, curr = 0;
    rep(i, 0, N/2+1) {
        curr += A[i*2];
    }
    ans = curr;
    int oi = 0, ni = 1;
    rep(j, 0, N-1) {
        curr -= A[oi];
        curr += A[ni];
        ans = max(curr, ans);
        oi = (oi+2) % N;
        ni = (ni+2) % N;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}