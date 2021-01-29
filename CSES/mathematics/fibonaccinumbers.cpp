#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Matrix = vector<vector<int>>;

const ll MOD = 1e9+7;
ll N;

Matrix multMatrices(Matrix& a, Matrix& b) {
    Matrix c;
    c.resize(a.size());
    for (int i = 0; i < c.size(); i++) c[i].resize(b[0].size());
    for (int i = 0; i < c.size(); i++) {
        for (int j = 0; j < c[0].size(); j++) {
            for (int k = 0; k < b.size(); k++) {
                c[i][j] += (ll) a[i][k] * b[k][j] % MOD;
                c[i][j] %= MOD;
            }
        }
    }
    return c;
}

Matrix base, fib;

void matrixExpo() {
    while (N > 0) {
        if (N % 2 == 1) {
            base = multMatrices(base, fib);
        }
        fib = multMatrices(fib, fib);
        N /= 2;
    }
}

void solve() {
    cin >> N;
    base.resize(1);
    base[0].resize(2);
    fib.resize(2);
    fib[0].resize(2);
    fib[1].resize(2);
    base[0][0] = 0;
    base[0][1] = 1;
    fib[0][0] = 0;
    fib[1][0] = 1;
    fib[0][1] = 1;
    fib[1][1] = 1;
    matrixExpo();
    cout << base[0][0] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}