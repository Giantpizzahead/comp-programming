#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 102;

int N, K;
int X[MAXN], Y[MAXN];
vector<int> adj[MAXN];

bool visited[MAXN];
deque<pair<int, int>> q;
int tryPoint(int x) {
    q.clear();
    q.emplace_back(x, 0);
    for (int i = 0; i < N; i++) visited[i] = false;
    visited[x] = true;
    int numVisited = 0, maxCost = 0;
    while (!q.empty()) {
        auto p = q.front();
        int n = p.first, c = p.second;
        numVisited++;
        maxCost = max(c, maxCost);
        q.pop_front();
        for (int e : adj[n]) {
            if (visited[e]) continue;
            q.emplace_back(e, c+1);
            visited[e] = true;
        }
    }
    if (numVisited != N) return 9999999;
    else return maxCost;
}

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        adj[i].clear();
        cin >> X[i] >> Y[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            if (abs(X[i] - X[j]) + abs(Y[i] - Y[j]) <= K) adj[i].push_back(j);
        }
    }
    int answer = 9999999;
    for (int i = 0; i < N; i++) {
        answer = min(tryPoint(i), answer);
    }
    cout << (answer == 9999999 ? -1 : answer) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}