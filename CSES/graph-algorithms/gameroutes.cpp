#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5, MOD = 1e9+7;

int N, M;
int inDeg[MAXN], dp[MAXN];
vector<int> topo;
vector<int> adj[MAXN];

stack<int> valid;
void solve() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        inDeg[b]++;
    }
    for (int i = 0; i < N; i++) if (inDeg[i] == 0) valid.push(i);

    while (!valid.empty()) {
        int n = valid.top(); valid.pop();
        topo.push_back(n);
        for (int e : adj[n]) if (--inDeg[e] == 0) valid.push(e);
    }

    for (int n : topo) {
        if (n == 0) dp[n] = 1;
        if (n == N-1) {
            cout << dp[n] << '\n';
            return;
        }
        for (int e : adj[n]) {
            dp[e] = (dp[e] + dp[n]) % MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}