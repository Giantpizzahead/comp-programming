/**
 * For K = 0:
 * Since it's guaranteed that there is a routing scheme, every node gives degree(node)! choices (which sender follows
 * which edge?). One additional choice is to consider which sender uses which receiver (if the receiver has outgoing
 * edges). So, add a dummy node for each receiver, with one inedge from the actual receiver. Then, the answer is just
 * all of the degree(node)! multiplied together.
 * 
 * For K = 1:
 * It's (almost) equivalent to change the back edge into one more sender and receiver, where the receiver is at the back
 * edge's starting node, and the sender is at the back edge's ending node. Essentially, you split up one sender-receiver
 * path into two - one to the back edge, and one to the receiver. Then, just run the K=0 algorithm to solve it.
 * The above overcounts the case where the added sender is paired with the added receiver. A DP-ish solution can be used
 * to count the paths while fixing one pair (dp[i][j] = # ways with all nodes <i cleared, fixed path is on node j).
 * 
 * For K = 2:
 * Similar to K = 1, think of the back edges as two added senders and receivers. Run the K=0 algorithm.
 * Let S1 and S2 be the added senders, R1 and R2 be the added receivers. The above overcounts when S1 -> R1, S2 -> R2,
 * or (S1 -> R2 and S2 -> R1). Again, a DP-ish solution can be used while fixing two pairs (dp[i][j][k] = # ways with
 * all nodes <i cleared, fixed paths are on nodes j and k), working out to just the right complexity. Careful to use
 * PIE with the 1st two overcounts.
 * 
 * Runtime: O(4 * N^3)
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 204;
const ll MOD = 1e9+7;

int N, K;
int type[MAXN];
struct Edge {
    int a, b;
};
vector<Edge> bad;
ll fact[MAXN];
vector<int> adj[MAXN];

inline void plusMod(ll& a, ll b) {
    a = (a+b) % MOD;
}

ll dpO[MAXN];
ll dp[MAXN][MAXN][MAXN];

ll overcount(int s1, int f1, int s2, int f2) {
    debug << "overcount " << s1 << ' ' << f1 << ' ' << s2 << ' ' << f2 << endl;
    dp[0][s1][s2] = 1;
    rep(i, 0, N-1) {
        rep(j, 0, N) {
            rep(k, 0, N) {
                if (dp[i][j][k] == 0) continue;
                debug << i << ' ' << j << ' ' << k << " = " << dp[i][j][k] << endl;
                int deg = sz(adj[i]);
                // Move normally
                plusMod(dp[i+1][j][k], dp[i][j][k] * fact[deg]);
                if (j == i && k == i && deg >= 2) {
                    // Move both
                    if (deg <= 1) continue;
                    for (int e : adj[i]) {
                        for (int f : adj[i]) {
                            if (e == f) continue;
                            plusMod(dp[i+1][e][f], dp[i][j][k] * fact[deg-2]);
                        }
                    }
                }
                if (j == i && deg != 0) {
                    // Move j
                    for (int e : adj[i]) {
                        plusMod(dp[i+1][e][k], dp[i][j][k] * fact[deg-1]);
                    }
                }
                if (k == i && deg != 0) {
                    // Move k
                    for (int e : adj[i]) {
                        plusMod(dp[i+1][j][e], dp[i][j][k] * fact[deg-1]);
                    }
                }
            }
        }
    }
    ll over = dp[N-1][f1][f2];
    rep(i, 0, N) {
        rep(j, 0, N) {
            rep(k, 0, N) {
                dp[i][j][k] = 0;
            }
        }
    }
    debug << "result: " << over << endl;
    return over;
}

void solve() {
    cin >> N >> K;
    string S; cin >> S;
    rep(i, 0, N) {
        if (S[i] == 'S') type[i] = 0;
        else if (S[i] == 'R') type[i] = 2;
        else type[i] = 1;
    }
    // int M; cin >> M;
    // rep(i, 0, M) {
    //     int a, b; cin >> a >> b;
    //     a--, b--;
    //     adj[a].push_back(b);
    // }
    rep(i, 0, N) {
        cin >> S;
        rep(j, 0, N) {
            if (S[j] == '1') {
                if (i < j) adj[i].push_back(j);
                else bad.push_back({i, j});
            }
        }
    }

    // Add a node for each receiver
    rep(i, 0, N) {
        if (type[i] == 2) {
            type[N] = 3;
            adj[i].push_back(N);
            N++;
        }
    }

    // Add send and receive nodes for bad edges
    rep(i, 0, sz(bad)) {
        type[N] = 3;
        adj[bad[i].a].push_back(N);
        bad[i].a = N;
        N++;
    }

    rep(i, 0, N) {
        debug << i << ": ";
        for (int e : adj[i]) debug << e << ' ';
        debug << endl;
    }

    // DP to find all paths
    dpO[0] = 1;
    rep(i, 0, N-1) {
        int deg = sz(adj[i]);
        plusMod(dpO[i+1], dpO[i]*fact[deg]);
    }
    debug << "original: " << dpO[N-1] << '\n';

    // Handle overcount
    ll answer = dpO[N-1];
    if (K == 1) {
        answer -= overcount(bad[0].b, bad[0].a, N-1, N-1);
    } else if (K == 2) {
        answer -= overcount(bad[0].b, bad[0].a, N-1, N-1);
        answer -= overcount(bad[1].b, bad[1].a, N-1, N-1);
        answer += overcount(bad[0].b, bad[0].a, bad[1].b, bad[1].a);
        answer -= overcount(bad[0].b, bad[1].a, bad[1].b, bad[0].a);
    }
    answer = ((answer % MOD) + MOD) % MOD;

    cout << answer << '\n';

    // Cleanup
    rep(i, 0, N) {
        type[i] = 0;
        adj[i].clear();
        dpO[i] = 0;
        bad.clear();
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fact[0] = 1;
    rep(i, 1, MAXN) fact[i] = fact[i-1] * i % MOD;
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}