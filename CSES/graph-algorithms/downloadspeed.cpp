#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 500, MAXM = 2000;
const int INF = 1e9+7;

int N, M;
int capacity[MAXM];
vector<pair<int, int>> adj[MAXN];

int currCap = 1 << 30;
bool visited[MAXN];
int fordFulkerson(int n, int f) {
    visited[n] = true;
    if (n == N-1) return f;  // Add this flow
    for (auto e : adj[n]) {
        if (!visited[e.first] && capacity[e.second] >= currCap) {
            int edgeF = fordFulkerson(e.first, min(capacity[e.second], f));
            if (edgeF != 0) {
                // Flow added; forward edge
                capacity[e.second] -= edgeF;
                int other = e.second;
                if (other % 2 == 0) other++;
                else other--;
                // Back edge
                capacity[other] += edgeF;
                return edgeF;
            }
        }
    }
    return 0;
}

void solve() {
    cin >> N >> M;
    int a, b, c;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        a--;
        b--;
        capacity[i*2] = c;
        adj[a].emplace_back(b, i*2);
        capacity[i*2+1] = 0;
        adj[b].emplace_back(a, i*2+1);
    }
    ll answer = 0;
    while (currCap > 0) {
        for (int i = 0; i < N; i++) visited[i] = false;
        int flow = fordFulkerson(0, INF);
        if (flow == 0) currCap /= 2;
        else answer += flow;
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}