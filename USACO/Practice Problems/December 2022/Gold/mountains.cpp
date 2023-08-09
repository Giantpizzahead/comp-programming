/*
http://usaco.org/index.php?page=viewproblem2&cpid=1258

Solution:
Track each pair of mountains that can see each other by storing (index, slope) pairs on the left mountain that's part
of the pair. Then, when updating a mountain, manually insert a new (index, slope) pair for each mountain on the left.
Recalculate the pairs for the updated mountain. The runtime is O((N^2 + NQ) * log(N)). This impl barely runs in time.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 2005;
const int INF = 1e9+7;

int N, Q, currAns;
int H[MAXN];
set<int> pairs[MAXN];

inline bool slopeDecreasing(int x1, ll y1, int x2, ll y2) {
    return y1 * x2 > y2 * x1;
}

void fillPairs(int i) {
    currAns -= sz(pairs[i]);
    pairs[i].clear();
    int y2 = -INF, x2 = 1;
    rep(j, i+1, N) {
        int y1 = H[j]-H[i], x1 = j-i;
        if (slopeDecreasing(x2, y2, x1, y1)) continue;  // Only add greater slopes
        pairs[i].insert(j);
        y2 = y1, x2 = x1;
        currAns++;
    }
}

void updateSlope(int i, int j) {
    int y1 = H[j] - H[i], x1 = j-i;
    // Remove pair if it already exists
    auto ptr = pairs[i].find(j);
    if (ptr != pairs[i].end()) {
        pairs[i].erase(ptr);
        currAns--;
    }

    // Can we insert this pair?
    ptr = pairs[i].lower_bound(j);
    if (ptr != pairs[i].begin()) {
        int k = *prev(ptr);
        if (slopeDecreasing(k-i, H[k]-H[i], x1, y1)) {
            // Cannot insert this pair, so nothing would happen
            return;
        }
    }
    
    // Can insert this pair; get rid of blocked pairs on right
    while (ptr != pairs[i].end()) {
        // if (ptr != pairs[i].end()) cout << "on " << ptr->i << " " << ptr->s << " comp " << newSlope << endl;
        int k = *ptr;
        if (!slopeDecreasing(x1, y1, k-i, H[k]-H[i])) break;
        // Remove this blocked pair
        auto nextPtr = next(ptr);
        pairs[i].erase(ptr);
        currAns--;
        ptr = nextPtr;
    }

    // Add this pair
    pairs[i].insert(j);
    currAns++;
}

void printPairs() {
    cout << "pairs:\n";
    rep(i, 0, N) {
        cout << i << ": ";
        for (int j : pairs[i]) cout << "(" << j << ", " << (double) (H[j]-H[i])/(j-i) << "), ";
        cout << endl;
    }
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> H[i];
    currAns = 0;
    rep(i, 0, N) fillPairs(i);
    // printPairs();
    
    cin >> Q;
    rep(i, 0, Q) {
        int x, y; cin >> x >> y;
        x--;
        H[x] += y;
        // Update slopes for all mountains to the left
        rep(j, 0, x) updateSlope(j, x);
        // Manually recalculate this mountain
        fillPairs(x);
        // printPairs();
        cout << currAns << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
