#include <iostream>
#include <string>

using namespace std;

const int N = 7;

string str;
int numPaths = 0, numMoves = -1;
bool used[N+2][N+2];

inline int numNeighbors(int i, int j) {
    int count = 0;
    if (!used[i-1][j]) count++;
    if (!used[i+1][j]) count++;
    if (!used[i][j-1]) count++;
    if (!used[i][j+1]) count++;
    return count;
}

void findPaths(int i, int j) {
    // cout << i << " " << j << endl;
    used[i][j] = true;
    numMoves++;

    if (i == N && j == 1) {
        // End reached
        if (numMoves == N*N-1) {
            numPaths++;
            // cout << numPaths << ' ';
        }
        used[i][j] = false;
        numMoves--;
        return;
    }

    // Heuristic (is there any direction it must go to?)
    bool mustGoUp = (!used[i-1][j] && numNeighbors(i-1, j) <= 1);
    bool mustGoDown = (!used[i+1][j] && (i != N-1 || j != 1) && numNeighbors(i+1, j) <= 1);
    bool mustGoLeft = (!used[i][j-1] && (i != N || j != 2) && numNeighbors(i, j-1) <= 1);
    bool mustGoRight = (!used[i][j+1] && numNeighbors(i, j+1) <= 1);
    // cout << mustGoUp << mustGoDown << mustGoLeft << mustGoRight << endl;

    // Satisfy heuristic
    if (mustGoUp) {
        if (str[numMoves] == '?' || str[numMoves] == 'U') {
            findPaths(i-1, j);
        }
        used[i][j] = false;
        numMoves--;
        return;
    }
    if (mustGoDown) {
        if (str[numMoves] == '?' || str[numMoves] == 'D') {
            findPaths(i+1, j);
        }
        used[i][j] = false;
        numMoves--;
        return;
    }
    if (mustGoLeft) {
        if (str[numMoves] == '?' || str[numMoves] == 'L') {
            findPaths(i, j-1);
        }
        used[i][j] = false;
        numMoves--;
        return;
    }
    if (mustGoRight) {
        if (str[numMoves] == '?' || str[numMoves] == 'R') {
            findPaths(i, j+1);
        }
        used[i][j] = false;
        numMoves--;
        return;
    }

    // Heuristic did not find anything; try going in each direction
    if ((str[numMoves] == '?' || str[numMoves] == 'U') && !used[i-1][j]) {
        findPaths(i-1, j);
    }
    if ((str[numMoves] == '?' || str[numMoves] == 'D') && !used[i+1][j]) {
        findPaths(i+1, j);
    }
    if ((str[numMoves] == '?' || str[numMoves] == 'L') && !used[i][j-1]) {
        findPaths(i, j-1);
    }
    if ((str[numMoves] == '?' || str[numMoves] == 'R') && !used[i][j+1]) {
        findPaths(i, j+1);
    }

    used[i][j] = false;
    numMoves--;
}

int main() {
    cin >> str;
    for (int i = 0; i <= N + 1; i++) {
        used[i][0] = true;
        used[0][i] = true;
        used[i][N+1] = true;
        used[N+1][i] = true;
    }
    findPaths(1, 1);
    cout << numPaths << endl;
}