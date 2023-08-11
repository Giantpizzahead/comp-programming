// ============================== BEGIN TEMPLATE ==============================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

void solve();

int runTests(bool multiple_tests) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (multiple_tests) {
        int T = 100;
        cout << T << endl;
        rep(i, 0, T) solve();
    } else solve();
    return 0;
}
// =============================== END TEMPLATE ===============================

random_device rd;
mt19937 g(rd());

int randint(int a, int b) {
    return g() % (b-a+1) + a;
}

vector<int> V, parent;
vector<vector<int>> kids;

vector<pair<int, int>> validMerges;

void findValidMerges(int n=0) {
    rep(i, 0, sz(kids[n])) rep(j, 0, i) {
        validMerges.push_back({kids[n][i], kids[n][j]});
    }
    for (int e : kids[n]) findValidMerges(e);
}

void applyMerge(int a, int b) {
    // cout << "merge " << a+1 << " " << b+1 << endl;
    if (V[a] < V[b]) swap(a, b);
    for (int e : kids[b]) {
        kids[a].push_back(e);
        parent[e] = a;
    }
    kids[b].clear();
    rep(i, 0, sz(kids[parent[b]])) if (kids[parent[b]][i] == b) {
        kids[parent[b]].erase(kids[parent[b]].begin() + i);
        break;
    }
    parent[b] = -2;
}

void solve() {
    int N = randint(5, 13);

    // Values
    V = vector<int>(N);
    rep(i, 0, N) V[i] = i+1;
    shuffle(all(V), g);

    // Tree
    kids = vector<vector<int>>(N);
    parent = vector<int>(N, -1);
    rep(i, 1, N) {
        int p = randint(0, i-1);
        parent[i] = p;
        kids[p].push_back(i);
    }

    // Print tree
    cout << N << "\n";
    rep(i, 1, N) cout << V[i] << " " << V[parent[i]] << "\n";

    // Merges
    int M = randint(0, N);
    int actualM = 0;
    rep(i, 0, M) {
        validMerges.clear();
        findValidMerges();
        if (sz(validMerges) == 0) break;
        int c = randint(0, sz(validMerges)-1);
        applyMerge(validMerges[c].first, validMerges[c].second);
        actualM++;
    }
    M = actualM;

    // Print final tree
    cout << N-M << "\n";
    rep(i, 1, N) if (parent[i] != -2) cout << V[i] << " " << V[parent[i]] << "\n";

    // Newline for clarity
    cout << "\n";
}

int main() {
    bool multipleTests = true;
    return runTests(multipleTests);
}
