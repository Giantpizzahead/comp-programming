#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N;

int numFactors(ll X) {
    int cnt = 0;
    for (ll i = 1; i*i <= X; i++) {
        if (X % i == 0) {
            if (i*i != X) cnt += 2;
            else cnt++;
        }
    }
    return cnt;
}

void solve() {
    cin >> N;
    ll currSum = 0;
    for (int i = 1;; i++) {
        currSum += i;
        int cnt = numFactors(currSum);
        cout << "# " << cnt << endl;
        if (cnt > N) {
            cout << currSum << endl;
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}