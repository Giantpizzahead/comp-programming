/*
Wrong greedy solution

4 2 5 1

4 2 5 1
4 1 4 1
4 0 3 1
4 0 2 0
2 0 0 0

1s must go first (the number that will be paired)
Then go in order from 2 onwards, except for when later must be paired (1 gang is too big)

Ignoring gang 1:
1 2 3
If sum(all except max) >= max for all, answer is either -0 or -1
1 2 4
Else, answer is -(max - sum(all except max))

To pair:
1 3 6 2
When sum(all except max) < max, it's impossible to pair
If this would occur pairing with earliest, then pair with largest instead

(This is not fully correct)
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXM = 105;

int N, M;
int A[MAXM];

void pairAll(int x) {
    int maxI = x+1;
    rep(i, x+1, M) if (A[i] > A[maxI]) maxI = i;
    int other = N - A[maxI];
    vector<int> paired;

    int ci = x+1;
    while (A[x] != 0) {
        if (A[maxI] != 0 && (ci == maxI || other-2 < A[maxI])) {
            // Pair with largest
            paired.push_back(maxI);
            A[maxI]--;
            other--;
        } else {
            // Pair with smallest
            paired.push_back(ci);
            A[ci]--;
            other -= 2;
        }
        A[x]--; N -= 2;
        if (A[ci] == 0) ci++;
    }

    rep(i, 0, sz(paired)) cout << x+1 << '\n';
    for (int i : paired) cout << i+1 << '\n';
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) cin >> A[i];

    if (A[0] > N - A[0] && M == 2) {
        // Special case
        cout << "YES\n";
        cout << A[0] - (N - A[0]) << '\n';
        rep(i, 0, M) rep(j, 0, A[i]) cout << i+1 << '\n';
        return;
    }

    // Determine max cows on the field
    int maxA = 0;
    rep(i, 1, M) maxA = max(A[i], maxA);
    int other = N - A[0] - maxA;
    int ans = 0;
    if (other >= maxA) {
        if ((other + maxA) % 2 == 0) ans = A[0];
        else ans = A[0] - 1;
    } else ans = A[0] - (maxA - other);

    if (ans <= 0) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    cout << ans << '\n';
    // Generate lexographically earliest pairings
    A[0] -= ans;
    N -= ans;
    rep(i, 0, M) pairAll(i);
    rep(i, 0, ans) cout << "1\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("gangs.in", "r", stdin);
    freopen("gangs.out", "w", stdout);
    solve();
    return 0;
}