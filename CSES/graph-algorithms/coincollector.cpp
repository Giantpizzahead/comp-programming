#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5;

int N, M, compN;
int K[MAXN], compID[MAXN];
ll compCoins[MAXN];
ll dp[MAXN];
bool visited[MAXN];
vector<int> adj[MAXN], revAdj[MAXN], compAdj[MAXN];

stack<int> finishTime;
void firstDFS(int n) {
    compID[n] = -1;
    for (int e : adj[n]) {
        if (compID[e] != -1) firstDFS(e);
    }
    finishTime.push(n);
}

void secondDFS(int n) {
    compID[n] = compN;
    for (int e : revAdj[n]) {
        if (compID[e] == -1) secondDFS(e);
    }
}

void solve() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) cin >> K[i];
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        revAdj[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        if (compID[i] != -1) {
            firstDFS(i);
        }
    }
    while (!finishTime.empty()) {
        int n = finishTime.top();
        finishTime.pop();
        if (compID[n] == -1) {
            secondDFS(n);
            compN++;
        }
    }
    for (int i = 0; i < N; i++) {
        compCoins[compID[i]] += K[i];
        for (int e : adj[i]) {
            if (compID[i] != compID[e]) compAdj[compID[i]].push_back(compID[e]);
        }
    }
    for (int i = 0; i < compN; i++) {
        compAdj[i].resize(distance(compAdj[i].begin(), unique(compAdj[i].begin(), compAdj[i].end())));
    }
    ll answer = 0;
    for (int i = 0; i < compN; i++) {
        dp[i] += compCoins[i];
        answer = max(dp[i], answer);
        for (int e : compAdj[i]) {
            dp[e] = max(dp[i], dp[e]);
        }
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}