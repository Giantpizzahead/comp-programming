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
    ll diff = 0;
    rep(i, 0, N-1) diff += abs(A[i+1] - A[i]);
    ll ans = min(diff - abs(A[1] - A[0]), diff - abs(A[N-1] - A[N-2]));
    rep(i, 1, N-1) {
        ll curr = diff - abs(A[i+1] - A[i]) - abs(A[i] - A[i-1]) + abs(A[i+1] - A[i-1]);
        ans = min(curr, ans);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}