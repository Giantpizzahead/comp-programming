#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1000;

int N;
ll X[MAXN], Y[MAXN], D[MAXN][MAXN];
vector<int> adj[MAXN];

int curr = 0;
int vis[MAXN];

int dfs(int n) {
    int cnt = 1;
    vis[n] = curr;
    for (int e : adj[n]) if (vis[e] != curr) cnt += dfs(e);
    return cnt;
}

bool check(ll M) {
    rep(i, 0, N) adj[i].clear();
    rep(i, 0, N) {
        rep(j, i+1, N) {
            if (D[i][j] <= M) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    curr++;
    return dfs(0) == N;
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> X[i] >> Y[i];
    rep(i, 0, N) {
        rep(j, i+1, N) {
            D[i][j] = abs(X[i] - X[j]) * abs(X[i] - X[j]) + abs(Y[i] - Y[j]) * abs(Y[i] - Y[j]);
        }
    }
    // Binary search for cost (M)
    ll low = 0, high = 2LL * 25000 * 25000;
    while (low < high) {
        ll mid = (low + high) / 2;
        if (check(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    cout << low << '\n';
}

int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}