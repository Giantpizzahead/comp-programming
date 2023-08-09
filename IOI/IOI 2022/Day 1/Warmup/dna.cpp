/*
IOI 2021 Day 2: DNA
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
string A, B;
vector<int> numsA, numsB;
vector<int> preCnt[2][3], preSwaps[9];

int getSwapID(int x, int y) {
    return x * 3 + y;
}

void init(string a, string b) {
    A = a, B = b, N = a.length();
    numsA.resize(N), numsB.resize(N);
    for (int i = 0; i < N; i++) {
        int x = (A[i] == 'A' ? 0 : (A[i] == 'C' ? 1 : 2));
        int y = (B[i] == 'A' ? 0 : (B[i] == 'C' ? 1 : 2));
        numsA[i] = x, numsB[i] = y;
    }

    // Generate prefix sums
    for (int t = 0; t < 2; t++) {
        vector<int>& nums = (t == 0 ? numsA : numsB);
        for (int i = 0; i < 3; i++) {
            preCnt[t][i].resize(N+1);
            preCnt[t][i][0] = 0;
            for (int j = 0; j < N; j++) {
                preCnt[t][i][j+1] = preCnt[t][i][j] + (nums[j] == i);
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        preSwaps[i].resize(N+1);
        preSwaps[i][0] = 0;
        for (int j = 0; j < N; j++) {
            int id = getSwapID(numsA[j], numsB[j]);
            preSwaps[i][j+1] = preSwaps[i][j] + (id == i);
        }
    }
}

int get_distance(int x, int y) {
    // Get counts
    int cnt[2][3];
    for (int t = 0; t < 2; t++) {
        for (int i = 0; i < 3; i++) {
            cnt[t][i] = preCnt[t][i][y+1] - preCnt[t][i][x];
        }
    }
    int swaps[9];
    for (int i = 0; i < 9; i++) {
        swaps[i] = preSwaps[i][y+1] - preSwaps[i][x];
    }

    // Answer the query
    for (int i = 0; i < 3; i++) if (cnt[0][i] != cnt[1][i]) return -1;
    // Pair swaps
    int ans = 0;
    int canPair[3][2] = {{0, 1}, {1, 2}, {0, 2}};
    for (int i = 0; i < 3; i++) {
        int a = canPair[i][0], b = canPair[i][1];
        int toPair = min(swaps[getSwapID(a, b)], swaps[getSwapID(b, a)]);
        ans += toPair, swaps[getSwapID(a, b)] -= toPair, swaps[getSwapID(b, a)] -= toPair;
    }
    // Remaining swaps are cyclic
    int remaining = 2 * (swaps[getSwapID(0, 1)] + swaps[getSwapID(1, 0)]);
    assert(remaining == 2 * (swaps[getSwapID(1, 2)] + swaps[getSwapID(2, 1)]));
    ans += remaining;
    return ans;
}

// --- Begin judge code ---













/*
void sampleTest() {
    init("ATACAT", "ACTATA");
    assert(get_distance(1, 3) == 2);
    assert(get_distance(4, 5) == 1);
    assert(get_distance(3, 5) == -1);
    cout << "Sample test passed!" << endl;
}

int randint(int a, int b) {
    return random() % (b-a+1) + a;
}

int naive_get_distance(int a, int b) {
    vector<char> vectA(N), vectB(N);
    for (int i = 0; i < N; i++) vectA[i] = A[i], vectB[i] = B[i];
    // Swap only if needed
    int ans = 0;
    for (int i = a; i <= b; i++) {
        if (vectA[i] == vectB[i]) continue;
        // Swap with future position, preferring one that matches
        int status = -1, loc = -1;
        for (int j = i+1; j <= b; j++) {
            if (vectA[j] == vectB[j] || vectB[i] != vectA[j]) continue;
            if (vectB[j] == vectA[i]) {
                // Best possible swap
                status = 1;
                // cout << "swap " << i << " " << j << endl;
                swap(vectA[i], vectA[j]);
                break;
            } else {
                status = 0;
                loc = j;
            }
        }
        if (status == 0) {
            // cout << "swap " << i << " " << loc << endl;
            swap(vectA[i], vectA[loc]);
        }
        else if (status == -1) return -1;
        ans++;
    }
    return ans;
}

void stressTest(string name, int runs, int maxN, int maxQ, int maxC) {
    srand(793878234);
    for (int i = 0; i < runs; i++) {
        cout << "On test " << i+1 << "..." << endl;
        // Generate input values
        int N = randint(1, maxN);
        stringstream ssA, ssB;
        char dna[3] = {'A', 'T', 'C'};
        for (int j = 0; j < N; j++) {
            ssA << dna[randint(0, maxC-1)];
            ssB << dna[randint(0, maxC-1)];
        }
        string A = ssA.str(), B = ssB.str();
        init(A, B);

        // Generate queries
        int Q = randint(1, maxQ);
        for (int j = 0; j < Q; j++) {
            int a = randint(0, N-1), b = randint(0, N-1);
            if (a > b) swap(a, b);
            // Calculate the answer naively
            int ans = naive_get_distance(a, b);
            int result = get_distance(a, b);
            if (ans != result) {
                cout << "Query: " << a << " " << b << endl;
                cout << A << endl;
                cout << B << endl;
                cout << ans << " != " << result << endl;
                exit(-1);
            }
        }
        // cout << A << " " << B << endl;
    }
    cout << "Subtask " << name << " passed!" << endl;
}

int main() {
    sampleTest();
    stressTest("small and binary", 100, 100, 200, 2);
    stressTest("binary", 20, 5000, 5000, 2);
    stressTest("small", 100, 100, 200, 3);
    stressTest("full", 20, 5000, 5000, 3);
    return 0;
}
*/
