// ============================== BEGIN TEMPLATE ==============================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#ifdef LOCAL
    #include "pprint.hpp"
#else
    #define debug(...) 42
    #define dumpVars(...) 42
#endif

void solve();

int runTests(bool multiple_tests) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (multiple_tests) {
        int T; cin >> T;
        rep(i, 0, T) solve();
    } else solve();
    return 0;
}
// =============================== END TEMPLATE ===============================

const int MAXA = 3e5+5;
vector<int> nextPrime(MAXA);
vector<set<int>> adj;

void genPrimeTree() {
    nextPrime[1] = 0;
    rep(i, 2, MAXA) {
        if (nextPrime[i]) continue;
        for (int j = i; j < MAXA; j += i) nextPrime[j] = i;
    }
}

void solve() {
    genPrimeTree();

    // Input parsing
    int N; cin >> N;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];
    int S, T; cin >> S >> T;
    S--, T--;

    // Special case
    if (S == T) {
        cout << "1\n";
        cout << S+1 << "\n";
        return;
    }

    // Generate graph
    int M = N;
    adj = vector<set<int>>(M);
    map<int, int> primeToNode;
    rep(n, 0, N) {
        int x = A[n];
        while (nextPrime[x]) {
            auto ptr = primeToNode.find(nextPrime[x]);
            if (ptr == primeToNode.end()) {
                ptr = primeToNode.emplace(nextPrime[x], M).first;
                adj.push_back(set<int>());
                debug("prime " << nextPrime[x] << " given node " << M << "\n");
                M++;
            }
            int e = ptr->second;
            adj[n].insert(e);
            adj[e].insert(n);
            x /= nextPrime[x];
        }
    }
    dumpVars(adj);

    // BFS
    queue<int> q; q.push(S);
    vector<int> from(M, -1);
    from[S] = -2;
    while (!q.empty()) {
        int n = q.front(); q.pop();
        for (int e : adj[n]) {
            if (from[e] != -1) continue;
            from[e] = n;
            q.push(e);
        }
    }
    if (from[T] == -1) {
        cout << "-1\n";
        return;
    }
    
    // Get the found path
    vector<int> path;
    int n = T;
    while (n != S) {
        if (n < N) path.push_back(n);
        n = from[n];
    }
    path.push_back(S);
    reverse(all(path));
    cout << sz(path) << "\n";
    rep(i, 0, sz(path)) cout << path[i]+1 << " \n"[i==sz(path)-1];
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
