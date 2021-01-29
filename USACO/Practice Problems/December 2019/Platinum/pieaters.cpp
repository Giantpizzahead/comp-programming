#include <bits/stdc++.h>
using namespace std;

const int MAXN = 302;

int N, M;
int cows[MAXN][MAXN][MAXN];
int dp[MAXN][MAXN];

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int w, l, r;
        cin >> w >> l >> r;
        for (int j = l; j <= r; j++) {
            cows[l][r][j] = max(w, cows[l][r][j]);
        }
    }
    
    for (int sz = 1; sz < N; sz++) {
        for (int i = 1; i <= N; i++) {
            int j = i+sz;
            if (j > N) break;
            for (int k = i; k <= j; k++) {
                cows[i][j][k] = max(cows[i+1][j][k], cows[i][j][k]);
                cows[i][j][k] = max(cows[i][j-1][k], cows[i][j][k]);
            }
        }
    }

    for (int sz = 0; sz < N; sz++) {
        for (int i = 1; i <= N; i++) {
            int j = i+sz;
            if (j > N) break;
            // Merge
            for (int k = i; k < j; k++) {
                dp[i][j] = max(dp[i][k] + dp[k+1][j], dp[i][j]);
            }
            // Add cow
            for (int k = i; k <= j; k++) {
                dp[i][j] = max(dp[i][k-1] + dp[k+1][j] + cows[i][j][k], dp[i][j]);
            }
        }
    }

    // for (int i = 1; i <= N; i++) {
    //     for (int j = 1; j <= N; j++) cerr << dp[i][j] << ' ';
    //     cerr << endl;
    // }

    cout << dp[1][N] << '\n';
}

int main() {
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    cout.flush();
    fclose(stdin);
    fclose(stdout);
    return 0;
}