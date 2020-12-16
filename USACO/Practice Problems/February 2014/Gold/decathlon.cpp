#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 20;

int N, B;
int dp[1 << MAXN];
int S[MAXN][MAXN];
struct Bonus {
    int p, k, a;
    const bool operator<(const Bonus& o) const {
        return p < o.p;
    }
};
Bonus P[MAXN];

int main() {
    freopen("dec.in", "r", stdin);
    freopen("dec.out", "w", stdout);
    cin >> N >> B;
    for (int i = 0; i < B; i++) {
        cin >> P[i].k >> P[i].p >> P[i].a;
    }
    sort(P, P+B);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> S[i][j];
        }
    }
    for (int mask = 1; mask < (1 << N); mask++) {
        int numOnes = 0;
        for (int i = 0; i < N; i++) {
            if ((mask & (1 << i)) != 0) numOnes++;
        }
        int bestTrans = 0;
        for (int i = 0; i < N; i++) {
            if ((mask & (1 << i)) != 0) {
                // Transition from here
                bestTrans = max(dp[mask ^ (1 << i)] + S[i][numOnes-1], bestTrans);
            }
        }
        // Bonuses
        for (int i = 0; i < B; i++) {
            if (P[i].k == numOnes && bestTrans >= P[i].p) {
                bestTrans += P[i].a;
            }
        }
        dp[mask] = bestTrans;
    }
    cout << dp[(1 << N) - 1] << endl;
    fclose(stdout);
    return 0;
}