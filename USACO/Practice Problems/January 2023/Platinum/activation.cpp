#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

int N;
vector<vector<int>> adj;
vector<vector<bool>> inSubtree;
vector<vector<int>> dists;

void dfsSubtree(int n, int id) {
    inSubtree[id][n] = true;
    for (int e : adj[n]) dfsSubtree(e, id);
}

int ans;
int currMoves, currOn, numUsed;
vector<bool> currUsed;

void tryPerms() {
    if (numUsed == N) {
        ans = min(currMoves + (N - dists[currOn][0]), ans);
        return;
    }
    rep(i, 0, N) {
        if (currUsed[i]) continue;
        int newMoves = currMoves;
        if (currOn == -1) newMoves += (N - dists[0][i]);
        else newMoves += dists[currOn][i];

        numUsed++;
        currUsed[i] = true;
        int prevMoves = currMoves;
        currMoves = newMoves;
        int prevOn = currOn;
        currOn = i;

        tryPerms();

        numUsed--;
        currUsed[i] = false;
        currMoves = prevMoves;
        currOn = prevOn;
    }
}

void solve() {
    cin >> N;
    adj.resize(N);
    rep(i, 1, N) {
        int p; cin >> p; p--;
        adj[p].push_back(i);
    }
    inSubtree.resize(N, vector<bool>(N, false));
    rep(i, 0, N) dfsSubtree(i, i);
    dists.resize(N, vector<int>(N, 0));
    rep(i, 0, N) rep(j, 0, N) {
        rep(k, 0, N) dists[i][j] += (inSubtree[i][k] != inSubtree[j][k]);
    }

    // Try all permutations
    ans = 1e9;
    currMoves = 0;
    currOn = -1;
    numUsed = 0;
    currUsed.resize(N);
    tryPerms();
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
