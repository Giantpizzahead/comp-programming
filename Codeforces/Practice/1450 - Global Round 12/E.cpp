#include <iostream>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
using namespace std;

const int MAXN = 205, INF = 1e9;

int N, M;
bool valid = true;
bool vis[MAXN], color[MAXN];
int adj[MAXN][MAXN], answers[MAXN];

void dfsCheck(int n, bool c) {
    vis[n] = true;
    color[n] = c;
    rep(e, 0, N) {
        if (e == n || adj[n][e] == INF) continue;
        if (vis[e]) {
            if (color[e] == color[n]) valid = false;
            continue;
        }
        dfsCheck(e, !c);
    }
}

bool floydWarshall() {
    bool changed = false;
    rep(k, 0, N) {
        rep(i, 0, N) {
            rep(j, 0, N) {
                if (adj[i][k] + adj[k][j] < adj[i][j]) changed = true;
                adj[i][j] = min(adj[i][k] + adj[k][j], adj[i][j]);
            }
        }
    }
    return changed;
}

int main() {
    cin >> N >> M;
    rep(i, 0, N) {
        rep(j, 0, N) {
            adj[i][j] = INF;
        }
        adj[i][i] = 0;
    }
    int a, b, t;
    rep(i, 0, M) {
        cin >> a >> b >> t;
        a--;
        b--;
        if (t == 0) {
            adj[a][b] = 1;
            adj[b][a] = 1;
        } else {
            adj[a][b] = 1;
            adj[b][a] = -1;
        }
    }

    // Check bipartite graph
    dfsCheck(0, 0);
    if (!valid) {
        cout << "NO" << endl;
        return 0;
    }

    // Check negative cycles
    floydWarshall();
    if (floydWarshall()) {
        cout << "NO" << endl;
        return 0;
    }

    // Construction
    int bestN = -1, bestD = -INF;
    rep(i, 0, N) {
        rep(j, 0, N) {
            if (adj[i][j] > bestD) {
                bestN = i;
                bestD = adj[i][j];
            }
        }
    }
    cout << "YES" << endl << bestD << endl;
    rep(j, 0, N) {
        if (j != 0) cout << ' ';
        answers[j] = adj[bestN][j] + N;
        cout << answers[j];
    }
    cout << endl;
}