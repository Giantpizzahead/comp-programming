#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

void solve() {
    int N; cin >> N;
    string S; cin >> S;
    int unanswered = 0;
    for (int c : S) {
        if (c == 'Q') unanswered++;
        else unanswered = max(unanswered-1, 0);
    }
    cout << (unanswered == 0 ? "Yes" : "No") << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    // int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
