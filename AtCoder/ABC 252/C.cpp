#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 105;

int N;
string S[MAXN];
bool on[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> S[i];
    int ans = 1e9;
    rep(d, 0, 10) {
        int curr = 0;
        rep(i, 0, N) on[i] = false;
        while (true) {
            rep(i, 0, N) {
                if (!on[i] && S[i][curr % 10]-'0' == d) {
                    on[i] = true;
                    break;
                }
            }
            bool allOn = true;
            rep(i, 0, N) if (!on[i]) allOn = false;
            if (allOn) break;
            curr++;
        }
        ans = min(curr, ans);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}