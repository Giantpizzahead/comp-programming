/*
<Link to problem>

Solution:
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int N = 10;
int K = 3;
int A[N];
int maxRev = 0;

int testArr() {
    set<int> vals;
    rep(i, 0, N) vals.insert(A[i]);
    if (sz(vals) == 1) return 0;
    int cnt = 0;
    rep(i, 0, N) {
        bool works = true;
        rep(j, 0, N/2) {
            if (A[j] != A[N-1-j]) works = false;
        }
        cnt += works;
        int temp = A[0];
        rep(j, 1, N) swap(A[j], A[j-1]);
        A[N-1] = temp;
    }
    return cnt;
}

void genArr(int i) {
    if (i == N) {
        int res = testArr();
        if (res > 2) {
            cerr << res << "\n";
            rep(j, 0, N) cerr << A[j] << " \n"[j==N-1];
        }
        maxRev = max(res, maxRev);
        return;
    }
    rep(j, 0, K) {
        A[i] = j;
        genArr(i+1);
    }
}

void solve() {
    genArr(0);
    cerr << "max " << maxRev << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // For HackerCup
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    int T; cin >> T; T = 1;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
