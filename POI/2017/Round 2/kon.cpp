/*
Solution: Split the queries into light and heavy ones (d is small or large). Do these types of queries differently to
simulate them efficiently.
Runtime: O(N * sqrt(N))
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int SQRT = 100;
const int MAXN = 1e5+5;

int N, K;
int loc[MAXN][SQRT];
int ans[MAXN];

void solve() {
    cin >> N >> K;
    rep(i, 0, K) {
        int a, l, d; cin >> a >> l >> d;
        a--;
        if (d >= SQRT) {
            rep(j, 0, l) {
                ans[a]++;
                a += d;
            }
        } else {
            loc[a][d]++;
            int b = a+l*d;
            if (b < N) loc[b][d]--;
        }
    }
    rep(d, 1, SQRT) {
        rep(i, 0, d) {
            int j = i;
            while (j < N) {
                loc[j][d] += (j-d < 0 ? 0 : loc[j-d][d]);
                ans[j] += loc[j][d];
                j += d;
            }
        }
    }
    rep(i, 0, N) cout << ans[i] << " \n"[i==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}