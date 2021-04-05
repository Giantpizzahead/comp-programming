#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 4e5;

int N, C, bestN, bestS, best2N, best2S;
vector<int> adj[MAXN];
bool ans[MAXN];

int stSize[MAXN];

void dfsSize(int n, int p) {
    stSize[n] = 1;
    for (int e : adj[n]) {
        if (e == p) continue;
        dfsSize(e, n);
        stSize[n] += stSize[e];
    }
}

bool findCentroid() {
    dfsSize(0, 0);
    C = -1;
    rep(n, 0, N) {
        bool isCent = (N - stSize[n] <= N/2);
        for (int e : adj[n]) {
            if (stSize[e] > stSize[n]) continue;
            if (stSize[e] > N/2) {
                isCent = false;
                break;
            }
        }
        if (isCent) {
            if (C == -1) C = n;
            else return false;
        }
    }
    return true;
}

void dfsAnswer(int n, int p, int s) {
    int outer = N - stSize[n] - s;
    ans[n] = (outer <= N/2);
    for (int e : adj[n]) {
        if (e == p) continue;
        dfsAnswer(e, n, s);
    }
}

void solve() {
    cin >> N;
    int u, v;
    rep(i, 1, N) {
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if (!findCentroid()) {
        // 2 centroids
        rep(i, 0, N) cout << 1 << " \n"[i == N-1];
        return;
    }
    // Find subtree sizes
    dfsSize(C, C);
    bestS = -1, best2S = -1;
    for (int e : adj[C]) {
        if (stSize[e] > bestS) {
            best2S = bestS;
            best2N = bestN;
            bestS = stSize[e];
            bestN = e;
        } else if (stSize[e] > best2S) {
            best2S = stSize[e];
            best2N = e;
        }
    }
    // Gen answers
    ans[C] = true;
    for (int e : adj[C]) {
        if (e == bestN) dfsAnswer(e, C, best2S);
        else dfsAnswer(e, C, bestS);
    }
    rep(i, 0, N) cout << ans[i] << " \n"[i == N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}