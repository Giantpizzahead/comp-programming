#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, stSize[MAXN];
vi adj[MAXN];

void dfsSize(int n, int p) {
    stSize[n] = 1;
    for (int e : adj[n]) {
        if (e == p) continue;
        dfsSize(e, n);
        stSize[n] += stSize[e];
    }
}

void solve() {
    cin >> N;
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfsSize(0, 0);
    // Find centroid
    int c = 0;
    bool good;
    do {
        good = true;
        for (int e : adj[c]) {
            if (stSize[e] > stSize[c]) continue;  // Parent
            if (stSize[e] > N/2) {
                good = false;
                c = e;
                break;
            }
        }
    } while (!good);
    cout << c+1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}