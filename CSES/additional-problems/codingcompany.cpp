#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 101, MAXX = 10001, MOD = 1e9+7;

int N, X;
int T[MAXN];
int dp[MAXN][MAXX], dp2[MAXN][MAXX];

typedef unsigned long long ull;
struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(-1ULL / b) {}
	ull reduce(ull a) { // a % b + (0 or b)
		return a - (ull)((__uint128_t(m) * a) >> 64) * b;
	}
};

FastMod F(MOD);

inline void plusMod(int& a, ll b) {
    a = F.reduce(a+b);
}

void solve() {
    cin >> N >> X;
    rep(i, 0, N) cin >> T[i];
    sort(T, T+N);
    dp[0][5000] = 1;
    int minX = 5000, maxX = 5000;
    rep(i, 0, N) {
        // Reset next DP
        rep(j, 0, i+2) {
            rep(k, max(minX-100, 0), min(maxX+100, MAXX)) {
                dp2[j][k] = 0;
            }   
        }
        rep(j, 0, i+1) {
            rep(k, minX, maxX+1) {
                // Make solo team
                plusMod(dp2[j][k], dp[j][k]);
                // Make team
                plusMod(dp2[j+1][max(k-T[i], 0)], dp[j][k]);
                if (j != 0) {
                    // Join team and close it
                    plusMod(dp2[j-1][k+T[i]], static_cast<ll>(dp[j][k]) * j);
                    // Join team and keep it open
                    plusMod(dp2[j][k], static_cast<ll>(dp[j][k]) * j);
                }
            }
        }
        minX = max(minX-100, 0);
        if (i % 2 == 1) maxX = maxX+100;
        swap(dp, dp2);
    }
    
    int answer = 0;
    rep(k, 0, 5001+X) plusMod(answer, dp[0][k]);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}