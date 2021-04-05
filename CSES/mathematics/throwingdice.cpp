#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using Matrix = vector<vector<ll>>;

const ll MOD = 1e9+7;

Matrix mult(Matrix& A, Matrix& B) {
    assert(sz(A[0]) == sz(B));
    Matrix C(sz(A));
    rep(i, 0, sz(C)) C[i].resize(sz(B[0]));
    rep(i, 0, sz(C)) {
        rep(j, 0, sz(C[i])) {
            rep(k, 0, sz(B)) {
                C[i][j] += A[i][k] * B[k][j];
                C[i][j] %= MOD;
            }
        }
    }
    return C;
}

void print(Matrix& M) {
    rep(i, 0, sz(M)) {
        rep(j, 0, sz(M[i])) cout << M[i][j] << ' ';
        cout << endl;
    }
}

void powmod(Matrix& R, Matrix& B, ll E) {
    for (; E > 0; E >>= 1) {
        if (E & 1) R = mult(R, B);
        B = mult(B, B);
    }
}

ll N;
Matrix ans, trans;

void solve() {
    cin >> N;
    ans.resize(1);
    ans[0].resize(6);
    ans[0][5] = 1;
    trans.resize(6);
    rep(i, 0, 6) {
        trans[i].resize(6);
        if (i != 0) trans[i][i-1] = 1;
        trans[i][5] = 1;
    }
    powmod(ans, trans, N);
    cout << ans[0][5] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}