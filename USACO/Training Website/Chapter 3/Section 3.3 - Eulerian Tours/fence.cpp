/*
ID: sunnyky1
LANG: C++
TASK: fence

Solution: Standard Eulerian Path problem. Use an ordered set to
traverse the lowest-labeled neighbors first (to preserve ordering).
Runtime: O(F * log(500))
*/

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <set>
#include <stack>
#include <algorithm>

#define N 500

using namespace std;

int F;
int deg[N];
multiset<int> adj[N];

stack<int> currPath;

void findEulerianPath(int n) {
    while (!adj[n].empty()) {
        int low = *(adj[n].begin());
        adj[n].erase(adj[n].begin());
        adj[low].erase(adj[low].find(n));
        findEulerianPath(low);
    }
    currPath.push(n);
}

int main() {
    // Trying out C-style file IO :)
    FILE* fin = fopen("fence.in", "r");
    FILE* fout = fopen("fence.out", "w");

    // Parse input
    fscanf(fin, "%d", &F);
    int a, b;
    for (int i = 0; i < F; i++) {
        fscanf(fin, "\n%d %d", &a, &b);
        a--;
        b--;
        // cout << a << " " << b << endl;
        adj[a].insert(b);
        adj[b].insert(a);
        deg[a]++;
        deg[b]++;
    }

    // Check for odd degree nodes
    bool nonzero = false;
    int sn = 0;
    for (int i = 0; i < N; i++) {
        if (deg[i] % 2 == 1) {
            sn = i;
            break;
        } else if (deg[i] != 0 && !nonzero) {
            sn = i;
            nonzero = true;
        }
    }

    // Run algorithm from that node
    findEulerianPath(sn);

    while (!currPath.empty()) {
        fprintf(fout, "%d\n", currPath.top() + 1);
        currPath.pop();
    }
    return 0;
}