#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 5005;

int N, M;

bool chg[MAXN];
int A[MAXN], B[MAXN], C[MAXN];
ll dists[MAXN];

bool bellmanFord() {
    bool diff = false;
    rep(i, 0, M) {
        ll newDist = dists[A[i]] + C[i];
        if (newDist < dists[B[i]]) {
            diff = true;
            dists[B[i]] = newDist;
        }
    }
    return diff;
}

vector<pair<int, int>> adj[MAXN];

int vis[MAXN];
stack<int> edges;
void dfs(int n, int lastE) {
    vis[n] = 1;
    edges.push(n);
    for (auto& p : adj[n]) {
        if (p.second == lastE) continue;
        if (vis[p.first] == 1) {
            // Cycle
            cout << "YES\n";
            stack<int> nodes;
            nodes.push(p.first);
            while (edges.top() != p.first) {
                nodes.push(edges.top());
                edges.pop();
            }
            nodes.push(edges.top());
            bool first = true;
            while (!nodes.empty()) {
                if (!first) cout << ' ';
                first = false;
                cout << nodes.top()+1; nodes.pop();
            }
            cout << '\n';
            exit(0);
        } else {
            dfs(p.first, p.second);
        }
    }
    vis[n] = 2;
    edges.pop();
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        cin >> A[i] >> B[i] >> C[i];
        A[i]--, B[i]--;
    }
    rep(i, 0, N-1) bellmanFord();
    rep(j, 0, N) {
        rep(i, 0, M) {
            ll newDist = dists[A[i]] + C[i];
            if (newDist < dists[B[i]]) {
                chg[i] = true;
                dists[B[i]] = newDist;
            }
        }
    }
    rep(i, 0, M) {
        if (chg[i]) {
            adj[A[i]].emplace_back(B[i], i);
        }
    }
    rep(i, 0, N) if (vis[i] == 0) dfs(i, -1);
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}