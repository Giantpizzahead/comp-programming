#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5;

int N, M, numComps;
int compID[MAXN];
vector<int> adj[MAXN], revAdj[MAXN], comps[MAXN];

stack<int> finishTime;
void firstDFS(int n) {
    compID[n] = -1;
    for (int e : adj[n]) {
        if (compID[e] != -1) firstDFS(e);
    }
    finishTime.push(n);
}

void secondDFS(int n) {
    compID[n] = numComps;
    comps[numComps].push_back(n);
    for (int e : revAdj[n]) {
        if (compID[e] == -1) secondDFS(e);
    }
}

void solve() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        revAdj[b].push_back(a);
    }

    for (int i = 0; i < N; i++) if (compID[i] != -1) firstDFS(i);
    while (!finishTime.empty()) {
        int n = finishTime.top(); finishTime.pop();
        if (compID[n] == -1) {
            secondDFS(n);
            numComps++;
        }
    }

    if (numComps != N) cout << "IMPOSSIBLE\n";
    else {
        for (int i = 0; i < N; i++) {
            if (i != 0) cout << ' ';
            cout << comps[i][0] + 1;
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}