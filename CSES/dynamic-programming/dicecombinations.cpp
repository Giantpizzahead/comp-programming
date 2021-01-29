#include <iostream>
using namespace std;

const int MAXN = 1e6+1;

int N;
int dp[MAXN];

int main() {
    cin >> N;
    dp[0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= 6; j++) {
            if (i-j < 0) break;
            dp[i] = (dp[i] + dp[i-j]) % 1000000007;
        }
    }
    cout << dp[N] << '\n';
    return 0;
}