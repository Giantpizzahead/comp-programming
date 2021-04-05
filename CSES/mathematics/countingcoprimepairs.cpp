#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5, MAXX = 1e6+5;

int N;
int X[MAXN], prime[MAXX], primeCnt[MAXX];
vi primes[MAXN];
ll answer = 0;

void addSubsets(vi& P, int i, int c, int m) {
    if (i == sz(P)) {
        answer += primeCnt[c] * m;
        primeCnt[c]++;
    } else {
        addSubsets(P, i+1, c, m);
        addSubsets(P, i+1, c*P[i], -m);
    }
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> X[i];
    // Sieve
    rep(i, 2, MAXX) {
        if (!prime[i]) {
            for (int j = i; j < MAXX; j += i) prime[j] = i;
        }
    }
    // Gen primes list
    rep(i, 0, N) {
        while (X[i] != 1) {
            primes[i].push_back(prime[X[i]]);
            X[i] /= prime[X[i]];
        }
        sort(all(primes[i]));
        primes[i].resize(distance(primes[i].begin(), unique(all(primes[i]))));
    }
    // Count # of non-coprime pairs, including with itself
    rep(i, 0, N) addSubsets(primes[i], 0, 1, 1);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}