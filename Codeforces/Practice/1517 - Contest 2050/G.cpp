#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 2005, MAXE = 20005;
const int INF = 1e9+7;

// 3 2 3 2
// 0 1 0 1
// 3 2 3 2
// 0 1 0 1
// Where important tents are 1
// Source is 2*N, sink is 2*N+1

int N, M;
int X[MAXN], Y[MAXN], W[MAXN], T[MAXN];

vector<int> adj[MAXN];
int A[MAXE], B[MAXE], C[MAXE];

void addEdge(int a, int b, int c) {
    debug << "addEdge(" << a << ", " << b << ", " << c << ")" << endl;
    A[M] = a, B[M] = b, C[M] = c;
    adj[a].push_back(M);
    M++;
    A[M] = b, B[M] = a, C[M] = 0;
    adj[b].push_back(M);
    M++;
}

int vis[MAXN];
int currIter;
int currCap;

int pushFlow(int n, int f) {
    debug << "pushFlow(" << n << ", " << f << ")" << endl;
    vis[n] = currIter;
    if (n == 2*N+1) return f;
    for (int id : adj[n]) {
        int e = B[id], nf = min(f, C[id]);
        if (vis[e] == currIter || nf < currCap) continue;
        // Try to push flow here
        int res = pushFlow(e, nf);
        if (res != 0) {
            C[id] -= res;
            C[id ^ 1] += res;
            return res;
        }
    }
    return 0;
}

void solve() {
    cin >> N;
    M = 0;
    rep(i, 0, N) {
        cin >> X[i] >> Y[i] >> W[i];
        X[i] += 1e9, Y[i] += 1e9;
        // Point removal cost
        addEdge(2*i, 2*i+1, W[i]);
        // Edges from source and to sink
        if (X[i] % 2 == 0 && Y[i] % 2 == 0) {
            T[i] = 1;
        } else if (X[i] % 2 == 1 && Y[i] % 2 == 0) {
            T[i] = 0;
            addEdge(2*N, 2*i, INF);
        } else if (X[i] % 2 == 1 && Y[i] % 2 == 1) {
            T[i] = 3;
            addEdge(2*i+1, 2*N+1, INF);
        } else {
            T[i] = 2;
        }
    }
    
    // Edges between adjacent nodes
    rep(i, 0, N) {
        rep(j, 0, N) {
            if (T[i] + 1 != T[j]) continue;
            if (abs(X[i] - X[j]) > 1 || abs(Y[i] - Y[j]) > 1) continue;
            addEdge(2*i+1, 2*j, INF);
        }
    }
    
    // Min cut algorithm
    ll result = 0;
    currIter = 0, currCap = INF;
    while (currCap > 0) {
        currIter++;
        int f = pushFlow(2*N, INF);
        if (f == 0) currCap /= 2;
        else result += f;
    }
    
    // Answer is sum of all used (inverse of all removed)
    ll answer = 0;
    rep(i, 0, N) answer += W[i];
    answer -= result;
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}