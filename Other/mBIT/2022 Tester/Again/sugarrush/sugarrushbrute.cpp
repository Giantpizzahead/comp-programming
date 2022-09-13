/*
Naive solution for sugar rush. For testing purposes.
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
int X[MAXN];
ll ans[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> X[i];
    rep(i, 0, N) {
        int l = i, r = i, c = i;
        while (l != 0 || r != N-1) {
            if (r != N-1 && (l == 0 || X[r+1]-X[c] <= X[c]-X[l-1])) {
                ans[i] += X[r+1]-X[c];
                r++;
                c = r;
            } else {
                ans[i] += X[c]-X[l-1];
                l--;
                c = l;
            }
        }
    }
    rep(i, 0, N) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}