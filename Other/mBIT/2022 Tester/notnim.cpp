#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;

int N, A, B;
int P[MAXN];

void solve() {
    cin >> N >> A >> B;
    rep(i, 0, N) {
        cin >> P[i];
        P[i] %= (A+B);
    }
    int numPickable = 0;
    rep(i, 0, N) if (P[i] >= min(A, B)) numPickable++;
    if (A == B) {
        if (numPickable % 2 == 0) cout << "Bob\n";
        else cout << "Alice\n";
        return;
    }

    int numOver = 0;
    rep(i, 0, N) {
        if (P[i] >= max(A, B)) numOver++;
    }
    if (numOver > 1) {
        // Lower number wins
        if (A < B) cout << "Alice\n";
        else cout << "Bob\n";
    } else if (numOver == 1) {
        if (A > B) {
            if (numPickable == 1) cout << "Alice\n";
            else cout << "Bob\n";
        } else {
            cout << "Alice\n";
        }
    } else {
        if (A > B) cout << "Bob\n";
        else if (numPickable == 0) cout << "Bob\n";
        else cout << "Alice\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}