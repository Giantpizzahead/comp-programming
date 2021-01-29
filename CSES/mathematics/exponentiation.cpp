#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
ll A, B;

ll modpow(ll b, ll e, ll m) {
    ll r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % m;
        b = b * b % m;
        e /= 2;
    }
    return r;
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A >> B;
        cout << modpow(A, B, 1e9+7) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}