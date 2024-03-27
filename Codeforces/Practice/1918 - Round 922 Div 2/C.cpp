/*
|(a ^ x) - (b ^ x)|
Consider each bit independently:

If bits a_i and b_i are the same, it's always 0.
Else, if a_i = 1 and b_i = 0, then x_i = 0 causes +2^i, x_i = 1 causes -2^i. And vice versa.

We want the smallest absolute value.
Limit on x makes it so we need to first fix the uppermost bit of x.

Then, it branches into another problem.
We want both the min and max possible values of the equation to be returned?

The uppermost different bit between a and b sort of fixes the direction we have to go (+ or -). If it's controllable by us, we should always choose 0 to allow the rest to be set. Everything else is then fixed!

So, the answer is just sum(2^uppermost different or uncontrollable) - sum(2^other different).

9 6 10

1001
0110
+8 -4 -2 -1
0
1010
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 62;
ll A, B, R;

void solve() {
    cin >> A >> B >> R;
    ll ans = 0;
    for (int i = MAXN; i >= 0; i--) {
        ll twoI = 1LL << i;
        if ((A & twoI) == (B & twoI)) continue;
        ll currDiff = (A & twoI) - (B & twoI);

        // cout << "On " << twoI << " " << currDiff << endl;

        // Controllable?
        if (twoI <= R) {
            // Yes, should we?
            if (ans != 0 && ((ans > 0) == (currDiff > 0))) {
                // Should invert this
                R -= twoI;
                ans -= currDiff;
            } else ans += currDiff;
        } else {
            // No; this bit must be 0
            ans += currDiff;
        }
    }

    cout << abs(ans) << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    // int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
