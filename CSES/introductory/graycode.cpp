#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N;
bool on[MAXN];

void grayCode(int i) {
    if (i == N) {
        rep(j, 0, N) cout << on[j];
        cout << '\n';
        return;
    }

    grayCode(i+1);
    on[i] = !on[i];
    grayCode(i+1);
}

void solve() {
    cin >> N;
    grayCode(0);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}