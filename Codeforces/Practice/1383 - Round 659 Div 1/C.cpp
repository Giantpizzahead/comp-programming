/**
 * Solution:
 * First of all, think of each letter as a node, and if you need to change from letter a to b, add an edge between those
 * nodes. This removes the strings entirely, and changes the problem into a graph-based one with much lower bounds. In
 * this new problem, the goal is to find a sequence of changes such that at some point, all edges will be satisfied. The
 * changes correspond to "moving" some of the edges in the graph from one source node to another source node. Edges are
 * satisfied when the source and target nodes are the same.
 * 
 * The first thing is to split the graph into several weakly connected components (components found when treating
 * directional edges as bidirectional). Solve each one independently, and sum the moves needed to get the answer. From
 * now on, I'll focus on the solution for one component.
 * 
 * One helpful observation is that when moving edges, you might as well move ALL of them (that aren't satisfied yet).
 * This means changing all the same letters to a different one, regardless of the target letter. This is because two
 * moves A->C and B->C is the same as A->B->C; all edges still end up at C.
 * 
 * Now, if the graph is a DAG, the solution becomes relatively simple: Do a topological sort on the nodes, and change
 * the letters in that order. Since the component is connected, all the nodes must be visited at least once. You can
 * think of it as "merging" the letters in topo order, almost like a bus taking all the letters along with it. When a
 * letter reaches the target, it hops off the bus. This analogy hopefully makes it clear why this is optimal. (This is
 * the solution to Div 1 A)
 * 
 * In the case where the graph has cycles, at least one of the nodes must be visited twice on this "bus ride". (Think
 * of a simple cycle with 3 nodes to prove this to yourself). All nodes will be visited at most twice, since the order
 * 1234512345 would work for all possible edges. In addition, the # of moves needed is (# visited - 1). So, the goal is
 * to maximize the number of nodes that are visited once.
 * 
 * For a set of nodes to be visited once, the nodes must form a DAG; otherwise, as proved earlier, at least one must be
 * visited twice. These nodes can be visited in the same topo order as in the Div 1 A problem. The nodes that are
 * visited twice should be put at the very front and the very end, in the order 123 <topo order> 123. This way, all
 * edges will be satisfied (can be proved by cases, node visited once vs twice).
 * 
 * It also never makes sense to have multiple DAGs, since one topo order must be put before the other. However, that
 * implies that the 2nd DAG couldn't reach the 1st DAG, so the 1st DAG would need to be put twice. This is no better
 * than just using one DAG, and treating the other as cycle nodes.
 * 
 * Therefore, the answer for each connected component is (2 * N - 1 - |LDAG|), where LDAG is the largest DAG in the
 * component, only considering edges between the chosen nodes.
 * 
 * To find the LDAG, use bitmask DP. dag[mask] = Whether the given nodes make up a DAG or not. Transitions are done by
 * checking if there is a node such that the mask without that node is a DAG, and if that node cannot reach any of the
 * other nodes in the mask. This must be true for the last node in the topo ordering. If the DAG has a cycle, then cycle
 * nodes will fail the 2nd condition, while other nodes will fail the 1st.
 * 
 * Runtime: O(2^N * N), where N is the alphabet size (at most 20)
 */

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int M = 20;
int N, compN;
bool adj[M][M];
string A, B;
vi comps[M];

bool vis[M];

void findComp(int n) {
    vis[n] = true;
    comps[compN].push_back(n);
    rep(e, 0, M) {
        if (vis[e]) continue;
        if (adj[n][e] || adj[e][n]) findComp(e);
    }
}

int reach[M];
bool dag[1 << M];

int solveComp(int comp) {
    vi& C = comps[comp];
    int K = sz(C);
    rep(i, 0, K) reach[i] = 0;
    rep(n, 0, K) {
        rep(e, 0, K) {
            if (adj[C[n]][C[e]]) reach[n] |= 1 << e;
        }
        // cout << C[n] << ": " << reach[n] << endl;
    }
    int longest = 0;
    dag[0] = true;
    rep(mask, 1, 1 << K) {
        dag[mask] = false;
        int cnt = 0;
        rep(i, 0, K) {
            if (!(mask & 1 << i)) continue;
            cnt++;
            dag[mask] |= dag[mask ^ 1 << i] && !(reach[i] & (mask ^ 1 << i));
        }
        if (dag[mask]) longest = max(cnt, longest);
        // cout << bitset<5>(mask) << " = " << dag[mask] << endl;
    }
    int answer = 2 * K - 1 - longest;
    // cout << "comp " << K << " = " << answer << endl;
    return answer;
}

void solve() {
    compN = 0;
    rep(i, 0, M) {
        comps[i].clear();
        vis[i] = false;
        rep(j, 0, M) {
            adj[i][j] = false;
        }
    }
    cin >> N >> A >> B;
    rep(i, 0, N) {
        adj[A[i]-'a'][B[i]-'a'] = true;
    }
    // Find weakly connected components
    rep(i, 0, M) {
        if (!vis[i]) {
            findComp(i);
            compN++;
        }
    }
    // Solve each component separately
    int answer = 0;
    rep(i, 0, compN) {
        if (sz(comps[i]) != 1) answer += solveComp(i);
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}