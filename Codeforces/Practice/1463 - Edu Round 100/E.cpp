#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 3e5+1;

int N, K, root;
int P[MAXN], X[MAXN], Y[MAXN], numReqs[MAXN];
bool inGroup[MAXN];
vi reqs[MAXN], edges[MAXN], revEdges[MAXN];

vi ordering;
bool used[MAXN];
stack<int> available;

void solve() {
    cin >> N >> K;
    rep(i, 1, N+1) {
        cin >> P[i];
        if (P[i] != 0) {
            reqs[P[i]].push_back(i);
            numReqs[i]++;
        } else root = i;
    }
    int a, b;
    rep(i, 1, K+1) {
        cin >> a >> b;
        edges[a].push_back(b);
        revEdges[b].push_back(a);
    }

    // Find grouped edges
    int numGroups = 0;
    rep(i, 1, N+1) {
        if (revEdges[i].empty() && !edges[i].empty()) {
            numGroups++;
            // Follow this trail
            int n = i;
            while (!edges[n].empty()) {
                inGroup[n] = true;
                reqs[n].push_back(edges[n][0]);
                numReqs[edges[n][0]]++;
                n = edges[n][0];
                if (P[n] == 0) {
                    cout << "0\n";
                    return;
                }
                if (!inGroup[P[n]]) {
                    reqs[P[n]].push_back(i);
                    numReqs[i]++;
                }
            }
            // Unmark inGroup
            n = i;
            while (!edges[n].empty()) {
                inGroup[n] = false;
                n = edges[n][0];
            }
        }
    }
    if (numGroups == 0) {
        // Cycle in special pairs
        cout << "0\n";
        return;
    }
    // rep(i, 1, N+1) {
    //     cout << i << ": ";
    //     for (int x : reqs[i]) cout << x << ' ';
    //     cout << endl;
    // }

    // Create ordering
    available.push(root);
    while (!available.empty()) {
        int n = available.top();
        available.pop();
        if (used[n]) continue;
        while (true) {
            used[n] = true;
            if (numReqs[n] != 0) {
                cout << "0\n";
                return;
            }
            ordering.push_back(n);
            for (int x : reqs[n]) {
                numReqs[x]--;
                assert(numReqs[x] >= 0);
                if (numReqs[x] == 0) {
                    available.push(x);
                }
            }
            // Follow requirements if needed
            if (!edges[n].empty()) {
                n = edges[n][0];
            } else break;
        }
    }
    if (ordering.size() != N) {
        cout << "0\n";
        return;
    }

    rep(i, 0, N) {
        if (i != 0) cout << ' ';
        cout << ordering[i];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}                                                                                                                   