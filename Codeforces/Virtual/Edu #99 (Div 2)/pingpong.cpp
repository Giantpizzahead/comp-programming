#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int X, Y;

void solve() {
    cin >> X >> Y;
    int A = 0, B = 0;
    A = X-1;
    B = Y;
    cout << A << " " << B << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}