/*
Solution: Tree DP.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 1e6+5;

int N;
int numMerges[MAXN];
vector<int> adj[MAXN];
set<string> topics[MAXN];

map<string, int>* dfs(int n) {
    map<string, int>* curr = new map<string, int>();
    vector<map<string, int>*> res;
    for (int e : adj[n]) {
        res.emplace_back(dfs(e));
        numMerges[n] += numMerges[e];
    }
    numMerges[n] += max(sz(adj[n]) - 1, 0);

    if (sz(adj[n]) == 0) {
        // Leaf
        for (auto& currStr : topics[n]) (*curr)[currStr] = 1;
        return curr;
    }

    // General case
    // map<string, int> strCnt;
    // for (set<string>* strSet : res) {
    //     for (auto& s : *strSet) strCnt[s]++;
    // }

    // Merge maps
    sort(all(res), [](const map<string, int>* a, const map<string, int>* b) { return a->size() < b->size(); });
    reverse(all(res));
    for (int i = 1; i < sz(res); i++) {
        for (auto& p : *res[i]) (*res[0])[p.first] += p.second;
    }
    curr = res[0];

    for (auto& currStr : topics[n]) {
        // One child can miss it
        int numPaths = (*curr)[currStr];
        if (numPaths < numMerges[n]) {
            curr->erase(currStr);
        } else if (numPaths == numMerges[n]) {
            (*curr)[currStr]++;  // Use this topic
        }  // Otherwise, no help needed
    }

    // cerr << "on node " << n+1 << ":    ";
    // for (auto& p : *curr) {
    //     cerr << p.first << ": " << p.second << ", ";
    // }
    // cerr << endl;
    return curr;
}

void solve() {
    cin >> N;
    rep(n, 0, N) {
        adj[n].clear();
        topics[n].clear();
        numMerges[n] = 0;
    }
    rep(i, 1, N) {
        int x; cin >> x; x--;
        adj[x].push_back(i);
    }
    rep(n, 0, N) {
        int m; cin >> m;
        rep(k, 0, m) {
            string s; cin >> s;
            topics[n].insert(s);
        }
    }

    map<string, int>* res = dfs(0);
    int ans = 0;
    for (auto& p : *res) if (p.second == numMerges[0]+1) ans++;
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // For HackerCup
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
