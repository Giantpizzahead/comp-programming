#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 100005;
int N, A, B, da, db, diameter;
vector<int> adj[MAXN];

int currNode, currDist;
void dfsFurthest(int n, int p, int d) {
    if (d > currDist) {
        currNode = n;
        currDist = d;
    }
    for (int e : adj[n]) {
        if (e != p) dfsFurthest(e, n, d+1);
    }
}

int foundDist;
void dfsSearch(int n, int p, int d) {
    if (n == B) foundDist = d;
    else {
        for (int e : adj[n]) {
            if (e != p) dfsSearch(e, n, d+1);
        }
    }
}

void solve() {
    cin >> N >> A >> B >> da >> db;
    // Reset
    for (int i = 0; i < N; i++) adj[i].clear();
    A--;
    B--;
    int u, v;
    for (int i = 1; i < N; i++) {
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Find diameter
    currNode = 0;
    currDist = 0;
    dfsFurthest(0, 0, 0);
    currDist = 0;
    dfsFurthest(currNode, currNode, 0);
    diameter = currDist;

    da = min(diameter, da);
    db = min(diameter, db);

    // Can Alice get eventually?
    if (da >= db - 1) {
        cout << "Alice\n";
        return;
    }

    // Can Alice reach on first turn?
    dfsSearch(A, A, 0);
    if (foundDist <= da) {
        cout << "Alice\n";
        return;
    }

    // Is diameter big enough?
    if ((db+1)/2 <= da) {
        cout << "Alice\n";
        return;
    }

    // Everything passes
    cout << "Bob\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) solve();
    return 0;
}