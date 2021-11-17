#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int C = 26;

int N;
vector<int> adjD[C], adjB[C];
bool matAdj[C][C];
string S, T;

int M = 0;
int compID[C], nodeCnt[C], edgeCnt[C];

void dfsComp(int n) {
    compID[n] = M;
    for (int e : adjB[n]) {
        if (compID[e] == -1) dfsComp(e);
    }
}

void solve() {
    cin >> N >> S >> T;
    bool diff = false;
    rep(i, 0, N) {
        int a = S[i]-'a', b = T[i]-'a';
        if (a != b) diff = true;
        matAdj[a][b] = true;
    }
    // Special case
    if (!diff) {
        cout << "0\n";
        return;
    }
    // Outdegree check
    rep(i, 0, C) {
        int outDeg = 0;
        rep(j, 0, C) {
            if (matAdj[i][j]) {
                outDeg++;
                if (i != j) {
                    adjD[i].push_back(j);
                    adjB[i].push_back(j);
                    adjB[j].push_back(i);
                }
            }
        }
        if (outDeg > 1) {
            cout << "-1\n";
            return;
        }
    }
    // Undirected components
    rep(i, 0, C) compID[i] = -1;
    rep(i, 0, C) {
        if (compID[i] == -1) {
            dfsComp(i);
            M++;
        }
    }
    // Detailed info for each component
    rep(i, 0, C) {
        nodeCnt[compID[i]]++;
        edgeCnt[compID[i]] += sz(adjD[i]);
    }

    // Check special case
    bool special = true;
    int tempSum = 0;
    rep(i, 0, M) {
        int actualEdges = 0;
        rep(a, 0, C) {
            if (compID[a] != i) continue;
            rep(b, 0, C) actualEdges += matAdj[a][b];
        }
        if (actualEdges != nodeCnt[i]) {
            special = false;
            break;
        }
        tempSum += nodeCnt[i];
        // Check for whole cycle
        int sn, n;
        rep(j, 0, C) if (compID[j] == i) {
            sn = j;
            rep(e, 0, C) {
                if (matAdj[sn][e]) {
                    n = e;
                    break;
                }
            }
            break;
        }
        int cycleLen = 1;
        while (n != sn && cycleLen <= nodeCnt[i]) {
            rep(e, 0, C) {
                if (matAdj[n][e]) {
                    n = e;
                    break;
                }
            }
            cycleLen++;
        }
        if (cycleLen != nodeCnt[i]) {
            special = false;
            break;
        }
    }
    if (tempSum != C) special = false;
    if (special) {
        cout << "-1\n";
        return;
    }

    int answer = 0;
    rep(i, 0, M) {
        if (edgeCnt[i] == nodeCnt[i]-1) answer += edgeCnt[i];
        else {
            // Check for whole cycle
            int sn, n;
            rep(j, 0, C) if (compID[j] == i) {
                sn = j, n = adjD[j][0];
                break;
            }
            int cycleLen = 1;
            while (n != sn && cycleLen <= nodeCnt[i]) {
                n = adjD[n][0];
                cycleLen++;
            }
            if (cycleLen == nodeCnt[i]) {
                answer += nodeCnt[i] + 1;
            } else {
                answer += nodeCnt[i];
            }
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}