#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2e5+5;

int N, M;
int inEdges1[MAXN], inEdges2[MAXN];
bool is1[MAXN], is2[MAXN];
vector<int> adj1[MAXN], adj2[MAXN], biAdj[MAXN];

int viscnt = 0;
bool vis[MAXN];
void dfs(int n) {
    viscnt++;
    vis[n] = true;
    for (int e : biAdj[n]) {
        if (vis[e]) continue;
        dfs(e);
    }
}
vector<int> order;

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj1[u].push_back(v);
        adj2[v].push_back(u);
        biAdj[u].push_back(v);
        biAdj[v].push_back(u);
        inEdges1[v]++;
        inEdges2[u]++;
    }

    dfs(0);
    if (viscnt != N) {
        cout << "0\n";
        return;
    }

    queue<int> toEval;
    rep(i, 0, N) if (inEdges1[i] == 0) {
        toEval.push(i);
    }
    rep(i, 0, N) {
        int n = toEval.front(); toEval.pop();
        if (toEval.empty()) is1[n] = true;
        order.push_back(n);
        for (int e : adj1[n]) {
            inEdges1[e]--;
            if (inEdges1[e] == 0) {
                toEval.push(e);
            }
        }
    }
    assert(toEval.empty());

    int numOpen = 0;
    rep(i, 0, N) if (inEdges2[i] == 0) {
        numOpen++;
    }
    reverse(all(order));
    for (int n : order) {
        numOpen--;
        if (numOpen == 0) is2[n] = true;
        for (int e : adj2[n]) {
            inEdges2[e]--;
            if (inEdges2[e] == 0) {
                numOpen++;
            }
        }
    }

    int answer = 0;
    rep(i, 0, N) if (is1[i] && is2[i]) answer++;
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}