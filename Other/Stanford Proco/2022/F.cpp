#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int m = 2000007;

long double dp[m][2];
long double psum[m][2];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int i, j, t;
	cin >> i >> j >> t;
	psum[1][0] = 1.0L / i;
	psum[i + 1][0] = -1.0L / i;
	long double ans = 0;
	for(int n = 1; n <= t + max(i, j) - 1; ++n) {
		psum[n][0] += psum[n - 1][0];
		psum[n][1] += psum[n - 1][1];
		dp[n][0] += psum[n][0];
		dp[n][1] += psum[n][1];
		if(n < t) {
			psum[n + 1][0] += dp[n][1] * 1.0L / i;
			psum[n + i + 1][0] -= dp[n][1] * 1.0L / i;
			psum[n + 1][1] += dp[n][0] * 1.0L / j;
			psum[n + j + 1][1] -= dp[n][0] * 1.0L / j;
		} else ans += dp[n][0];
	}
    double ansd = (ll) (ans * 10000) / 10000.0L;
	cout << setprecision(4) << ansd << '\n';
}