/**
 * Greedy (go row by row, fill the columns that need the most squares first)
 * Runtime: O(N^2 * log(N))
 */

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 50;

int N;
int A[MAXN], B[MAXN];
bool ans[MAXN][MAXN];

set<pair<int, int>> cols;
stack<pair<int, int>> toAdd;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) {
        cin >> B[i];
        if (B[i] != 0) cols.emplace(B[i], i);
    }
    rep(i, 0, N) {
        rep(j, 0, A[i]) {
            if (cols.empty()) {
                cout << "-1\n";
                return;
            }
            auto ptr = prev(cols.end());
            ans[i][ptr->second] = true;
            if (ptr->first != 1) toAdd.emplace(ptr->first-1, ptr->second);
            cols.erase(ptr);
        }
        while (!toAdd.empty()) {
            cols.emplace(toAdd.top());
            toAdd.pop();
        }
    }
    if (!cols.empty()) cout << "-1\n";
    else rep(i, 0, N) {
        rep(j, 0, N) cout << (ans[i][j] ? 'X' : '.');
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}