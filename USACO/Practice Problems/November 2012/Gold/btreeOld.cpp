/**
 * Solution:
 * To handle vertical paths in the tree, a simple greedy approach can be used (or reuse the
 * below code).
 * To handle paths involving two subtrees (^ paths):
 * Maintain info for the "left" side of a parentheses path, meaning unclosed ( brackets.
 * Also maintain info for the "right" side of a parentheses path, meaning unclosed ) brackets.
 * Combine these at each node to form paths involving two subtrees.
 * 
 * Use the tree merging technique (merge into the smaller set) to get a good runtime.
 * 
 * The implementation is tricky to get right. The below code is quite long because copy paste
 * was used multiple times.
 * 
 * Runtime: O(4N * log(2N))
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 40005;

int N, answer;
bool P[MAXN];
vector<int> adj[MAXN];

struct LeftData {
    struct Pair {
        int p, t;
    };

    // For each sum, store:
    // (Maximum prefix sum, Minimum time added)
    unordered_map<int, Pair> R;
    vector<int> zeroHistory;
    int currT = 0, zeroC = 0;

    LeftData() {
        zeroHistory.push_back(0);
    }

    void extend(bool p) {
        // Add new key
        if (R.find(zeroC) == R.end()) {
            R[zeroC] = {0, currT};
        }
        // Handle parenthesis
        if (p) zeroC--;
        else {
            // Remove ranges that close too much
            auto p = R.find(zeroC);
            if (p != R.end()) R.erase(p);
            zeroC++;
        }
        zeroHistory.push_back(zeroC);
        currT++;
    }

    void lazyUpdate(int c) {
        if (R.find(c) == R.end()) cerr << "AHH LEFT" << endl;
        int minZero = zeroC;
        rep(i, R[c].t, currT+1) {
            minZero = min(zeroHistory[i], minZero);
        }
        R[c].p = max(c - minZero, R[c].p);
        R[c].t = currT;
    }

    void print(int x) {
        cout << "leftData[" << x+1 << "] = ";
        for (auto& p : R) {
            lazyUpdate(p.first);
            cout << p.first - zeroC << ": " << p.second.p << " " << p.second.t << ", ";
        }
        cout << endl;
    }

    static LeftData* merge(LeftData* a, LeftData* b) {
        if (a->currT < b->currT) swap(a, b);
        // Merge all data from b into a
        for (auto& p : b->R) {
            int c = p.first;
            Pair& data = p.second;
            b->lazyUpdate(c);
            c = c - b->zeroC + a->zeroC;
            if (a->R.find(c) == a->R.end()) {
                // Add new key
                a->R[c] = {data.p, a->currT};
            } else {
                // Update existing key
                a->lazyUpdate(c);
                a->R[c].p = max(data.p, a->R[c].p);
                a->R[c].t = a->currT;
            }
        }
        b->R.clear();
        return a;
    }
};

LeftData* leftData[MAXN];

struct RightData {
    struct Pair {
        int p, t, minZero;
    };

    // For each sum, store:
    // (Maximum suffix sum, Minimum time added)
    unordered_map<int, Pair> R;
    vector<int> zeroHistory;
    int currT = 0, zeroC = 0;

    RightData() {
        zeroHistory.push_back(0);
    }

    void extend(bool p) {
        // Add new key
        if (R.find(zeroC) == R.end()) {
            R[zeroC] = {0, currT, zeroC};
        }
        // Handle parenthesis
        if (!p) zeroC--;
        else {
            // Remove ranges that close too much
            auto p = R.find(zeroC);
            if (p != R.end()) R.erase(p);
            zeroC++;
        }
        zeroHistory.push_back(zeroC);
        currT++;
    }

    void lazyUpdate(int c) {
        if (R.find(c) == R.end()) cerr << "AHH RIGHT" << endl;
        int minZero = R[c].minZero;
        rep(i, R[c].t, currT+1) {
            minZero = min(zeroHistory[i], minZero);
        }
        int diff = c - minZero;
        int rawSum = zeroC - c;
        R[c].p = rawSum + diff;
        R[c].t = currT;
        R[c].minZero = minZero;
    }

    void print(int x) {
        cout << "rightData[" << x+1 << "] = ";
        for (auto& p : R) {
            lazyUpdate(p.first);
            cout << p.first - zeroC << ": " << p.second.p << " " << p.second.t << " " << p.second.minZero << ", ";
        }
        cout << endl;
    }

    static RightData* merge(RightData* a, RightData* b) {
        if (a->currT < b->currT) swap(a, b);
        // Merge all data from b into a
        for (auto& p : b->R) {
            int c = p.first;
            Pair& data = p.second;
            b->lazyUpdate(c);
            c = c - b->zeroC + a->zeroC;
            int zeroDiff = b->zeroC - a->zeroC;
            int newMinZero = data.minZero - zeroDiff;
            if (a->R.find(c) == a->R.end()) {
                // Add new key
                a->R[c] = {data.p, a->currT, newMinZero};
            } else {
                // Update existing key
                a->lazyUpdate(c);
                if (data.p > a->R[c].p) {
                    a->R[c].p = data.p;
                    a->R[c].t = a->currT;
                    a->R[c].minZero = newMinZero;
                }
            }
        }
        b->R.clear();
        return a;
    }
};

RightData* rightData[MAXN];

void updateAnswer(LeftData* L, RightData* R) {
    if (L->currT < R->currT) {
        // Iterate through left
        for (auto& rawPair : L->R) {
            int leftC = rawPair.first;
            int actualC = leftC - L->zeroC;
            int rightC = actualC + R->zeroC;
            L->lazyUpdate(leftC);
            int leftPre = rawPair.second.p;
            // Find matching on right
            auto ptr = R->R.find(rightC);
            if (ptr != R->R.end()) {
                R->lazyUpdate(rightC);
                int rightPre = ptr->second.p;
                int maxDepth = max(leftPre, actualC + rightPre);
                answer = max(maxDepth, answer);
            }
        }
    } else {
        // Iterate through right
        for (auto& rawPair : R->R) {
            int rightC = rawPair.first;
            int actualC = rightC - R->zeroC;
            int leftC = actualC + L->zeroC;
            R->lazyUpdate(rightC);
            int rightPre = rawPair.second.p;
            // Find matching on right
            auto ptr = L->R.find(leftC);
            if (ptr != L->R.end()) {
                L->lazyUpdate(leftC);
                int leftPre = ptr->second.p;
                int maxDepth = max(leftPre, actualC + rightPre);
                answer = max(maxDepth, answer);
            }
        }
    }
}

LeftData* singleLeftData;
RightData* singleRightData;

void dfs(int n, int p) {
    leftData[n] = new LeftData();
    rightData[n] = new RightData();
    bool leaf = true;
    for (int e : adj[n]) if (e != p) {
        leaf = false;
        dfs(e, n);
    }

    // Base case
    if (leaf) {
        leftData[n]->extend(P[n]);
        // leftData[n]->print(n);
        rightData[n]->extend(P[n]);
        // rightData[n]->print(n);
        return;
    }

    // Base combinations (straight path)
    for (int e : adj[n]) {
        if (e == p) continue;
        if (P[n]) updateAnswer(singleLeftData, rightData[e]);
        else updateAnswer(leftData[e], singleRightData);
    }

    // Combine two straight paths in the other direction
    // rep(i, 0, sz(adj[n])) {
    //     int e = adj[n][sz(adj[n])-1-i];
    //     if (e == p) continue;
    //     leftData[e]->extend(P[n]);
    //     leftData[n] = LeftData::merge(leftData[n], leftData[e]);
    //     updateAnswer(leftData[n], rightData[e]);
    // }

    // Combine two straight paths & merge subtrees
    // leftData[n] = new LeftData();
    for (int e : adj[n]) {
        if (e == p) continue;
        updateAnswer(leftData[n], rightData[e]);
        leftData[e]->extend(P[n]);
        leftData[n] = LeftData::merge(leftData[n], leftData[e]);
        rightData[n] = RightData::merge(rightData[n], rightData[e]);
    }
    rightData[n]->extend(P[n]);

    // leftData[n]->print(n);
    // rightData[n]->print(n);
}

void solve() {
    // Input parsing
    cin >> N;
    rep(i, 1, N) {
        int p; cin >> p;
        p--;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    rep(i, 0, N) {
        char c; cin >> c;
        P[i] = (c == '(');
    }
    // Setup DFS
    singleLeftData = new LeftData();
    singleLeftData->extend(true);
    singleRightData = new RightData();
    singleRightData->extend(false);
    answer = 0;
    dfs(0, 0);
    // Repeat for the other direction
    rep(i, 0, N) reverse(all(adj[i]));
    dfs(0, 0);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    freopen("btree.in", "r", stdin);
    freopen("btree.out", "w", stdout);
    solve();
    return 0;
}