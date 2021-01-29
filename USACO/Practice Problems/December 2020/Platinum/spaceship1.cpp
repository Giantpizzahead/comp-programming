#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 60, MAXK = 15;
const int MOD = 1e9+7;

int N, K, Q;
bool adj[MAXN][MAXN];
int dp1[MAXN][1 << MAXK], dp2[MAXN][1 << MAXK];
// int dp3[60][1 << 5], dp4[60][1 << 5];

inline void plusMod(int& a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int doDP(int bs, int s, int bt, int t) {
    for (int i = 0; i < N; i++) {
        fill(dp1[i], dp1[i]+(1<<K), 0);
        fill(dp2[i], dp2[i]+(1<<K), 0);
    }
    int answer = 0;
    if (bs == bt && s == t) answer++;
    // Base cases
    for (int i = 0; i < N; i++) {
        if (adj[s][i]) dp1[i][1 << bs] = 1;
    }
    for (int mask = (1 << bs); mask < (1 << K); mask++) {
        // Move to a room
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (adj[i][j]) plusMod(dp1[j][mask], dp2[i][mask]);
            }
        }
        // Press a button
        for (int j = 0; j < K; j++) {
            if (mask & (1 << j)) continue;
            int newMask = ((mask >> j) + 1) << j;
            for (int i = 0; i < N; i++) {
                plusMod(dp2[i][newMask], dp1[i][mask]);
            }
            if (j == bt) plusMod(answer, dp1[t][mask]);
        }
    }
    return answer;
}

void solve() {
    cin >> N >> K >> Q;
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < N; j++) adj[i][j] = str[j] == '1';
    }
    int bs, s, bt, t;
    for (int i = 0; i < Q; i++) {
        cin >> bs >> s >> bt >> t;
        bs--;
        s--;
        bt--;
        t--;
        cout << doDP(bs, s, bt, t) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}