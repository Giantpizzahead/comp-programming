/*
The saboteur must be at a leaf for maximum effectiveness.
Use binary seardh
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 5e5+5;

int N, K;
double M;
int stSize[MAXN];
bool valid;
vector<int> adj[MAXN];

bool dfs(int n, int p) {
    stSize[n] = 1;
    int maxMutiny = 0;
    for (int e : adj[n]) {
        if (e == p) continue;
        if (dfs(e, n)) maxMutiny = max(stSize[e], maxMutiny);
        stSize[n] += stSize[e];
    }
    bool canMutiny = (stSize[n] == 1 || (double) maxMutiny / (stSize[n]-1) >= M);
    if (canMutiny && stSize[n] > K) valid = false;
    return canMutiny;
}

void solve() {
    cin >> N >> K;
    rep(i, 1, N) {
        int c; cin >> c; c--;
        adj[i].push_back(c);
        adj[c].push_back(i);
    }
    double low = 0, high = 1;
    while (high-low > 1e-10) {
        double mid = (low + high) / 2;
        M = mid, valid = true;
        dfs(0, 0);
        if (valid) high = mid;
        else low = mid;
    }
    cout << fixed << setprecision(9) << (low+high)/2 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}