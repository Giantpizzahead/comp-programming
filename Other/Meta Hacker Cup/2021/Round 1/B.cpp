#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N, M, A, B;

void solve() {
    cin >> N >> M >> A >> B;
    int minTime = N+M-1;
    if (A < minTime || B < minTime) cout << "Impossible\n";
    else {
        cout << "Possible\n";
        int targetA = A - minTime + 1;
        int targetB = B - minTime + 1;
        rep(i, 0, N) {
            rep(j, 0, M) {
                int x = 1;
                if (i == 0 && j == 0) x = targetA;
                else if (i == 0 && j == M-1) x = targetB;
                cout << x << " \n"[j==M-1];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}