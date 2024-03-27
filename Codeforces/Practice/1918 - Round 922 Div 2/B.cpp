/*

1 3 4 5 2
5 3 1 2 4

Swapping adjacent can swap everything.
Adjacent changes inversion count by: -1 or +1 for each. So either -2, 0, or +2.

a b  If a < b and c < d, or a > b and c > d, then the order is set. Otherwise, it doesn't matter?
c d

No. Just sort 1! Never changes after that.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

int N;
vector<pair<int, int>> A, B;

void solve() {
    cin >> N;
    A.resize(N), B.resize(N);
    rep(i, 0, N) {
        cin >> A[i].first;
        A[i].second = i;
    }
    rep(i, 0, N) cin >> B[i].first;
    sort(all(A));
    rep(i, 0, N) cout << A[i].first << " \n"[i==N-1];
    rep(i, 0, N) cout << B[A[i].second].first << " \n"[i==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    // int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
