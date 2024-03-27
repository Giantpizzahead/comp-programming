#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 1e5+5;
const int INF = 1e9+7;

int N, K;
bool isInfected[MAXN];
bool couldBeFirst[MAXN];
vector<int> adj[MAXN];

bool vis[MAXN];

void bfsFromHealthy() {
    queue<pair<int, int>> q;
    rep(i, 0, N) {
        if (!isInfected[i]) {
            q.push({i, 0});
            vis[i] = true;
        } else vis[i] = false;
    }
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        for (int e : adj[p.first]) {
            if (vis[e] || p.second + 1 > K) continue;
            vis[e] = true;
            q.push({e, p.second + 1});
        }
    }
    rep(i, 0, N) couldBeFirst[i] = !vis[i];
}

bool bfsSolvable() {
    // If using all marked nodes, can we get correct ending infected?
    queue<pair<int, int>> q;
    rep(i, 0, N) {
        if (couldBeFirst[i]) {
            q.push({i, 0});
            vis[i] = true;
        } else vis[i] = false;
    }
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        for (int e : adj[p.first]) {
            if (vis[e] || p.second + 1 > K) continue;
            vis[e] = true;
            q.push({e, p.second + 1});
        }
    }
    rep(i, 0, N) if (vis[i] != isInfected[i]) return false;
    return true;
}


int currAns;
int closestStar[MAXN], furthestNormal[MAXN];

void dfs(int n, int p) {
    vis[n] = true;
    closestStar[n] = INF, furthestNormal[n] = -INF;
    for (int e : adj[n]) {
        if (e == p) continue;
        else if (isInfected[e]) {
            dfs(e, n);
            furthestNormal[n] = max(furthestNormal[e] + 1, furthestNormal[n]);
            closestStar[n] = min(closestStar[e] + 1, closestStar[n]);
        } else {
            // Don't do anything...
            // Connected to a non-marked node, this must be a star!
            // furthestNormal[n] = max(K, furthestNormal[n]);
        }
    }
    if (closestStar[n] > K) furthestNormal[n] = max(furthestNormal[n], 0);

    assert(furthestNormal[n] <= K);

    if (closestStar[n] + furthestNormal[n] <= K) {
        // All satisfied here
        furthestNormal[n] = -INF;
        return;
    } else if (furthestNormal[n] == K) {
        // Need to put a star here
        // cout << "star at " << n+1 << endl;
        currAns++;
        closestStar[n] = 0;
        furthestNormal[n] = -INF;
        return;
    } else {
        // No need to do anything yet
        return;
    }
}

int solveQuery() {
    // First, mark nodes that could be initially infected
    bfsFromHealthy();

    // Ensure this is solvable
    if (!bfsSolvable()) return -1;

    // Now, solve each individual marked component
    currAns = 0;
    rep(i, 0, N) vis[i] = false;
    rep(i, 0, N) {
        if (vis[i] || !couldBeFirst[i]) continue;
        // cout << "dfs " << i+1 << endl;
        dfs(i, i);
        if (furthestNormal[i] >= 0) currAns++;  // Need one more star
    }
    return currAns;
}

void solve() {
    cin >> N;
    string str; cin >> str;
    rep(i, 0, N) isInfected[i] = (str[i] == '1');
    rep(i, 1, N) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int Q; cin >> Q;
    rep(i, 0, Q) {
        cin >> K;
        cout << solveQuery() << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("test.in", "r", stdin);
    solve();
    return 0;
}
