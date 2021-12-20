/*
Test cases: 2, 8, 12, 14, 26, 33, 44, 50, 75, 97, 112, 140, 173, 200, 240, 255

Must have a 0 register that is never changed, and a register with N at the beginning
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int INF = 987654321;

vector<string> toPrint;
int K, N, currV, numS, maxS;
int R[9];

void printInitial() {
    string str = "";
    rep(i, 0, 9) {
        str += to_string(R[i]);
        if (i != 8) str += " ";
    }
    toPrint.push_back(str);
}

void printRegister(int x) {
    string str = "P " + to_string(x+1);
    toPrint.push_back(str);
    assert(R[x] == currV);
    currV--, numS = 0;
}

void storePlus1(int a, int b) {
    string str = "S " + to_string(a+1) + " " + to_string(b+1);
    toPrint.push_back(str);
    maxS = max(++numS, maxS);

    R[b] = R[a] + 1;
}

void resetData() {
    currV = N, numS = 0, maxS = 0;
    toPrint.clear();
}

/*
===RECURSIVE METHOD===

Similar to the smarter method, but go recursively.

First number is hardcoded (no S operations). The algorithm starts
from N-1. Note that a larger first number always means more or the same
number of S operations, so it's ok to make it a little different.

Ex (S = 8):
Level 1 = [255] 254 253 ... 2 1 0
Level 2 = [255] 246 237 ... 12 3 0
Level 3 = [255] 246 201 ... 66 21 0
Level 4 = [255] 246 156 66 0 (small enough to fit)
*/

// vector<vector<vector<vector<int>>>> memo;
// vector<vector<vector<vector<vector<int>>>>> from;

unordered_map<int, unordered_map<int, unordered_map<int, unordered_map<int, int>>>> memo;
unordered_map<int, unordered_map<int, unordered_map<int, unordered_map<int, vector<int>>>>> from;

/*
S[i] represents number of operations allowed before V[i] must be
outputted.
*/
int solveRec(int depth, int firstV, int step, int numS) {
    assert(depth < 9 && firstV >= 0 && step >= 0 && numS >= 0 && numS <= firstV);

    // Return saved result if available
    int savedCount = memo[depth][firstV][step][numS];
    if (savedCount != 0) return savedCount;

    // First value can be hardcoded
    R[depth] = firstV;
    firstV -= step;

    // Base cases
    // No more numbers
    if (firstV < 0) return 1;
    // Only one more number
    else if (firstV - step < 0) return 2;
    // Can all be satisfied with a 0 register
    else if (firstV <= numS) return 2;
    // Too many registers
    else if (depth == 8) return INF;

    // Try all ways to generate the remaining values
    int bestFirstV = -1, bestStep = -1, bestNumS = -1, bestCount = INF;
    for (int newStep = step; newStep <= numS + 1; newStep += step) { //newStep++) {
        // newStep must be a multiple of step... for now
        for (int newFirstV = firstV - numS; newFirstV <= firstV; newFirstV++) {
            // Calculate newNumS
            int newNumS = 0;
            for (int j = 0; j < newStep / step; j++) newNumS += (numS - j * step);
            // If newNumS is greater than newFirstV, the extra operations won't be useful
            newNumS = min(newFirstV, newNumS);
            // cerr << "gen " << newStep << " " << newFirstV << " = " << newNumS << "\n";

            // Get number of hardcoded registers needed
            int numRegs = solveRec(depth+1, newFirstV, newStep, newNumS) + 1;
            if (numRegs < bestCount) {
                bestStep = newStep;
                bestFirstV = newFirstV;
                bestNumS = newNumS;
                bestCount = numRegs;
            }
        }
    }
    // cerr << "best: " << " " << bestStep << " " << bestFirstV << " " << bestNumS << " = " << bestCount << "\n";

    memo[depth][firstV+step][step][numS] = bestCount;
    // Record best transition
    if (bestCount != INF) {
        from[depth][firstV+step][step][numS].push_back(depth+1);
        from[depth][firstV+step][step][numS].push_back(bestFirstV);
        from[depth][firstV+step][step][numS].push_back(bestStep);
        from[depth][firstV+step][step][numS].push_back(bestNumS);
    }
    /*
    cerr << "solveRec(" << depth << ", " << firstV+step << ", " << step << ", " << numS << ") = " << bestCount << " from";
    for (int x : from[depth][firstV+step][step][numS]) cerr << " " << x;
    cerr << "\n";
    */
    return bestCount;
}

void setupRec() {
    // memo.resize(9);
    // from.resize(9);
    // rep(i, 0, 9) {
    //     memo[i].resize(N+1);
    //     from[i].resize(N+1);
    //     rep(j, 0, N+1) {
    //         memo[i][j].resize(N+1);
    //         from[i][j].resize(N+1);
    //         rep(k, 0, N+1) {
    //             memo[i][j][k].resize(j+1);
    //             from[i][j][k].resize(j+1);
    //             fill(all(memo[i][j][k]), 0);
    //         }
    //     }
    // }
}


/*
===SMARTER METHOD (71)===

Since the score is based on the maximum # of *consecutive* S
operations, you should take advantage of unused S operations.
The program does this by using extra S operations to "prepare"
new values that can then be used to continue the descending
sequence.
*/

/*
Forms a number at the specified register using the minimum # of
S operations. If the number already exists at another register,
does nothing and returns that index. Otherwise, returns -1 while
the number is being formed, and r once the number is there.
*/
int formNumber(int r, int x) {
    // Find the best place to make the number from
    int from = -1, minMoves = INF;
    for (int i = 0; i < 9; i++) {
        if (R[i] > x) continue;
        else if (R[i] == x) return i;
        else {
            int moves = x - R[i];
            if (moves < minMoves) {
                minMoves = moves;
                from = i;
            }
        }
    }
    assert(from != -1);

    // Make the number
    storePlus1(from, r);
    if (R[r] != x) return -1;
    else return r;
}

void simulateSmart(int S) {
    // 0 will always be for the next sequence number
    // 1 and 2 will be the alternating sources
    printInitial();
    printRegister(1);
    printRegister(0);

    // Main loop
    int currSource = 2, currTarget = max(N-2-S, 0);
    int nextSource = 1, nextTarget = max(currTarget-S-1, 0);
    for (int x = N-2; x >= 0; x--) {
        for (int i = 0; i < S; i++) {
            bool found = false;
            for (int j = 0; j < 9; j++) if (R[j] == x) found = true;
            if (found) {
                // Number has been created; use remaining actions on next number
                formNumber(nextSource, nextTarget);
            } else {
                // Create the sequence number
                formNumber(0, x);
            }
            // for (int j = 0; j < 9; j++) cerr << R[j] << " \n"[j==8];
        }

        // Print the number
        int r = formNumber(0, x);
        printRegister(r);

        // Switch source if needed
        if (x == currTarget) {
            swap(currSource, nextSource);
            currTarget = nextTarget;
            nextTarget = max(currTarget-S-1, 0);
        }
    }
}

bool smartAlgorithm(int S) {
    int extra = 0;
    vector<int> savedVals;
    // First two values can be hardcoded in
    currV = N-2;
    while (currV != -1) {
        int target = max(currV - S, 0);
        // See if saved values can be used to form the target
        bool useSaved = false;
        for (int x : savedVals) {
            if (x <= target && x + extra >= target) {
                // Yes!
                extra -= (target - x);
                useSaved = true;
                break;
            }
        }
        if (!useSaved) {
            // Must add new saved value
            int needed = target;
            while (extra > 0 && needed > 0) {
                needed--;
                extra--;
            }
            savedVals.push_back(needed);
        }
        extra = 0;
        
        // Special case for first iteration
        // if (currV == N) extra = S;
        
        // Create descending values
        while (currV >= target) {
            extra += S - (currV - target);
            currV--;
        }
        // cerr << target << " " << useSaved << " " << extra << endl;
    }

    // Will this work?
    if (sz(savedVals) > 7) return false;

    // This works; do it!
    for (int i = 0; i < sz(savedVals); i++) R[i+2] = savedVals[i];
    R[0] = N-1, R[1] = N;
    resetData();
    simulateSmart(S);

    cerr << "S = " << S << endl;
    cerr << "savedVals = ";
    for (int x : savedVals) cerr << x << " ";
    cerr << endl;
    return true;
}

/*
===BASIC METHOD (45)===

8 registers evenly spaced. Use the last register for all calculations / add ones.
*/

void basicAlgorithm() {
    rep(i, 0, 8) R[i] = N * i / 7;
    R[8] = 0;
    printInitial();

    for (int x = N; x >= 0; x--) {
        // Start with the closest register
        for (int i = 7; i >= 0; i--) {
            if (R[i] == x) {
                printRegister(i);
                break;
            } else if (R[i] < x) {
                // Use this register
                storePlus1(i, 8);
                while (R[8] != x) storePlus1(8, 8);
                printRegister(8);
                break;
            }
        }
    }
}

void solve() {
    cin >> K >> N;

    cout << "FILE reverse " << K << "\n";
    if (N <= 8) {
        // Special case
        resetData();
        for (int i = 0; i <= N; i++) R[i] = i;
        printInitial();
        for (int i = N; i >= 0; i--) printRegister(i);
    } else if (true) {
        setupRec();
        for (int S = 0; S <= N; S++) {
            resetData();
            int numRegs = solveRec(0, N, 1, S);
            cerr << "S = " << S << ": " << numRegs << "\n";
            // Follow transition path
            int depth = 0, firstV = N, step = 1, numS = S;
            while (true) {
                vector<int>& f = from[depth][firstV][step][numS];
                cerr << "solveRec(" << depth << ", " << firstV << ", " << step << ", " << numS << ")\n";
                if (f.empty()) break;
                depth = f[0], firstV = f[1], step = f[2], numS = f[3];
            }
            cerr << "\n";
            if (numRegs <= 8) break;
        }
    }

    // Baseline
    for (int S = 0; S <= N; S++) {
        resetData();
        if (smartAlgorithm(S)) break;
    }

    // assert(currV == -1);
    // for (string& str : toPrint) cout << str << "\n";
    cerr << "Max consecutive S operations: " << maxS << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}