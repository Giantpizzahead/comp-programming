#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 5005;
const int INF = 2e9+7;

int N;
struct Range {
    int a, b;
    void set(int aa, int bb) {
        aa = max(-1000000000, aa);
        bb = min(1000000000, bb);
        if (a == INF) {
            a = aa;
            b = bb;
        } else {
            a = min(a, aa);
            b = max(b, bb);
        }
    }
};
Range dp[MAXN][MAXN];
pair<int, int> C[MAXN];

int timeNeeded(Range& r, int x) {
    if (x >= r.a && x <= r.b) return 0;
    int answer = min(abs(r.a - x), abs(r.b - x));
    return answer;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> C[i].first >> C[i].second;
    }
    C[0].first = 0;
    C[0].second = 0;
    sort(C+1, C+N+1);

    // for (int i = 0; i <= N; i++) cout << C[i].first << " " << C[i].second << endl;

    for (int t = 0; t <= N; t++) {
        for (int l = 0; l <= N; l++) {
            dp[t][l].a = INF;
            dp[t][l].b = INF;
        }
    }
    dp[0][0].set(0, 0);

    for (int t = 1; t <= N; t++) {
        int timeDiff = C[t].first - C[t-1].first;
        for (int l = 1; l <= N; l++) {
            if (t != l) {
                // Person must be at cake t
                if (dp[t-1][l].a != INF) {
                    int timeToReach = timeNeeded(dp[t-1][l], C[t].second);
                    if (timeToReach <= timeDiff) {
                        dp[t][l].set(C[t].second, C[t].second);
                    }
                }
                if (dp[t-1][0].a != INF) {
                    int timeToReach = timeNeeded(dp[t-1][0], C[l].second) + abs(C[l].second - C[t].second);
                    if (timeToReach <= timeDiff) {
                        dp[t][l].set(C[t].second, C[t].second);
                    }
                }
                if (dp[t-1][t-1].a != INF) {
                    int timeToReach = timeNeeded(dp[t-1][t-1], C[l].second) + abs(C[l].second - C[t].second);
                    if (timeToReach <= timeDiff) {
                        dp[t][l].set(C[t].second, C[t].second);
                    }
                }
            } else {
                // Person can be anywhere
                if (dp[t-1][t].a != INF) {
                    dp[t][t].set(dp[t-1][t].a - timeDiff, dp[t-1][t].b + timeDiff);
                }
            }
        }
        // Handle dp[t][0]
        if (dp[t-1][0].a != INF) {
            int timeToReach = timeNeeded(dp[t-1][0], C[t].second);
            if (timeToReach <= timeDiff) {
                dp[t][0].set(C[t].second - (timeDiff - timeToReach), C[t].second + (timeDiff - timeToReach));
            }
        }
        if (dp[t-1][t-1].a != INF) {
            int timeToReach = timeNeeded(dp[t-1][t-1], C[t].second);
            if (timeToReach <= timeDiff) {
                dp[t][0].set(C[t].second - (timeDiff - timeToReach), C[t].second + (timeDiff - timeToReach));
            }
        }
    }

    // for (int t = 0; t <= N; t++) {
    //     for (int l = 0; l <= N; l++) {
    //         cout << "[" << dp[t][l].a << " " << dp[t][l].b << "] ";
    //     }
    //     cout << endl;
    // }

    // Check if possible
    bool possible = false;
    for (int i = 0; i <= N; i++) {
        if (dp[N][i].a != INF) {
            possible = true;
            break;
        }
    }
    cout << (possible ? "YES" : "NO") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}