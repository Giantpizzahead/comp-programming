#include <iostream>
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
int dp[MAX_MASK + 1];

int numOn;
bool on[BOARD_SIDE][BOARD_SIDE];
bool open[BOARD_SIDE][BOARD_SIDE];

inline bool isOpen(int i, int j) {
    return i == 0 || i == BOARD_SIDE - 1 || j == 0 || j == BOARD_SIDE - 1 || !on[i-1][j] || !on[i+1][j] || !on[i][j-1] || !on[i][j+1];
}

void print2DArr(bool a[BOARD_SIDE][BOARD_SIDE]) {
    for (int i = 0; i < BOARD_SIDE; i++) {
        for (int j = 0; j < BOARD_SIDE; j++) cout << (a[i][j] ? 1 : 0);
        cout << endl;
    }
}

int numStates = 0;

int rec(int mask) {
    // print2DArr(open);
    // Memoization
    if (mark[mask] == currMark) return dp[mask];

    bool turn = (numOn % 2 == 1), updateU, updateD, updateL, updateR;
    int answer = turn ? -INF : INF, greedyI = -1, greedyJ = -1, newMask, result;

    // Try each cell
    for (int i = 0; i < BOARD_SIDE; i++) {
        for (int j = 0; j < BOARD_SIDE; j++) {
            if (open[i][j]) {
                // This cell can be used
                // Figure out which sides need to be updated
                updateU = (i != 0 && on[i-1][j] && !open[i-1][j]);
                updateD = (i != BOARD_SIDE - 1 && on[i+1][j] && !open[i+1][j]);
                updateL = (j != 0 && on[i][j-1] && !open[i][j-1]);
                updateR = (j != BOARD_SIDE - 1 && on[i][j+1] && !open[i][j+1]);
                if (!(updateU || updateD || updateL || updateR)) {
                    // This cell won't affect anything; it should be greedied
                    if (greedyI == -1 || arr[i][j] > arr[greedyI][greedyJ]) {
                        // This cell is the new best greedy choice
                        greedyI = i;
                        greedyJ = j;
                    }
                } else {
                    // Try picking this cell
                    on[i][j] = false;
                    open[i][j] = false;
                    numOn--;
                    if (updateU) open[i-1][j] = true;
                    if (updateD) open[i+1][j] = true;
                    if (updateL) open[i][j-1] = true;
                    if (updateR) open[i][j+1] = true;
                    newMask = mask ^ (1 << (i * BOARD_SIDE + j));
                    result = (mark[newMask] == currMark) ? dp[newMask] : rec(newMask);
                    if (turn) answer = max(result + arr[i][j], answer);
                    else answer = min(result, answer);
                    on[i][j] = true;
                    open[i][j] = true;
                    numOn++;
                    if (updateU) open[i-1][j] = false;
                    if (updateD) open[i+1][j] = false;
                    if (updateL) open[i][j-1] = false;
                    if (updateR) open[i][j+1] = false;
                }
            }
        }
    }

    // Try greedy cell
    if (greedyI != -1) {
        on[greedyI][greedyJ] = false;
        open[greedyI][greedyJ] = false;
        numOn--;
        if (turn) answer = max(rec(mask ^ (1 << (greedyI * BOARD_SIDE + greedyJ))) + arr[greedyI][greedyJ], answer);
        else answer = min(rec(mask ^ (1 << (greedyI * BOARD_SIDE + greedyJ))), answer);
        on[greedyI][greedyJ] = true;
        open[greedyI][greedyJ] = true;
        numOn++;
    }

    numStates++;
    mark[mask] = currMark;
    dp[mask] = answer;
    return answer;
}

int main() {
    for (int i = 0; i < MAX_MASK + 1; i++) mark[i] = 0;
    dp[0] = 0;
    cin >> T;
    for (int t = 0; t < T; t++) {
        currMark++;
        for (int i = 0; i < BOARD_SIDE; i++) {
            for (int j = 0; j < BOARD_SIDE; j++) {
                cin >> arr[i][j];
                on[i][j] = true;
                if (i == 0 || j == 0 || i == BOARD_SIDE - 1 || j == BOARD_SIDE - 1) open[i][j] = true;
                else open[i][j] = false;
            }
        }

        numOn = BOARD_SQUARES;
        mark[0] = currMark;
        cout << rec(0b1111111111111111111111111) << endl;
        // cout << "States: " << numStates << " out of " << MAX_MASK << endl;
    }
    return 0;
}
