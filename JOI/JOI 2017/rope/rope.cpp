/*
Solution: The problem statement can be simplified as follows.
Given an array C of N integers, each in the range [1, M]. (Guaranteed at least 1 of each color)
For each c in [1, M], what's the minimum # of elements you must change to create an array that:
- Only has one or two colors, one of which is c
- Can be separated into contiguous ranges of same elements, with the middle ranges having an even size

After fixing 2 colors, how to find minimum cost quickly?
. . 1 . 2 2 . 1 2 . . . 2 1 1 . 2 . . . 1
Fix parity (location of evens)
. . 1 . 2 2 . 1 2 . . . 2 1 1 . 2 . . . 1
   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^
For each pair, optimal cost can be easily determined
No match (. .) = 2
One match (1 ., . 1, 2 ., . 2) = 1
Both match (1 2, 2 1) = 1
Same match (1 1, 2 2) = 0
Might need to add one element matching either of the target colors on the ends (special for loc 0 and N-1)
Don't need to fix two colors to calc above cost (can process each independently), it doesn't affect anything
O(NM^2)

Total cost of a pair = sum of min(cost 1, cost 2) for each element
Each pair can only have up to one color = 0, only up to two colors = 1, everything else will be = 2
Total cost of a pair = 2 * (# of pairs) - Places with improvement

Only 1s will conflict, and only conflict between 2 colors (call these "conflict pairs")
Total cost of a pair =
2 * (# of pairs) - 2 * # with 0 in either color - # with 1 in either color + # where colors conflict
O(N+M^2)

To get full credit, evaluate conflict pairs manually, and just take color that saves the most for all other colors
- Simply iterate to next one if conflict arises (happens at most N times)

Runtime: O(N+M * log(M))
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e6+5;
const int INF = 1e9;

int N, M;
int C[MAXN], saved[MAXN], ans[MAXN];
vector<pair<int, int>> toTry;
map<pair<int, int>, int> conflicts;

void genPairs(bool isOdd) {
    // Clear previous data
    rep(i, 0, M) saved[i] = 0;
    toTry.clear();
    conflicts.clear();
    // Generate pairs
    for (int i = isOdd; i < N; i += 2) {
        if (i == N-1) {
            // Final one
            saved[C[i]]++;
        } else {
            // Pair
            int j = i+1;
            if (C[i] == C[j]) saved[C[i]] += 2;
            else {
                saved[C[i]]++;
                saved[C[j]]++;
                pair<int, int> p = {min(C[i], C[j]), max(C[i], C[j])};
                conflicts[p]++;
            }
        }
    }
    if (isOdd) saved[C[0]]++;
}

void updateAns() {
    // Sort best colors to pair with
    rep(i, 0, M) toTry.push_back({saved[i], i});
    sort(all(toTry));
    reverse(all(toTry));
    // Update answer for each
    rep(a, 0, M) {
        // Change all to one color
        ans[a] = min(N - saved[a], ans[a]);
        for (auto& p : toTry) {
            int b = p.second;
            if (a == b) continue;
            auto ptr = conflicts.find({min(a, b), max(a, b)});
            if (ptr == conflicts.end()) {
                // This is the best pairing; can stop here
                ans[a] = min(N - saved[a] - saved[b], ans[a]);
                break;
            } else {
                // Process manually and continue searching
                ans[a] = min(N - saved[a] - saved[b] + ptr->second, ans[a]);
            }
        }
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        cin >> C[i];
        C[i]--;
    }
    rep(i, 0, M) ans[i] = INF;

    // Pairs start at even indexes
    genPairs(false);
    updateAns();
    // Pairs start at odd indexes
    genPairs(true);
    updateAns();
    
    rep(i, 0, M) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}