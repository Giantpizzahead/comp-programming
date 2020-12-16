#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 52, MAXC = 2505;
const ll MOD = 1000000007;

int N, M, numBad, numGood;
int freq[MAXN];
bool isBad[MAXN], inSeq[MAXN];
ll fact[MAXC];
ll dp[MAXC][MAXC][2];

inline void plusMod(ll& a, ll& b) {
    a = (a+b)%MOD;
}

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % MOD;
        b = b * b % MOD;
        e /= 2;
    }
    return r;
}

ll moddiv(ll a, ll b) {
    return a * powmod(b, MOD-2) % MOD;
}

void solve() {
    int K, L, temp;
    fact[0] = 1;
    for (int i = 1; i < MAXC; i++) {
        fact[i] = (ll) fact[i-1] * i % MOD;
    }
    
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> freq[i];
    }
    cin >> K;
    for (int i = 0; i < K; i++) {
        cin >> temp;
        temp--;
        isBad[temp] = true;
    }
    cin >> L;
    for (int i = 0; i < L; i++) {
        cin >> temp;
        temp--;
        inSeq[temp] = true;
    }

    numBad = 0;
    numGood = 0;
    int bottleneck = (L == 0) ? 0 : 99999;
    for (int i = 0; i < N; i++) {
        if (isBad[i]) numBad += freq[i];
        else numGood += freq[i];
        if (inSeq[i]) bottleneck = min(freq[i], bottleneck);
    }

    if (numBad > numGood + 1) {
        // Impossible
        cout << 0 << endl;
        return;
    }

    // Form sequences
    freq[N] = bottleneck;
    numGood -= (L-1) * bottleneck;
    /*
    while (freq[N] < bottleneck) {
        // Can we form more sequences?
        int nextGood = numGood - L + 1;
        if (numBad > nextGood + 1) break;
        // This is valid
        freq[N]++;
        numGood = nextGood;
    }
    */
    M = numBad + numGood;
    for (int i = 0; i < N; i++) {
        if (inSeq[i]) freq[i] -= freq[N];
    }
    N++;
    while (N > 51 || M > 2500) {
        N++;
        M++;
    }
    // cout << "info " << M << " " << numBad << " " << numGood << " " << freq[N-1] << endl;
    dp[0][0][0] = 1;
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j <= numBad; j++) {
            for (int l = 0; l < 2; l++) {
                if (l == 0) {
                    // Good ball here
                    plusMod(dp[i][j][l], dp[i-1][j][0]);
                    plusMod(dp[i][j][l], dp[i-1][j][1]);
                } else if (j != 0) {
                    // Bad ball here
                    plusMod(dp[i][j][l], dp[i-1][j-1][0]);
                }
            }
        }
    }
    ll answer = (dp[M][numBad][0] + dp[M][numBad][1]) % MOD;
    // Handle undercount
    answer = answer * fact[numBad] % MOD;
    answer = answer * fact[numGood] % MOD;
    for (int i = 0; i < N; i++) {
        answer = moddiv(answer, fact[freq[i]]);
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}