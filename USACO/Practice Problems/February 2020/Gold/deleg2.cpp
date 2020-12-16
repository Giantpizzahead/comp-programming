#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 5;

int N, K, maxDepth;
vector<int> adj[MAXN];
bool works[MAXN];
bool valid;

int dfs(int n, int p) {
    vector<int> paths;
    for (int e : adj[n]) {
        if (e == p) continue;
        int x = dfs(e, n);
        if (!valid) return -1;
        if (x != 0) {
            paths.push_back(x);
        }
    }
    // Merge paths
    sort(paths.begin(), paths.end());
    // cerr << "node " << n+1 << ": ";
    // for (int p : paths) {
    //     cerr << p << ' ';
    // }
    // cerr << endl;
    int unmerged = -1;
    for (int i = 0; i < paths.size(); i++) {
        int p1 = paths[i];
        if (i == paths.size()-1) {
            // Cannot merge (last one)
            if (unmerged == -1) unmerged = p1;
            else {
                valid = false;
                return -1;
            }
            break;
        }
        int p2 = paths[paths.size()-1];
        if (p1 + p2 == K) {
            // Merge
            paths.pop_back();
        } else {
            // Cannot merge
            if (unmerged == -1) unmerged = p1;
            else {
                // Too many unmerged
                valid = false;
                return -1;
            }
        }
    }
    
    if (unmerged == -1) {
        // Start new path
        return (1 == K ? 0 : 1);
    } else {
        // Continue this path
        return (unmerged + 1 == K ? 0 : unmerged + 1);
    }
}

void solve() {
    cin >> N;
    int a, b;
    for (int i = 1; i < N; i++) {
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // Divisors of N
    for (int i = 1; i < N; i++) {
        if ((N-1) % i == 0) {
            valid = true;
            K = i;
            // cerr << "check " << K << endl;
            int res = dfs(0, 0);
            if (res > 1) valid = false;
            if (valid) works[i] = true;
        }
    }
    for (int i = 1; i < N; i++) cout << (works[i] ? 1 : 0);
    cout << endl;
}

int main() {
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    fclose(stdout);
    return 0;
}