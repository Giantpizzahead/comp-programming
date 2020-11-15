#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>

using namespace std;

int X, Y;

void solve() {
    int X, Y;
    cin >> X >> Y;

    if (Y == 0 || X < Y - 1 || (Y == 1 && X != 0)) {
        cout << "No" << endl;
        return;
    }

    X -= (Y-1);
    Y = 0;

    if (X % 2 == 0) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}