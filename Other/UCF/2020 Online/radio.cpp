#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 105;

int N, P, S;
unordered_map<string, int> strToI;
int adj[MAXN][MAXN];

void solve() {
    cin >> N >> P >> S;
    string str;
    for (int i = 0; i < N; i++) {
        cin >> str;
        strToI[str] = i;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            adj[i][j] = 99999;
            if (i == j) adj[i][j] = 0;
        }
    }
    for (int i = 0; i < N; i++) {
        adj[i][(i+1)%N] = 1;
        adj[(i+1)%N][i] = 1;
    }
    for (int i = 0; i < P; i++) {
        cin >> str;
        int x = strToI[str];
        for (int j = 0; j < N; j++) if (x != j) adj[j][x] = 1;
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                adj[i][j] = min(adj[i][k] + adj[k][j], adj[i][j]);
            }
        }
    }

    int a, b;
    for (int i = 0; i < S; i++) {
        cin >> str;
        a = strToI[str];
        cin >> str;
        b = strToI[str];
        cout << adj[a][b] << '\n';
    }
    strToI.clear();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Day #" << i << ":\n";
        solve();
        cout << '\n';
    }
    return 0;
}