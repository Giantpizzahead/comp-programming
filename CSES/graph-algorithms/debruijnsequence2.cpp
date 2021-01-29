#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define F0R(i, a) for (int i = 0; i < a; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)

const int MAXM = 16500;

int N, M;
vector<pair<int, bool>> adj[MAXM];
stack<int> nodes;
stack<bool> bits;

void findCircuit(int n, bool fromBit) {
    while (!adj[n].empty()) {
        int x = prev(adj[n].end())->first;
        bool b = prev(adj[n].end())->second;
        adj[n].pop_back();
        findCircuit(x, b);
    }
    nodes.push(n);
    bits.push(fromBit);
}

void solve() {
    cin >> N;
    M = round(pow(2, N-1));
    F0R(i, M) {
        int ni = i * 2 % M;
        adj[i].emplace_back(ni, false);
        ni = (ni + 1) % M;
        adj[i].emplace_back(ni, true);
    }
    // for (int i = 0; i < M; i++) {
    //     cout << i << ": ";
    //     for (auto x : adj[i]) cout << x.first << ' ';
    //     cout << endl;
    // }
    
    // Find eulerian circuit
    findCircuit(0, false);
    bits.pop();
    string str;
    for (int i = 0; i < N-1; i++) str += '0';
    while (!bits.empty()) {
        str += bits.top() ? '1' : '0';
        bits.pop();
    }
    reverse(str.begin(), str.end());
    cout << str << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}