/*
24 = 2 * 2 * 2 * 3
12

n log n to simulate it... because of the prime thing!
Greedy from left to right to find min button presses.

C2: Answer changes by at most + or - 1. Use that.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 4e6+5;

int N, Q;
bool P[MAXN];
bool S[MAXN];

void solve() {
    cin >> N;
    string str; cin >> str;
    rep(i, 1, N+1) {
        S[i] = (str[i-1] == '1');
        P[i] = false;
    }

    // Greedily calculate first answer
    int ans = 0;
    rep(i, 1, N+1) {
        if (S[i]) {
            P[i] = true, ans++;
            for (int j = i; j <= N; j += i) S[j] = !S[j];
        }
    }
    // cerr << "initial: " << ans << endl;
    // rep(i, 1, N+1) cerr << P[i];
    // cerr << endl;
    // Update answers as we go
    cin >> Q;
    rep(i, 0, Q) {
        int b; cin >> b;
        if (P[b]) P[b] = false, ans--;
        else P[b] = true, ans++;
        // cerr << "between " << ans << endl;
        // ansSum += ans;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("c.txt", "r", stdin);
    freopen("c.out", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
