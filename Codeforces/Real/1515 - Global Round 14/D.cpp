#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 2e5+5;

int N, L, R;
set<pair<int, int>> A, B;

void solve() {
    A.clear();
    B.clear();
    cin >> N >> L >> R;
    rep(i, 0, L) {
        int x; cin >> x;
        x--;
        A.insert({x, i});
    }
    rep(i, 0, R) {
        int x; cin >> x;
        x--;
        B.insert({x, i});
    }
    if (L < R) {
        swap(L, R);
        swap(A, B);
    }

    // Remove already matching
    int currC = 0;
    while (true) {
        auto ptr = A.lower_bound({currC, -1});
        if (ptr == A.end()) break;
        auto ptr2 = B.lower_bound({ptr->first, -1});
        if (ptr2 != B.end() && ptr->first == ptr2->first) {
            // Matching
            debug << "matching " << ptr->first << "\n";
            A.erase(ptr);
            B.erase(ptr2);
            L--, R--;
            N -= 2;
        } else currC = ptr->first + 1;
    }

    // Take advantage of colors
    int mustMove = (L-R) / 2;
    int colorSwitches = N / 2;
    debug << "initial " << mustMove << " " << colorSwitches << "\n";
    while (sz(A) > 1 && mustMove > 0) {
        auto ptr = A.begin();
        auto ptr2 = next(ptr);
        if (ptr->first != ptr2->first) {
            A.erase(ptr);
        } else {
            // Use this
            ptr2 = A.erase(ptr);
            A.erase(ptr2);
            mustMove--;
        }
    }
    debug << "final " << mustMove << " " << colorSwitches << "\n";

    cout << mustMove + colorSwitches << '\n';
    debug << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}