#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 5e5+5;

int N, currR;
int L[MAXN], R[MAXN];
vi adj[MAXN];

void dfs(int n, int p) {
    int deg = sz(adj[n]);
    if (n != p) deg--;
    R[n] = currR + deg;
    int savedR = currR;
    currR = R[n] + 1;
    for (int loc = R[n]-1; loc >= savedR; loc--) {
        int e = adj[n].back(); adj[n].pop_back();
        if (e == p) {
            loc++;
            continue;
        }
        L[e] = loc;
        dfs(e, n);
    }
}

void solve() {
    cin >> N;
    rep(i, 1, N) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    L[0] = 0;
    currR = 1;
    dfs(0, 0);
    rep(i, 0, N) {
        cout << L[i]+1 << ' ' << R[i]+1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}