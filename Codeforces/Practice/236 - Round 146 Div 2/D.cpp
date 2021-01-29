#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N;
double P[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> P[i];

    double answer = 0;
    double probSum = P[N-1];
    for (int i = N-2; i >= 0; i--) {
        probSum *= P[i];
        answer += probSum;
        probSum += P[i];
    }
    answer *= 2;
    rep(i, 0, N) answer += P[i];
    cout << fixed << setprecision(12) << answer << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}