#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N;
double ySum;

void solve() {
    cin >> N;
    rep(i, 0, N) {
        double x, y;
        cin >> x >> y;
        ySum += y;
    }
    cout << fixed << 5 + ySum / N << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}