#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2500, MAXM = 5000;

int N, M, answer;
int A[MAXM], B[MAXM];
bool ignoreEdge[MAXM];
vector<pair<int, int>> adj[MAXN];

bool visited[MAXN];
queue<pair<int, int>> q;
int search(int a, int b) {
    while (!q.empty()) q.pop();
    q.emplace(a, 0);
    for (int j = 0; j < N; j++) visited[j] = false;
    visited[a] = true;
    while (!q.empty()) {
        auto p = q.front();
        int n = p.first, c = p.second;
        q.pop();
        if (n == b) return c+1;
        for (auto e : adj[n]) {
            if (ignoreEdge[e.second] || visited[e.first]) continue;
            visited[e.first] = true;
            q.emplace(e.first, c+1);
        }
    }
    return 1e9;
}

void solve() {
    cin >> N >> M;
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        a--; b--;
        A[i] = a;
        B[i] = b;
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
    }
    answer = 1e9;
    for (int i = 0; i < M; i++) {
        ignoreEdge[i] = true;
        answer = min(search(A[i], B[i]), answer);
        ignoreEdge[i] = false;
    }
    cout << (answer == 1e9 ? -1 : answer) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}