#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;
using namespace std;

const int MAXN = 360;

int N, J, K, M;
int dp[MAXN][MAXN][2];
vector<int> adj[MAXN];

void solve() {
    cin >> J >> K >> M >> N;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
    for(int j = 0; j < N; ++j) {
	string s;
	getline(cin, s);
	int sum = 0, changed = 0;
	for(int i = 0; i < s.size(); ++i) {
        	if(s[i] == ' ') {
 			changed = 0;
                        adj[j].push_back(sum);
                        sum = 0;
                } else {
                        sum *= 10;
                        sum += s[i] - '0';
                        changed = true;
                }
        }
        if(changed) adj[j].push_back(sum);
    }
    // Base cases
    rep(j, 0, N) rep(k, 0, 2) dp[J][j][k] = 1;
    rep(i, 0, N) rep(k, 0, 2) dp[i][i][k] = -1;
    while (true) {
        bool edited = false;
        rep(i, 0, N) {
            rep(j, 0, N) {
                rep(k, 0, 2) {
                    if (dp[i][j][k] != 0) continue;
                    if (k == 0) {
                        // Bunny's turn, can it win?
                        bool allLose = true;
                        for (int e : adj[i]) {
                            if (dp[e][j][1-k] == 1) {
                                dp[i][j][k] = 1;
                                edited = true;
                            }
                            if (dp[e][j][1-k] != -1) allLose = false;
                        }
                        if (allLose) {
                            dp[i][j][k] = -1;
                            edited = true;
                        }
                    } else {
                        // Wolf's turn, can it win?
                        bool allLose = true;
                        for (int e : adj[j]) {
                            if (e == J) continue;
                            if (dp[i][e][1-k] == -1) {
                                dp[i][j][k] = -1;
                                edited = true;
                            }
                            if (dp[i][e][1-k] != 1) allLose = false;
                        }
                        if (allLose) {
                            dp[i][j][k] = 1;
                            edited = true;
                        }
                    }
                }
            }
        }
        if (!edited) break;
    }
    cout << dp[K][M][0] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}