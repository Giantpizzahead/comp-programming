#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 105;

int N;
ll X[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> X[i];
    ll ans = 0;
    string currNum = to_string(X[0]);
    rep(i, 1, N) {
        // Try to make equal length
        string str1 = "";
        // Match with greater
        bool carry = true;
        for (int j = sz(currNum)-1; j >= 0; j--) {
            if (!carry) {
                str1 = currNum[j] + str1;
            } else if (currNum[j] != '9' && carry) {
                carry = false;
                str1 = (char)(currNum[j]+1) + str1;
            } else {
                str1 = '0' + str1;
            }
        }
        if (carry) str1 = '1' + str1;
        string str2 = to_string(X[i]);
        if (sz(str2) > sz(str1)) {
            currNum = str2;
            continue;
        }
        int numApps = sz(str1) - sz(str2);
        int state = 0;
        rep(j, 0, sz(str1)) {
            if (state == 1) {
                // Already greater
                if (j == sz(str2)) str2 = str2 + '0';
                else continue;
            } else if (j == sz(str2)) {
                // Set to same
                str2 = str2 + str1[j];
            } else if (str2[j] > str1[j]) {
                // Greater
                state = 1;
            } else if (str2[j] == str1[j]) {
                // Same
                state = 0;
            } else {
                // Smaller; must use extra
                state = 2;
                break;
            }
        }
        // cout << str1 << " " << str2 << endl;
        ans += numApps;
        if (state != 2) {
            currNum = str2;
        } else {
            // Must use extra
            while (sz(str2) <= sz(str1)) str2 = str2 + '0';
            currNum = str2;
            ans++;
        }
        // cout << "num " << currNum << " ans " << ans << endl;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 1, T+1) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}