#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e3+5;

int N;
int A[MAXN], B[MAXN], C[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) cin >> B[i];
    int sum = 0;
    rep(i, 0, N) {
        sum += A[i] - B[i];
        C[i] = A[i] + B[i];
    }
    sort(C, C+N, greater<int>());
    rep(i, 0, N) {
        if (i & 1) sum -= C[i];
        else sum += C[i];
    }
    if (sum > 0) cout << "First\n";
    else if (sum < 0) cout << "Second\n";
    else cout << "Tie\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}