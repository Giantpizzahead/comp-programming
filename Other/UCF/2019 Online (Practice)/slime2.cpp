#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 50005;
const int LOGN = 20;

int N, D;
int cnt[LOGN];
ll dp[LOGN][LOGN];

ll totalSum = 0;
// Go down in DFS order
ll goDown(int N, int T, int leftSum) {
    ll sum = 0;
    while (true) {

    }
}

ll go(int L, int R) {
    if (dp[L][R] != -1) return dp[L][R];
    // Try going down to every next layer
    dp[L][R]
}

void solve() {
    cin >> N;
    D = 0;
    int tempN = N;
    while (N != 0) {
        cnt[D] = tempN;
        tempN /= 2;
        D++;
    }
    for (int i = 0; i <= D; i++) {
        for (int j = 0; j <= D; j++) {
            dp[i][j] = -1;
        }
    }
    cout << go(0, D) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Fight #" << i << ": ";
        solve();
    }
    return 0;
}