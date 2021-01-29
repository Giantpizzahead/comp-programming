#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define F0R(i, a) for (int i = 0; i < a; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)

const int MAXN = 1e5;

int N, M, numComps;
int compID[MAXN];
vector<int> adj[MAXN], revAdj[MAXN];

bool visited[MAXN];
stack<int> finishTime;
void firstDFS(int n) {
    visited[n] = true;
    for (int e : adj[n]) {
        if (!visited[e]) firstDFS(e);
    }
    finishTime.push(n);
}

void secondDFS(int n) {
    visited[n] = true;
    compID[n] = numComps;
    for (int e : revAdj[n]) {
        if (!visited[e]) secondDFS(e);
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
    for (int i = 0; i < N; i++) {
        if (!visited[i]) firstDFS(i);
    }
    for (int i = 0; i < N; i++) visited[i] = false;
    while (!finishTime.empty()) {
        int n = finishTime.top();
        finishTime.pop();
        if (!visited[n]) {
            secondDFS(n);
            numComps++;
        }
    }

    cout << numComps << '\n';
    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ' ';
        cout << compID[i] + 1;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}