#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N;

void solve() {
    int x;
    rep(i, 1, N) {
        cout << "M " << i << " " << N << endl;
        cin >> x;
        if (x != i) {
            cout << "S " << i << " " << x << endl;
            cin >> x;
            if (x != 1) exit(0);
        }
    }
    cout << "D" << endl;
    cin >> x;
    if (x != 1) exit(0);
}

int main() {
    int T; cin >> T >> N;
    rep(i, 0, T) {
        solve();
    }
    return 0;
}