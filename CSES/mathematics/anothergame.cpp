/**
 * If all piles have even coin count, lose
 * (Copycat can ensure all piles remain even => will go to 0)
 * Otherwise, win
 * (Remove one from all odd piles)
 */

#include <iostream>
#include <vector>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N;

void solve() {
    cin >> N;
    bool allEven = true;
    rep(i, 0, N) {
        int x; cin >> x;
        if (x % 2 == 1) allEven = false;
    }
    cout << (allEven ? "second" : "first") << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}