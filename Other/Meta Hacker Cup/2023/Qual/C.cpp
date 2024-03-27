/*
Solution: Sort apples. Try putting new apple as the min or max.
Then, assume it's in the middle and fix the target sum greedily.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 3e5+5;
const int INF = 2e9+7;

int N, M;
int A[MAXN];

int tryTarget(int K) {
    int i = 0, j = M-1;
    int numUsed = -1;
    while (i < j) {
        if (A[i] + A[j] != K) {
            if (numUsed != -1) return INF;  // Impossible
            else if (A[i] + A[j] < K) {
                // Must add to the right side
                numUsed = K - A[i];
                i++;
            } else {
                // Must add to the left side
                numUsed = K - A[j];
                j--;
            }
        } else i++, j--;
    }
    if (i == j) numUsed = K - A[i];
    return (numUsed <= 0 ? INF : numUsed);
}

void solve() {
    cin >> N;
    M = 2*N-1;
    rep(i, 0, M) cin >> A[i];
    sort(A, A+M);
    if (N == 1) {
        cout << "1\n";
        return;
    }

    int best = INF;
    best = min(best, tryTarget(A[0] + A[M-2]));  // Min
    best = min(best, tryTarget(A[1] + A[M-1]));  // Max
    best = min(best, tryTarget(A[0] + A[M-1]));  // Middle
    cout << (best == INF ? -1 : best) << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
