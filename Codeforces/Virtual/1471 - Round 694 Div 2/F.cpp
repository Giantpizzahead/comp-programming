#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 3e5+5;

int N, M;
vi adj[MAXN];
vi answer;
bool vis[MAXN], teacher[MAXN];

void dfs(int n) {
    vis[n] = true;
    bool teach = false;
    for (int e : adj[n]) {
        if (teacher[e]) teach = true;
    }
    if (!teach) {
        teacher[n] = true;
        answer.push_back(n);
    }
    for (int e : adj[n]) {
        if (!vis[e]) dfs(e);
    }
}

void solve() {
    cin >> N >> M;
    answer.clear();
    rep(i, 0, N) {
        vis[i] = false;
        teacher[i] = false;
        adj[i].clear();
    }
    rep(i, 0, M) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0);
    rep(i, 0, N) {
        if (!vis[i]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    cout << answer.size() << '\n';
    for (int i = 0; i < sz(answer); i++) {
        if (i != 0) cout << ' ';
        cout << answer[i]+1;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}