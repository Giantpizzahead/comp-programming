#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using ll = long long;

const int MAXN = 1002;
const ll MOD = 1e9+7;

int N;
ll A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN];
ll rowSumB[MAXN][MAXN];
ll rng[MAXN];

int genRand(int a, int b) {
    return (ll) rand() * rand() % (b-a+1) + a;
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cin >> A[i][j];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cin >> B[i][j];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cin >> C[i][j];
    }
    for (int i = 0; i < N; i++) rng[i] = genRand(1, 1e9+6);

    for (int i = 0; i < N; i++) {
        rowSumB[i][0] = B[i][0] * rng[0] % MOD;
        for (int j = 1; j < N; j++) rowSumB[i][j] = (rowSumB[i][j-1] + B[i][j] * rng[j]) % MOD;
    }

    // Check each row at once
    
    ll expected, actual;
    for (int i = 0; i < N; i++) {
        expected = 0;
        for (int j = 0; j < N; j++) {
            expected += A[i][j] * rowSumB[j][N-1];
            expected %= MOD;
        }
        actual = 0;
        for (int j = 0; j < N; j++) {
            actual += C[i][j] * rng[j];
            actual %= MOD;
        }
        if (expected != actual) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    srand(chrono::system_clock::now().time_since_epoch().count());
    solve();
    return 0;
}