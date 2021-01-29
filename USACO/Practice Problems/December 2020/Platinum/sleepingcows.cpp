#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

const int MAXN = 3005;
const ll MOD = 1e9+7;

int N;
ll dp1[MAXN][MAXN], dpRev[MAXN][MAXN], dpRev2[MAXN][MAXN], fact[MAXN];
ll S[MAXN], T[MAXN];
int newCows[MAXN], preNewCows[MAXN];

void fillRev() {
    // For this whole method, barns and cows are reversed
    int li = 0, barnI = 0;
    rep(i, 0, N) {
        while (barnI != N && S[i] > T[barnI]) {
            newCows[barnI] = i-li;
            li = i;
            barnI++;
        }
    }
    newCows[barnI] = N-li;

    dpRev2[0][newCows[0]] = 1;
    rep(i, 1, N+1) {
        int chg = newCows[i];
        rep(j, 0, N+1) {
            // Use this barn
            if (j-chg+1 >= 0) dpRev2[i][j] += dpRev2[i-1][j-chg+1] * (j-chg+1);
            // Don't use this barn
            if (j-chg >= 0) dpRev2[i][j] += dpRev2[i-1][j-chg];
            dpRev2[i][j] %= MOD;
        }
    }

    rep(i, 0, N+1) {
        rep(j, 0, N+1) {
            dpRev[i][j] = dpRev2[i][j+newCows[i]];
        }
    }

    // cout << "dpRev:\n";
    // rep(i, 0, N+1) {
    //     rep(j, 0, N+1) {
    //         cout << dpRev[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;
}

void solve() {
    cin >> N;
    fact[0] = 1;
    rep(i, 1, N+1) fact[i] = fact[i-1] * i % MOD;
    rep(i, 0, N) {
        cin >> S[i];
    }
    rep(i, 0, N) {
        cin >> T[i];
    }
    // Evaluate reverse first
    rep(i, 0, N) {
        swap(S[i], T[i]);
        S[i] *= -1;
        T[i] *= -1;
    }
    sort(S, S+N);
    sort(T, T+N);
    // rep(i, 0, N) cout << S[i] << ' ';
    // cout << endl;
    // rep(i, 0, N) cout << T[i] << ' ';
    // cout << endl;
    fillRev();
    // Fix array
    rep(i, 0, N) {
        swap(S[i], T[i]);
        S[i] *= -1;
        T[i] *= -1;
    }
    sort(S, S+N);
    sort(T, T+N);
    // rep(i, 0, N) cout << S[i] << ' ';
    // cout << endl;
    // rep(i, 0, N) cout << T[i] << ' ';
    // cout << endl;

    rep(i, 0, N+1) newCows[i] = 0;
    int li = 0, barnI = 0;
    rep(i, 0, N) {
        while (barnI != N && S[i] > T[barnI]) {
            newCows[barnI] = i-li;
            li = i;
            barnI++;
        }
    }
    newCows[barnI] = N-li;
    preNewCows[0] = newCows[0];
    rep(i, 1, N+1) {
        preNewCows[i] = preNewCows[i-1] + newCows[i];
    }

    // cout << "newCows: ";
    // rep(i, 0, N) cout << newCows[i] << ' ';
    // cout << endl;

    ll answer = 0;
    dp1[0][newCows[0]] = 1;
    rep(i, 1, N+1) {
        int chg = newCows[i];
        rep(j, 0, N+1) {
            // Use this barn
            if (j-chg+1 >= 0) dp1[i][j] += dp1[i-1][j-chg+1] * (j-chg+1);
            // Don't use this barn
            if (j-chg >= 0) dp1[i][j] += dp1[i-1][j-chg];
            dp1[i][j] %= MOD;
        }
        rep(j, 0, N+1) {
            int dup = 0, k = i;
            while (k != N && newCows[k] == 0) {
                k++;
                dup++;
            }
            if (j-dup < 0) continue;
            // Mark as last unused
            //cout << i << " " << j << ": " << N - preNewCows[i-1] << " " << j-dup << " = " << dpRev[N-preNewCows[i-1]][j-dup] << " * " << fact[j] << " * " << dp1[i-1][j] << endl;
            ll waysRight = dpRev[N - preNewCows[i-1]][j-dup];
            answer += waysRight * dp1[i-1][j] % MOD * fact[j];
            answer %= MOD;
            // dp2[i][j][chg] += dp1[i-1][j];
            // rep(k, 0, N+1) {
            //     // Use left cow
            //     if (k-chg >= 0) dp2[i][j][k] += dp2[i-1][j+1][k-chg] * (j+1);
            //     // Use right cow
            //     if (k-chg+1 >= 0) dp2[i][j][k] += dp2[i-1][j][k-chg+1] * (k-chg+1);
            //     dp2[i][j][k] %= MOD;
            // }
        }
    }

    // cout << "dp1:\n";
    // rep(i, 0, N+1) {
    //     rep(j, 0, N+1) {
    //         cout << dp1[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // cout << "dp2:\n";
    // rep(j, 0, N+1) {
    //     rep(k, 0, N+1) {
    //         cout << dp2[N][j][k] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    answer = (answer + dp1[N][0]) % MOD;
    // rep(k, 0, N+1) answer = (answer + dp2[N][0][k]) % MOD;
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}