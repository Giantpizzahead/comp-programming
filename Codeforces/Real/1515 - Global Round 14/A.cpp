#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 102;

int N, X;
int A[MAXN];

void solve() {
    cin >> N >> X;
    int s = 0;
    rep(i, 0, N) {
        cin >> A[i];
        s += A[i];
    }
    if (X == s) cout << "NO\n";
    else {
        cout << "YES\n";
        s = 0;
        rep(i, 0, N) {
            if (s + A[i] == X) swap(A[i], A[i+1]);
            cout << A[i] << " \n"[i==N-1];
            s += A[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}