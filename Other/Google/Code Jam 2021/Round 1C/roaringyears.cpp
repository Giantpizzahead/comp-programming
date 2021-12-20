#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = unsigned long long;

string Y;
ll numY, bestYear;

bool checkNum(ll x) {
    if (numY < x) bestYear = min(x, bestYear);
    return numY < x;
}

bool tryStarting(int x, int numTimes = 99) {
    ll currNum = x;
    string S = "";
    bool found = false;
    rep(i, 0, numTimes) {
        int newLen = sz(to_string(currNum)) + sz(S);
        if (newLen > 19) break;
        S += to_string(currNum);
        ll numS = stoull(S);
        if (i != 0 && checkNum(numS)) found = true;
        currNum++;
    }
    return found;
}

void solve() {
    cin >> Y;
    numY = stoull(Y);
    bestYear = 5e18;
    // Try nearby numbers (transition to more digits)
    rep(d, 1, 11) {
        rep(i, 1, 20) {
            ll x = 1;
            rep(j, 0, d) x *= 10;
            x -= i;
            if (x <= 0) continue;
            tryStarting(x, 99);
        }
    }
    // Try specific digits (binary search)
    rep(d, 1, 11) {
        rep(t, 2, 21) {
            if (d*t > 18) continue;
            ll low = 1, high = 1;
            rep(i, 0, d-1) {
                low *= 10;
                high *= 10;
            }
            high = high * 10 - 1;
            while (low < high) {
                ll mid = (low+high)/2;
                if (tryStarting(mid, t)) high = mid;
                else low = mid+1;
            }
            tryStarting(low, t);
        }
    }
    cout << bestYear << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}