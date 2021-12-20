/*
Notes go here.
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1000005;
const int INF = 1e9+7;

ll xSum, ySum;
int currX, currY;
int R, C, N, K;
vector<vector<int>> H, S;
struct Loc {
    int i, j, v;
    bool operator<(const Loc& o) const {
        if (v != o.v) return v > o.v;
        else if (i != o.i) return i < o.i;
        else return j < o.j;
    }
};
// Sort by greatest time first, then by ID
struct Robot {
    int n, t, id;
    Robot(): n(-1), t(-1), id(-1) {}
    Robot(int n, int t, int id) : n(n), t(t), id(id) {}
    bool operator<(const Robot& o) const {
        if (t != o.t) return t > o.t;
        else return id < o.id;
    }
};
struct Sample {
    int n, t, id;
    Sample(): n(-1), t(-1), id(-1) {}
    Sample(int n, int t, int id) : n(n), t(t), id(id) {}
    bool operator<(const Sample& o) const {
        if (t != o.t) return t > o.t;
        else return id < o.id;
    }
};
int currID;

struct DisjointSet {
    struct Edge {
        int n, c;
    };
    // adj will be sorted from largest to smallest c for each node
    vector<vector<Edge>> adj;
    vector<Edge> parent;
    vector<int> stSize;
    vector<bool> active;
    // Contains all robots active at this location & time
    vector<set<Robot>> robots;
    vector<Robot> rootRobot;
    // Contains all samples to be picked up at this location & time
    vector<set<Sample>> samples;

    void init() {
        adj.clear(); adj.resize(N);
        parent.clear(); parent.resize(N);
        stSize.clear(); stSize.resize(N);
        active.clear(); active.resize(N);
        robots.clear(); robots.resize(N);
        rootRobot.clear(); rootRobot.resize(N);
        samples.clear(); samples.resize(N);
        rep(i, 0, N) {
            stSize[i] = 1;
            parent[i] = {-1, -1};
            active[i] = false;
            rootRobot[i] = {-1, -1, -1};
        }
    }

    int find(int x, int t = -1) {
        if (parent[x].n == -1 || parent[x].c <= t) return x;
        else {
            int r = find(parent[x].n, t);
            return r;
        }
    }

    // a must be active!
    int merge(int a, int b, int c) {
        if (!active[b]) return a;
        a = find(a), b = find(b);
        if (a == b) return a;
        else if (stSize[a] > stSize[b]) {
            // Merge into a
            stSize[a] += stSize[b];
            parent[b] = {a, c};
            adj[a].push_back({b, c});
            return a;
        } else {
            // Merge into b
            stSize[b] += stSize[a];
            parent[a] = {b, c};
            adj[b].push_back({a, c});
            return b;
        }
    }

    void deleteRobot(int x, int t, int id) {
        currY--;
        while (x != -1) {
            assert(robots[x].find({x, t, id}) != robots[x].end());
            robots[x].erase({x, t, id});
            t = min(parent[x].c, t);
            x = parent[x].n;
        }
    }

    void addRobot(int x, int t, int id) {
        rootRobot[x] = {x, t, id};
        currY++;
        while (x != -1) {
            robots[x].insert({x, t, id});
            t = min(parent[x].c, t);
            x = parent[x].n;
        }
    }

    void recalcRobots(int x) {
        // Delete root robot
        if (rootRobot[x].id != -1) {
            deleteRobot(rootRobot[x].n, rootRobot[x].t, rootRobot[x].id);
            rootRobot[x] = {-1, -1, -1};
        }
        // Do we need to add a root robot?
        auto ptr1 = robots[x].begin();
        auto ptr2 = samples[x].begin();
        if (ptr2 == samples[x].end() || (ptr1 != robots[x].end() && ptr1->t > ptr2->t)) {
            // Already have one, or don't need
            return;
        }
        // Must add a root robot
        addRobot(x, ptr2->t+1, currID++);
    }
} ds;

void removeSample(int a, int b) {
    // Remove the old sample
    if (S[a][b] >= H[a][b]) return;  // Nothing to be done
    currX--;
    // Find old sample's location
    int x = a * C + b;
    x = ds.find(x, S[a][b]);
    assert(ds.samples[x].find({x, S[a][b], a*C+b}) != ds.samples[x].end());
    ds.samples[x].erase({x, S[a][b], a*C+b});
    while (x != -1) {
        ds.recalcRobots(x);
        x = ds.parent[x].n;
    }
}

void addSample(int a, int b, int u) {
    // Add the new sample
    S[a][b] = u;
    if (S[a][b] >= H[a][b]) return;  // Cannot get this sample
    else {
        currX++;
        // Check if there's a robot here
        int x = a * C + b;
        x = ds.find(x, S[a][b]);
        ds.samples[x].insert({x, S[a][b], a*C+b});
        while (x != -1) {
            ds.recalcRobots(x);
            x = ds.parent[x].n;
        }
    }
}

// Build the disjoint set tree
void initDSU() {
    vector<Loc> sortedH, sortedS;
    rep(i, 0, R) {
        rep(j, 0, C) {
            sortedH.push_back({i, j, H[i][j]});
            sortedS.push_back({i, j, S[i][j]});
        }
    }
    sort(all(sortedH), [](const Loc& a, const Loc& b) {
        return a.v > b.v;
    });
    sort(all(sortedS), [](const Loc& a, const Loc& b) {
        return a.v > b.v;
    });

    // Iterate through platforms and samples
    xSum = 0;
    ySum = 0;
    currX = 0;
    currY = 0;
    ds.init();
    currID = 0;
    for (Loc& l : sortedH) {
        // Process platform
        int x = l.i * C + l.j;
        ds.active[x] = true;
        if (l.j != C-1) ds.merge(x, x+1, l.v);
        if (l.j != 0) ds.merge(x, x-1, l.v);
        if (l.i != R-1) ds.merge(x, x+C, l.v);
        if (l.i != 0) ds.merge(x, x-C, l.v);
    }
    // Add samples
    for (Loc& l : sortedS) {
        addSample(l.i, l.j, l.v);
    }
}

void handleUpdate(int a, int b, int u) {
    removeSample(a, b);
    addSample(a, b, u);
}

void solve() {
    cin >> R >> C;
    N = R*C;
    H.clear();
    H.resize(R, vector<int>(C));
    S.clear();
    S.resize(R, vector<int>(C));
    rep(i, 0, R) {
        rep(j, 0, C) {
            cin >> H[i][j];
        }
    }
    rep(i, 0, R) {
        rep(j, 0, C) {
            cin >> S[i][j];
        }
    }
    initDSU();
    cin >> K;
    // cerr << endl;
    rep(i, 0, K) {
        int a, b, u; cin >> a >> b >> u;
        if (i != 0) {
            a ^= currY;
            b ^= currY;
            u ^= currY;
        }
        a--, b--;
        // cerr << a << " " << b << " " << u << endl;
        handleUpdate(a, b, u);
        // cerr << currX << " " << currY << endl;
        xSum += currX;
        ySum += currY;
    }
    cout << xSum << " " << ySum << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}