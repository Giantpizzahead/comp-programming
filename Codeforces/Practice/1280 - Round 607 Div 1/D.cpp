#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 3001;

int N, M;
int V[MAXN], stSize[MAXN];
int dpW[MAXN][MAXN];
ll dpV[MAXN][MAXN];
int tempW[MAXN];
ll tempV[MAXN];
vi adj[MAXN];

void dfs(int n, int p) {
    stSize[n] = 1;
    vector<pair<int, int>> children;
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs(e, n);
        stSize[n] += stSize[e];
        children.emplace_back(stSize[e], e);
    }
    sort(all(children));

    // Knapsack
    rep(i, 0, stSize[n]+1) {
        dpW[n][i] = -1;
        dpV[n][i] = -1;
        tempW[i] = -1;
        tempV[i] = -1;
    }
    dpW[n][0] = 0;
    dpV[n][0] = V[n];

    int currParts = 0;
    for (auto p : children) {
        int e = p.second;
        rep(i, 0, currParts+1) {
            for (int j = min(M-i, p.first); j >= 0; j--) {
                // j partitions in child, currently have i partitions
                // Extend partition
                int nw = dpW[n][i] + dpW[e][j];
                ll nv = dpV[n][i] + dpV[e][j];
                if (nw > tempW[i+j]) {
                    tempW[i+j] = nw;
                    tempV[i+j] = nv;
                } else if (nw == tempW[i+j] && nv > tempV[i+j]) {
                    tempV[i+j] = nv;
                }
            }
        }
        currParts = min(currParts + p.first, M);
        swap(dpW[n], tempW);
        swap(dpV[n], tempV);
        rep(i, 0, stSize[n]) {
            tempW[i] = -1;
            tempV[i] = -1;
        }
    }

    // Try cutting off partitions
    rep(i, 1, stSize[n]+1) {
        int nw = dpW[n][i-1] + (dpV[n][i-1] > 0 ? 1 : 0);
        if (nw > dpW[n][i] || (nw == dpW[n][i] && dpV[n][i] < 0)) {
            dpW[n][i] = nw;
            dpV[n][i] = 0;
        }
    }

    // cout << n+1 << ":\n";
    // rep(i, 0, stSize[n]+1) cout << dpW[n][i] << ' ';
    // cout << endl;
    // rep(i, 0, stSize[n]+1) cout << dpV[n][i] << ' ';
    // cout << endl;
}

void solve() {
    cin >> N >> M;
    int x;
    rep(i, 0, N) {
        V[i] = 0;
        adj[i].clear();
        cin >> x;
        V[i] -= x;
    }
    rep(i, 0, N) {
        cin >> x;
        V[i] += x;
    }
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, 0);
    int answer = dpW[0][M-1];
    if (dpV[0][M-1] > 0) answer++;
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}