/*
Solution: Make a graph using the info, with self-loop edges for the ones who are sure. Then, use casework.
Each component in the graph must have the same number of edges and nodes. If the component contains a self-loop edge,
then it must be filled in a unique way (think of the other edges like a tree). Otherwise, there are 2 ways (choose for
one edge, then the rest becomes a tree again).
Runtime: O(N)
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e6+5;
const ll MOD = 1e9+7;

ll ans = 1;
bool valid = true;
int N;
int person[MAXN];
bool vis[MAXN];
vector<pair<int, int>> adj[MAXN];

int currN, currE;

void dfs(int n) {
    currN++;
    vis[n] = true;
    for (auto& e : adj[n]) {
        currE++;
        if (!vis[e.first]) {
            if (person[n] != -1 && person[e.first] == -1) person[e.first] = e.second;
            dfs(e.first);
            if (person[n] == -1 && person[e.first] != -1) person[n] = e.second;
        }
    }
}

void solve() {
    cin >> N;
    rep(i, 0, N) person[i] = -1;
    rep(i, 0, N) {
        char c;
        int a, b;
        cin >> c >> a; a--;
        if (c == 'N') {
            cin >> b; b--;
            adj[a].push_back({b, i});
            adj[b].push_back({a, i});
        } else {
            adj[a].push_back({a, i});
            adj[a].push_back({a, i});
            person[a] = i;
        }
    }
    rep(i, 0, N) {
        if (!vis[i]) {
            currN = 0;
            currE = 0;
            dfs(i);
            currE /= 2;
            if (currN == 1 && currE == 1) continue;
            else if (currN == 1) valid = false;
            else if (currE != currN) valid = false;
            else if (person[i] == -1) ans = ans * 2 % MOD;
        }
    }
    if (!valid) ans = 0;
    if (ans == 1) {
        cout << "TAK\n";
        // Generate people
        rep(i, 0, N) vis[i] = false;
        rep(i, 0, N) if (!vis[i]) dfs(i);
        vector<int> res(N);
        rep(i, 0, N) res[person[i]] = i+1;
        rep(i, 0, N) cout << res[i] << '\n';
    } else {
        cout << "NIE\n";
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}