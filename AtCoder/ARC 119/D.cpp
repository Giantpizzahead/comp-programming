#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 5000;

int H, W, C = 0;
vector<int> adj[MAXN];
bool vis[MAXN];
vector<int> comps[MAXN];
vector<pair<int, int>> compVals;
int from[MAXN];

int compH, compW;
vector<int> comp;
void dfs(int n) {
    vis[n] = true;
    if (n < H) compH++;
    else compW++;
    for (int e : adj[n]) {
        if (vis[e]) continue;
        from[e] = n;
        dfs(e);
    }
    comp.push_back(n);
}

void solve() {
    cin >> H >> W;
    rep(i, 0, H) {
        string str; cin >> str;
        rep(j, 0, W) {
            if (str[j] == 'R') {
                adj[i].push_back(H+j);
                adj[H+j].push_back(i);
            }
        }
    }

    // Find components
    int sumH = 0, sumW = 0, numOps = 0;
    rep(n, 0, H+W) {
        if (!vis[n]) {
            comp.clear();
            compH = 0, compW = 0;
            from[n] = -1;
            dfs(n);
            if (compH == 0 || compW == 0) continue;
            sumH += compH, sumW += compW;
            numOps += sz(comp) - 1;
            compVals.emplace_back(compH, compW);
            comps[C++] = comp;
        }
    }

    // Choose the better option and do it
    cout << numOps << '\n';
    bool removeW = (W - sumW < H - sumH);
    rep(i, 0, C) {
        rep(j, 0, sz(comps[i])-1) {
            if (j == sz(comps[i])-2 && removeW && comps[i][j] < H) {
                // Use the root instead
                cout << "Y " << comps[i][j]+1 << " " << from[comps[i][j]]-H+1 << "\n";
            } else if (j == sz(comps[i])-2 && !removeW && comps[i][j] >= H) {
                // Use the root instead
                cout << "X " << from[comps[i][j]]+1 << " " << comps[i][j]-H+1 << "\n";
            } else {
                // Use the leaf
                if (comps[i][j] < H) cout << "X " << comps[i][j]+1 << " " << from[comps[i][j]]-H+1 << "\n";
                else cout << "Y " << from[comps[i][j]]+1 << " " << comps[i][j]-H+1 << "\n";
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}