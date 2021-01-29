#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define F0R(i, a) for (int i = 0; i < a; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)

const int MAXM = 33000;

int N, M, numVisited = 0;
bool visited[MAXM];
vector<pair<int, bool>> adj[MAXM];
stack<bool> bits;

void dfs(int n) {
    numVisited++;
    visited[n] = true;
    if (numVisited == M) {
        string str = "";
        while (!bits.empty()) {
            str += (bits.top() ? '1' : '0');
            bits.pop();
        }
        reverse(str.begin(), str.end());
        cout << str << endl;
        exit(0);
    }
    for (auto e : adj[n]) {
        if (visited[e.first]) continue;
        bits.push(e.second);
        dfs(e.first);
        bits.pop();
    }
    numVisited--;
    visited[n] = false;
}

void solve() {
    cin >> N;
    M = round(pow(2, N));
    F0R(i, M) {
        int ni = i * 2 % M;
        adj[i].emplace_back(ni, false);
        ni++;
        adj[i].emplace_back(ni, true);
    }
    // for (int i = 0; i < M; i++) {
    //     cout << i << ": ";
    //     for (auto x : adj[i]) cout << x.first << ' ';
    //     cout << endl;
    // }

    for (int i = 0; i < N; i++) bits.push(false);
    dfs(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}