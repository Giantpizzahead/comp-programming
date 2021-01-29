#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5, MAXX = 1e6+5;

int N;
int prime[MAXX], divisors[MAXX];

void solve() {
    cin >> N;
    for (int i = 2; i*i < MAXX; i++) {
        if (prime[i] == 0) {
            for (int j = i*2; j < MAXX; j += i) {
                prime[j] = i;
            }
        }
    }
    divisors[1] = 1;
    rep(i, 2, MAXX) {
        if (prime[i] == 0) {
            divisors[i] = 2;
            for (ll j = (ll) i*i, k = 3; j < MAXX; j *= i, k++) {
                divisors[j] = k;
            }
        } else if (divisors[i] == 0) {
            int primeFact = prime[i];
            while (prime[i/primeFact] == prime[i]) primeFact *= prime[i];
            divisors[i] = divisors[i/primeFact] * divisors[primeFact];
        }
    }
    // rep(i, 1, 101) {
    //     cout << divisors[i] << ' ';
    // }
    // cout << endl;
    rep(i, 0, N) {
        int x;
        cin >> x;
        cout << divisors[x] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}