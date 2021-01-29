#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, Q, treeN, currLabel;
int T[MAXN], treeNum[MAXN], treeI[MAXN], treeParent[MAXN], depth[MAXN], slabel[MAXN], elabel[MAXN];
bool isTreeRoot[MAXN];
int visited[MAXN];
vi treeRoot[MAXN], treeKids[MAXN], revT[MAXN];

stack<int> nodes;
void dfsCycle(int n) {
    nodes.push(n);
    visited[n] = -1;
    if (visited[T[n]] == 0) {
        dfsCycle(T[n]);
        if (visited[n] == 1) return;
    } else if (visited[T[n]] == -1) {
        // Cycle!
        while (true) {
            bool stop = nodes.top() == T[n];
            int x = nodes.top();
            treeNum[x] = treeN;
            isTreeRoot[x] = true;
            treeI[x] = treeRoot[treeN].size();
            treeRoot[treeN].push_back(x);
            visited[x] = 1;
            nodes.pop();
            if (stop) break;
        }
        treeN++;
        return;
    }
    nodes.pop();
    visited[n] = 1;
}

void dfsTree(int n, int d, int tn, int tp = -1) {
    if (d == 1) tp = T[n];
    treeNum[n] = tn;
    treeParent[n] = tp;
    depth[n] = d;
    slabel[n] = currLabel++;
    for (int e : revT[n]) {
        dfsTree(e, d+1, tn, tp);
    }
    elabel[n] = currLabel-1;
}

void solve() {
    cin >> N >> Q;
    rep(i, 0, N) {
        cin >> T[i];
        T[i]--;
        revT[T[i]].push_back(i);
        treeNum[i] = -1;
    }
    rep(i, 0, N) {
        if (visited[i] == 0) dfsCycle(i);
    }
    rep(i, 0, N) {
        if (treeNum[i] == -1 && treeNum[T[i]] != -1) {
            treeKids[treeNum[T[i]]].push_back(i);
        }
    }
    rep(i, 0, treeN) {
        for (int e : treeKids[i]) {
            dfsTree(e, 1, i);
        }
    }
    // rep(i, 0, N) cout << treeNum[i] << ' ';
    // cout << endl;
    // rep(i, 0, N) cout << isTreeRoot[i] << ' ';
    // cout << endl << endl;
    // rep(i, 0, N) cout << depth[i] << ' ';
    // cout << endl;
    // rep(i, 0, N) cout << slabel[i] << ' ';
    // cout << endl;
    // rep(i, 0, N) cout << elabel[i] << ' ';
    // cout << endl;

    rep(i, 0, Q) {
        // cout.flush();
        int a, b, dist = 0; cin >> a >> b; a--, b--;
        if (treeNum[a] != treeNum[b] || (isTreeRoot[a] && !isTreeRoot[b])) {
            cout << -1 << '\n';
            continue;
        }
        if (!isTreeRoot[a] && isTreeRoot[b]) {
            // Fast-forward to cycle
            dist += depth[a];
            a = treeParent[a];
        }
        if (isTreeRoot[a] && isTreeRoot[b]) {
            // Both in cycle
            int ai = treeI[a], bi = treeI[b];
            if (ai < bi) ai += treeRoot[treeNum[a]].size();
            dist += ai-bi;
            cout << dist << '\n';
            continue;
        }
        // Both not in cycle
        if (slabel[a] >= slabel[b] && elabel[a] <= elabel[b]) cout << depth[a] - depth[b] << '\n';
        else cout << -1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}