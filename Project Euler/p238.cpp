/**
 * What is the largest possible value of p(k) for any k?
 * +9 maximum per digit, starting at 0
 * -1, -5, -5, -7, -12, -14, -19, -25
 */

#include <bits/stdc++.h>
#define sz(x) ((int) x.size())
using ll = long long;
using namespace std;

const ll FIRST = 14025256;
const ll MOD = 20300713;

ll N;
string cycleStr;

ll digitSum(string& str) {
    ll s = 0;
    for (char c : str) s += c - '0';
    return s;
}

ll genNextNum(ll x) {
    x = x * x % MOD;
    return x;
}

string genCycleStr() {
    string str = "";
    vector<bool> seen(MOD+1);
    ll x = FIRST;
    while (!seen[x]) {
        seen[x] = true;
        str += to_string(x);
        x = genNextNum(x);
    }
    cout << "First digits: " << str.substr(0, 30) << endl;
    cout << "Last digits: " << str.substr(sz(str)-30) << endl;
    return str;
}


void solve() {
    cin >> N;
    // Generate cycle string
    cycleStr = genCycleStr();
    // Get all digit sums
}

int main() {
    freopen("input.txt", "r", stdin);
    solve();
}