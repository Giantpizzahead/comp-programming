#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define F0R(i, a) for (int i = 0; i < a; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)

const int MAXM = 1005, MAXF = 2000005, MAXDP = 3020;
const ll MOD = 1e9+7;

int N, M;
vector<int> xCoords, yCoords;
int X[MAXM], Y[MAXM];
ll fact[MAXF], invFact[MAXF];

bool trap[MAXDP][MAXDP];
ll dp[MAXDP][MAXDP];

ll modpow(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % MOD;
        b = b * b % MOD;
        e /= 2;
    }
    return r;
}

inline ll nCk(int n, int k) {
    return fact[n] * invFact[k] % MOD * invFact[n-k] % MOD;
}

void solve() {
    cin >> N >> M;
    fact[0] = 1;
    FOR(i, 1, MAXF) {
        fact[i] = fact[i-1] * i % MOD;
        invFact[i] = modpow(fact[i], MOD-2);
    }
    F0R(i, M) cin >> X[i] >> Y[i];

    xCoords.push_back(1);
    xCoords.push_back(N);
    yCoords.push_back(1);
    yCoords.push_back(N);
    F0R(i, M) {
        if (X[i] != 1) xCoords.push_back(X[i]-1);
        xCoords.push_back(X[i]);
        if (X[i] != N) xCoords.push_back(X[i]+1);
        if (Y[i] != 1) yCoords.push_back(Y[i]-1);
        yCoords.push_back(Y[i]);
        if (Y[i] != N) yCoords.push_back(Y[i]+1);
    }
    sort(xCoords.begin(), xCoords.end());
    sort(yCoords.begin(), yCoords.end());
    xCoords.resize(distance(xCoords.begin(), unique(xCoords.begin(), xCoords.end())));
    yCoords.resize(distance(yCoords.begin(), unique(yCoords.begin(), yCoords.end())));

    F0R(i, M) {
        int x = distance(xCoords.begin(), lower_bound(xCoords.begin(), xCoords.end(), X[i]));
        int y = distance(yCoords.begin(), lower_bound(yCoords.begin(), yCoords.end(), Y[i]));
        trap[x][y] = true;
    }

    dp[0][0] = 1;
    F0R(i, xCoords.size()) {
        F0R(j, yCoords.size()) {
            if (trap[i][j]) continue;
            // Take diagonal
            if (i != 0 && j != 0) {
                int dx = xCoords[i] - xCoords[i-1];
                int dy = yCoords[j] - yCoords[j-1];
                ll paths = nCk(dx + dy, dx) - 2;
                // cout << dx << " " << dy << " " << paths << endl;
                if (paths < 0) paths += MOD;
                dp[i][j] = (dp[i][j] + dp[i-1][j-1] * paths) % MOD;
            }
            // Go right
            if (i != 0) dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
            // Go down
            if (j != 0) dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD;
            // cout << dp[i][j] << ' ';
        }
        // cout << endl;
    }

    cout << dp[xCoords.size()-1][yCoords.size()-1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}