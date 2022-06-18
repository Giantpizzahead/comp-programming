/*
https://atcoder.jp/contests/abc250/tasks/abc250_c
*/

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;

int N, Q;
int A[MAXN], vToI[MAXN];

void solve() {
    cin >> N >> Q;
    rep(i, 0, N) {
        A[i] = i;
        vToI[i] = i;
    }
    rep(i, 0, Q) {
        int x; cin >> x; x--;
        int j = vToI[x];
        if (j == N-1) j--;
        vToI[A[j]]++;
        vToI[A[j+1]]--;
        swap(A[j], A[j+1]);
    }
    rep(i, 0, N) cout << A[i]+1 << " \n"[i==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}