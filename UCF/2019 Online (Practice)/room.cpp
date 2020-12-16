#include <iostream>
#include <string>
using namespace std;
using ll = long long;

const int MAXN = 100005;

string G;
ll D;

int check(__int128_t B) {
    // cout << "check " << (ll) B << endl;
    __int128_t num = 0, currB = 1;
    for (int i = G.length() - 1; i >= 0; i--) {
        for (int j = 0; j < G[i] - '0'; j++) {
            num += currB;
            if (num > 1e18) return -1;
        }
        if (i != 0) {
            currB *= B;
            if (currB > 1e18) return -1;
        }
    }
    if (num == D) return 0;
    else if (num > D) return -1;
    else return 1;
}

void solve() {
    cin >> G >> D;
    ll low = 10, high = 1e18;
    while (low < high) {
        ll mid = (low + high) / 2;
        int res = check(mid);
        if (res == 0) {
            cout << mid << '\n';
            return;
        } else if (res == -1) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout << low << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Hotel Visit #" << i << ": Base ";
        solve();
    }
    return 0;
}