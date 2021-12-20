/*
2n choose n:
(2n)! / [(n!)(n!)]
(2n)(2n-1)...(n+1) / n!
(n+1)/1 * (n+2)/2 * ... * (n+n)/n

137846528820
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

void solve() {
    double ans = 1;
    int N; cin >> N;
    rep(i, 1, N+1) {
        ans *= static_cast<double>(N+i) / i;
    }
    cout << static_cast<ll>(round(ans)) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}