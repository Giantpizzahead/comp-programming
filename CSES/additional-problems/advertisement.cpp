#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5;

int N;
pair<int, int> locs[MAXN];
multiset<int> sizes;
set<pair<int, int>> ranges;

void solve() {
    cin >> N;
    int minK = 1e9;
    for (int i = 0; i < N; i++) {
        cin >> locs[i].first;
        locs[i].second = i;
        minK = min(locs[i].first, minK);
    }
    ranges.emplace(0, N-1);
    sizes.insert(0);
    sizes.insert(N);
    sort(locs, locs+N);
    int i = 0;
    ll answer = (ll) N * minK;
    while (true) {
        int k = locs[i].first;
        while (i != N && locs[i].first == k) {
            auto ptr = prev(ranges.lower_bound({locs[i].second, 1e9}));
            int l = ptr->first, r = ptr->second;
            ranges.erase(ptr);
            sizes.erase(sizes.find(r-l+1));
            if (l != locs[i].second) {
                ranges.emplace(l, locs[i].second-1);
                sizes.insert(locs[i].second-l);
            }
            if (r != locs[i].second) {
                ranges.emplace(locs[i].second+1, r);
                sizes.insert(r-locs[i].second);
            }
            i++;
        }
        if (i == N) break;
        answer = max((ll) locs[i].first * *prev(sizes.end()), answer);
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}