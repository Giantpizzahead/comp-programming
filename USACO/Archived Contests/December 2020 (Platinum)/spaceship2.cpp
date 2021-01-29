#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 60, MAXK = 10;
const int MOD = 1e9+7;

int N, K, Q;
bool adj[MAXN][MAXN];
int dp1[MAXN], dp2[1 << MAXK], oldDP1[MAXN], oldDP2[1 << MAXK];

inline void plusMod(int& a, ll b) {
    a = (a+b) % MOD;
}

int doDP(int bs, int s, int bt, int t) {
    for (int i = 0; i < N; i++) {
        fill(dp1, dp1+N, 0);
        fill(dp2, dp2+(1<<K), 0);
        fill(oldDP1, oldDP1+N, 0);
        fill(oldDP2, oldDP2+(1<<K), 0);
    }
    int answer = 0;
    if (bs == bt && s == t) answer++;
    // Base cases
    for (int i = 0; i < N; i++) {
        if (adj[s][i]) oldDP1[i] = 1;
    }
    oldDP2[1 << bs] = 1;
    for (int mask = (1 << bs); mask < (1 << K); mask++) {
        // Move to a room
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (adj[i][j]) plusMod(dp1[j], oldDP1[i]);
            }
        }
        // Press a button
        for (int j = 0; j < K; j++) {
            if (mask & (1 << j)) continue;
            int newMask = (mask >> j) << j;
            newMask |= 1 << j;
            for (int i = 0; i < N; i++) {
                plusMod(dp2[newMask], oldDP2[mask]);
            }
        }
        // Update answer
        if ((mask & (1 << bt)) && mask % (1 << bt) == 0) {
            plusMod(answer, (ll) dp1[t] * dp2[mask]);
        }
        swap(dp1, oldDP1);
        swap(dp2, oldDP2);
        fill(dp1, dp1+N, 0);
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