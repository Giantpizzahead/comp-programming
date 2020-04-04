#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define HEAVY 625
#define MAXN 200000
#define MAXR 25000
#define MAXHEAVY 320

using namespace std;

struct Pair {
    int i, v;
    Pair(int i, int v) : i(i), v(v) {}
};

int N, R, Q, numHeavy = 0, numLight = 0;
int region[MAXN];
int regionCount[MAXR];
int heavyToAny[MAXHEAVY][MAXR];
int lightToHeavy[MAXR][MAXHEAVY];
int regionToNewI[MAXR];
vector<int> adj[MAXN];
vector<Pair> lightData[MAXR];

int heavyAnc[MAXHEAVY];
void precompHeavy(int n) {
    // Update this node's region count by # heavy ancestors
    for (int i = 0; i < numHeavy; i++) heavyToAny[i][region[n]] += heavyAnc[i];
    // Add this node (if appropriate) to ancestor count
    if (region[n] < numHeavy) heavyAnc[region[n]]++;
    for (auto e : adj[n]) {
        precompHeavy(e);
    }
    // Backtracking
    if (region[n] < numHeavy) heavyAnc[region[n]]--;
}

int numInST[MAXN][MAXHEAVY];
void precompLightToHeavy(int n) {
    // Find # nodes from each heavy region in subtree
    for (int e : adj[n]) {
        precompLightToHeavy(e);
        for (int i = 0; i < numHeavy; i++) numInST[n][i] += numInST[e][i];
    }
    // Update light to heavy query counts
    for (int i = 0; i < numHeavy; i++) {
        lightToHeavy[region[n]][i] += numInST[n][i];
    }
    // Add this node (if appropriate)
    if (region[n] < numHeavy) numInST[n][region[n]]++;
}

int clabel = 0;
void genLightData(int n) {
    lightData[region[n]].emplace_back(clabel++, 1);
    for (int e : adj[n]) genLightData(e);
    lightData[region[n]].emplace_back(clabel - 1, -1);
}

int calcLTL(int a, int b) {
    if (lightData[b].size() == 0) return 0;
    int currCount = 0, answer = 0;
    uint32_t bi = 0;
    for (auto const& p : lightData[a]) {
        while (lightData[b][bi].i <= p.i) {
            if (lightData[b][bi].v == 1) answer += currCount;
            bi++;
            if (bi == lightData[b].size()) return answer;
        }
        currCount += p.v;
    }
    return answer;
}

int main() {
    scanf("%d", &N);
    scanf("%d", &R);
    scanf("%d", &Q);
    int p, r;
    scanf("%d", &r);
    r--;
    region[0] = r;
    regionCount[r]++;
    for (int i = 1; i < N; i++) {
        scanf("%d", &p);
        scanf("%d", &r);
        p--;
        r--;
        region[i] = r;
        regionCount[r]++;
        adj[p].push_back(i);
    }

    // Figure out which regions are heavy
    for (int i = 0; i < R; i++) {
        if (regionCount[i] >= HEAVY) {
            // Heavy region
            regionToNewI[i] = numHeavy++;
        } else {
            // Light region
            regionToNewI[i] = R - 1 - numLight++;
        }
    }

    // Relabel regions in the new ordering (heavy regions are first)
    for (int i = 0; i < N; i++) region[i] = regionToNewI[region[i]];

    // Precomputation for (H, H) and (H, L) queries
    precompHeavy(0);

    // Precomputation for (L, H) [and technically (H, H)] queries
    precompLightToHeavy(0);

    // Precomputation for (L, L) queries
    for (int i = 0; i < R; i++) lightData[regionToNewI[i]].reserve(regionCount[i] * 2);
    genLightData(0);

    // Finally, answer the queries!
    int a, b;
    for (int i = 0; i < Q; i++) {
        scanf("%d", &a);
        scanf("%d", &b);
        a--;
        b--;
        a = regionToNewI[a];
        b = regionToNewI[b];
        if (a < numHeavy) {
            // Heavy to any
            printf("%d\n", heavyToAny[a][b]);
        } else if (b < numHeavy) {
            // Light to heavy
            printf("%d\n", lightToHeavy[a][b]);
        } else {
            // Light to light; calculate answer
            printf("%d\n", calcLTL(a, b));
        }
        fflush(stdout);
    }
}
