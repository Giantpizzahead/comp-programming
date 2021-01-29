#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5+1;

int N, M;
vector<int> compRoot;
vector<int> adj[MAXN];
bool visited[MAXN];

void dfs(int n) {
    visited[n] = true;
    for (int e : adj[n]) if (!visited[e]) dfs(e);
}

void solve() {
    cin >> N >> M;
    int a, b;
    for (int i = 1; i <= M; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            compRoot.push_back(i);
            dfs(i);
        }
    }
    cout << compRoot.size()-1 << '\n';
    for (int i = 0; i < compRoot.size()-1; i++) {
        cout << compRoot[i] << ' ' << compRoot[i+1] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}