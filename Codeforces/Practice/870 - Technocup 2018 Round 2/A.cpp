#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N, M;
bool A[10], B[10];

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        int x;
        cin >> x;
        A[x] = true;
    }
    rep(i, 0, M) {
        int x;
        cin >> x;
        B[x] = true;
    }
    rep(i, 1, 10) {
        if (A[i] && B[i]) {
            cout << i << '\n';
            return;
        }
    }
    rep(i, 1, 10) {
        rep(j, 1, 10) {
            if (A[i] && B[j]) {
                cout << min(i,j)*10+max(i,j) << '\n';
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}