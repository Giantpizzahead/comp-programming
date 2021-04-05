#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N;
struct Loc {
    int i, j;
};
vector<Loc> odds, evens;

void solve() {
    cin >> N;
    rep(i, 0, N) {
        rep(j, 0, N) {
            if ((i+j)%2==1) odds.push_back({i+1, j+1});
            else evens.push_back({i+1, j+1});
        }
    }
    rep(i, 0, N*N) {
        int a; cin >> a;
        Loc l;
        int b;
        if (odds.empty()) {
            b = (a != 2 ? 2 : 3);
            l = evens.back(); evens.pop_back();
        } else if (evens.empty()) {
            b = (a != 1 ? 1 : 3);
            l = odds.back(); odds.pop_back();
        } else if (a == 1) {
            l = evens.back(); evens.pop_back();
            b = 2;
        } else {
            l = odds.back(); odds.pop_back();
            b = 1;
        }
        cout << b << ' ' << l.i << ' ' << l.j << endl;
    }
}

int main() {
    solve();
    return 0;
}