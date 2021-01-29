#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e3;

int N, W;
int A[MAXN];

void solve() {
    cin >> N >> W;
    rep(i, 0, N) cin >> A[i];

    int curr = 0, minV = 0, maxV = 0;
    rep(i, 0, N) {
        curr += A[i];
        minV = min(curr, minV);
        maxV = max(curr, maxV);
    }

    int dist = maxV - minV;
    cout << max(W+1-dist, 0) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}