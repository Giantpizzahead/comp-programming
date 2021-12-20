#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 50;
const int MAXM = 1000;
const int INF = 987654321;

int N, M;
int adj[MAXN][MAXN];
int A[MAXM], B[MAXM], W[MAXM];

void solve(int tn) {
    fin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            adj[i][j] = INF;
        }
        adj[i][i] = 0;
    }
    for (int i = 0; i < M; i++) {
        fin >> A[i] >> B[i] >> W[i];
        A[i]--;
        B[i]--;
        adj[A[i]][B[i]] = W[i];
        adj[B[i]][A[i]] = W[i];
    }

    // Floyd Warshall
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }

    bool possible = true;
    for (int i = 0; i < M; i++) {
        if (adj[A[i]][B[i]] != W[i]) {
            possible = false;
        }
    }
    fout << "Case #" << tn << ": ";
    if (possible) {
        fout << M << endl;
        for (int i = 0; i < M; i++) {
            fout << A[i]+1 << " " << B[i]+1 << " " << W[i] << endl;
        }
    } else {
        fout << "Impossible" << endl;
    }
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}