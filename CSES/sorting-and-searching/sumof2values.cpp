#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, X;
pair<int, int> A[MAXN];

void solve() {
    cin >> N >> X;
    rep(i, 0, N) {
        cin >> A[i].first;
        A[i].second = i+1;
    }
    sort(A, A+N);
    rep(i, 0, N) {
        int j = distance(A, lower_bound(A+i+1, A+N, pair<int, int>{X-A[i].first, -1}));
        if (j == N || A[j].first != X-A[i].first) continue;
        cout << A[i].second << " " << A[j].second << "\n";
        return;
    }
    cout << "IMPOSSIBLE\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}