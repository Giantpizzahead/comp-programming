#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

int N, M;
string S, T;
int pre[MAXN], post[MAXN];
vector<int> sLocs[256];

int main() {
    ios::sync_with_stdio(false);
    cin >> S >> T;
    N = S.size();
    M = T.size();

    int currLoc = -1;
    for (int i = 0; i < N; i++) {
        if (currLoc != M-1 && S[i] == T[currLoc+1]) {
            currLoc++;
        }
        pre[i] = currLoc;
    }
    currLoc = M;
    for (int i = N-1; i >= 0; i--) {
        if (currLoc != 0 && S[i] == T[currLoc-1]) {
            currLoc--;
        }
        post[i] = currLoc;
    }

    for (int i = 0; i < M; i++) {
        sLocs[T[i]].push_back(i);
    }

    bool possible = true;
    for (int i = 0; i < N; i++) {
        // Find longest prefix that could include this letter
        if (sLocs[S[i]].empty()) {
            possible = false;
            break;
        }
        auto x = upper_bound(sLocs[S[i]].begin(), sLocs[S[i]].end(), pre[i]);
        if (x == sLocs[S[i]].begin()) {
            // No characters appear before this; cannot be part of subsequence
            possible = false;
            break;
        }
        x--;

        int startLoc = *x;
        if (post[i] > startLoc) {
            // Suffix cannot finish the subsequence
            possible = false;
            break;
        }
    }

    cout << (possible ? "Yes" : "No") << endl;

    /*    
    for (int i = 'a'; i <= 'z'; i++) {
        for (int x : sLocs[i]) cout << x << ' ';
        cout << endl;
    }
    for (int i = 0; i < N; i++) {
        cout << pre[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << post[i] << ' ';
    }
    cout << endl;
    */
}