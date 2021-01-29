#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5, MAXM = 2e5;

int N, M, inDeg[MAXN], outDeg[MAXN];
vi adj[MAXN];

vector<int> nodes;

void findPath(int n) {
    while (!adj[n].empty()) {
        int e = *prev(adj[n].end());
        adj[n].pop_back();
        findPath(e);
    }
    nodes.push_back(n);
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int a, b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        outDeg[a]++;
        inDeg[b]++;
    }
    if (outDeg[0] - inDeg[0] != 1 || inDeg[N-1] - outDeg[N-1] != 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    rep(i, 1, N-1) {
        if (inDeg[i] != outDeg[i]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    findPath(0);
    if (sz(nodes) != M+1) {
        cout << "IMPOSSIBLE\n";
        return;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}