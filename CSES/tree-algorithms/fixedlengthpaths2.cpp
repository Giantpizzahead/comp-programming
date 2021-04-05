#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

ll answer = 0;
int N, K1, K2;
bool blocked[MAXN];
vi adj[MAXN];

int currN;
int stSize[MAXN], cntPre[MAXN], addedPre[MAXN];

void dfsSize(int n, int p) {
    stSize[n] = 1;
    for (int e : adj[n]) {
        if (e == p || blocked[e]) continue;
        dfsSize(e, n);
        stSize[n] += stSize[e];
    }
}

int currMaxPath;
vector<int> currPaths;

void dfsPaths(int n, int p, int d) {
    currMaxPath = max(d, currMaxPath);
    currPaths.push_back(d);
    if (d == K2) return;
    for (int e : adj[n]) {
        if (e == p || blocked[e]) continue;
        dfsPaths(e, n, d+1);
    }
}

void solveRec(int n) {
    // Find centroid
    dfsSize(n, n);
    currN = stSize[n];
    bool changed;
    do {
        changed = false;
        for (int e : adj[n]) {
            if (stSize[e] > stSize[n] || blocked[e]) continue;
            if (stSize[e] > currN / 2) {
                n = e;
                changed = true;
                break;
            }
        }
    } while (changed);
    // cout << "centroid " << n+1 << endl;

    // Solve for all paths that include the centroid
    rep(i, max(0, K2-currN+1-1), K2) cntPre[i] = 0;
    cntPre[K2] = 1;
    for (int e : adj[n]) {
        if (blocked[e]) continue;
        // cout << "search " << e+1 << endl;
        currMaxPath = -1;
        dfsPaths(e, n, 1);
        // Update answer
        for (int d : currPaths) {
            // This path can link with [d, d+(K2-K1)]
            int a = max(d, K2-currN+1), b = min(d+K2-K1, K2);
            if (a <= b) {
                int sumPre = cntPre[b] - cntPre[a-1];
                answer += sumPre;
                // cout << d << ": " << sumPre << endl;
            }
        }
        // Add paths to prefix sum count
        rep(i, K2-currMaxPath, K2+1) {
            addedPre[i] = 0;
        }
        while (!currPaths.empty()) {
            // cout << "added " << K2-currPaths.back() << endl;
            addedPre[K2-currPaths.back()]++;
            currPaths.pop_back();
        }
        rep(i, K2-currMaxPath, K2+1) {
            if (i != K2-currMaxPath) addedPre[i] += addedPre[i-1];
            cntPre[i] += addedPre[i];
        }
        // cout << "pre ";
        // rep(i, 0, K2+1) cout << cntPre[i] << ' ';
        // cout << endl;
    }

    // Recurse
    blocked[n] = true;
    for (int e : adj[n]) {
        if (!blocked[e]) solveRec(e);
    }
}

void solve() {
    cin >> N >> K1 >> K2;
    rep(i, 1, N) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    solveRec(0);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}