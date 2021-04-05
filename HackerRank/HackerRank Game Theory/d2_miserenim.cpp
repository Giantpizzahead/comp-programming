#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N;

void solve() {
    cin >> N;
    int ans = 0, num1 = 0;
    rep(i, 0, N) {
        int x; cin >> x;
        ans ^= x;
        if (x == 1) num1++;
    }
    if (num1 == N) cout << (N % 2 ? "Second" : "First") << endl;
    else if (ans != 0) cout << "First" << endl;
    else cout << "Second" << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}