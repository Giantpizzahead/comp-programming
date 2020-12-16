#include <iostream>
#include <vector>
#include <map>
using namespace std;
const int MAXN = 1e5 + 5;

int N, K, maxDepth;
vector<int> adj[MAXN];
bool works[MAXN];
bool valid;

int dfs(int n, int p) {
    int pathCount = 0;
    map<int, int> paths;
    for (int e : adj[n]) {
        if (e == p) continue;
        int x = dfs(e, n);
        if (!valid) return -1;
        if (x != 0) {
            paths[x]++;
            pathCount++;
        }
    }
    // cerr << "node " << n+1 << ": ";
    // for (auto p : paths) {
    //     cerr << "(" << p.first << ", " << p.second << ") ";
    // }
    // cerr << endl;
    // Merge paths
    int unmerged = 0, currUnmerged = 0;
    while (!paths.empty()) {
        auto p = paths.begin();
        auto p2 = paths.find(K - p->first);
        if (p2 == paths.end()) {
            // Cannot merge
            unmerged += p->second;
            currUnmerged = p->first;
            paths.erase(p);
        } else {
            // Merge as many as possible
            int p2f = p2->first;
            if (p->first == p2->first) {
                // Special case; merge with itself
                if (p->second % 2 == 0) {
                    // All can be merged
                    paths.erase(p);
                } else {
                    // One will be unmerged
                    unmerged++;
                    currUnmerged = p->first;
                    paths.erase(p);
                }
            } else if (p->second > p2->second) {
                p->second -= p2->second;
                unmerged += p->second;
                currUnmerged = p->first;
                paths.erase(p);
                paths.erase(p2f);
            } else if (p->second < p2->second) {
                p2->second -= p->second;
                paths.erase(p);
            } else {
                paths.erase(p);
                paths.erase(p2f);
            }
        }
    }

    if (pathCount % 2 == 0) {
        // Must merge all paths
        if (unmerged != 0) {
            valid = false;
            // cerr << "invalid even" << endl;
            return -1;
        } else {
            // Start new path
            return (K == 1) ? 0 : 1;
        }
    } else {
        // One path unmerged
        if (unmerged != 1) {
            valid = false;
            // cerr << "invalid odd" << endl;
            return -1;
        } else {
            currUnmerged++;
            if (currUnmerged == K) return 0;
            else return currUnmerged;
        }
    }
}

void genInfo(int n, int p, int d) {
    maxDepth = max(d, maxDepth);
    for (int e : adj[n]) {
        if (e == p) continue;
        genInfo(e, n, d+1);
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
    genInfo(0, 0, 0);
    // Divisors of N
    for (int i = 1; i <= min(N, maxDepth * 2); i++) {
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