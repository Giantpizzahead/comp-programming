#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 61;
const int MOD = 1e9+7;

struct Matrix {
    int r, c;
    vector<vector<int>> m;

    Matrix() {}

    Matrix(int r, int c) : r(r), c(c) {
        m.resize(r);
        for (int i = 0; i < r; i++) m[i].resize(c);
    }

    void print() {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) cout << m[i][j] << ' ';
            cout << endl;
        }
    }

    static Matrix add(Matrix& a, Matrix& b) {
        assert(a.r == b.r && a.c == b.c);
        Matrix c(a.r, a.c);
        for (int i = 0; i < c.r; i++) {
            for (int j = 0; j < c.c; j++) {
                c.m[i][j] = (a.m[i][j] + b.m[i][j]) % MOD;
            }
        }
        return c;
    }

    static Matrix mult(Matrix& a, Matrix& b) {
        assert(a.c == b.r);
        Matrix c(a.r, b.c);
        for (int i = 0; i < c.r; i++) {
            for (int j = 0; j < c.c; j++) {
                for (int k = 0; k < b.r; k++) {
                    ll v = static_cast<ll>(a.m[i][k]) * b.m[k][j] % MOD;
                    c.m[i][j] = (c.m[i][j] + v) % MOD;
                }
            }
        }
        return c;
    }
};

int N, K, Q;
Matrix adj, revAdj, zero, identity;
Matrix button[MAXN];

void genButtons() {
    for (int i = 0; i < K; i++) {
        button[i] = Matrix(N, N);
    }
    button[0] = Matrix::add(adj, zero);

    for (int i = 1; i < K; i++) {
        button[i] = Matrix::mult(button[i-1], button[i-1]);
        button[i] = Matrix::add(button[i-1], button[i]);

        // cout << "button[" << i << "]:\n";
        // button[i].print();
    }
}

int bt, t, answer;
Matrix answerMat[MAXN];

void genAnswerMat() {
    Matrix transMat(1, N);
    for (int b = 0; b < K; b++) {
        answerMat[b] = Matrix(1, N);
        // Matrix state(N, N);
        // for (int i = 0; i < N; i++) state.m[i][i] = 1;
        if (b == bt) answerMat[b].m[0][t] = 1;

        if (b != 0) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    int toAdd = (ll) button[b-1].m[j][k] * answerMat[b-1].m[0][k] % MOD;
                    transMat.m[0][j] = (toAdd + transMat.m[0][j]) % MOD;
                }
                answerMat[b].m[0][j] = (answerMat[b].m[0][j] + transMat.m[0][j]) % MOD;
            }
        }

        //state = Matrix::mult(state, adj);
        // for (int i = 0; i < b; i++) {
        //     for (int j = 0; j < N; j++) {
        //         for (int k = 0; k < N; k++) {
        //             answerMat[b].m[0][j] = (answerMat[b].m[0][j] + (ll) button[i].m[j][k] * answerMat[i].m[0][k]) % MOD;
        //         }
        //     }
        //     // Matrix added = Matrix::mult(state, button[i]);
        //     // state = Matrix::add(added, state);
        // }

        // cout << "answerMat " << b << ": ";
        // answerMat[b].print();
    }
}

int answerQuery(int bs, int bt2, int s, int t2) {
    if (bs == K-2 && bt2 == K-1) return button[K-2].m[s][t2];
    bt = bt2;
    t = t2;
    answer = 0;
    genAnswerMat();

    Matrix state(1, N);
    state.m[0][s] = 1;
    for (int i = bs; i < K; i++) {
        for (int j = 0; j < N; j++) {
            answer = (answer + (ll) answerMat[i].m[0][j] * state.m[0][j]) % MOD;
        }
        Matrix newState = Matrix::mult(state, button[i]);
        if (i != bs) newState = Matrix::add(state, newState);
        state = newState;
    }
    return answer;
}

void solve() {
    cin >> N >> K >> Q;
    adj = Matrix(N, N);
    revAdj = Matrix(N, N);
    zero = Matrix(N, N);
    identity = Matrix(N, N);
    for (int i = 0; i < N; i++) {
        identity.m[i][i] = 1;
        string str; cin >> str;
        for (int j = 0; j < N; j++) {
            adj.m[i][j] = str[j] == '1';
            revAdj.m[j][i] = str[j] == '1';
        }
    }

    genButtons();

    int bs, s, bt, t;
    for (int i = 0; i < Q; i++) {
        cin >> bs >> s >> bt >> t;
        bs--, bt--, s--, t--;
        cout << answerQuery(bs, bt, s, t) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}