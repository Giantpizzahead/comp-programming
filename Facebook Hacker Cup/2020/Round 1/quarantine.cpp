#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXN = 1000005;

ll answer;
ll batch1, batch2;
int N, totalUninfected;
int batchSize[MAXN], batchID[MAXN], stSize[MAXN];
bool isInfected[MAXN];
vector<int> children[MAXN];

struct Info {
    ll c1, c2, ec1, ec2;
    int ignoreID;
};

Info info[MAXN];

void solveGeneral(int n) {
    vector<Info*> childInfo;
    for (int e : children[n]) {
        solveGeneral(e);
        childInfo.push_back(&info[e]);
    }

    // Merge childInfos
    for (Info* i : childInfo) {
        // Check if current node has a batch
        if (batchID[n] != -1 && i->ignoreID != batchID[n]) {
            // Batch exists and is not ignored; does it add to the answer?
            if (batchSize[batchID[n]] == batch1) {
                answer += i->ec2 * batch1 * batch2;
            }
            if (batchSize[batchID[n]] == batch2) {
                answer += i->ec1 * batch1 * batch2;
            }
        }
        if (info[n].c1 != 0 && i->c2 != 0) {
            answer += info[n].ec1 * i->c2 * batch1 * batch2;
            answer += i->ec2 * info[n].c1 * batch1 * batch2;
        }
        if (info[n].c2 != 0 && i->c1 != 0) {
            answer += info[n].ec2 * i->c1 * batch1 * batch2;
            answer += i->ec1 * info[n].c2 * batch1 * batch2;
        }
        info[n].c1 += i->c1;
        info[n].c2 += i->c2;
        info[n].ec1 += i->ec1;
        info[n].ec2 += i->ec2;
        // cout << i->c1 << " " << i->c2 << " " << i->ec1 << " " << i->ec2 << endl;
    }
    // cout << "node " << n+1 << ": " << answer << endl;

    // Update batch counts
    if (batchSize[n] == batch1) {
        info[n].c1++;
    }
    if (batchSize[n] == batch2) {
        info[n].c2++;
    }

    // Update edge counts
    info[n].ec1 += info[n].c1;
    info[n].ec2 += info[n].c2;

    // Set ignore id (to avoid overcounting)
    info[n].ignoreID = batchID[n];
}

int dfs(int n, int compRoot) {
    int numUninfected = 0;
    bool isRoot = false;
    if (compRoot == -1 && !isInfected[n]) {
        compRoot = n;
        isRoot = true;
    }
    if (compRoot != -1 && !isInfected[n]) batchID[n] = compRoot;
    if (isInfected[n]) compRoot = -1;
    for (int e : children[n]) {
        numUninfected += dfs(e, compRoot);
        stSize[n] += stSize[e];
    }
    stSize[n]++;
    if (!isInfected[n]) {
        numUninfected++;
        if (isRoot) {
            batchSize[n] = numUninfected;
            return 0;
        }
    }
    return numUninfected;
}

int solveOneBatch(int n, bool parentUninfected) {
    if (n != 0 && (isInfected[n] || !parentUninfected)) {
        // Edge outside of batch
        answer += (ll) stSize[n] * (N - stSize[n]);
    }

    int numUninfected = 0;
    for (int e : children[n]) {
        numUninfected += solveOneBatch(e, !isInfected[n]);
    }
    if (!isInfected[n]) numUninfected++;

    if (n != 0 && !isInfected[n] && parentUninfected) {
        // Edge inside batch
        answer += (ll) numUninfected * (totalUninfected - numUninfected);
    }
    return numUninfected;
}

void solve(int tn) {
    for (int i = 0; i < N; i++) {
        batchSize[i] = 0;
        batchID[i] = -1;
        stSize[i] = 0;
        info[i].c1 = 0;
        info[i].c2 = 0;
        info[i].ec1 = 0;
        info[i].ec2 = 0;
        info[i].ignoreID = -1;
    }
    dfs(0, -1);

    // Casework
    int numBatches = 0;
    batch1 = -1;
    batch2 = -1;
    for (int i = 0; i < N; i++) {
        if (batchSize[i] != 0) {
            numBatches++;
            if (batchSize[i] >= batch1) {
                batch2 = batch1;
                batch1 = batchSize[i];
            } else if (batchSize[i] >= batch2) {
                batch2 = batchSize[i];
            }
        }
    }

    ll maxPairs = 0;
    answer = 0;
    if (numBatches == 0 || (numBatches == 1 && batch1 == 1)) {
        // No / one uninfected
        for (int i = 1; i < N; i++) {
            answer += (ll) stSize[i] * (N - stSize[i]);
        }
    } else if (batch2 == -1) {
        // Only one batch
        maxPairs = (ll) batch1 * (batch1 - 1) / 2;
        solveOneBatch(0, true);
    } else {
        // General case
        for (int i = 0; i < N; i++) {
            if (batchSize[i] != 0) {
                maxPairs += (ll) batchSize[i] * (batchSize[i] - 1) / 2;
            }
        }
        maxPairs += (ll) batch1 * batch2;
        solveGeneral(0);
        // Handle overcount
        if (batch1 == batch2) answer /= 2;
    }
    /*
    for (int i = 0; i < N; i++) cout << batchID[i] << ' ';
    cout << endl;
    */
    fout << "Case #" << tn << ": " << maxPairs << " " << answer << endl;
}

int E[MAXN];

void parseInput(int tn) {
    int K;
    ll A, B, C;
    fin >> N >> K;
    string str;
    fin >> str;
    totalUninfected = 0;
    for (int i = 0; i < N; i++) {
        isInfected[i] = (str[i] == '#');
        if (!isInfected[i]) totalUninfected++;
        children[i].clear();
    }
    int x;
    for (int i = 1; i <= K; i++) {
        fin >> x;
        E[i] = x;
        children[x-1].push_back(i);
    }
    fin >> A >> B >> C;
    for (int i = K + 1; i < N; i++) {
        x = (A * E[i-2] + B * E[i-1] + C) % i + 1;
        E[i] = x;
        children[x-1].push_back(i);
    }
    /*
    cout << "----" << endl;
    for (int i = 1; i < N; i++) cout << E[i] << ' ';
    cout << endl;
    */
    solve(tn);
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) parseInput(i);
    return 0;
}