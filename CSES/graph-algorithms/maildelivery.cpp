#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5, MAXM = 2e5;

int N, M;
int deg[MAXN];
bool edgeUsed[MAXM];
vector<pair<int, int>> adj[MAXN];

stack<int> nodes;
int firstNode = -1;
void findCircuit(int n) {
    while (!adj[n].empty()) {
        auto ptr = prev(adj[n].end());
        int e = ptr->first, id = ptr->second;
        adj[n].pop_back();
        if (edgeUsed[id]) continue;
        edgeUsed[id] = true;
        findCircuit(e);
    }
    if (firstNode == -1) firstNode = n;
    nodes.push(n);
}

void solve() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
        deg[a]++;
        deg[b]++;
    }

    for (int i = 0; i < N; i++) {
        if (deg[i] % 2 == 1) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }

    findCircuit(0);

    if (nodes.size() != M+1 || firstNode != 0) cout << "IMPOSSIBLE\n";
    else {
        bool first = true;
        while (!nodes.empty()) {
            if (!first) cout << ' ';
            else first = false;
            int x = nodes.top(); nodes.pop();
            cout << x+1;
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}