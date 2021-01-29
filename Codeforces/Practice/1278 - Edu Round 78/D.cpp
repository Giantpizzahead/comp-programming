#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 5e5+5;

int N;
int A[MAXN*2], E[MAXN];
bool vis[MAXN];
vi adj[MAXN];
set<pair<int, int>> active;

void dfs(int n, int p) {
    vis[n] = true;
    for (int e : adj[n]) {
        if (e == p) continue;
        if (vis[e]) {
            cout << "NO\n";
            exit(0);
        }
        dfs(e, n);
    }
}

void solve() {
    cin >> N;
    rep(i, 1, N+1) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        A[l] = i;
        A[r] = -i;
        E[i-1] = r;
    }
    int numEdges = 0;
    rep(i, 0, N*2) {
        int x = abs(A[i]) - 1;
        if (A[i] > 0) {
            // Start
            for (auto p : active) {
                if (p.first > E[x]) break;
                // Edge
                numEdges++;
                adj[x].push_back(p.second);
                adj[p.second].push_back(x);
                if (numEdges >= N) {
                    cout << "NO\n";
                    return;
                }
            }
            active.emplace(E[x], x);
        } else {
            // End
            active.erase({i, x});
        }
    }
    dfs(0, 0);

    rep(i, 0, N) {
        if (!vis[i]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}