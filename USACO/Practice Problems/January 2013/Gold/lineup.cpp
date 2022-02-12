/*
Solution: Use a sliding window containing cows with at most K+1 breed types. The answer for each window is the max #
of cows in any 1 breed.
Runtime: O(N * log(N))
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 1e5+5;

int N, K, ans = 0;
int A[MAXN];
unordered_map<int, int> currCows;
multiset<int> currSizes;

void updateCow(int i, int v) {
    debug << "update " << i << " " << v << "\n";
    int c = currCows[i];
    if (c != 0) currSizes.erase(currSizes.find(c));
    c += v;
    if (c == 0) currCows.erase(i);
    else {
        currCows[i] = c;
        currSizes.insert(c);
    }
}

void solve() {
    cin >> N >> K;
    rep(i, 0, N) cin >> A[i];
    int li = 0;
    rep(ri, 0, N) {
        updateCow(A[ri], 1);
        while (sz(currCows) > K+1) {
            updateCow(A[li], -1);
            li++;
        }
        ans = max(*prev(currSizes.end()), ans);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);
    solve();
    return 0;
}