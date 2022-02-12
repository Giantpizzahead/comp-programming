/*
IOI 2010 Day 2 - Traffic
Solution: Find the weighted centroid(s) of the tree.
Runtime: O(N)
*/

#include "grader.h"
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e6+5;

int N, K;
int P[MAXN];
vector<int> adj[MAXN];
vector<int> centroids;

void dfsPre(int n, int p) {
    for (int e : adj[n]) {
        if (e == p) continue;
        dfsPre(e, n);
        P[n] += P[e];
    }
}

void findCentroid(int n, int p) {
    // cout << "cent " << n << " " << P[n] << endl;
    bool isCentroid = (K - P[n] <= K/2);
    for (int e : adj[n]) {
        if (e == p) continue;
        if (P[e] >= K/2) {
            if (P[e] > K/2) isCentroid = false;
            findCentroid(e, n);
        }
    }
    if (isCentroid) centroids.push_back(n);
}

int LocateCentre(int n, int pp[], int S[], int D[]) {
    N = n;
    K = 0;
    rep(i, 0, N) {
        P[i] = pp[i];
        K += P[i];
    }
    rep(i, 0, N-1) {
        adj[S[i]].push_back(D[i]);
        adj[D[i]].push_back(S[i]);
    }
    dfsPre(0, 0);
    findCentroid(0, 0);
    sort(all(centroids));
    // for (int x : centroids) cout << x << endl;
    return centroids[0];
}

/*
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    int p[n], s[n-1], d[n-1];
    rep(i, 0, n) cin >> p[i];
    rep(i, 0, n-1) cin >> s[i] >> d[i];
    LocateCentre(n, p, s, d);
    return 0;
}
*/
