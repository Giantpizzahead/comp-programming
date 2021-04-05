#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5;

int N;
ll X;
ll A[MAXN];
map<ll, int> M;

void solve() {
    cin >> N >> X;
    rep(i, 0, N) cin >> A[i];
    M[0] = 1;
    ll sum = 0, answer = 0;
    rep(i, 0, N) {
        sum += A[i];
        answer += M[sum-X];
        M[sum]++;
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}