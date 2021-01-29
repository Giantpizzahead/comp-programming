#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int MAXN = 100;
const int MOD = 1e9+7;

struct Matrix {
    int r, c;
    vector<vector<int>> m;

    Matrix(int r, int c) : r(r), c(c) {
        m.resize(r);
        for (int i = 0; i < r; i++) m[i].resize(c);
    }
};

int N, M, K;
Matrix adj(0, 0), base(0, 0);

Matrix matrixMult(Matrix& a, Matrix& b) {
    Matrix c(a.r, b.c);
    for (int i = 0; i < c.r; i++) {
        for (int j = 0; j < c.c; j++) {
            for (int k = 0; k < b.r; k++) {
                c.m[i][j] = (c.m[i][j] + (ll) a.m[i][k] * b.m[k][j]) % MOD;
            }
        }
    }
    return c;
}

int main() {
    cin >> N >> M >> K;
    adj = Matrix(N, N);
    base = Matrix(1, N);
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        a--;
        b--;
        adj.m[a][b]++;
    }
    base.m[0][0] = 1;

    while (K > 0) {
        if (K % 2 == 1) base = matrixMult(base, adj);
        adj = matrixMult(adj, adj);
        K /= 2;
    }

    cout << base.m[0][N-1] << endl;
    return 0;
}