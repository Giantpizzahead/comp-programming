#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, Q;
int A[MAXN], P[MAXN];

void solve() {
    cin >> N >> Q;
    rep(i, 1, N+1) {
        cin >> A[i];
        P[i] = P[i-1] ^ A[i];
    }
    int a, b;
    rep(i, 1, Q+1) {
        cin >> a >> b;
        cout << (P[b] ^ P[a-1]) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}