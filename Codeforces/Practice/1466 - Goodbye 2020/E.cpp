#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 5e5+5;
const int MAXB = 61;
const ll MOD = 1e9+7;

int N;
int onBits[MAXB];
ll X[MAXN];

void solve() {
    rep(i, 0, MAXB) onBits[i] = 0;
    cin >> N;
    rep(i, 0, N) {
        cin >> X[i];
        rep(j, 0, MAXB) {
            if (X[i] & (1LL << j)) onBits[j]++;
        }
    }

    ll ans = 0;
    rep(i, 0, N) {
        ll sumAnd = 0, sumOr = 0;
        rep(j, 0, MAXB) {
            bool currOn = X[i] & (1LL << j);
            if (currOn) {
                // Update AND sum
                ll toAdd = (1LL << j) % MOD * onBits[j] % MOD;
                sumAnd = (sumAnd + toAdd) % MOD;
            }
            // Update OR sum
            if (!currOn) {
                ll toAdd = (1LL << j) % MOD * onBits[j] % MOD;
                sumOr = (sumOr + toAdd) % MOD;
            } else {
                // This makes everything work
                ll toAdd = (1LL << j) % MOD * N % MOD;
                sumOr = (sumOr + toAdd) % MOD;
            }
        }
        ans = (ans + sumAnd * sumOr) % MOD;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}