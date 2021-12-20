#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1005;

int N, M, K, numComps;
int compID[MAXN], compSize[MAXN];
vector<int> adj[MAXN];
double fact[MAXN];
double answer;

void dfs(int n, int p) {
    compSize[numComps]++;
    compID[n] = numComps;
    for (int e : adj[n]) {
        if (e == p || compID[e] != -1) continue;
        dfs(e, n);
    }
}

void solve() {
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        adj[i].clear();
    }
    for (int i = 0; i < N; i++) {
        compID[i] = -1;
        compSize[i] = 0;
    }
    numComps = 0;
    answer = 0;
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        if (compID[i] == -1) {
            dfs(i, i);
            numComps++;
        }
    }
    // Count for each
    for (int i = 0; i < N; i++) {
        int M = N - compSize[compID[i]];
        if (M < K) {
            // Must pick one in this comp
            answer++;
            continue;
        }
        // cout << "\ni: " << i << " " << M << " " << K << endl;
        double contrib = fact[M] - fact[M-K] - fact[N] + fact[N-K];
        answer += 1 - pow(2, contrib);
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(3);
    fact[0] = 0;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i-1] + log2(i);
        // cout << fact[i] << ' ';
    }
    // cout << endl;
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Pond #" << i << ": ";
        solve();
    }
    return 0;
}