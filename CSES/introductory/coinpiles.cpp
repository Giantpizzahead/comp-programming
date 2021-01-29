#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int A, B;

void solve() {
    cin >> A >> B;
    int sum = A + B;
    int diff = abs(A-B);
    if (sum % 3 != 0 || diff > sum / 3) cout << "NO\n";
    else cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    rep(i, 0, T) solve();
    return 0;
}