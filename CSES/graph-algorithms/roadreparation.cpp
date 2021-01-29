#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5;
const int INF = 1e9+7;

int N, M;
vector<pair<int, int>> adj[MAXN];

ll answer;
int bestDist[MAXN];
bool visited[MAXN];
priority_queue<pair<int, int>> pq;

void solve() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        adj[a].emplace_back(c, b);
        adj[b].emplace_back(c, a);
    }
    for (int i = 0; i < N; i++) bestDist[i] = INF;
    bestDist[0] = 0;

    int visitedCount = 0;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto ptr = pq.top();
        int n = ptr.second, c = -ptr.first;
        pq.pop();
        if (visited[n]) continue;
        visited[n] = true;
        visitedCount++;
        answer += c;
        for (auto e : adj[n]) {
            if (!visited[e.second] && e.first < bestDist[e.second]) {
                bestDist[e.second] = e.first;
                pq.emplace(-e.first, e.second);
            }
        }
    }

    cout << (visitedCount == N ? to_string(answer) : "IMPOSSIBLE") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}