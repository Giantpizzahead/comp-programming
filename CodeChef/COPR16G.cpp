#include <iostream>
using namespace std;
using ll = long long;

ll A, B;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> A >> B;
        ll G = gcd(A, B);
        if (G != 1) cout << -1 << '\n';
        else {
            ll ans = A * B - A - B + 1;
            cout << ans << '\n';
        }
    }
    return 0;
}