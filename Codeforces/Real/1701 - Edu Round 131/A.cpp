#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int A, B, C, D;

void solve() {
    cin >> A >> B >> C >> D;
    int cnt = A+B+C+D;
    if (cnt == 4) cout << "2\n";
    else if (cnt == 0) cout << "0\n";
    else cout << "1\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}