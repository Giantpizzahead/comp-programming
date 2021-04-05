/**
 * Fix pairs of rows, and use a bitset to quickly count the # of beautiful subgrids.
 * To do this, don't count full rectangles; instead, count the # of vertical lines that have 2 one bits, and use math to
 * count the ways to create rectangles using these lines. (AND operation + Count # of 1 bits)
 * Pragmas are needed (at least in my case) to get AC.
 * Runtime: O([N^2 / 2] * [N / 64]) but bitset is pretty fast
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;
 
const int MAXN = 3000;
 
int N;
bitset<MAXN> rows[MAXN];
 
void solve() {
    cin >> N;
    string str;
    rep(i, 0, N) {
        cin >> str;
        rep(j, 0, N) rows[i].set(j, str[j] == '1');
    }
    ll answer = 0;
    rep(i, 0, N) {
        rep(j, i+1, N) {
            int numOn = (rows[i] & rows[j]).count();
            answer += numOn * (numOn-1) >> 1;
        }
    }
    cout << answer << '\n';
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}