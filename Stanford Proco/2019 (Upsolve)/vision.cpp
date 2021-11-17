#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXP = 1e4;

vector<ll> P;
bool composite[MAXP];

ll C, N, M;

void solve() {
    cin >> C;
    N = C, M = C;
    bool found = false;
    // Find any primes with power >= 3
    for (ll p : P) {
        int cnt = 0;
        ll tempC = C;
        while (tempC % p == 0) {
            cnt++;
            tempC /= p;
        }
        if (cnt >= 3) {
            // Modify powers
            found = true;
            int toRemove = cnt / 3;
            rep(i, 0, toRemove) {
                N = N / p / p;
                M = M / p / p / p;
            }
        }
    }
    if (!found) {
        N *= 4;
        M *= 8;
    }
    cout << N << ' ' << M << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    rep(p, 2, MAXP) {
        if (!composite[p]) {
            P.push_back(p);
            for (int q = 2*p; q < MAXP; q += p) composite[q] = true;
        }
    }
    // cout << sz(P) << '\n';
    int Q; cin >> Q;
    rep(i, 0, Q) solve();
    return 0;
}