#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N, M;
int from[MAXN];
vi adj[MAXN];

queue<pair<int, int>> q;
vector<int> nodes;

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    from[1] = -1;
    q.emplace(1, 1);
    while (!q.empty()) {
        auto p = q.front();
        int n = p.first, c = p.second;
        q.pop();
        if (n == N) {
            cout << c << '\n';
            nodes.push_back(n);
            while (from[n] != -1) {
                n = from[n];
                nodes.push_back(n);
            }
            reverse(all(nodes));
            rep(i, 0, sz(nodes)) {
                if (i != 0) cout << ' ';
                cout << nodes[i];
            }
            cout << '\n';
            return;
        }
        for (int e : adj[n]) {
            if (from[e] != 0) continue;
            from[e] = n;
            q.emplace(e, c+1);
        }
    }
    cout << "IMPOSSIBLE\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}