#include <iostream>
#include <set>
using namespace std;

const int MAXN = 2e5+5;

int N, M, answer;
bool hasCycle;
bool isUniversal[MAXN];
bool blocked[MAXN];
int visited[MAXN], currVisited = 1;
set<int> adj[MAXN], revAdj[MAXN];

void dfsCycle(int n) {
    visited[n] = currVisited;
    for (int e : adj[n]) {
        if (visited[e] == currVisited) {
            hasCycle = true;
            return;
        }
        if (visited[e] == 0) dfsCycle(e);
        if (hasCycle) return;
    }
    visited[n] = -1;
}

void dfs(int n) {
    blocked[n] = true;
    // visited[n] = currVisited;
    for (int e : adj[n]) {
        dfs(e);
        // revAdj[e].erase(n);
    }
    adj[n].clear();
}

void dfsRev(int n) {
    blocked[n] = true;
    // visited[n] = currVisited;
    for (int e : revAdj[n]) {
        dfsRev(e);
        // adj[e].erase(n);
    }
    revAdj[n].clear();
}

void removeEdges(int n) {
    blocked[n] = true;
    // visited[n] = currVisited;
    for (int e : adj[n]) {
        dfs(e);
        // revAdj[e].erase(n);
    }
    // currVisited++;
    // visited[n] = currVisited + 1;
    for (int e : revAdj[n]) {
        dfsRev(e);
        // adj[e].erase(n);
    }
    adj[n].clear();
    revAdj[n].clear();
    // currVisited++;
}

void solve() {
    cin >> N >> M;
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        a--;
        b--;
        adj[a].insert(b);
        revAdj[b].insert(a);
    }
    for (int i = 0; i < N; i++) {
        if (visited[i] == 0) dfsCycle(i);
        currVisited++;
    }
    if (hasCycle) {
        cout << -1 << endl;
        return;
    }
    // Start marking universal
    for (int i = 0; i < N; i++) {
        if (!blocked[i]) {
            isUniversal[i] = true;
            answer++;
        }
        removeEdges(i);
    }

    cout << answer << endl;
    for (int i = 0; i < N; i++) {
        cout << (isUniversal[i] ? 'A' : 'E');
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}