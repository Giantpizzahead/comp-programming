#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int A, B, H;

void solve() {
    cin >> A >> B >> H;
    int endAt = H-A;
    if (endAt <= 0) cout << 1 << '\n';
    else {
        int C = A-B;
        int T = (endAt+C-1)/C;
        cout << T+1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}