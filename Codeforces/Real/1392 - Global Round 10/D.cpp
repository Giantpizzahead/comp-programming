#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 200005;
const int INF = 987654321;

int N;
string str;
int strNum[MAXN];
// dp[i][j][k], i = index, j = last 2 people directions, k = first person direction
int dp[MAXN][4][4];

void solve() {
    cin >> N >> str;
    for (int i = 0; i < N; i++) strNum[i] = str[i] == 'R' ? 1 : 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 2; k++) dp[i][j][k] = INF;
        }
    }
    // 0 = Left, 1 = Right
    dp[1][strNum[0] + 2 * strNum[1]][strNum[0] + 2 * strNum[1]] = 0;
    dp[1][strNum[0] + 2 * (1-strNum[1])][strNum[0] + 2 * (1-strNum[1])] = 1;
    dp[1][1-strNum[0] + 2 * strNum[1]][1-strNum[0] + 2 * strNum[1]] = 1;
    dp[1][1-strNum[0] + 2 * (1-strNum[1])][1-strNum[0] + 2 * (1-strNum[1])] = 2;
    for (int i = 1; i < N - 1; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                // Left direction
                if (j == 1 || j == 2 || j == 3) {
                    dp[i+1][j%2*2][k] = min(dp[i][j][k] + (strNum[i+1] == 0 ? 0 : 1), dp[i+1][j%2*2][k]);
                }
                // Right direction
                if (j == 0 || j == 1 || j == 2) {
                    dp[i+1][j%2*2+1][k] = min(dp[i][j][k] + (strNum[i+1] == 1 ? 0 : 1), dp[i+1][j%2*2+1][k]);
                }
            }
        }
    }

    // Check only valid states
    int answer = INF;
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
            bool left[4];
            left[0] = j / 2;
            left[1] = j % 2;
            left[2] = k / 2;
            left[3] = k % 2;
            if (left[2] && left[1] && left[0]) continue;
            if (left[3] && left[2] && left[1]) continue;
            if (!left[0] && !left[1] && !left[2]) continue;
            if (!left[1] && !left[2] && !left[3]) continue;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}