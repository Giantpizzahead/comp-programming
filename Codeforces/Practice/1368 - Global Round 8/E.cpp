#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 2e5+5;

int N, M;
int length[MAXN];
vector<int> closed;
vector<int> adj[MAXN];

void solve() {
    cin >> N >> M;
    closed.clear();
    for (int i = 0; i < N; i++) {
        length[i] = 0;
        adj[i].clear();
    }
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // Topo sort / greedily close last spot
    int numClosed = 0;
    for (int n = 0; n < N; n++) {
        if (length[n] == 2) {
            // Close this spot
            numClosed++;
            closed.push_back(n+1);
            continue;
        }
        for (int e : adj[n]) {
            length[e] = max(length[n] + 1, length[e]);
        }
    }

    cout << numClosed << '\n';
    for (int i = 0; i < numClosed; i++) {
        if (i != 0) cout << ' ';
        cout << closed[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}