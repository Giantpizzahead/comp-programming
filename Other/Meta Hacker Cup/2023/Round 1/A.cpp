#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

void solve() {
    int N; cin >> N;
    vector<double> A;
    rep(i, 0, N) {
        double x; cin >> x; A.push_back(x);
    }
    sort(all(A));
    double ans;
    if (N == 5) {
        ans = max((A[3]+A[4])/2 - (A[0]+A[2])/2,
                  (A[2]+A[4])/2 - (A[0]+A[1])/2);
    } else {
        ans = (A[N-1]+A[N-2])/2 - (A[0]+A[1])/2;
    }
    cout << fixed << setprecision(6) << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
