/*
Solution: DFS on a trie. Dynamically maintain the graph of conditions required for the current node to be the least
lexicographical ordering, and return when the conditions contradict each other. Optimize using bitwise operations.
More specifically, maintain an adjacency matrix that's valid for all pairs (adj[a][b] = Does a have to come before b).
New directed edges are added when moving down the trie (to process node 1 first, node 1 must come before node 2
lexicographically).
Any pair of nodes a and b where a can reach the new edge, and the new edge can reach b, are now connected. Using
bitwise or, iterate through all nodes a to update the matrix. Track the changes made, and backtrack when returning.
Runtime: O(|S|*26^2) in theory, but probably more like O(|S|*26) in practice
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 3e4+5;

const int C = 26;
int N;
string S[MAXN];
bool works[MAXN];

int adj[C];

inline bool isAdj(int a, int b) {
    return (adj[a] & (1 << b));
}

inline void flipAdj(int a, int b) {
    adj[a] ^= (1 << b);
}

struct Trie {
    Trie* kids[C];
    int v, loc = -1;

    Trie(int v) {
        rep(i, 0, C) kids[i] = nullptr;
        this->v = v;
    }

    void addStr(int i, int j) {
        if (j == sz(S[i])) {
            loc = i;
            return;
        }
        int e = S[i][j] - 'a';
        if (!kids[e]) kids[e] = new Trie(e);
        kids[e]->addStr(i, j+1);
    }

    void solve() {
        if (loc != -1) {
            // This one works; none after it will work
            works[loc] = true;
            return;
        }
        // Try adding each child character
        vector<int> edges;
        rep(e, 0, C) if (kids[e]) edges.push_back(e);
        vector<pair<int, int>> changes;
        for (int a : edges) {
            // Add new edges
            bool valid = true;
            for (int b : edges) {
                if (a == b || isAdj(a, b)) continue;
                // Process this new edge
                if (isAdj(b, a)) {
                    // Not valid
                    valid = false;
                    break;
                }
                changes.emplace_back(a, adj[a]);
                flipAdj(a, b);
                rep(c, 0, C) {
                    if (isAdj(c, a)) {
                        changes.emplace_back(c, adj[c]);
                        adj[c] |= adj[b];
                    }
                }
                /*
                rep(c, 0, C) {
                    rep(d, 0, C) {
                        if (!isAdj(c, d) && isAdj(c, a) && isAdj(b, d)) {
                            changes.emplace_back(c, d);
                            flipAdj(c, d);
                        }
                    }
                }
                */
            }
            if (valid) kids[a]->solve();
            // Undo changes
            while (!changes.empty()) {
                auto p = changes.back();
                adj[p.first] = p.second;
                changes.pop_back();
            }
        }
    }

    void print(int i = 0) {
        if (i == 0) debug << "trie:\n";
        rep(j, 0, i) debug << ' ';
        debug << (char) (v + 'a');
        if (loc != -1) debug << " (" << loc << ")";
        debug << '\n';
        rep(e, 0, C) if (kids[e]) kids[e]->print(i+1);
    }
};

Trie trie(-1);

void solve() {
    // Parse the input
    cin >> N;
    rep(i, 0, N) {
        cin >> S[i];
        trie.addStr(i, 0);
    }
    // trie.print();
    // Solve the problem
    rep(i, 0, C) flipAdj(i, i);
    trie.solve();
    // Output the answer
    int ans = 0;
    rep(i, 0, N) if (works[i]) ans++;
    cout << ans << '\n';
    rep(i, 0, N) if (works[i]) cout << S[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("first.in", "r", stdin);
    freopen("first.out", "w", stdout);
    solve();
    return 0;
}