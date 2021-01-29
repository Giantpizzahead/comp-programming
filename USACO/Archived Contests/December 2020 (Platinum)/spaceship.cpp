#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 60, MAXM = 181;
const ll MOD = 1e9+7;

int N, K, Q;
int adj[MAXN][MAXN];
vector<vector<ll>> base, trans;

void multMatrices(vector<vector<ll>>& A, vector<vector<ll>>& B) {
    vector<vector<ll>> C;
    C.resize(A.size());
    for (int i = 0; i < C.size(); i++) C[i].resize(B[0].size());
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < B.size(); k++) {
                C[i][j] += A[i][k] * B[k][j];
                C[i][j] %= MOD;
            }
        }
    }
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            A[i][j] = C[i][j];
        }
    }
}

void matrixExpo(int e) {
    while (e > 0) {
        if (e % 2 == 0) {
            multMatrices(base, trans);
        }
        multMatrices(trans, trans);
        e /= 2;
    }
}

int prepMatrix(int bs, int s, int bt, int t) {
    for (int i = 0; i < trans.size(); i++) fill(trans[i].begin(), trans[i].end(), 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            trans[i][j] = adj[i][j];
        }
    }
    for (int i = N; i < N+K; i++) {
        for (int j = N; j < N+K; j++) {
            
        }
    }
    matrixExpo(1e9);
}

void solve() {
    cin >> N >> K >> Q;
    trans.resize(N+K+1);
    for (int i = 0; i < trans.size(); i++) trans[i].resize(N+K+1);
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < N; j++) adj[i][j] = str[j] == '1';
    }
    int bs, s, bt, t;
    for (int i = 0; i < Q; i++) {
        cin >> bs >> s >> bt >> t;
        bs--;
        s--;
        bt--;
        t--;
        cout << prepMatrix(bs, s, bt, t) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}