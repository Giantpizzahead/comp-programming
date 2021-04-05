#include <iostream>
#include <vector>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1223; //1e6+1;

int G[MAXN];
int seen[MAXN];

void genGrundy() {
    rep(n, 1, MAXN) {
        // Transitions
        rep(k, 1, (n+1)/2) {
            seen[G[k] ^ G[n-k]] = n;
        }
        // Get Grundy number
        for (int g = 0;; g++) {
            if (seen[g] != n) {
                G[n] = g;
                break;
            }
        }
    }
    // rep(n, 1, MAXN) cout << G[n] << ' ';
    // cout << endl << endl;
    // rep(n, 1, MAXN) if (G[n] == 0) cout << n << ' ';
    // cout << endl;
}

int N;

void solve() {
    cin >> N;
    if (N > 1222) cout << "first" << '\n';
    else cout << (G[N] == 0 ? "second" : "first") << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    genGrundy();
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}