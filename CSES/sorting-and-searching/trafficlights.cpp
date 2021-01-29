#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int X, N;
multiset<int> lengths;
set<pair<int, int>> ranges;

void solve() {
    cin >> X >> N;
    ranges.emplace(0, X);
    lengths.insert(X);
    int x;
    for (int i = 0; i < N; i++) {
        cin >> x;
        // Split range
        auto range = prev(ranges.upper_bound({x, X+1}));
        int a = range->first, b = range->second;
        ranges.erase(range);
        lengths.erase(lengths.find(b-a));
        ranges.emplace(a, x);
        ranges.emplace(x, b);
        lengths.insert(x-a);
        lengths.insert(b-x);

        if (i != 0) cout << ' ';
        cout << *prev(lengths.end());
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}