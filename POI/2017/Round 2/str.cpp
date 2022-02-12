/*
Solution:
# components = 1 + sum(degree of strike nodes) - # of strike nodes - # of adjacent strike nodes

How to efficiently track # of adjacent strike nodes?
For each edge:
Process on heavier node (more updates), sweep to determine active times
If each edge is directed towards the node that processes the edge, the worst case should be O(M*log(M)) events

Runtime: O(M * log^2(M))
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 5e5+5;

int N, M;
int ans[MAXN];
vector<int> adj[MAXN], events[MAXN];

void solve() {
    cin >> N;
    rep(i, 1, N) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    ans[0]++;
    cin >> M;
    rep(i, 0, M) {
        int n; cin >> n;
        if (n > 0) {
            n--;
            events[n].push_back(i);
            ans[i] += sz(adj[n])-1;
        } else {
            n = -n-1;
            events[n].push_back(i);
            ans[i] -= sz(adj[n])-1;
        }
    }

    // Process events at greater node
    rep(n, 0, N) {
        vector<pair<int, bool>> curr;
        for (int e : adj[n]) {
            if (make_pair(sz(events[n]), n) < make_pair(sz(events[e]), e)) continue;
            // Process this edge here
            rep(i, 0, sz(events[e])) {
                curr.push_back({events[e][i], i % 2});
            }
        }
        sort(all(curr));
        int ni = 0, ci = 0, numAdj = 0;
        bool on = false;
        while (ni != sz(events[n]) || ci != sz(curr)) {
            if (ci == sz(curr) || (ni != sz(events[n]) && events[n][ni] <= curr[ci].first)) {
                int t = events[n][ni++];
                if (!on) ans[t] += numAdj;
                else ans[t] -= numAdj;
                on = !on;
            } else {
                int t = curr[ci].first;
                bool b = curr[ci++].second;
                if (b) {
                    numAdj++;
                    if (on) ans[t]++;
                } else {
                    numAdj--;
                    if (on) ans[t]--;
                }
            }
        }
    }

    rep(i, 1, M) ans[i] += ans[i-1];
    rep(i, 0, M) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}