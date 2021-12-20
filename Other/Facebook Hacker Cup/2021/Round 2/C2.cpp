#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2000005;

int R, C, K, S;
vector<vector<bool>> G;
vector<vector<int>> indPre, indAns;
int currAns[MAXN], finalAns[MAXN];
int updateI[MAXN], updateJ[MAXN];

void simulateUp() {
    // Only need to check within a range of [K, K+C]
    // Otherwise it's better to just remove all cars from row K
    int minI = max(K, 0);
    int maxI = min(K+C, R);
    // Initialize (process all rows at first)
    indPre.resize(0);
    indPre.resize(R, vector<int>(C));
    indAns.resize(0);
    indAns.resize(R, vector<int>(C));
    rep(j, 0, C) {
        rep(i, 0, R) {
            indPre[i][j] = (i == 0 ? 0 : indPre[i-1][j]) + G[i][j];
        }
    }
    // From C1, initialize currAns and indAns arrays
    rep(i, 0, R) currAns[i] = i;
    rep(j, 0, C) {
        int currMoves = 0;
        rep(i, 0, R) {
            while (currMoves < R) {
                int k = min(K+currMoves, R-1);
                if (k != i) break;
                // Process this
                if (indPre[i][j] > K || (K+currMoves < R && G[i][j])) {
                    currAns[currMoves]++;
                    indAns[currMoves][j] = 1;
                } else indAns[currMoves][j] = 0;
                currMoves++;
            }
        }
    }
    // Process each update, only processing rows in [minI, maxI)
    rep(s, 0, S) {
        int ui = updateI[s], uj = updateJ[s];
        // Update prefix
        int ci = max(ui, minI);
        int d = (G[ui][uj] ? -1 : 1);
        rep(i, ci, maxI) {
            indPre[i][uj] += d;
        }
        // Update array
        G[ui][uj] = !G[ui][uj];
        // Update answer for the whole section
        int currMoves = 0;
        rep(i, minI, maxI) {
            while (currMoves < min(R, C)) {
                int k = min(K+currMoves, R-1);
                if (k != i) break;
                // Process this
                if (indPre[i][uj] > K || (K+currMoves < R && G[i][uj])) {
                    if (indAns[currMoves][uj] == 0) {
                        currAns[currMoves]++;
                        indAns[currMoves][uj] = 1;
                    }
                } else {
                    if (indAns[currMoves][uj] == 1) {
                        currAns[currMoves]--;
                        indAns[currMoves][uj] = 0;
                    }
                }
                currMoves++;
            }
        }
        // Get the best answer
        rep(i, 0, min(R, C)) {
            finalAns[s] = min(currAns[i], finalAns[s]);
        }
        // cout << "update " << s << ": " << finalAns[s] << endl;
        // rep(i, 0, R) cout << currAns[i] << " \n"[i==R-1];
        // rep(i, 0, R) rep(j, 0, C) cout << indPre[i][j] << " \n"[j==C-1];
    }
}

void solve() {
    // cout << endl;
    cin >> R >> C >> K >> S;
    K--;
    rep(i, 0, S) finalAns[i] = C;
    G.clear();
    G.resize(R, vector<bool>(C));
    rep(i, 0, R) {
        rep(j, 0, C) {
            char c; cin >> c;
            G[i][j] = (c == 'X');
        }
    }
    rep(i, 0, S) {
        cin >> updateI[i] >> updateJ[i];
        updateI[i]--, updateJ[i]--;
    }

    // Simulate moving up
    simulateUp();
    // Undo all updates
    rep(i, 0, S) {
        int ui = updateI[i], uj = updateJ[i];
        G[ui][uj] = !G[ui][uj];
    }
    // Flip the board and updates
    rep(i, 0, R/2) {
        rep(j, 0, C) {
            swap(G[i][j], G[R-1-i][j]);
        }
    }
    K = R-1-K;
    rep(i, 0, S) {
        updateI[i] = R-1-updateI[i];
    }
    // Simulate again (moving down)
    simulateUp();

    ll answerSum = 0;
    rep(i, 0, S) answerSum += finalAns[i];
    cout << answerSum << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}