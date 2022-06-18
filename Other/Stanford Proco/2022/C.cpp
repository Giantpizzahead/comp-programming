#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;
using namespace std;

int K, p;
vector<pair<int, int>> A;

void solve() {
    cin >> K >> p;
    rep(i, 0, K) {
        int t; cin >> t;
        A.push_back({t, i});
    }
    sort(all(A));
    bool works = true;
    rep(i, 0, K) {
        if (A[i].first < (i+1)*p) {
            works = false;
            break;
        }
    }
    if (works) {
        cout << "SUCCESSFUL!\n";
        rep(i, 0, K) cout << A[i].second+1 << '\n';
    } else {
        cout << "FAILED!\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}