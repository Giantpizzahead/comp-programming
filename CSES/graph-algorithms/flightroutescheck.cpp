#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;

int N, M, numVisited;
bool visited[MAXN];
vector<int> adj[MAXN], revAdj[MAXN];

void dfs(int n) {
    visited[n] = true;
    numVisited++;
    for (int e : adj[n]) {
        if (!visited[e]) dfs(e);
    }
}

void revDfs(int n) {
    visited[n] = true;
    numVisited++;
    for (int e : revAdj[n]) {
        if (!visited[e]) revDfs(e);
    }
}

void solve() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        revAdj[b].push_back(a);
    }
    dfs(0);
    if (numVisited != N) {
        cout << "NO\n";
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                cout << "1 " << i+1 << '\n';
                return;
            }
        }
    }
    numVisited = 0;
    for (int i = 0; i < N; i++) visited[i] = false;
    revDfs(0);
    if (numVisited != N) {
        cout << "NO\n";
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                cout << i+1 << " 1\n";
                return;
            }
        }
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}