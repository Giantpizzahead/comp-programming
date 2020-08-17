#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>

using namespace std;
using ll = long long;

const int MOD = (int) 1e9+7;
const int MODINV2 = (int) 5e8+4;
const int MAXN = 500;
int dp[62626];

int N;

int main() {
    cin >> N;
    int sum = N * (N + 1) / 2;
    if (sum % 2 == 1) {
        // Impossible
        cout << 0 << endl;
        return 0;
    }
    sum /= 2;
    dp[0] = 1;
    int currSum = 0;
    for (int i = 1; i <= N; i++) {
        currSum = min(currSum+i, sum);
        for (int j = currSum; j >= i; j--) {
            dp[j] += dp[j-i];
            if (dp[j] >= MOD) dp[j] -= MOD;
        }
    }
    cout << (ll) dp[sum] * MODINV2 % MOD << endl;
    return 0;
}