/*
http://usaco.org/index.php?page=viewproblem2&cpid=1258

Solution:
Track each pair of mountains that can see each other by storing (index, slope) pairs on the left mountain that's part
of the pair. Then, when updating a mountain, manually insert a new (index, slope) pair for each mountain on the left.
Recalculate the pairs for the updated mountain. The runtime is O((N^2 + NQ) * log(N)).
This impl barely runs in time, but gets wrong answer on some cases due to the usage of a float.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 2005;
const float INF = 1e12;

struct Pair {
    int i;
    float s;

    bool operator<(const Pair& o) const {
        return i < o.i;
    }
};

int N, Q, currAns;
int H[MAXN];
set<Pair> pairs[MAXN];

int compFloat(float a, float b) {
    if (abs(a-b) < 1e-9) return 0;
    else return (a < b ? -1 : 1);
}

void fillPairs(int i) {
    currAns -= sz(pairs[i]);
    pairs[i].clear();
    float prevSlope = -INF;
    rep(j, i+1, N) {
        float currSlope = (float) (H[j] - H[i]) / (j-i);
        if (compFloat(prevSlope, currSlope) == 1) continue;  // Only add greater slopes
        pairs[i].insert({j, currSlope});
        currAns++;
        prevSlope = currSlope;
    }
}

void updateSlope(int i, int j) {
    float newSlope = (float) (H[j] - H[i]) / (j-i);
    // Remove pair if it already exists
    auto ptr = pairs[i].find({j, -INF});
    if (ptr != pairs[i].end()) {
        pairs[i].erase(ptr);
        currAns--;
    }

    // Can we insert this pair?
    ptr = pairs[i].lower_bound({j, -INF});
    if (ptr != pairs[i].begin()) {
        ptr = prev(ptr);
        if (compFloat(ptr->s, newSlope) == 1) {
            // Cannot insert this pair, so nothing would happen
            return;
        }
    }
    
    // Can insert this pair; get rid of blocked pairs on right
    while (true) {
        ptr = pairs[i].lower_bound({j, -INF});
        // if (ptr != pairs[i].end()) cout << "on " << ptr->i << " " << ptr->s << " comp " << newSlope << endl;
        if (ptr == pairs[i].end() || compFloat(newSlope, ptr->s) != 1) break;
        // Remove this blocked pair
        pairs[i].erase(ptr);
        currAns--;
    }

    // Add this pair
    pairs[i].insert({j, newSlope});
    currAns++;
}

void printPairs() {
    cout << "pairs:\n";
    rep(k, 0, N) {
        cout << k << ": ";
        for (auto& p : pairs[k]) if (p.i != k) cout << "(" << p.i << ", " << p.s << "), ";
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
