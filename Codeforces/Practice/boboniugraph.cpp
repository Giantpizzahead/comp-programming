#include <iostream>
#include <set>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 200005;
const int MAXK = 10;
const int MOD = 1000000007;

int N, M, K, answer;

struct Edge {
    int n, w;
    Edge(int n, int w) : n(n), w(w) {}
    bool operator<(const Edge& o) const {
        return w < o.w;
    }
};

set<Edge> adj[MAXN];
ll targetAddH, targetMultH;
ll randVals[MAXN];
ll hashAdd[MAXK][MAXK], hashMult[MAXK][MAXK];
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int getRand() {
    int result = abs((ll) rng()) % MOD;
    // Avoid issues with multiplication and addition hashes
    if (result < 2) result = 2;
    return result;
}

void tryTuples(int i, ll addH, ll multH) {
    if (i > K) {
        // Done
        if (addH == targetAddH && multH == targetMultH) answer++;
    } else {
        // Try each value
        for (int j = 1; j <= i; j++) {
            ll newAddH = (addH + hashAdd[i][j]) % MOD;
            ll newMultH = (multH * hashMult[i][j]) % MOD;
            tryTuples(i+1, newAddH, newMultH);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> M >> K;
    int a, b, w;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> w;
        a--;
        b--;
        adj[a].insert(Edge(b, w));
    }
    // Gen random vals for hashes
    for (int i = 0; i < N; i++) {
        randVals[i] = getRand();
    }
    // Setup initial hashes
    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= i; j++) {
            hashMult[i][j] = 1;
        }
    }
    // Gen hash values
    for (int n = 0; n < N; n++) {
        int i = 0;
        for (const Edge& e : adj[n]) {
            i++;
            hashAdd[adj[n].size()][i] += randVals[e.n];
            hashAdd[adj[n].size()][i] %= MOD;
            hashMult[adj[n].size()][i] *= randVals[e.n];
            hashMult[adj[n].size()][i] %= MOD;
        }
    }
    // Gen target hashes
    targetMultH = 1;
    for (int n = 0; n < N; n++) {
        targetAddH += randVals[n];
        targetAddH %= MOD;
        targetMultH *= randVals[n];
        targetMultH %= MOD;
    }
    // Try all tuples
    tryTuples(1, 0, 1);
    /*
    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= i; j++) {
            cout << hashMult[i][j] << '\t';
        }
        cout << endl;
    }
    cout << targetAddH << ' ' << targetMultH << endl;
    */
    cout << answer << endl;
    return 0;
}