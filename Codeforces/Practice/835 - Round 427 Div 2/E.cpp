#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

int N, X, Y;

vector<int> nums;

// True if exactly 1, false if 0 or 2
int queries = 0;
bool query() {
    queries++;
    assert(queries <= 19);
    vector<int> actualNums;
    for (int x : nums) {
        if (x < N) actualNums.push_back(x);
    }
    assert(!actualNums.empty());
    cout << "? " << sz(actualNums);
    for (int x : actualNums) cout << ' ' << x+1;
    cout << endl;
    int x; cin >> x;
    if (sz(actualNums) % 2 == 0) {
        // Either even-0/2, or odd-1
        nums.clear();
        if (x == (X ^ Y)) return true;
        else if (x == 0) return false;
        else assert(false);
    } else {
        // Either odd-0/2, or even-1
        nums.clear();
        if (x == Y) return true;
        else if (x == X) return false;
        else assert(false);
    }
}

bool doQuery(int M) {
    int S = sz(nums);
    rep(i, 0, S) {
        int x = nums[i];
        while (x+M < N) {
            x += M;
            nums.push_back(x);
        }
    }
    return query();
}

pair<int, int> solve(int M) {
    assert(M >= 2);
    debug << "solve(" << M << ")" << endl;
    // Query first half
    rep(i, 0, M/2) nums.push_back(i);
    bool res = doQuery(M);
    if (!res) {
        // Keep going down, then merge back up
        pair<int, int> retPair = solve(M/2);
        int loc1 = retPair.first, loc2 = retPair.second;
        debug << "ret " << loc1+1 << " " << loc2+1 << endl;
        // Which half is this in?
        nums.push_back(loc1);
        res = doQuery(M);
        if (!res) {
            // Right half
            return {M/2 + loc1, M/2 + loc2};
        } else {
            // Left half
            return {loc1, loc2};
        }
    } else {
        assert(N > M/2);
        // Binary search for special left
        int low = 0, high = M/2-1;
        while (low < high) {
            int mid = (low + high) / 2;
            rep(i, 0, mid+1) nums.push_back(i);
            res = doQuery(M);
            if (!res) {
                low = mid+1;
            } else {
                high = mid;
            }
        }
        int loc1 = low;
        // Binary search for special right
        low = 0, high = M/2-1;
        while (low < high) {
            int mid = (low + high) / 2;
            rep(i, 0, mid+1) nums.push_back(M/2+i);
            res = doQuery(M);
            if (!res) {
                low = mid+1;
            } else {
                high = mid;
            }
        }
        int loc2 = M/2 + low;
        return {loc1, loc2};
    }
}

void solve() {
    cin >> N >> X >> Y;
    pair<int, int> ansPair = solve(1024);
    debug << "queries: " << queries << endl;
    cout << "! " << ansPair.first+1 << ' ' << ansPair.second+1 << endl;
}

int main() {
    solve();
    return 0;
}