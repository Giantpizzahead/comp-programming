#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 202;
const ll MOD = 1e9+7;

int N;
int X[MAXN], Y[MAXN];
ll dp[MAXN][MAXN];

int ccw(int a, int b, int c) {
    ll result = (ll) (X[a] - X[c]) * (Y[b] - Y[c]) - (ll) (Y[a] - Y[c]) * (X[b] - X[c]);
    if (result < 0) return -1;
    else if (result > 0) return 1;
    else return 0;
}

bool inBetween(int a, int b, int c) {
    if (X[a] == X[c]) {
        if (Y[a] <= Y[b] && Y[b] <= Y[c]) return true;
        if (Y[c] <= Y[b] && Y[b] <= Y[a]) return true;
    } else {
        if (X[a] <= X[b] && X[b] <= X[c]) return true;
        if (X[c] <= X[b] && X[b] <= X[a]) return true;
    }
    return false;
}

bool triangleValid(int a, int b, int c) {
    if (ccw(a, b, c) == 0) return false;
    for (int i = 0; i < N; i++) {
        if (i == a || i == b || i == c) continue;
        int r1 = ccw(a, b, i);
        int r2 = ccw(b, c, i);
        int r3 = ccw(c, a, i);
        if (r1 == 0 && inBetween(a, i, b)) return false;
        if (r2 == 0 && inBetween(b, i, c)) return false;
        if (r3 == 0 && inBetween(c, i, a)) return false;
        if (r1 == r2 && r2 == r3) return false;
    }
    return true;
}

ll go(int a, int b) {
    if (dp[a][b] != -1) return dp[a][b];
    if (b - a == 1) return 1;  // Base case
    ll numWays = 0;
    for (int c = a+1; c < b; c++) {
        if (triangleValid(a, b, c)) {
            ll newWays = go(a, c) * go(c, b) % MOD;
            numWays = (numWays + newWays) % MOD;
        }
    }
    dp[a][b] = numWays;
    return numWays;
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = -1;
        }
    }
    cout << go(0, N-1) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}