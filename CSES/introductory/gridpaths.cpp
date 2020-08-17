#include <iostream>
#include <unordered_map>

using namespace std;
using ll = long long;

const int N = 6;
string str = "???????????????????????????????????";
unordered_map<long, int> dp;

inline ll hashState(int i, int j, ll state) {
    ll loc = i * N + j;
    return state + (loc << (N * N));
}

inline int saveState(int i, int j, ll state, int v) {
    dp[hashState(i, j, state)] = v;
    return v;
}

inline bool stateUsed(int i, int j, ll state) {
    return (state & (1L << (i * N + j))) != 0;
}

inline ll markUsed(int i, int j) {
    return 1L << (i * N + j);
}

int genPaths(int i, int j, int c, ll state) {
    // cout << i << " " << j << " " << c << endl;
    // Check if already evaluated
    auto ptr = dp.find(hashState(i, j, state));
    if (ptr != dp.end()) {
        // Already evaluated
        return ptr->second;
    }
    if (i == N-1 && j == 0) {
        // At end; did the path go through all N^2 squares?
        // cout << c << endl;
        if (c == N * N) return saveState(i, j, state, 1);
        else return saveState(i, j, state, 0);
    }

    int numPaths = 0;
    if ((str[c-1] == '?' || str[c-1] == 'U') && i != 0 && !stateUsed(i-1, j, state)) {
        numPaths += genPaths(i-1, j, c+1, state + markUsed(i-1, j));
    }
    if ((str[c-1] == '?' || str[c-1] == 'D') && i != N-1 && !stateUsed(i+1, j, state)) {
        numPaths += genPaths(i+1, j, c+1, state + markUsed(i+1, j));
    }
    if ((str[c-1] == '?' || str[c-1] == 'L') && j != 0 && !stateUsed(i, j-1, state)) {
        numPaths += genPaths(i, j-1, c+1, state + markUsed(i, j-1));
    }
    if ((str[c-1] == '?' || str[c-1] == 'R') && j != N-1 && !stateUsed(i, j+1, state)) {
        numPaths += genPaths(i, j+1, c+1, state + markUsed(i, j+1));
    }
    return saveState(i, j, state, numPaths);
}

int main() {
    cout << genPaths(0, 0, 1, 1) << endl;
}