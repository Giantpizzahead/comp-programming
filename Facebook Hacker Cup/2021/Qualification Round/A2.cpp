#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

const int INF = 999999999;

int tryChar(vector<int>& S, int C, vector<vector<int>>& adj) {
    int ans = 0;
    for (int x : S) {
        if (adj[x][C] == INF) return INF;
        else ans += adj[x][C];
    }
    return ans;
}

void solve() {
    string str; cin >> str;
    vector<int> S(sz(str));
    rep(i, 0, sz(str)) S[i] = str[i] - 'A';
    
    vector<vector<int>> adj(26);
    rep(i, 0, 26) {
        adj[i].resize(26);
        fill(all(adj[i]), INF);
        adj[i][i] = 0;
    }
    int M; cin >> M;
    rep(i, 0, M) {
        string T; cin >> T;
        adj[T[0]-'A'][T[1]-'A'] = 1;
    }
    
    // Floyd-Warshall
    rep(k, 0, 26) {
        rep(i, 0, 26) {
            rep(j, 0, 26) {
                adj[i][j] = min(adj[i][k] + adj[k][j], adj[i][j]);
            }
        }
    }
    
    // Try changing to every character
    int ans = INF;
    rep(i, 0, 26) ans = min(tryChar(S, i, adj), ans);
    cout << (ans == INF ? -1 : ans) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}