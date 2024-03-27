#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
const int N = 10000000;
// const int maxn = N + 10;

int cnt[N];

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x] += 1;
    }
    ll ans = 0;
    ll opt = 0;
    int cntFirst = 0;
    int cntLast = 0;
    for(int i = 0; i < N/2; i++) {
        ans += abs(1LL * cnt[i] * i);
        cntFirst += cnt[i];
    }
    for(int i = N/2; i < N; i++) {
        ans += abs(1LL * cnt[i] * (N - i));
        cntLast += cnt[i];
    }
    opt = ans;
    for(int i = 0; i < N; i++) {
        int other = (i + N/2) % N;
        ans += cntLast - cnt[other];
        ans -= cntFirst - cnt[i];
        ans -= cnt[other];
        ans += cnt[i];

        cntFirst -= cnt[i];
        cntFirst += cnt[other];
        cntLast += cnt[i];
        cntLast -= cnt[other];
        opt = min(opt, ans);
    }
    cout << opt << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int T; cin >> T;
    int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
