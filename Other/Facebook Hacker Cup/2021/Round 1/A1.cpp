#include <iostream>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

void solve() {
    int N;
    string S;
    cin >> N >> S;
    int ans = 0;
    int on = -1;
    rep(i, 0, N) {
        if (S[i] == 'O' && on != 0) {
            if (on != -1) ans++;
            on = 0;
        } else if (S[i] == 'X' && on != 1) {
            if (on != -1) ans++;
            on = 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}