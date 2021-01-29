#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5;
const int INF = 1e9+7;

int N, M;
int degIn[MAXN], longestDist[MAXN], longestFrom[MAXN];
vector<int> adj[MAXN], topo;

stack<int> available;
void solve() {
    cin >> N >> M;
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        degIn[b]++;
    }

    for (int i = 0; i < N; i++) {
        if (degIn[i] == 0) available.push(i);
        longestDist[i] = -INF;
    }

    while (!available.empty()) {
        int n = available.top();
        // cout << n << endl;
        topo.push_back(n);
        available.pop();
        for (int e : adj[n]) {
            if (--degIn[e] == 0) available.push(e);
        }
    }
    for (int i = 0; i < N; i++) {
        int n = topo[i];
        if (n == 0) {
            longestDist[n] = 1;
            longestFrom[n] = -1;
        } else if (n == N-1) {
            if (longestDist[n] == -INF) cout << "IMPOSSIBLE\n";
            else {
                cout << longestDist[n] << '\n';
                vector<int> nodes;
                while (n != -1) {
                    nodes.push_back(n);
                    n = longestFrom[n];
                }
                reverse(nodes.begin(), nodes.end());
                bool first = true;
                for (int x : nodes) {
                    if (!first) cout << ' ';
                    else first = false;
                    cout << x+1;
                }
                cout << '\n';
            }
            return;
        }
        if (longestDist[n] == -INF) continue;
        for (int e : adj[n]) {
            if (longestDist[n] + 1 > longestDist[e]) {
                longestDist[e] = longestDist[n] + 1;
                longestFrom[e] = n;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}