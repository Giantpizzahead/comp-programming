#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;

int S, N;
int A[MAXN], P[MAXN];
set<pair<int, int>> pushups;

void solve() {
    cin >> S >> N;
    rep(i, 0, N) cin >> A[i];
    sort(A, A+N);

    int li = 0;
    rep(i, 1, N+1) {
        if (A[i] != A[li] || i == N) {
            // New group
            pushups.insert({i, A[li]});
            // cout << i << " " << A[li] << endl;
            li = i;
        }
    }

    int Q;
    cin >> Q;
    int x;
    rep(i, 0, Q) {
        cin >> x;
        auto ptr = pushups.lower_bound({x+1, -1});
        if (ptr == pushups.end()) cout << S << '\n';
        else cout << ptr->second - 1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}