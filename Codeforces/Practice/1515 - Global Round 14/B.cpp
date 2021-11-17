#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

void solve() {
    int N; cin >> N;
    if (N % 2 == 0) {
        int x = round(sqrt(N/2));
        if (x * x == N/2) {
            cout << "YES\n";
            return;
        }
    }
    if (N % 4 == 0) {
        int x = round(sqrt(N/4));
        if (x * x == N/4) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}