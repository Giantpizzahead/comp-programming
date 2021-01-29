#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXS = 605;

int N, A, B;
double prob[MAXS], prevProb[MAXS];

void solve() {
    cin >> N >> A >> B;
    prob[0] = 1;
    rep(i, 0, N) {
        swap(prob, prevProb);
        rep(j, 0, 6*N+1) {
            prob[j] = 0;
            rep(k, 1, 7) {
                if (j-k < 0) continue;
                prob[j] += prevProb[j-k] / 6;
            }
        }
    }
    double ans = 0;
    rep(i, A, B+1) ans += prob[i];
    cout << fixed << setprecision(6) << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}