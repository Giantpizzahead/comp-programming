#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;

int N, M, C;
int S[MAXN], inEdges[MAXN];
struct Edge {
    int n, c;
};
vector<Edge> adj[MAXN];

int main() {
    freopen("timeline.in", "r", stdin);
    freopen("timeline.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> C;
    for (int i = 0; i < N; i++) cin >> S[i];
    for (int i = 0; i < C; i++) {
        int a, b, x; cin >> a >> b >> x;
        a--;
        b--;
        adj[a].push_back({b, x});
        inEdges[b]++;
    }

    queue<int> valid;
    for (int i = 0; i < N; i++) {
        if (inEdges[i] == 0) valid.push(i);
    }
    while (!valid.empty()) {
        int n = valid.front();
        valid.pop();
        for (Edge& e : adj[n]) {
            S[e.n] = max(S[n] + e.c, S[e.n]);
            if (--inEdges[e.n] == 0) valid.push(e.n);
        }
    }

    for (int i = 0; i < N; i++) cout << S[i] << '\n';

    cout.flush();
    fclose(stdin);
    fclose(stdout);
    return 0;
}