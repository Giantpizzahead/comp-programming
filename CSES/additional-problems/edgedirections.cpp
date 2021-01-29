#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5, MAXM = 2e5;

int N, M;
bool isSet[MAXM];
pair<int, int> answers[MAXM];
vector<pair<int, int>> adj[MAXN];

void solve() {
    cin >> N >> M;
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        a--;
        b--;
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
    }
    // Arbitrary topo order
    for (int i = 0; i < N; i++) {
        for (auto e : adj[i]) {
            if (isSet[e.second]) continue;
            isSet[e.second] = true;
            answers[e.second].first = i;
            answers[e.second].second = e.first;
        }
    }
    for (int i = 0; i < M; i++) cout << answers[i].first+1 << ' ' << answers[i].second+1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}