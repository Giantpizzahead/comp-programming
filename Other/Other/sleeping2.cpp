#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 1e5+5;

int N, M;
ll aSum;
ll A[MAXN], preA[MAXN], Q[MAXN], res[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    cin >> M;
    rep(i, 0, M) cin >> Q[i];

    aSum = 0;
    rep(i, 0, N) aSum += A[i];
    preA[0] = A[0];
    rep(i, 1, N) preA[i] = preA[i-1] + A[i];

    rep(i, 0, M) {
        ll q = Q[i];
        if (aSum % q != 0) {
            res[i] = -1;
            continue;
        }
        // Answer = Below - 2 * (# prefixes divisible by q)
        ll ans = aSum / q + N;
        rep(j, 0, N) {
            if (preA[j] % q == 0) ans -= 2;
        }
        res[i] = ans;
    }

    rep(i, 0, M) cout << res[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}