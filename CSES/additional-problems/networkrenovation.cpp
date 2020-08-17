#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

int N, root;
vector<int> adj[MAXN];
vector<int> leaves;

void dfs(int n, int p) {
    if (adj[n].size() == 1) leaves.push_back(n+1);
    for (int e : adj[n]) {
        if (e != p) dfs(e, n);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> N;
    int a, b;
    for (int i = 1; i < N; i++) {
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    root = 0;
    if (adj[root].size() == 1) {
        // 0 is leaf; move to non-leaf
        root = adj[root][0];
    }
    dfs(root, root);

    int answer = (leaves.size() + 1) / 2;
    if (leaves.size() % 2 == 1) leaves.push_back(leaves[0]);
    cout << answer << endl;
    for (int i = 0; i < answer; i++) {
        cout << leaves[i*2] << " " << leaves[i*2+1] << endl;
    }
}