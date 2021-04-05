#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXX = 1e6+1;

int N;
int A[MAXX];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        int x; cin >> x;
        A[x]++;
    }
    for (int i = MAXX-1; i > 0; i--) {
        int s = 0;
        for (int j = i; j < MAXX; j += i) {
            s += A[j];
        }
        if (s > 1) {
            cout << i << '\n';
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}