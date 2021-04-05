#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const ll MAXN = 1e12+5, MOD = 1e9+7;

ll N;

ll sumFrom1(ll a) {
    a %= MOD;
    return a * (a+1) / 2 % MOD;
}

ll sumRange(ll a, ll b) {
    return sumFrom1(b) - sumFrom1(a-1);
}

void solve() {
    cin >> N;
    ll answer = 0;
    ll currDiv = 1;
    while (currDiv <= N) {
        ll numTimes = N / currDiv;
        ll lastDiv = N / numTimes;
        answer += sumRange(currDiv, lastDiv) * numTimes;
        answer %= MOD;
        // cout << currDiv << "-" << lastDiv << ": " << numTimes << endl;
        currDiv = lastDiv + 1;
    }
    if (answer < 0) answer += MOD;
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}