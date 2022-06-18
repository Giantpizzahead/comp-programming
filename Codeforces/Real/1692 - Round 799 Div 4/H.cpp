#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;

int N;
int A[MAXN];
map<int, int> lastStart, lastLoc, lastVal;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    int bestV = -1, bestA = -1, bestL = -1, bestR = -1;
    rep(i, 0, N) {
        int x = A[i];
        int v;
        if (lastLoc.find(x) == lastLoc.end()) {
            lastStart[x] = i;
            v = 1;
        } else v = lastVal[x] - (i - lastLoc[x] - 1) + 1;
        if (v < 1) {
            lastStart[x] = i;
            v = 1;
        }
        if (v > bestV) {
            bestV = v;
            bestA = x;
            bestL = lastStart[x];
            bestR = i;
        }
        lastLoc[x] = i, lastVal[x] = v;
    }
    cout << bestA << " " << bestL+1 << " " << bestR+1 << "\n";
    lastStart.clear();
    lastLoc.clear();
    lastVal.clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}