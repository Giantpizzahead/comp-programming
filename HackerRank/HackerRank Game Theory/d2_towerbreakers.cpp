#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 105, MAXH = 1e6+5;

int N;
int H[MAXN], grundy[MAXH];

int currIter = 0;
int seen[MAXH];
int findGrundy(int x) {
    if (grundy[x] != -1) return grundy[x];
    currIter++;
    seen[findGrundy(1)] = currIter;
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) {
            seen[findGrundy(i)] = currIter;
            seen[findGrundy(x/i)] = currIter;
        }
    }
    // Find mex
    for (int i = 0;; i++) {
        if (seen[i] != currIter) {
            grundy[x] = i;
            break;
        }
    }
    return grundy[x];
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> H[i];
    }
    int xorSum = 0;
    rep(i, 0, N) {
        xorSum ^= findGrundy(H[i]);
    }
    cout << (xorSum == 0 ? 2 : 1) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    rep(i, 0, MAXH) grundy[i] = -1;
    grundy[1] = 0;
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}