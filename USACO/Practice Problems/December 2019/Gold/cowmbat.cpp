#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5, MAXM = 30, INF = 1e9;

int N, M, K;
int adj[26][26], preCost[MAXM][MAXN];
int A[MAXN], dp[MAXN][MAXM], dpMin[MAXN];
string S;

int changeCost(int i, int j, int c) {
    return preCost[c][j] - (i == 0 ? 0 : preCost[c][i-1]);
}

void solve() {
    cin >> N >> M >> K >> S;
    for (int i = 0; i < N; i++) A[i] = S[i] - 'a';
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cin >> adj[i][j];
        }
    }
    for (int k = 0; k < M; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                adj[i][j] = min(adj[i][k] + adj[k][j], adj[i][j]);
            }
        }
    }
    for (int i = 0; i < M; i++) {
        preCost[i][0] = adj[A[0]][i];
        for (int j = 1; j < N; j++) {
            preCost[i][j] = preCost[i][j-1] + adj[A[j]][i];
        }
    }

    // for (int i = 0; i < M; i++) {
    //     for (int j = 0; j < N; j++) {
    //         cerr << preCost[i][j] << ' ';
    //     }
    //     cerr << endl;
    // }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dp[i][j] = INF;
        }
        dpMin[i] = INF;
    }

    for (int j = 0; j < M; j++) {
        dp[K-1][j] = changeCost(0, K-1, j);
        dpMin[K-1] = min(dp[K-1][j], dpMin[K-1]);
    }
    for (int i = K; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // Extend
            dp[i][j] = dp[i-1][j] + changeCost(i, i, j);
            // New streak
            dp[i][j] = min(dpMin[i-K] + changeCost(i-K+1, i, j), dp[i][j]);
            dpMin[i] = min(dp[i][j], dpMin[i]);
        }
    }
    
    cout << dpMin[N-1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);
    solve();
    cout.flush();
    fclose(stdin);
    fclose(stdout);
    return 0;
}