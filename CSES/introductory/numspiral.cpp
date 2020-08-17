#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int T, X, Y;

int main() {
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> Y >> X;
        int outer = max(X, Y);
        ll num = (ll) (outer - 1) * (outer - 1) + 1;
        if (outer % 2 == 1) {
            // Right, then up
            if (Y == outer) {
                cout << num + X - 1 << endl;
            } else {
                cout << num + outer - 1 + (outer - Y) << endl;
            }
        } else {
            // Down, then left
            if (X == outer) {
                cout << num + Y - 1 << endl;
            } else {
                cout << num + outer - 1 + (outer - X) << endl;
            }
        }
    }
}