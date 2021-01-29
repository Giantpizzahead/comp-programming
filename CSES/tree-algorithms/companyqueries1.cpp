#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5;

int N, Q;
int depth[MAXN], answers[MAXN];
vector<int> kids[MAXN];
vector<pair<int, int>> queries[MAXN];

vector<int> currQueries[MAXN];

void dfs(int n, int d) {
    depth[n] = d;
    for (auto p : queries[n]) if (d - p.first >= 0) currQueries[d - p.first].push_back(p.second);
    for (int e : kids[n]) {
        dfs(e, d+1);
    }
    // Answer queries
    for (int x : currQueries[d]) answers[x] = n+1;
    currQueries[d].clear();
}

void solve() {
    cin >> N >> Q;
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        p--;
        kids[p].push_back(i);
    }
    for (int i = 0; i < Q; i++) {
        int x, k;
        cin >> x >> k;
        x--;
        queries[x].emplace_back(k, i);
        answers[i] = -1;
    }
    dfs(0, 0);
    for (int i = 0; i < Q; i++) cout << answers[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}