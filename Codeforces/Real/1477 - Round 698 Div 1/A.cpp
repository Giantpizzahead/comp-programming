#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;

int N;
ll K;
ll A[MAXN];

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    else return gcd(b, a%b);
}

void solve() {
    cin >> N >> K;
    rep(i, 0, N) {
        cin >> A[i];
        A[i] -= K;
    }
    rep(i, 0, N) {
        if (A[i] == 0) {
            cout << "YES\n";
            return;
        }
    }
    sort(A, A+N);

    ll currDist = A[1] - A[0];
    rep(i, 1, N-1) {
        currDist = gcd(currDist, A[i+1] - A[i]);
    }
    if (A[0] % currDist == 0) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) {
        solve();
    }
    return 0;
}