#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 2000005;
const ll MOD = 1000000007;

int N, M, E;
ll currEdgeSum, currInnerRemoveSum;
int X[MAXN], Y[MAXN], currW[MAXN], I[MAXN], W[MAXN];
bool inFirstSet[MAXN], canRemove2[MAXN];
multiset<int> innerEdges1[MAXN], innerEdges2[MAXN], innerSumBonuses, outerEdges;

void updateCircle(int circleI, int ei, int wi) {
    // cout << "inner " << circleI << ' ' << ei << ' ' << wi << ' ' << currW[ei] << endl;
    currEdgeSum -= currW[ei];
    currEdgeSum += wi;

    // Get inner remove sum
    int best1 = *innerEdges1[circleI].rbegin();
    int best2 = *innerEdges2[circleI].rbegin();
    int maxRemove = max(best1, best2);
    int currBonus = best1 + best2 - maxRemove;

    // Add edge
    if (inFirstSet[ei]) {
        innerEdges1[circleI].erase(innerEdges1[circleI].find(currW[ei]));
        innerEdges1[circleI].insert(wi);
    } else {
        innerEdges2[circleI].erase(innerEdges2[circleI].find(currW[ei]));
        innerEdges2[circleI].insert(wi);
    }
    currW[ei] = wi;

    // Update best inner remove sum
    int newBest1 = *innerEdges1[circleI].rbegin();
    int newBest2 = *innerEdges2[circleI].rbegin();
    int newMaxRemove = max(newBest1, newBest2);
    currInnerRemoveSum = currInnerRemoveSum - maxRemove + newMaxRemove;

    // Handle circles with different connection points
    if (canRemove2[circleI]) {
        // Update best bonus
        int newBonus = newBest1 + newBest2 - newMaxRemove;
        // cout << "removebonus" << endl;
        innerSumBonuses.erase(innerSumBonuses.find(currBonus));
        innerSumBonuses.insert(newBonus);
    }
}

void solve(int tn) {
    // cout << "Case " << tn << endl;
    // Reset outer edges
    outerEdges.clear();
    for (int i = 0; i < N; i++) {
        outerEdges.insert(1);
    }
    innerSumBonuses.clear();
    // Easier impl
    innerSumBonuses.insert(0);
    currInnerRemoveSum = 0;
    for (int i = 0; i < N; i++) {
        // Determine which set each edge is in
        for (int j = 0; j < M; j++) {
            inFirstSet[i * M + j] = false;
        }
        canRemove2[i] = false;
        for (int j = X[i]; j != Y[i]; j = (j+1) % M) {
            inFirstSet[i * M + j] = true;
            canRemove2[i] = true;
        }

        // Fill sets with initial values
        innerEdges1[i].clear();
        innerEdges2[i].clear();
        // Easier impl
        innerEdges1[i].insert(0);
        innerEdges2[i].insert(0);
        for (int j = 0; j < M; j++) {
            if (inFirstSet[i * M + j]) innerEdges1[i].insert(1);
            else innerEdges2[i].insert(1);
        }
        if (canRemove2[i]) innerSumBonuses.insert(1);
        currInnerRemoveSum++;
    }
    // Reset edge weight
    currEdgeSum = N * M + N;
    for (int i = 0; i < N * M + N; i++) {
        currW[i] = 1;
    }
    /*
    for (int x : outerEdges) {
        cout << x << ' ';
    }
    cout << endl;
    */
    // Handle events
    __int128 answer = 1;
    int ei, wi;
    for (int e = 0; e < E; e++) {
        ei = I[e];
        wi = W[e];
        if (ei < N * M) {
            // Inner circle edge
            int circleI = ei / M;
            updateCircle(circleI, ei, wi);
        } else {
            // Outer circle edge
            currEdgeSum -= currW[ei];
            currEdgeSum += wi;
            /*
            cout << "outer" << ' ' << ei << ' ' << wi << ' ' << currW[ei] << endl;
            for (int x : outerEdges) {
                cout << x << ' ';
            }
            cout << endl;
            */
            outerEdges.erase(outerEdges.find(currW[ei]));
            outerEdges.insert(wi);
            currW[ei] = wi;
        }

        // Calculate new MST weight
        ll mstWeight = currEdgeSum - currInnerRemoveSum;
        // Remove outer circle edge
        ll mstWeight1 = mstWeight - *outerEdges.rbegin();
        // Remove another inner circle edge
        ll mstWeight2 = mstWeight - *innerSumBonuses.rbegin();
        mstWeight = min(mstWeight1, mstWeight2);
        // cout << (ll) answer << ' ' << mstWeight << endl;
        answer = answer * mstWeight % MOD;
    }

    fout << "Case #" << tn << ": " << (ll) answer << endl;
}

void parseInput(int tn) {
    int K;
    ll Ax, Bx, Cx, Ay, By, Cy, Ai, Bi, Ci, Aw, Bw, Cw;
    fin >> N >> M >> E >> K;
    for (int i = 0; i < K; i++) {
        fin >> X[i];
    }
    fin >> Ax >> Bx >> Cx;
    for (int i = 0; i < K; i++) {
        fin >> Y[i];
    }
    fin >> Ay >> By >> Cy;
    for (int i = 0; i < K; i++) {
        fin >> I[i];
    }
    fin >> Ai >> Bi >> Ci;
    for (int i = 0; i < K; i++) {
        fin >> W[i];
    }
    fin >> Aw >> Bw >> Cw;
    for (int i = K; i < N; i++) {
        X[i] = (Ax * X[i-2] + Bx * X[i-1] + Cx) % M;
        Y[i] = (Ay * Y[i-2] + By * Y[i-1] + Cy) % M;
    }
    for (int i = K; i < E; i++) {
        I[i] = (Ai * I[i-2] + Bi * I[i-1] + Ci) % (N * M + N);
        W[i] = (Aw * W[i-2] + Bw * W[i-1] + Cw) % 1000000000;
    }
    solve(tn);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) parseInput(i);
    return 0;
}