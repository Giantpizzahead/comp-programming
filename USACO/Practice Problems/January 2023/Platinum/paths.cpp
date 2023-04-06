/*
Each tractor can reach a contiguous interval of other tractors.

To find the shortest possible path, you can use binary lifting on the furthest
right and left tractors that each one can reach.

Fix a special tractor k. It only works if dist(a, b) = dist(a, k) + dist(k, b).
It's guaranteed that dist(a, b) is at least dist(a, k) + dist(k, b), it just can't
be greater.
Evaluating this directly from the definition works if |K| <= 10. But what about more?

Choosing to use a special tractor might stray from the optimal rightmost at each time, but only once.
That is, first you need to check the earliest dist at which the special tractor is reachable.

Let's just settle for the partial credit.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

struct Tractor {
    int l, r;
};

void doBinaryLifting(vector<vector<int>>& dists) {
    rep(i, 1, sz(dists)) {
        rep(j, 0, sz(dists[i])) {
            dists[i][j] = dists[i-1][dists[i-1][j]];
        }
    }
}

int getDist(int a, int b, vector<vector<int>>& dists) {
    if (a == b) return 0;
    int dist = 0;
    for (int k = sz(dists)-1; k >= 0; k--) {
        if (dists[k][a] < b) {
            dist += (1 << k);
            a = dists[k][a];
        }
    }
    // cout << "getDist(" << a << ", " << b << ") = " << dist+1 << endl;
    return dist + 1;
}

void solve() {
    // Parse input
    int N, Q; cin >> N >> Q;
    vector<int> lLocs, rLocs;
    string S; cin >> S;
    rep(i, 0, 2*N) {
        (S[i] == 'L' ? lLocs : rLocs).push_back(i);
    }
    vector<Tractor> tractors;
    rep(i, 0, N) tractors.push_back({lLocs[i], rLocs[i]});
    vector<int> special;
    string T; cin >> T;
    rep(i, 0, N) if (T[i] == '1') special.push_back(i);

    // Find initial furthest reachable left and right
    int K = (int) log2(N) + 2;
    vector<vector<int>> reachLeft(K, vector<int>(N)), reachRight(K, vector<int>(N));
    int ci = 0;
    rep(i, 0, N) {
        while (ci != N && tractors[ci].l < tractors[i].r) ci++;
        reachRight[0][i] = ci-1;
    }
    ci = N-1;
    for (int i = N-1; i >= 0; i--) {
        while (ci != -1 && tractors[ci].r > tractors[i].l) ci--;
        reachLeft[0][i] = ci+1;
    }

    // Binary lifting
    doBinaryLifting(reachLeft);
    doBinaryLifting(reachRight);

    // Answer each query
    rep(i, 0, Q) {
        int a, b; cin >> a >> b;
        a--, b--;
        if (a > b) swap(a, b);
        // Shortest distance
        int dist = getDist(a, b, reachRight);
        // Special tractors
        int numSpecial = 0;
        for (int s : special) {
            if (s < a || s > b) continue;
            if (getDist(a, s, reachRight) + getDist(s, b, reachRight) == dist) {
                numSpecial++;
            }
        }
        cout << dist << " " << numSpecial << "\n";
    }

    // cout << "tractors:\n";
    // rep(i, 0, N) cout << tractors[i].l << " " << tractors[i].r << "\n";
    // cout << "reachLeft:\n";
    // rep(i, 0, K) rep(j, 0, N) cout << reachLeft[i][j] << " \n"[j==N-1];
    // cout << "reachRight:\n";
    // rep(i, 0, K) rep(j, 0, N) cout << reachRight[i][j] << " \n"[j==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
