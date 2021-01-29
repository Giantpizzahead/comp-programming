#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 5e3+5;

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
        rep(j, i+1, N) {
            int T = X - A[i].first - A[j].first;
            int k = distance(A, lower_bound(A+j+1, A+N, pair<int, int>{T, -1}));
            if (k == N || A[k].first != T) continue;
            cout << A[i].second << " " << A[j].second << " " << A[k].second << '\n';
            return;
        }
    }
    cout << "IMPOSSIBLE\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}