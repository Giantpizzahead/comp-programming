#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, M, R, C;

void solve() {
    cin >> N >> M >> R >> C;

    int ans = max(R-1 + C-1, (N-R) + (M-C));
    ans = max(R-1 + (M-C), ans);
    ans = max((N-R) + (C-1), ans);
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
    return 0;
}