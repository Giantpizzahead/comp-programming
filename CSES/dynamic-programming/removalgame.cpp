#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 5000;

int N;
int arr[MAXN];
ll dp[MAXN][MAXN];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];
    // Base case
    if (N % 2 == 1) for (int i = 0; i < N; i++) dp[i][i] = arr[i];
    // DP
    for (int r = 1; r < N; r++) {
        for (int i = 0, j = r; j < N; i++, j++) {
            if ((N-r) % 2 == 1) {
                // Maximize
                dp[i][j] = max(dp[i+1][j] + arr[i], dp[i][j-1] + arr[j]);
            } else {
                // Minimize
                dp[i][j] = min(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    cout << dp[0][N-1] << endl;
}