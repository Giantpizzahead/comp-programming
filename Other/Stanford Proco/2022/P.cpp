#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;
using namespace std;

const int MAXN = 1e6+5;

int N;
ll ans[MAXN];
vector<int> adj[MAXN];

int stSize[MAXN];
bool blocked[MAXN];

void dfs1(int n, int p) {
    stSize[n] = 1;
    for (int e : adj[n]) {
        if (e == p || blocked[e]) continue;
        dfs1(e, n);
        stSize[n] += stSize[e];
    }
}

vector<ll> currV;

void dfs2(int n, int p, ll d) {
    currV.push_back(d);
    for (int e : adj[n]) {
        if (e == p || blocked[e]) continue;
        dfs2(e, n, d+1);
    }
}

ll allSum0, allSum1, allSum2;

void dfs3(int n, int p, ll d, ll s0, ll s1, ll s2) {
    ans[n] += allSum2 - s2;
    ans[n] += 2 * d * (allSum1 - s1);
    ans[n] += (allSum0 - s0 + 1) * d * d;
    for (int e : adj[n]) {
        if (e == p || blocked[e]) continue;
        dfs3(e, n, d+1, s0, s1, s2);
    }
}

void solve(int n);

void splitCentroid(int c) {
    // cout << "split " << c << endl;
    vector<ll> sum0, sum1, sum2;
    allSum0 = 0, allSum1 = 0, allSum2 = 0;
    for (int e : adj[c]) {
        if (blocked[e]) continue;
        currV.clear();
        dfs2(e, c, 1);
        ll s0 = 0, s1 = 0, s2 = 0;
        for (ll x : currV) {
            s0++;
            s1 += x;
            s2 += x * x;
        }
        sum0.push_back(s0);
        sum1.push_back(s1);
        sum2.push_back(s2);
        allSum0 += s0;
        allSum1 += s1;
        allSum2 += s2;
    }
    ans[c] += allSum2;

    // rep(i, 0, sz(sum0)) cout << sum0[i] << " \n"[i == sz(sum0)-1];
    // rep(i, 0, sz(sum1)) cout << sum1[i] << " \n"[i == sz(sum1)-1];
    // rep(i, 0, sz(sum2)) cout << sum2[i] << " \n"[i == sz(sum2)-1];

    // Add to answer for each subtree
    int currI = 0;
    for (int e : adj[c]) {
        if (blocked[e]) continue;
        dfs3(e, c, 1, sum0[currI], sum1[currI], sum2[currI]);
        currI++;
    }

    // rep(i, 0, N) cout << ans[i] << " \n"[i==N-1];

    blocked[c] = true;
    for (int e : adj[c]) {
        if (blocked[e]) continue;
        solve(e);
    }
}

// Centroid decomp
void solve(int n) {
    dfs1(n, n);
    // rep(i, 0, N) cout << stSize[i] << " \n"[i==N-1];
    // Find centroid
    int c = n;
    while (true) {
        bool found = true;
        for (int e : adj[c]) {
            if (blocked[e]) continue;
            if (stSize[e] < stSize[c] && stSize[e] > stSize[n]/2) {
                c = e;
                found = false;
                break;
            }
        }
        if (found) break;
    }
    splitCentroid(c);
}

void solve() {
    cin >> N;
    int u, v;
    rep(i, 1, N) {
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve(0);
    rep(i, 0, N) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}