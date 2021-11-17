/*
ID: sunnyky1
LANG: C++11
TASK: theme
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 5000;
const ll POW = 271;

int N;
int A[MAXN], B[MAXN];
ll H[MAXN], P[MAXN];

unordered_set<ll> seen;

bool check(int L) {
    debug << "check(" << L << ") = ";
    seen.clear();
    ll currH = 0;
    rep(i, 0, N-1) {
        currH *= POW;
        // Remove old
        if (i >= L-1) currH -= P[L-1] * A[i-(L-1)];
        // Add new
        currH += A[i];
        H[i] = currH;
        // Add previous to seen
        if (i >= 2*(L-1)) seen.insert(H[i-L]);
        // Check if seen
        if (seen.count(H[i])) {
            debug << "true\n";
            return true;
        }
        // if (i >= L-2) {
        //     rep(j, i-(L-2), i+1) debug << A[j] << ' ';
        //     debug << "= " << H[i] << '\n';
        // }
    }
    debug << "false\n";
    return false;
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> B[i];
    rep(i, 0, N-1) {
        A[i] = B[i+1] - B[i] + 88;
    }
    int low = 4, high = N/2;
    while (low < high) {
        int mid = (low+high+1)/2;
        if (check(mid)) {
            low = mid;
        } else {
            high = mid-1;
        }
    }
    cout << (low == 4 ? 0 : low) << '\n';
}

int main() {
    freopen("theme.in", "r", stdin);
    freopen("theme.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    P[0] = 1;
    rep(i, 1, MAXN) P[i] = P[i-1] * POW;
    solve();
    return 0;
}