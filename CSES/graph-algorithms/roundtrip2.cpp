#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

int N, M;
int visited[MAXN];
vector<int> adj[MAXN];
vector<int> nodeStack, cycle;

void dfs(int n) {
    visited[n] = 1;
    nodeStack.push_back(n);
    for (int e : adj[n]) {
        if (visited[e] == 1) {
            // Cycle found (reached node in current search path); add nodes starting from current node
            bool started = false;
            for (int i = 0; i < nodeStack.size(); i++) {
                if (nodeStack[i] == e) started = true;
                if (started) cycle.push_back(nodeStack[i]);
            }
            cycle.push_back(e);
        } else {
            dfs(e);
        }
        if (!cycle.empty()) {
            // Cycle already found
            break;
        }
    }
    visited[n] = 2;
    nodeStack.pop_back();
}

int main() {
    cin >> N >> M;
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
    }

    // Check for cycles
    for (int i = 0; i < N; i++) {
        if (visited[i] == 0 && cycle.empty()) {
            dfs(i);
        }
    }

    if (cycle.empty()) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << cycle.size() << endl;
        for (int i = 0; i < cycle.size(); i++) {
            if (i != 0) cout << ' ';
            cout << cycle[i] + 1;
        }
        cout << endl;
    }
    return 0;
}