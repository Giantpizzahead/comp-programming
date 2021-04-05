#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 101;

int N;
double R[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> R[i];
    double answer = 0;
    rep(i, 0, N) {
        rep(j, i+1, N) {
            rep(k, 1, R[i]+1) {
                double prob = 1;
                if (k <= R[j]) prob = 1 - (R[j]+1-k) / R[j];
                answer += prob / R[i];
            }
        }
    }
    cout << fixed << setprecision(6) << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}