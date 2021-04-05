#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N, K;

int answerQuery(int n, int k, bool first) {
    // cout << n << " " << k << " " << first << endl;
    int toRemove = first ? (n+1)/2 : n/2;
    int res;
    if (k > toRemove) {
        // Not in this round
        bool newFirst = n % 2 ? !first : first;
        res = answerQuery(n-toRemove, k-toRemove, newFirst);
        // Adjust to skip removed (so the other half)
        res = first ? res*2 : res*2-1;
    } else {
        // Return result
        res = first ? k*2-1 : k*2;
    }
    return res;
}

void solve() {
    cin >> N >> K;
    cout << answerQuery(N, K, false) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int Q; cin >> Q;
    rep(i, 0, Q) solve();
    return 0;
}