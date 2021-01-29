#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Matrix {
    int r, c;
    vector<vector<ll>> m;

    Matrix(int r, int c) : r(r), c(c) {
        m.resize(r);
        for (int i = 0; i < r; i++) m[i].resize(c);
    }

    Matrix() : Matrix(0, 0) {}

    static Matrix combine(Matrix& a, Matrix& b) {
        Matrix c(a.r, b.c);
        for (int i = 0; i < c.r; i++) {
            for (int j = 0; j < c.c; j++) {
                for (int k = 0; k < b.r; k++) {
                    if (a.m[i][k] == 0 || b.m[k][j] == 0) continue;
                    ll newCost = a.m[i][k] + b.m[k][j];
                    if (c.m[i][j] == 0 || c.m[i][j] > newCost) c.m[i][j] = newCost;
                }
            }
        }
        return c;
    }
};

int N, M, K;
Matrix trans, base;

void solve() {
    cin >> N >> M >> K;
    trans = Matrix(N, N);
    base = Matrix(1, N);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        if (trans.m[a][b] == 0 || trans.m[a][b] > c) trans.m[a][b] = c;
    }
    base.m[0][0] = 1;

    while (K > 0) {
        if (K % 2 == 1) base = Matrix::combine(base, trans);
        trans = Matrix::combine(trans, trans);
        K /= 2;
    }

    if (base.m[0][N-1] == 0) cout << -1 << endl;
    else cout << base.m[0][N-1] - 1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}