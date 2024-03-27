#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 305;
const int INF = 987654321;

int H, S, K;
int dp[MAXN][MAXN][MAXN][2][2];
int stacks[MAXN][MAXN], minLost[MAXN][MAXN][2], answers[MAXN];

void solve(int tn) {
    fin >> H >> S >> K;
    for (int i = 0; i < H; i++) {
        string str;
        fin >> str;
        for (int j = 0; j < S; j++) {
            stacks[j][i] = (str[j] == 'A' ? 0 : 1);
        }
    }

    for (int i = 0; i < S; i++) {
        for (int j = 0; j <= H; j++) {
            for (int k = 0; k <= H; k++) {
                dp[i][j][k][0][0] = INF;
                dp[i][j][k][0][1] = INF;
                dp[i][j][k][1][0] = INF;
                dp[i][j][k][1][1] = INF;
            }
        }
    }

    for (int i = 0; i < S; i++) {
        // Base case: Start with top paper
        dp[i][0][0][0][0] = 0;
        dp[i][0][0][1][1] = 0;
        // Main DP
        for (int j = 1; j <= H; j++) {
            for (int k = 0; k <= H; k++) {
                for (int l = 0; l < 2; l++) {
                    for (int m = 0; m < 2; m++) {
                        int bestDP = dp[i][j][k][l][m];
                        if (stacks[i][j-1] == m) {
                            // Same type
                            bestDP = min(dp[i][j-1][k][l][m], bestDP);
                            if (k != 0) {
                                // Context switch
                                bestDP = min(dp[i][j-1][k-1][l][1-m], bestDP);
                            }
                        } else {
                            // Different type
                            bestDP = min(dp[i][j-1][k][l][m] + 1, bestDP);
                        }
                        if (k != 0) {
                            bestDP = min(dp[i][j][k-1][l][m], bestDP);
                        }

                        if (bestDP != INF) {
                            // cout << i << ' ' << j << ' ' << k << ' ' << l << ' ' << m << " = " << bestDP << endl;
                        }
                        dp[i][j][k][l][m] = bestDP;
                    }
                }
            }
        }
    }

    for (int i = 0; i < S; i++) {
        for (int k = 0; k <= H; k++) {
            for (int l = 0; l < 2; l++) {
                // cout << dp[i][H][k][l][0] << ' ' << dp[i][H][k][l][1] << endl;
                minLost[i][k][l] = min(dp[i][H][k][l][0], dp[i][H][k][l][1]);
            }
        }
    }

    /*
    for (int i = 0; i < S; i++) {
        cout << "Stack " << i << endl;
        for (int l = 0; l < 2; l++) {
            cout << "Start with " << l << ": ";
            for (int k = 0; k < H; k++) {
                cout << minLost[i][k][l] << ' ';
            }
            cout << endl;
        }
    }
    */

    for (int k = 0; k <= H; k++) {
        answers[k] = INF;
        for (int l = 0; l < 2; l++) {
            int currLost = 0;
            for (int i = 0; i < S; i++) {
                currLost += minLost[i][k][l];
            }
            answers[k] = min(currLost, answers[k]);
        }
    }

    /*
    for (int i = 0; i <= H; i++) {
        cout << answers[i] << ' ';
    }
    cout << endl;
    */

    fout << "Case #" << tn << ": ";
    int l;
    for (int i = 0; i < K; i++) {
        fin >> l;
        for (int j = 0; j <= H; j++) {
            if (answers[j] <= l) {
                fout << j+1 << (i == K-1 ? '\n' : ' ');
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}