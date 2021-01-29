#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

string str;

void solve() {
    cin >> str;
    bool hasOne = false;
    int answer = str.size(), numOnes = 0;
    for (int i = str.size()-1; i >= 0; i--) {
        if (str[i] == '1' && !hasOne) {
            hasOne = true;
        } else if (str[i] == '1') answer--;
        if (hasOne) answer++;
        if (str[i] == '1') numOnes++;
    }

    if (numOnes == 1) cout << str.size() - 1 << endl;
    else cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}