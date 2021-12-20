#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

ll fact(int n) {
    ll r = 1;
    rep(i, 1, n+1) r *= i;
    return r;
}

ll nCk(int n, int k) {
    assert(k >= 0 && k <= n);
    return fact(n) / fact(n-k) / fact(k);
}

const int D = 18;
const int P = 10;
const int T = 3;
vector<int> cnt(P);
ll answer = 0;
// int numStates = 0;

void dfs(int i) {
    if (i == P) {
        // Get rid of invalid states
        int numDigits = 0;
        rep(j, 0, P) numDigits += cnt[j];
        if (numDigits != D) return;
        // numStates++;
        // rep(j, 0, P) cout << cnt[j] << " \n"[j==P-1];
        // This is a valid state
        // Zeros cannot be leading, so fix first digit
        rep(j, 1, P) {
            if (cnt[j] == 0) continue;
            // Fix first digit
            cnt[j]--;
            // Add to the answer
            int num = D-1;
            ll numWays = 1;
            rep(k, 0, P) {
                if (cnt[k] == 0) continue;
                numWays *= nCk(num, cnt[k]);
                num -= cnt[k];
            }
            answer += numWays;
            // Backtrack
            cnt[j]++;
        }
    } else {
        rep(j, 0, T+1) {
            cnt[i] = j;
            dfs(i+1);
        }
    }
}

void solve() {
    dfs(0);
    cout << answer << endl;
    // cout << numStates << endl;
}

int main() {
    ios::sync_with_stdio(0);
    solve();
    return 0;
}