/*
ID: sunnyky1
LANG: C++11
TASK: milk6
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 32, MAXM = 2005;

int N, M;
int S[MAXM], E[MAXM];
ll C[MAXM];
set<int> adj[MAXN];

int currIter = 0;
int vis[MAXN];
ll currScale, maxCap = 0;

ll dfs(int n, ll f) {
    vis[n] = currIter;
    if (n == N-1) return f;
    for (int e : adj[n]) {
        ll nf = min(f, C[e]);
        if (vis[E[e]] == currIter || nf < currScale) continue;
        ll ret = dfs(E[e], nf);
        if (ret != 0) {
            C[e] -= ret;
            if (C[e] == 0) adj[n].erase(e);
            if (C[e^1] == 0) adj[E[e]].insert(e^1);
            C[e^1] += ret;
            return ret;
        }
    }
    return 0;
}

ll getFlow() {
    ll ans = 0;
    currScale = maxCap;
    while (currScale > 0) {
        currIter++;
        ll flow = dfs(0, maxCap);
        // debug << "augment " << currScale << " = " << flow << '\n';
        if (flow == 0) currScale /= 2;
        else ans += flow;
    }
    // Reset capacities
    rep(i, 0, N) adj[i].clear();
    rep(i, 0, M) {
        C[i*2] += C[i*2+1];
        C[i*2+1] = 0;
        adj[S[i*2]].insert(i*2);
    }
    return ans;
}

void findCut(int n) {
    vis[n] = currIter;
    for (int e : adj[n]) {
        if (e % 2 == 1 || vis[E[e]] == currIter || C[e] == 0) continue;
        findCut(E[e]);
    }
}

bool chosenBlock[MAXM];

bool sanityCheck(int n) {
    vis[n] = currIter;
    if (n == N-1) return false;
    for (int e : adj[n]) {
        if (e % 2 == 1 || vis[E[e]] == currIter || chosenBlock[e]) continue;
        if (!sanityCheck(E[e])) return false;
    }
    return true;
}

void solve() {
    cin >> N >> M;
    int lenAdj = 1000+1;
    int indexAdj = 1; //999*1000/2+1;
    rep(i, 0, M) {
        cin >> S[i*2] >> E[i*2] >> C[i*2];
        // if (S[i*2] == E[i*2] || C[i*2] == 0) {
        //     i--, M--;
        //     continue;
        // }
        S[i*2]--, E[i*2]--;
        S[i*2+1] = E[i*2];
        E[i*2+1] = S[i*2];
        C[i*2+1] = 0;
        adj[S[i*2]].insert(i*2);
        // adj[S[i*2+1]].push_back(i*2+1);
        // Modify cost to encourage min # of shut down routes, followed by index
        C[i*2] = C[i*2] * lenAdj + 1;
        // C[i*2] = C[i*2] * indexAdj + i;
        maxCap = max(C[i*2], maxCap);
    }

    // Get the flow
    ll flow = getFlow();
    rep(i, 0, M) debug << C[i*2] << ' ' << C[i*2+1] << '\n';

    // Find edges in min cut
    vector<int> edges;
    rep(e, 0, M) {
        debug << "testing edge " << e+1 << '\n';
        ll saved = C[e*2];
        C[e*2] = 0;
        ll newFlow = getFlow();
        if (flow - saved == newFlow) edges.push_back(e);
        C[e*2] = saved;
    }
    // currIter++;
    // findCut(0);
    // rep(i, 0, N) debug << (vis[i] == currIter) << " \n"[i==N-1];
    // if (vis[S[i*2]] == currIter && vis[E[i*2]] != currIter && C[i*2] == 0) edges.push_back(i);

    // Print results
    flow = flow / indexAdj / lenAdj;
    cout << flow << ' ' << sz(edges) << '\n';
    for (int e : edges) cout << e+1 << '\n';

    // Sanity check
    for (int e : edges) chosenBlock[e*2] = true;
    currIter++;
    debug << "sanity check: " << sanityCheck(0) << '\n';
}

int main() {
    freopen("milk6.in", "r", stdin);
    freopen("milk6.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}