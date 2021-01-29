#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 25;

int N;
ll K;
bool marked[MAXN][MAXN];

void search(int i, int j) {
    cout << i+1 << ' ' << j+1 << '\n';
    if (i == N-1 && j == N-1) return;
    else if (i == N-1) search(i, j+1);
    else if (j == N-1) search(i+1, j);
    else {
        int nextDiag = i+j+1;
        bool currMarked = ((K & (1LL << nextDiag)) != 0);
        if (currMarked) {
            if (marked[i+1][j]) search(i+1, j);
            else search(i, j+1);
        } else {
            if (!marked[i+1][j]) search(i+1, j);
            else search(i, j+1);
        }
    }
}

void solve() {
    cin >> K;
    search(0, 0);
    cout.flush();
}

int main() {
    ios::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j != 0) cout << ' ';
            int currDiag = i+j;
            if (i % 2 == 0 && (i != 0 || j != 0)) {
                marked[i][j] = true;
                cout << (1LL << currDiag);
            } else {
                marked[i][j] = false;
                cout << 0;
            }
        }
        cout << '\n';
    }
    cout.flush();
    int Q;
    cin >> Q;
    for (int i = 1; i <= Q; i++) solve();
    return 0;
}