#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int N = 499999;
const int M = 499999;
const int K = 5000;
int A[M];

int randint(int a, int b) {
    return a + rand() % (b-a+1);
}

void solve() {
    srand(time(NULL));
    assert(N >= M);
    rep(i, 0, M) A[i]++;
    int m = N-M;
    while (m > 0) {
        int toPut = randint(1, max(1, m/K));
        A[randint(0, M-1)] += toPut;
        m -= toPut;
    }
    cout << N << ' ' << M << '\n';
    rep(i, 0, M) cout << A[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("gangs.in", "w", stdout);
    solve();
    return 0;
}