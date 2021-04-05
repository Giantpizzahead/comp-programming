#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N, R;
int numLeaves[MAXN];
bool isLeaf[MAXN];
vi adj[MAXN];

void findLeaves(int n, int p) {
    for (int e : adj[n]) {
        if (e == p) continue;
        findLeaves(e, n);
        numLeaves[n] += numLeaves[e];
    }
    if (sz(adj[n]) == 1) {
        isLeaf[n] = true;
        numLeaves[n]++;
    }
}

vector<pair<int, int>> pairings[MAXN];

void groupLeaves(int n, int p, int mustPair) {
    if (isLeaf[n] || mustPair <= 0) exit(0);
    int maxLeaves = 0, leafSum = 0, maxE = -1;
    for (int e : adj[n]) {
        if (e == p) continue;
        leafSum += numLeaves[e];
        if (numLeaves[e] > maxLeaves) {
            maxLeaves = numLeaves[e];
            maxE = e;
        }
    }
    int pairsPossible = leafSum / 2;
    if (maxLeaves > leafSum - maxLeaves) pairsPossible = leafSum - maxLeaves;
    if (pairsPossible < mustPair / 2) {
        // Pair all with max leaf, and go down
        for (int e : adj[n]) {
            if (e != p && e != maxE) {
                rep(i, 0, numLeaves[e]) {
                    mustPair -= 2;
                    pairings[n].emplace_back(maxE, e);
                }
            }
        }
        groupLeaves(maxE, n, mustPair);
    } else {
        // Can pair all here
        set<pair<int, int>> left;
        for (int e : adj[n]) if (e != p) left.emplace(numLeaves[e], e);
        while (mustPair >= 2) {
            // Pair two largest subtrees
            auto p1 = prev(left.end());
            auto p2 = prev(p1);
            int a = p1->second, b = p2->second;
            mustPair -= 2;
            numLeaves[a]--;
            numLeaves[b]--;
            pairings[n].emplace_back(a, b);
            left.erase(p1);
            left.erase(p2);
            if (numLeaves[a] != 0) left.emplace(numLeaves[a], a);
            if (numLeaves[b] != 0) left.emplace(numLeaves[b], b);
        }
        if (mustPair == 1) {
            // One left; pair with root
            pairings[n].emplace_back(left.begin()->second, N);
        }
    }
    // cout << "pairs at " << n+1 << ": ";
    // for (auto& p : pairings[n]) cout << "(" << p.first+1 << ", " << p.second+1 << ") ";
    // cout << endl;
}

vector<pair<int, int>> connections;
stack<int> nodes[MAXN];

void genConnections(int n, int p) {
    if (isLeaf[n]) {
        nodes[n].push(n);
        return;
    }
    for (int e : adj[n]) {
        if (e == p) continue;
        genConnections(e, n);
    }
    for (auto& p : pairings[n]) {
        if (nodes[p.first].empty() || nodes[p.second].empty()) exit(0);
        int a = nodes[p.first].top(); nodes[p.first].pop();
        int b = nodes[p.second].top(); nodes[p.second].pop();
        connections.emplace_back(a, b);
    }
    // Merge leaf nodes
    for (int e : adj[n]) {
        if (sz(nodes[e]) > sz(nodes[n])) swap(nodes[e], nodes[n]);
        while (!nodes[e].empty()) {
            nodes[n].push(nodes[e].top()); nodes[e].pop();
        }
    }
}

void solve() {
    cin >> N;
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    R = (sz(adj[0]) == 1 ? adj[0][0] : 0);
    findLeaves(R, R);
    // rep(i, 0, N) cout << numLeaves[i] << ' ';
    // cout << endl;
    groupLeaves(R, R, numLeaves[R]);
    nodes[N].push(R);
    genConnections(R, R);
    cout << sz(connections) << '\n';
    for (auto& p : connections) cout << p.first+1 << ' ' << p.second+1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}