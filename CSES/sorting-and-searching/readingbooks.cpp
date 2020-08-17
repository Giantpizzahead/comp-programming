#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int N;

int main() {
    ios::sync_with_stdio(false);
    cin >> N;
    ll sum = 0;
    int longest = 0, x;
    for (int i = 0; i < N; i++) {
        cin >> x;
        sum += x;
        longest = max(x, longest);
    }

    if (longest >= sum - longest) cout << longest * 2 << endl;
    else cout << sum << endl;
    return 0;
}