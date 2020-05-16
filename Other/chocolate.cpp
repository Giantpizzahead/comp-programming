#include <iostream>
#include <stack>
#include <algorithm>

#define BOARD_SIDE 5
#define BOARD_SQUARES 25
#define MAX_MASK 33554432
#define INF 987654321

using namespace std;

int T;
char currMark = 0;
int arr[BOARD_SIDE][BOARD_SIDE];
char mark[MAX_MASK + 1];
int dp[MAX_MASK + 1], pow2[30];

inline int hashInfo(int i, int j, int bools) {
    return (i << 8) + (j << 5) + bools;
}

inline int getI(int h) {
    return h >> 8;
}

inline int getJ(int h) {
    return (h >> 5) % 8;
}

inline int getBools(int h) {
    return h % 32;
}

short dpInfoLength[MAX_MASK + 1];
int dpInfoStart[MAX_MASK + 1];
// Found after some experimentation
short dpInfoHashes[116000000];
int currHashLoc = 0;

int numOn, currSum;
bool on[BOARD_SIDE][BOARD_SIDE];
bool open[BOARD_SIDE][BOARD_SIDE];

void print2DArr(bool a[BOARD_SIDE][BOARD_SIDE]) {
    for (int i = 0; i < BOARD_SIDE; i++) {
        for (int j = 0; j < BOARD_SIDE; j++) cout << (a[i][j] ? 1 : 0);
        cout << endl;
    }
}

int numStates = 0;

int rec(int mask) {
    // Memoization
    if (mark[mask] == currMark) return dp[mask];

    // Heuristic that may not be entirely accurate
    int bad = currSum / 8 / numOn;

    int i, j, bools;
    int isGreedy, updateU, updateD, updateL, updateR;
    if (mark[mask] == 0) {
        // numStates++;
        // Never been visited before; try each cell
        dpInfoStart[mask] = currHashLoc;
        for (i = 0; i < BOARD_SIDE; i++) {
            for (j = 0; j < BOARD_SIDE; j++) {
                if (open[i][j]) {
                    // This cell can be used
                    // Figure out which sides need to be updated
                    updateU = (i != 0 && on[i-1][j] && !open[i-1][j]);
                    updateD = (i != BOARD_SIDE - 1 && on[i+1][j] && !open[i+1][j]);
                    updateL = (j != 0 && on[i][j-1] && !open[i][j-1]);
                    updateR = (j != BOARD_SIDE - 1 && on[i][j+1] && !open[i][j+1]);
                    isGreedy = !(updateU || updateD || updateL || updateR);
                    dpInfoHashes[currHashLoc++] = hashInfo(i, j, (isGreedy << 4) + (updateU << 3) + (updateD << 2) + (updateL << 1) + updateR);
                }
            }
        }
        dpInfoLength[mask] = currHashLoc - dpInfoStart[mask];
    }

    bool turn = (numOn % 2 == 1);
    int answer = turn ? -INF : INF, greedyI = -1, greedyJ = -1;

    // Use existing info to handle state
    for (int k = 0; k < dpInfoLength[mask]; k++) {
        int infoHash = dpInfoHashes[dpInfoStart[mask] + k];
        i = getI(infoHash);
        j = getJ(infoHash);
        bools = getBools(infoHash);
        if (bools & 16) {
            // This cell won't affect anything; it should be greedied
            if (greedyI == -1 || arr[i][j] > arr[greedyI][greedyJ]) {
                // This cell is the new best greedy choice
                greedyI = i;
                greedyJ = j;
            }
        } else {
            if (arr[i][j] < bad) continue;  // Heuristic (too low of a value to help)
            // Try picking this cell
            on[i][j] = false;
            open[i][j] = false;
            numOn--;
            currSum -= arr[i][j];
            if (bools & 8) open[i-1][j] = true;
            if (bools & 4) open[i+1][j] = true;
            if (bools & 2) open[i][j-1] = true;
            if (bools & 1) open[i][j+1] = true;
            if (turn) answer = max(rec(mask ^ pow2[i * BOARD_SIDE + j]) + arr[i][j], answer);
            else answer = min(rec(mask ^ pow2[i * BOARD_SIDE + j]), answer);
            on[i][j] = true;
            open[i][j] = true;
            numOn++;
            currSum += arr[i][j];
            if (bools & 8) open[i-1][j] = false;
            if (bools & 4) open[i+1][j] = false;
            if (bools & 2) open[i][j-1] = false;
            if (bools & 1) open[i][j+1] = false;
        }
    }

    // Try greedy cell
    if (greedyI != -1) {
        on[greedyI][greedyJ] = false;
        open[greedyI][greedyJ] = false;
        numOn--;
        currSum -= arr[i][j];
        if (turn) answer = max(rec(mask ^ (1 << (greedyI * BOARD_SIDE + greedyJ))) + arr[greedyI][greedyJ], answer);
        else answer = min(rec(mask ^ (1 << (greedyI * BOARD_SIDE + greedyJ))), answer);
        on[greedyI][greedyJ] = true;
        open[greedyI][greedyJ] = true;
        numOn++;
        currSum += arr[i][j];
    }

    mark[mask] = currMark;
    dp[mask] = answer;
    return answer;
}

int main() {
    for (int i = 0; i < MAX_MASK + 1; i++) mark[i] = 0;
    dp[0] = 0;
    for (int i = 0; i < 30; i++) pow2[i] = 1 << i;
    // cout << "ready" << endl;
    cin >> T;
    for (int t = 0; t < T; t++) {
        currMark++;
        currSum = 0;
        for (int i = 0; i < BOARD_SIDE; i++) {
            for (int j = 0; j < BOARD_SIDE; j++) {
                cin >> arr[i][j];
                currSum += arr[i][j];
                on[i][j] = true;
                if (i == 0 || j == 0 || i == BOARD_SIDE - 1 || j == BOARD_SIDE - 1) open[i][j] = true;
                else open[i][j] = false;
            }
        }

        numOn = BOARD_SQUARES;
        mark[0] = currMark;
        cout << rec(0b1111111111111111111111111) << endl;
        // cout << "States: " << numStates << " out of " << MAX_MASK << endl;
        // cout << "Hashes: " << currHashLoc << endl;
    }

    return 0;
}
