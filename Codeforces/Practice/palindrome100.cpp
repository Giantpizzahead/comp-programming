#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 50005;
const int MAXK = 51;

// dp[i][j] = Furthest right character in subsequence with length j*2, using character i
int dp[MAXN][MAXK], origI[MAXN][MAXK], from[MAXN][MAXK];
int N, K;
set<int> charLocs[256];
vector<char> usedChars;
string str;

int main() {
    ios::sync_with_stdio(false);
    cin >> str;
    N = str.size();
    K = min(N / 2 + 1, MAXK);
    for (int i = 0; i < N; i++) {
        charLocs[str[i]].insert(i);
        for (int j = 0; j < K; j++) {
            dp[i][j] = -1;
            origI[i][j] = -1;
            from[i][j] = -1;
        }
    }

    dp[0][0] = N;
    origI[0][0] = 0;
    if (charLocs[str[0]].size() != 1) {
        dp[0][1] = *charLocs[str[0]].rbegin();
        origI[0][1] = 0;
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < K; j++) {
            // Transfer previous one
            if (dp[i-1][j] > i) {
                dp[i][j] = dp[i-1][j];
                origI[i][j] = origI[i-1][j];
                from[i][j] = from[i-1][j];
            }
            // Use this character
            if (j != 0 && dp[i-1][j-1] != -1) {
                auto ptr = charLocs[str[i]].lower_bound(dp[i-1][j-1]);
                if (ptr == charLocs[str[i]].begin()) continue;
                ptr--;

                int loc = *ptr;
                if (loc <= i) continue;
                // On the right; this works
                if (dp[i][j] < loc) {
                    // New way is better!
                    dp[i][j] = loc;
                    origI[i][j] = i;
                    from[i][j] = origI[i-1][j-1];
                }
            }
        }
    }

    int currMaxLen = 0, maxI, maxJ;
    for (int j = K-1; j >= 0; j--) {
        for (int i = 0; i < N; i++) {
            if (dp[i][j] != -1) {
                bool hasCenter = (dp[i][j] > i+1);
                int currLen = j * 2 + (hasCenter ? 1 : 0);
                if (currLen > currMaxLen) {
                    currMaxLen = currLen;
                    maxI = i;
                    maxJ = j;
                }
            }
        }
    }

    if (currMaxLen <= 1) {
        // Special case
        cout << str[0] << endl;
        return 0;
    } else if (currMaxLen == 101) currMaxLen--;
    
    char centerChar;
    if (currMaxLen % 2 == 1) {
        centerChar = str[maxI+1];
    }
    while (maxJ > 0) {
        usedChars.push_back(str[dp[maxI][maxJ]]);
        maxI = from[maxI][maxJ];
        maxJ--;
    }
    for (auto x = usedChars.rbegin(); x != usedChars.rend(); x++) {
        cout << *x;
    }
    if (currMaxLen % 2 == 1) cout << centerChar;
    for (auto x = usedChars.begin(); x != usedChars.end(); x++) {
        cout << *x;
    }
    cout << endl;

    /*
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            cout << dp[i][j] << '\t';
        }
        cout << '\n';
    }
    cout << endl;
    */
    return 0;
}