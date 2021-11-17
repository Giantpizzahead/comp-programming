#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

ll N;

void solve() {
    cin >> N;
    ll answer = N;
    rep(b, 0, 60) {
        ll B = 1LL << b;
        if (B > N) continue;
        ll A = N / B;
        ll C = N - A * B;
        // cout << A << " " << B << " " << C << endl;
        answer = min(A+b+C, answer);
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}