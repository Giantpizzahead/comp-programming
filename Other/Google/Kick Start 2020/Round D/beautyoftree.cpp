#pragma GCC optimize("O0")
#pragma GCC optimize("conserve-stack")
#pragma GCC target("avx,avx2,fma")

/*
Takes about 40 MB of stack memory!
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;
using ll = long long;

const int MAXN = 500000;

int N, A, B;
ll numA, numB, numOvercount;
int depth[MAXN], parent[MAXN];
vector<int> children[MAXN];
vector<pair<int, int>> toMerge[MAXN];
pair<int, int> maxLocs[MAXN];
map<int, int> modACount[MAXN], modBCount[MAXN];

void dfs(int n) {
    depth[n] = depth[parent[n]] + 1;
    numA += 1 + depth[n] / A;
    numB += 1 + depth[n] / B;
    for (int e : children[n]) {
        dfs(e);
    }
}

map<int, int>::iterator x;
void overcount(int n) {
    modACount[n].emplace(depth[n] % A, 1);
    modBCount[n].emplace(depth[n] % B, 1);

    toMerge[n].emplace_back(n, n);
    maxLocs[n].first = n;
    maxLocs[n].second = n;
    int m;
    for (m = 0; m < children[n].size(); m++) {
        overcount(children[n][m]);
        toMerge[n].emplace_back(maxLocs[children[n][m]].first, maxLocs[children[n][m]].second);
        if (modACount[maxLocs[children[n][m]].first].size() > modACount[maxLocs[n].first].size()) {
            maxLocs[n].first = maxLocs[children[n][m]].first;
        }
        if (modBCount[maxLocs[children[n][m]].second].size() > modBCount[maxLocs[n].second].size()) {
            maxLocs[n].second = maxLocs[children[n][m]].second;
        }
    }
    for (m = 0; m < toMerge[n].size(); m++) {
        if (toMerge[n][m].first != maxLocs[n].first) {
            // Merge into maxLocs[n].first
            for (x = modACount[toMerge[n][m].first].begin(); x != modACount[toMerge[n][m].first].end(); x++) {
                if (modACount[maxLocs[n].first].count(x->first) == 0) modACount[maxLocs[n].first][x->first] = 0;
                modACount[maxLocs[n].first][x->first] += x->second;
            }
        }
        if (toMerge[n][m].second != maxLocs[n].second) {
            // Merge into maxLocs[n].second
            for (x = modBCount[toMerge[n][m].second].begin(); x != modBCount[toMerge[n][m].second].end(); x++) {
                if (modBCount[maxLocs[n].second].count(x->first) == 0) modBCount[maxLocs[n].second][x->first] = 0;
                modBCount[maxLocs[n].second][x->first] += x->second;
            }
        }
    }

    // Overcount
    numOvercount += (ll) modACount[maxLocs[n].first][depth[n] % A] * modBCount[maxLocs[n].second][depth[n] % B];
}

void solve(int tn) {
    cin >> N >> A >> B;
    int c;
    parent[0] = 0;
    depth[0] = -1;
    for (int i = 1; i < N; i++) {
        cin >> c;
        parent[i] = c-1;
        children[c-1].emplace_back(i);
    }
    numA = 0;
    numB = 0;
    numOvercount = 0;

    dfs(0);
    numA *= N;
    numB *= N;
    overcount(0);

    // cout << numA << ' ' << numB << ' ' << numOvercount << endl;

    long double answer = (long double) (numA + numB - numOvercount) / ((ll) N * N);
    cout << "Case #" << tn << ": " << fixed << setprecision(6) << answer << '\n';

    // Reset everything
    for (int i = 0; i < N; i++) {
        children[i].clear();
        modACount[i].clear();
        modBCount[i].clear();
        toMerge[i].clear();
    }
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}