/*
https://codeforces.com/contest/1693/problem/C

Solution: Use a sort of reverse Dijkstra from the ending node. d=0 from N-1 to N-1.
For each edge from a to b, simulate starting at node a, blocking all edges that lead to unvisited nodes, and taking one
of the edges to a visited node. Push the resulting distance to the priority queue (if applicable). This efficiently
tries all possible paths for each node.
Runtime: O(N * log(N))
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 2e5+5;
const int INF = 1e9+7;

int N, M;
int openDeg[MAXN];
int dist[MAXN];
vi adj[MAXN], revAdj[MAXN];

struct Pair {
    int n, c;
    bool operator<(const Pair& o) const {
        return c > o.c;
    }
};
priority_queue<Pair> pq;

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int a, b; cin >> a >> b; a--, b--;
        adj[a].push_back(b);
        revAdj[b].push_back(a);
        openDeg[a]++;
    }
    rep(i, 0, N) dist[i] = INF;
    dist[N-1] = 0;
    pq.push({N-1, 0});
    while (!pq.empty()) {
        Pair p = pq.top(); pq.pop();
        int n = p.n, c = p.c;
        if (dist[n] < c) continue;
        for (int e : revAdj[n]) {
            openDeg[e]--;
            int nc = c + 1 + openDeg[e];
            if (nc < dist[e]) {
                dist[e] = nc;
                pq.push({e, nc});
            }
        }
    }
    cout << dist[0] << '\n';
    // rep(i, 0, N) cout << dist[i] << " \n"[i==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}