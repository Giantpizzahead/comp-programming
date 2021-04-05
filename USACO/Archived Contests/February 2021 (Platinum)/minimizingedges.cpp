#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;

const int MAXN = 1e5+5, INF = 1e9;

int N, M;
vector<int> adj[MAXN];

int distE[MAXN], distO[MAXN];
int nodeType[MAXN];
struct State {
    int n, d;
};
queue<State> bfsQ;
void bfsDists() {
    rep(i, 0, N) {
        distE[i] = INF;
        distO[i] = INF;
    }
    distE[0] = 0;
    bfsQ.push({0, 0});
    while (!bfsQ.empty()) {
        State s = bfsQ.front(); bfsQ.pop();
        int nd = s.d+1;
        for (int e : adj[s.n]) {
            if ((nd & 1) && distO[e] == INF) {
                if (distE[e] == INF) nodeType[e] = 1;
                distO[e] = nd;
                bfsQ.push({e, nd});
            } else if (!(nd & 1) && distE[e] == INF) {
                if (distO[e] == INF) nodeType[e] = 0;
                distE[e] = nd;
                bfsQ.push({e, nd});
            }
        }
    }
}

multiset<int> mustExt[MAXN], canExt[MAXN];
multiset<int> usedMust, usedCan;

void genAnswer(int maxD) {
    int answer = 0;
    rep(i, 0, maxD) {
        // Connect this row to the next one
        int num1 = 0;
        for (int e : mustExt[i]) {
            if (e == 1) {
                num1++;
                continue;
            }
            // Try to extend while connecting bottom
            auto ptr = mustExt[i+1].find(e-1);
            if (ptr != mustExt[i+1].end()) {
                mustExt[i+1].erase(ptr);
                usedMust.insert(e-1);
                answer++;
                continue;
            }
            // Try to extend while reusing bottom
            answer++;
            // ptr = usedMust.find(e-1);
            // if (ptr != usedMust.end()) {
            //     answer++;
            //     continue;
            // }
            // assert(false);
        }
        // Connect the next row to this one
        while (!mustExt[i+1].empty()) {
            int e = *mustExt[i+1].begin();
            // Try to change to can extend
            auto ptr = mustExt[i].find(e);
            if (ptr != mustExt[i].end()) {
                mustExt[i+1].erase(mustExt[i+1].begin());
                usedCan.insert(e);
                answer++;
                continue;
            }
            ptr = canExt[i].find(e);
            if (ptr != canExt[i].end()) {
                mustExt[i+1].erase(mustExt[i+1].begin());
                usedCan.insert(e);
                answer++;
                continue;
            }
            // Try to connect with above
            ptr = mustExt[i].find(e+1);
            if (ptr != mustExt[i].end()) {
                mustExt[i+1].erase(mustExt[i+1].begin());
                usedMust.insert(e);
                answer++;
                continue;
            }
            // Use one of the can extends
            mustExt[i+1].erase(mustExt[i+1].begin());
            usedMust.insert(e);
            answer++;
            // assert(false);
        }
        // Cleanup
        answer += (num1+1)/2;
        mustExt[i+1].insert(all(usedMust));
        canExt[i+1].insert(all(usedCan));
        usedMust.clear();
        usedCan.clear();
    }
    // Final row (all ones)
    // for (int d : mustExt[maxD]) {
    //     if (d != 1) cout << "WHAT3" << endl;
    // }
    answer += (sz(mustExt[maxD])+1)/2;
    cout << answer << '\n';
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        adj[i].clear();
        nodeType[i] = -1;
    }
    nodeType[0] = 0;
    int a, b;
    rep(i, 0, M) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    bfsDists();
    rep(i, 0, N) {
        mustExt[i].clear();
        canExt[i].clear();
    }
    int maxD = 0;
    rep(i, 0, N) {
        if (distO[i] == INF || distE[i] == INF) {
            // Bipartite graph, means a tree would work
            // cout << "bipartite" << endl;
            cout << N-1 << '\n';
            return;
        }
        if (nodeType[i] == 0) {
            maxD = max(distE[i], maxD);
            mustExt[distE[i]].insert((distO[i] - distE[i] + 1) / 2);
        } else {
            maxD = max(distO[i], maxD);
            mustExt[distO[i]].insert((distE[i] - distO[i] + 1) / 2);
        }
    }
    // cout << "nodes\n";
    // rep(i, 0, maxD+1) {
    //     cout << i << ": ";
    //     for (int d : mustExt[i]) cout << d << ' ';
    //     cout << endl;
    // }
    // cout << endl;
    genAnswer(maxD);
    // cout << "dists\n";
    // rep(i, 0, N) cout << i+1 << ": " << (abs(distE[i]-distO[i])+1)/2 << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}