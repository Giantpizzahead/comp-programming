#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N, numV, numH;

void solve() {
    cin >> N;
    string str;
    for (int i = 0; i < N; i++) {
        cin >> str;
        if (str[0] == '0') numV++;
        if (str[1] == '0') numV++;
        if (str[2] == '0') numH++;
        if (str[3] == '0') numH++;
    }
    int numS = min(numV/2, numH/2);
    cout << numS << ' ' << numV - numS*2 << ' ' << numH - numS*2 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}