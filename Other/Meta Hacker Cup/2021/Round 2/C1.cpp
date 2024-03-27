#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int R, C, K, answer;
vector<vector<bool>> G;

void simulateUp() {
    // cout << "k = " << K << endl;
    vector<int> upAnswers(R);
    rep(i, 0, R) upAnswers[i] = i;
    rep(j, 0, C) {
        int numCars = 0;
        int currMoves = 0;
        rep(i, 0, R) {
            numCars += G[i][j];
            while (currMoves < R) {
                int k = min(K+currMoves, R-1);
                if (k != i) break;
                // Process this
                if (numCars > K || (K+currMoves < R && G[i][j])) upAnswers[currMoves]++;
                currMoves++;
            }
        }
    }
    rep(i, 0, R) {
        // cout << i << ": " << upAnswers[i] << endl;
        answer = min(upAnswers[i], answer);
    }
}

void solve() {
    // cout << endl;
    G.resize(0);
    cin >> R >> C >> K;
    K--;
    G.resize(R);
    rep(i, 0, R) G[i].resize(C);
    rep(i, 0, R) {
        rep(j, 0, C) {
            char c; cin >> c;
            G[i][j] = (c == 'X');
        }
    }

    answer = C;
    // Simulate moving up
    simulateUp();
    // Flip the board
    rep(i, 0, R/2) {
        rep(j, 0, C) {
            swap(G[i][j], G[R-1-i][j]);
        }
    }
    // rep(i, 0, R) {
    //     rep(j, 0, C) cout << G[i][j];
    //     cout << endl;
    // }
    K = R-1-K;
    // Simulate again (moving down)
    simulateUp();
    cout << answer << '\n';
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