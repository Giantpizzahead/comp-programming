/**
 * dp[a][b][c][d] =
 * Min cost to paint all cells in rows a-b, cols c-d white
 *
 * BC: dp[a][a][c][c] = 1 if black, 0 if white
 * 
 * dp[a][b][c][d] = min of all below
 * add new rect = max(b-a, d-c) + 1
 * merge rows:
 *  for k in range(a...b-1): dp[a][k][c][d] + dp[k+1][b][c][d]
 * merge cols:
 *  for k in range(c...d-1): dp[a][b][c][k] + dp[a][b][k+1][d]
 * 
 * Runtime: O(N^5) but not actually because lots of states
 * are invalid, so it'll run in time
 */

#include <iostream>
#include <string>

using namespace std;

const int MAXN = 50;

int N;
bool isBlack[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];

int main() {
    cin >> N;
    string str;
    for (int i = 0; i < N; i++) {
        cin >> str;
        for (int j = 0; j < N; j++) isBlack[i][j] = str[j] == '#';
    }
    for (int a = 0; a < N; a++) {
        for (int b = a; b < N; b++) {
            for (int c = 0; c < N; c++) {
                for (int d = c; d < N; d++) {
                    dp[a][b][c][d] = -10;
                }
            }
        }
    }

    for (int colSize = 0; colSize < N; colSize++) {
        for (int rowSize = 0; rowSize < N; rowSize++) {
            for (int a = 0; a < N - colSize; a++) {
                int b = a + colSize;
                for (int c = 0; c < N - rowSize; c++) {
                    int d = c + rowSize;
                    dp[a][b][c][d] = 987654321;
                    if (colSize == 0 && rowSize == 0) {
                        // Base case
                        dp[a][b][c][d] = isBlack[a][c] ? 1 : 0;
                    } else {
                        // Add new rectangle
                        dp[a][b][c][d] = max(colSize, rowSize) + 1;
                        // Merge rows
                        for (int k = a; k < b; k++) {
                            dp[a][b][c][d] = min(dp[a][k][c][d] + dp[k+1][b][c][d], dp[a][b][c][d]);
                        }
                        // Merge cols
                        for (int k = c; k < d; k++) {
                            dp[a][b][c][d] = min(dp[a][b][c][k] + dp[a][b][k+1][d], dp[a][b][c][d]);
                        }
                    }
                }
            }
        }
    }

    cout << dp[0][N-1][0][N-1] << endl;
    return 0;
}