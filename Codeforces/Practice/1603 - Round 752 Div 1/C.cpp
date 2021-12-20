#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using namespace std;
using ll = long long;

const int MAXN = 1e5+5;
const ll MOD = 998244353;

int N;
int A[MAXN], V[2][MAXN];
vector<int> toCheck, nextToCheck;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    toCheck.reserve(N); toCheck.clear();
    nextToCheck.reserve(N); nextToCheck.clear();
    ll answer = 0;
    int cr = 0, nr = 1;
    for (int i = N-1; i >= 0; i--) {
        int a = A[i];
        for (int b : toCheck) {
            if (!V[cr][b]) continue;
            // Transfer this
            if (a <= b) {
                V[nr][a] += V[cr][b];
                nextToCheck.push_back(a);
            } else {
                int n = (a+b-1) / b;
                int v = a / n;
                debug << a << " " << b << " " << n << " " << v << endl;
                // Add to answer
                answer += (ll) (n-1) * V[cr][b] % MOD * (i+1) % MOD;
                answer %= MOD;
                V[nr][v] += V[cr][b];
                nextToCheck.push_back(v);
            }
            V[cr][b] = 0;
        }
        // Case for subarray starting here
        V[nr][a]++;
        nextToCheck.push_back(a);
        toCheck.clear();
        swap(toCheck, nextToCheck);
        swap(cr, nr);
    }
    for (int b : toCheck) V[cr][b] = 0;
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}