#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 10, MAXM = 1024;
const int INF = 1e9;

int R, C, F, S;
int A[MAXN][MAXN], B[MAXN][MAXN];
int maskA[MAXN], maskB[MAXN];

int cost[MAXN][MAXM];

struct State {
    int c, m;
    bool operator<(const State& o) const {
        return c > o.c;
    }
};

priority_queue<State> pq;

void spreadRow(int X) {
    rep(i, 0, 1 << C) {
        cost[X][i] = INF;
    }
    cost[X][maskA[X]] = 0;
    pq.push({0, maskA[X]});
    while (!pq.empty()) {
        State s = pq.top(); pq.pop();
        if (cost[X][s.m] != s.c) continue;
        // debug << s.c << " " << bitset<5>(s.m) << endl;
        // Flips
        rep(d, 0, C) {
            int nm = s.m ^ (1 << d);
            int nc = s.c + F;
            if (nc < cost[X][nm]) {
                cost[X][nm] = nc;
                pq.push({nc, nm});
            }
        }
        // Swaps
        rep(d, 0, C-1) {
            bool leftOn = (s.m & (1 << d)) != 0;
            bool rightOn = (s.m & (1 << (d+1))) != 0;
            if (leftOn == rightOn) continue;
            int nm = s.m ^ (1 << d) ^ (1 << (d+1));
            int nc = s.c + S;
            if (nc < cost[X][nm]) {
                cost[X][nm] = nc;
                pq.push({nc, nm});
            }
        }
    }
}

int dp[MAXN][MAXM];

void solve() {
    cin >> R >> C >> F >> S;
    rep(i, 0, R) {
        rep(j, 0, C) {
            char c; cin >> c;
            A[i][j] = (c == 'M');
        }
    }
    rep(i, 0, R) {
        rep(j, 0, C) {
            char c; cin >> c;
            B[i][j] = (c == 'M');
        }
    }

    // Spread rows first
    rep(i, 0, R) {
        int m = 0;
        rep(j, 0, C) m = m * 2 + A[i][j];
        maskA[i] = m;
        m = 0;
        rep(j, 0, C) m = m * 2 + B[i][j];
        maskB[i] = m;
        spreadRow(i);
    }

    // DP for columns
    rep(i, 0, R) {
        rep(j, 0, 1 << C) {
            dp[i][j] = INF;
        }
    }
    rep(j, 0, 1 << C) dp[0][j] = cost[0][j];
    rep(i, 0, R-1) {
        rep(j, 0, 1 << C) {
            // Column swaps to match target
            rep(k, 0, 1 << C) {
                int newMask = k;
                int addedCost = 0;
                bool valid = true;
                rep(d, 0, C) {
                    if ((j & (1 << d)) != (maskB[i] & (1 << d))) {
                        // Different, must switch
                        if ((k & (1 << d)) != (maskB[i] & (1 << d))) {
                            // Both bad
                            valid = false;
                            break;
                        } else {
                            // Switch cost
                            addedCost += S;
                            newMask ^= (1 << d);
                        }
                    }
                }
                if (valid) {
                    dp[i+1][newMask] = min(dp[i][j] + cost[i+1][k] + addedCost, dp[i+1][newMask]);
                }
            }
        }
    }
    int answer = dp[R-1][maskB[R-1]];
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}