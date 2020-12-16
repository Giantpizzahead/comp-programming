#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 10005;
const ll INF = 1e18;

int H, M;
ll dp[MAXN][MAXN];
bool from[MAXN][MAXN];

vector<int> go(int N) {
    if (N == 1) {
        // Base case
        vector<int> v;
        v.push_back(1);
        v.push_back(0);
        return v;
    }

    vector<int> pluses = go(N/2);
    M = pluses.size();
    // DP
    dp[M-1][M-1] = 0;
    for (int i = M-1; i >= 0; i--) {
        for (int j = M-1; j >= 0; j--) {
            if (i == M-1 && j == M-1) continue;
            dp[i][j] = INF;
            if (i != M-1) {
                dp[i][j] = dp[i+1][j] + pluses[i+1] + pluses[j];
                from[i][j] = false;
            }
            if (j != M-1) {
                ll trans = dp[i][j+1] + pluses[i] + pluses[j+1];
                if (trans < dp[i][j]) {
                    dp[i][j] = trans;
                    from[i][j] = true;
                }
            }
        }
    }
    // Reconstruct pluses
    vector<int> newPluses;
    newPluses.push_back(N);
    newPluses.push_back(N/2*2);
    int ci = 0, cj = 0;
    cout << "Strategy for " << N << ":" << endl;
    while (ci != M-1 || cj != M-1) {
        cout << from[ci][cj];
        if (from[ci][cj]) cj++;
        else ci++;
        newPluses.push_back(pluses[ci] + pluses[cj]);
    }
    cout << endl;
    // for (int x : newPluses) {
    //     cout << x << ' ';
    // }
    // cout << endl;
    return newPluses;
}

void solve() {
    cin >> H;
    while (H > 10000) H++;
    vector<int> pluses = go(H);
    ll answer = 0;
    for (int i = 1; i < pluses.size(); i++) {
        answer += pluses[i];
    }
    cout << answer << endl;
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