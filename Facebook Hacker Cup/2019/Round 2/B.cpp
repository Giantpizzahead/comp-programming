#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 4005;

int compID[MAXN], bitString[MAXN], dp[MAXN][MAXN];
vector<int> adj[MAXN], components[MAXN];

int N, M, numComps;

void dfs(int n) {
    components[numComps].push_back(n);
    compID[n] = numComps;
    for (int e : adj[n]) {
        if (compID[e] == 0) dfs(e);
    }
}

void solve(int tn) {
    fin >> N >> M;

    // Reset
    for (int i = 0; i <= N; i++) {
        adj[i].clear();
        components[i].clear();
        compID[i] = 0;
        for (int j = 0; j <= N; j++) {
            dp[i][j] = 0;
        }
    }

    // cout << "Case " << tn << ": " << N << " " << M << endl;
    int x, y;
    for (int i = 0; i < M; i++) {
        fin >> x >> y;
        x--;
        y--;
        while (x < y) {
            adj[x].push_back(y);
            adj[y].push_back(x);
            x++;
            y--;
        }
    }

    // Find components
    numComps = 0;
    for (int i = 0; i < N; i++) {
        if (compID[i] == 0) {
            numComps++;
            dfs(i);
        }
    }

    // Knapsack
    dp[0][0] = -1;
    int bestI = -1, bestJ = -1, bestAbsDiff = 987654321;
    for (int i = 1; i <= numComps; i++) {
        int compSize = components[i].size();
        for (int j = N; j >= compSize; j--) {
            if (dp[i-1][j-compSize] != 0) {
                // This works
                dp[i][j] = i;
                int absDiff = abs(j - (N - j)); 
                if (absDiff < bestAbsDiff) {
                    bestI = i;
                    bestJ = j;
                    bestAbsDiff = absDiff;
                }
            } 
        }
        for (int j = N; j >= 0; j--) {
            if (dp[i][j] == 0 && dp[i-1][j] != 0) {
                // Transfer from previous
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    
    /*
    cout << bestI << ' ' << bestJ << ' ' << bestAbsDiff << endl;

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }

    for (int i = 1; i <= numComps; i++) {
        for (int x : components[i]) {
            cout << x << ' ';
        }
        cout << endl;
    }
    */
    
    // Generate bit string
    for (int i = 0; i < N; i++) bitString[i] = 1;
    while (dp[bestI][bestJ] != -1) {
        if (dp[bestI][bestJ] != 0) {
            for (int x : components[dp[bestI][bestJ]]) {
                bitString[x] = 0;
            }
            int tempI = dp[bestI][bestJ] - 1;
            bestJ -= components[dp[bestI][bestJ]].size();
            bestI = tempI;
        } else {
            cout << "AAAAAAAAAAAAAAAAAAAAAA" << endl;
            bestI--;
        }
    }
    
    fout << "Case #" << tn << ": ";
    for (int i = 0; i < N; i++) {
        fout << bitString[i];
    }
    fout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}