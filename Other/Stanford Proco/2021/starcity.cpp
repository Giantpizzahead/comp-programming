/*
Solution: Start with an empty graph. Add the nodes in decreasing order of offers. Then, we can use a DSU and a set to find the best path within a line or that goes across the star. Treat the root as not being in any star.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 1e5+5;

int N, R, K;

struct DisjointSet {
    int V[MAXN], highestLoc[MAXN];
    bool active[MAXN];

    void init() {
        rep(i, 0, N) V[i] = -1, active[i] = false;
    }

    int find(int n) {
        if (V[n] < 0) return n;
        else return V[n] = find(V[n]);
    }

    int compSize(int n) {
        return -V[find(n)];
    }

    int getHighestLoc(int n) {
        return highestLoc[find(n)];
    }

    void activate(int n) {
        active[find(n)] = true;
    }

    bool merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b || !active[a] || !active[b]) return false;

        if (V[a] > V[b]) swap(a, b);
        V[a] += V[b];
        V[b] = a;
        highestLoc[a] = min(highestLoc[a], highestLoc[b]);
        active[b] = false;
        return true;
    }
} ds;

ll A[MAXN];
int nodeToLine[MAXN], prevLineSize[MAXN];
bool processed[MAXN];
vector<int> adj[MAXN];
vector<pair<int, int>> sortedNodes;

vector<vector<int>> lines;
vector<int> currLine;
void genLine(int n, int p) {
    currLine.push_back(n);
    for (int e : adj[n]) {
        if (e == p) continue;
        genLine(e, n);
    }
}

ll bestAns = 0, bestX, bestY;
set<pair<int, int>> currSizes;

void updateAns(ll a, int x, int y) {
    // cout << "ans " << a << " " << x+1 << " " << y+1 << endl;
    if (x > y) swap(x, y);
    if (make_tuple(-a, x, y) < make_tuple(-bestAns, bestX, bestY)) {
        bestAns = a, bestX = x, bestY = y;
    }
}

void solve() {
    cin >> N;
    bestAns = 0;
    rep(i, 0, N) {
        cin >> A[i];
        sortedNodes.push_back({-A[i], i});
        updateAns(A[i], i, i);
    }
    rep(i, 1, N) {
        int a, b; cin >> a >> b; a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Find root
    R = 0;
    rep(i, 0, N) if (sz(adj[i]) > 2) R = i;

    // Find lines
    K = 0;
    for (int e : adj[R]) {
        genLine(e, R);
        lines.push_back(currLine);
        currLine.clear();
    }
    ds.init();
    K = sz(lines);
    nodeToLine[R] = -1;
    rep(i, 0, K) {
        prevLineSize[i] = -1;
        rep(j, 0, sz(lines[i])) {
            nodeToLine[lines[i][j]] = i;
            ds.highestLoc[lines[i][j]] = j;
        }
    }
    // cout << "lines\n";
    // rep(i, 0, K) {
    //     for (int x : lines[i]) cout << x+1 << " ";
    //     cout << endl;
    // }

    // Begin DSU merging
    sort(all(sortedNodes));
    for (auto& tempP : sortedNodes) {
        int currN = tempP.second;
        processed[currN] = true;
        // cout << "on " << currN+1 << endl;

        if (currN == R) {
            // Activated root node; do nothing
        } else {
            // Activated line node; merge
            int lineID = nodeToLine[currN];
            ds.activate(currN);
            for (int e : adj[currN]) ds.merge(currN, e);

            // Try this line size
            int lineSize = ds.compSize(currN);
            int highLoc = ds.getHighestLoc(currN);
            // cout << "lineSize " << lineSize << ", highLoc " << highLoc << endl;
            int newX = lines[lineID][highLoc], newY = lines[lineID][highLoc + lineSize - 1];
            ll newA = lineSize * A[currN];
            updateAns(newA, newX, newY);

            // Update line size sets
            if (highLoc == 0) {
                // Better, potentially
                // Remove old value
                if (prevLineSize[lineID] != -1) {
                    currSizes.erase(currSizes.find({prevLineSize[lineID], -lines[lineID][prevLineSize[lineID] - 1]}));
                }
                currSizes.insert({lineSize, -lines[lineID][lineSize - 1]});
                prevLineSize[lineID] = lineSize;
            }
        }

        // Try going through the root
        if (processed[R] && sz(currSizes) == 1) {
            // From root to end of line
            auto ptr1 = prev(currSizes.end());
            updateAns(A[currN] * (1 + ptr1->first), R, -ptr1->second);
        } else if (processed[R] && sz(currSizes) >= 2) {
            // Best 2
            auto ptr1 = prev(currSizes.end());
            auto ptr2 = prev(ptr1);
            updateAns(A[currN] * (1 + ptr1->first + ptr2->first), -ptr1->second, -ptr2->second);
        }
    }

    cout << bestAns << "\n";
    cout << bestX+1 << " " << bestY+1 << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("test.in", "r", stdin);
    solve();
    return 0;
}
