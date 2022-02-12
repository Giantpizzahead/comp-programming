/*
Works for the original problem

Solution:
Lexicographically least
Fix the number of smallest index cow at front, then do greedy to see if it's still possible to pair
Greedy = Place the cow with largest # left, put all the 1s at end
This is slow, but guaranteed to work.
Runtime: O(N^3)
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXM = 5e5;

int N, M;
int A[MAXM];
vector<int> order;

int n, curr, cnt;
int X[MAXM];

void useNum(int x) {
    assert(X[x] > 0);
    // debug << "use " << x << '\n';
    if (curr == -1 || curr == x) {
        curr = x;
        cnt++;
    } else {
        cnt--;
        if (cnt == 0) curr = -1;
    }
    X[x]--;
    n--;
}

int doGreedy() {
    // debug << "greedy\n";
    rep(i, 0, M) X[i] = A[i];
    n = N, curr = -1, cnt = 0;
    // Fixed cows
    for (int x : order) {
        if (X[x] == 0) return -1;
        else useNum(x);
    }
    // Use the largest cow #
    while (n > X[0]) {
        int maxI = 1;
        rep(i, 1, M) if (X[i] > X[maxI]) maxI = i;
        useNum(maxI);
    }
    while (n > 0) useNum(0);
    if (curr != 0) return 0;
    else return cnt;
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) cin >> A[i];

    int ans = doGreedy();
    if (ans <= 0) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    cout << ans << '\n';

    while (sz(order) < N) {
        // Next cow to place
        rep(i, 0, M) {
            order.push_back(i);
            int v = doGreedy();
            if (v == ans) break;
            else order.pop_back();
        }
    }
    for (int x : order) cout << x+1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("gangs.in", "r", stdin);
    freopen("gangs.out3", "w", stdout);
    solve();
    return 0;
}