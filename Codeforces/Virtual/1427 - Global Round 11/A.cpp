#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 51;

int N;
int A[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    int sum = 0;
    rep(i, 0, N) {
        sum += A[i];
    }
    sort(A, A+N);
    if (sum > 0) reverse(A, A+N);
    if (sum == 0) cout << "NO\n";
    else {
        cout << "YES\n";
        rep(i, 0, N) cout << A[i] << " \n"[i == N-1];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}