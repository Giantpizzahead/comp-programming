/*
Solution: Use DP to determine the smallest set of numbers that contains the desired integer. Fix the leftmost (biggest)
digit, then repeat. (This is a somewhat common technique for finding the kth element in a big sequence.)
dp[i][j][k] = # of numbers with i digits, a sum of j, and a remainder of k when divided by m
BC: dp[0][0][0] = 1
Trans: dp[i][j][k] =
Sum for each d from 0...9 -> dp[i-1][j-d][(k - d*10^(i-1) % m]

Runtime: O(10 * DSM + DQ), where D is the max # of digits
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 201;
const int D = 200;
const ll INF = (ll) 1e18 + 5;

int S, M, Q;
int tenMod[MAXN];
ll K;

ll dp[MAXN][MAXN][MAXN];
vector<int> digits;

ll calcState(int i, int j, int k) {
    ll res = 0;
    for (int d : digits) {
        if (j-d < 0) break;
        int oldK = (k - d * tenMod[i-1]) % M;
        if (oldK < 0) oldK += M;
        res += dp[i-1][j-d][oldK];
        if (res >= INF) break;
    }
    if (res >= INF) res = INF;
    debug << "calc " << i << " " << j << " " << k << " = " << res << endl;
    return res;
}

void solve() {
    cin >> S >> M >> Q;
    tenMod[0] = 1 % M;
    rep(i, 1, D+1) tenMod[i] = tenMod[i-1] * 10 % M;
    dp[0][0][0] = 1;
    rep(i, 0, 10) digits.push_back(i);
    rep(i, 1, D+1) {
        rep(j, 0, S+1) {
            rep(k, 0, M+1) {
                dp[i][j][k] = calcState(i, j, k);
            }
        }
    }

    rep(i, 0, Q) {
        cin >> K;
        string ans;
        // How many digits?
        int x = 1;
        while (x <= D) {
            digits.clear();
            rep(d, 1, 10) digits.push_back(d);
            ll cnt = calcState(x, S, 0);
            if (cnt >= K) break;
            K -= cnt;
            x++;
        }
        if (x == D+1) cout << "NIE\n";
        else {
            // Fill the digits
            int initX = x, currS = S, currM = 0;
            string ans;
            while (x > 0) {
                rep(d, 0, 10) {
                    if (d == 0 && x == initX) continue;  // 1st digit cannot be 0
                    digits.clear();
                    digits.push_back(d);
                    ll cnt = calcState(x, currS, currM);
                    if (cnt >= K) {
                        // Use this digit
                        ans += (char) (d + '0');
                        currS -= d;
                        currM -= d * tenMod[x-1] % M;
                        currM = (currM + M) % M;
                        debug << "use " << x << " " << d << " " << currM << endl;
                        x--;
                        break;
                    } else {
                        // Number is greater
                        K -= cnt;
                    }
                }
            }
            cout << ans << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}