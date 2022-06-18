#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;

int N, S;
int A[MAXN];

void solve() {
    cin >> N >> S;
    rep(i, 0, N) cin >> A[i];
    // Sliding window
    int ans = -1;
    int li = 0, cs = 0;
    rep(ri, 0, N) {
        cs += A[ri];
        while (cs > S) {
            cs -= A[li];
            li++;
        }
        if (cs == S) ans = max(ri-li+1, ans);
    }
    cout << (ans == -1 ? -1 : N - ans) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}