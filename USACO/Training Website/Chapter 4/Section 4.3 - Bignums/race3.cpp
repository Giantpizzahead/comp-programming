/*
ID: sunnyky1
LANG: C++11
TASK: race3
*/

#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 51;

int N;
vector<int> adj[MAXN], revAdj[MAXN];
vector<int> ans1, ans2;
bool blocked[MAXN], visited[MAXN];

int numVisited;
void dfs(int n) {
    visited[n] = true;
    numVisited++;
    for (int e : adj[n]) {
        if (blocked[e] || visited[e]) continue;
        dfs(e);
    }
}

void dfsRev(int n) {
    visited[n] = true;
    numVisited++;
    for (int e : revAdj[n]) {
        if (blocked[e] || visited[e]) continue;
        dfsRev(e);
    }
}

bool unavoidable(int x) {
    blocked[x] = true;
    for (int i = 0; i < N; i++) visited[i] = false;
    numVisited = 0;
    dfs(0);
    blocked[x] = false;
    return !visited[N-1];
}

bool splitPoint(int x) {
    blocked[x] = true;
    for (int i = 0; i < N; i++) visited[i] = false;
    numVisited = 0;
    dfs(x);
    int a = numVisited;
    for (int i = 0; i < N; i++) visited[i] = false;
    numVisited = 0;
    dfs(0);
    int b = numVisited;
    blocked[x] = false;
    return a + b == N;
}

void solve() {
    int x;
    while (true) {
        cin >> x;
        if (x == -1) break;
        else if (x == -2) N++;
        else {
            adj[N].push_back(x);
            revAdj[x].push_back(N);
        }
    }
    for (int i = 1; i < N-1; i++) {
        if (unavoidable(i)) {
            ans1.push_back(i);
        }
    }
    for (int x : ans1) {
        if (splitPoint(x)) {
            ans2.push_back(x);
        }
    }
    cout << ans1.size();
    for (int x : ans1) cout << ' ' << x;
    cout << endl;
    cout << ans2.size();
    for (int x : ans2) cout << ' ' << x;
    cout << endl;
}

int main() {
    freopen("race3.in", "r", stdin);
    freopen("race3.out", "w", stdout);
    solve();
    fclose(stdin);
    fclose(stdout);
    return 0;
}