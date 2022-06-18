#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e3+5;

int N;
int A[MAXN], B[MAXN], ans[MAXN];

void shift(int currN, int amount) {
    rep(i, 0, currN) B[i] = A[(i+amount) % currN];
    rep(i, 0, currN) A[i] = B[i];
    // rep(i, 0, N) cout << A[i] << " \n"[i==N-1];
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i];
        A[i]--;
    }
    for (int i = N-1; i >= 0; i--) {
        rep(j, 0, i+1) {
            if (A[j] == i) {
                if (j == i) ans[i] = 0;
                else {
                    ans[i] = j+1;
                    shift(i+1, j+1);
                }
                break;
            }
        }
    }
    rep(i, 0, N) cout << ans[i] << " \n"[i==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}