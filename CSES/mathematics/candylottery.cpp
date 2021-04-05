#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 101;

int N, K;
double prob[MAXN][MAXN];

void solve() {
    cin >> N >> K;
    prob[0][0] = 1;
    rep(i, 0, N) {
        rep(j, 0, K+1) {
            // Random # of candies
            rep(k, 1, K+1) {
                prob[i+1][max(j, k)] += prob[i][j] / K;
            }
        }
    }
    double answer = 0;
    rep(j, 0, K+1) answer += prob[N][j] * j;
    cout << fixed << setprecision(6) << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}