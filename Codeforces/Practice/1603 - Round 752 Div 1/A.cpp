#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;

int K = 30;
int N;
int A[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) {
        bool works = false;
        rep(j, 0, min(i+1, K)) {
            if (A[i] % (j+2) != 0) {
                works = true;
                break;
            }
        }
        if (!works) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}