#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
vi adj[MAXN];
int numD[MAXN], numT[MAXN];
ll sumD[MAXN], sumT[MAXN], sumA[MAXN];

void dfs(int n, int p) {
    numD[n] = 1;
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs(e, n);
        numD[n] += numD[e];
        sumD[n] += sumD[e] + numD[e];
    }
}

void dfs2(int n, int p) {
    if (n != p) {
        sumT[n] = sumD[p] + numD[p] - sumD[n] - numD[n] * 2;
        numT[n] = numD[p] - numD[n];
        sumT[n] += sumT[p] + numT[p];
        numT[n] += numT[p];
    }
    sumA[n] = sumD[n] + sumT[n];
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs2(e, n);
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
    dfs(0, 0);
    dfs2(0, 0);
    // rep(i, 0, N) cout << sumD[i] << (i == N-1 ? '\n' : ' ');
    // rep(i, 0, N) cout << sumT[i] << (i == N-1 ? '\n' : ' ');
    // rep(i, 0, N) cout << numT[i] << (i == N-1 ? '\n' : ' ');
    rep(i, 0, N) cout << sumA[i] << (i == N-1 ? '\n' : ' ');
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}