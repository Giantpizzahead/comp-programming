#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXK = 800005;
const ll MOD = 1e9+7;

int K;
ll ans;
// The first 'O' or 'X' character ('F' if neither), and its location
char firstChar;
int firstLoc;
// The last 'O' or 'X' character in the block ('F' if neither), and its location
char endingChar[MAXK];
int endingLoc[MAXK];
// Sum of swap counts, fixing left endpoint at 1 and varying right endpoint from 1 to |S|
ll totalLeftSwaps[MAXK];
// Sum of swap counts, varying left endpoint from 1 to |S| and fixing right endpoint at |S|
ll totalRightSwaps[MAXK];
// Sum of swap counts, varying both endpoints
ll totalSwaps[MAXK];
// Swap count from 1 to |S|
ll lastSwaps[MAXK];
// |S|
ll strLength[MAXK];

void solve() {
    string S;
    cin >> K >> S;
    S = " " + S;
    // Precompute string lengths
    strLength[0] = 0;
    rep(i, 1, K+1) {
        if (S[i] == '.') strLength[i] = (strLength[i-1] * 2) % MOD;
        else strLength[i] = (strLength[i-1] + 1) % MOD;
    }
    // Calculate the answer
    firstChar = 'F';
    firstLoc = -1;
    endingChar[0] = 'F';
    endingLoc[0] = -1;
    totalLeftSwaps[0] = 0;
    totalRightSwaps[0] = 0;
    totalSwaps[0] = 0;
    lastSwaps[0] = 0;
    rep(i, 1, K+1) {
        if (S[i] == 'F' || (S[i] == '.' && firstChar == 'F')) {
            // Nothing to do
            endingChar[i] = endingChar[i-1];
            endingLoc[i] = endingLoc[i-1];
            lastSwaps[i] = lastSwaps[i-1];
            totalLeftSwaps[i] = (totalLeftSwaps[i-1] + lastSwaps[i]) % MOD;
            totalRightSwaps[i] = totalRightSwaps[i-1];
            totalSwaps[i] = (totalSwaps[i-1] + totalRightSwaps[i]) % MOD;
        } else if (S[i] == 'O' || S[i] == 'X') {
            // Add swaps
            if (firstChar == 'F') {
                firstChar = S[i];
                firstLoc = strLength[i-1];
            }
            endingChar[i] = S[i];
            endingLoc[i] = strLength[i-1];
            lastSwaps[i] = lastSwaps[i-1];
            totalRightSwaps[i] = totalRightSwaps[i-1];
            if (endingChar[i-1] != 'F' && endingChar[i-1] != S[i]) {
                // This does cause a swap
                lastSwaps[i] = (lastSwaps[i] + 1) % MOD;
                totalRightSwaps[i] = (totalRightSwaps[i] + endingLoc[i-1]+1) % MOD;
            }
            totalLeftSwaps[i] = (totalLeftSwaps[i-1] + lastSwaps[i]) % MOD;
            totalSwaps[i] = (totalSwaps[i-1] + totalRightSwaps[i]) % MOD;
        } else {
            // Duplicate current block
            endingChar[i] = endingChar[i-1];
            endingLoc[i] = (strLength[i-1] + endingLoc[i-1]) % MOD;
            
            // Starting index on left, ending index on right
            // newWays += strLength[i-1] * (strLength[K]-strLength[i]) % MOD;
            // Starting index inside, ending index on right
            // newWays += totalRightSwaps[i-1] * (strLength[K]-strLength[i]) % MOD;

            // Update values
            
            // Combine last swap count
            lastSwaps[i] = (lastSwaps[i-1] * 2) % MOD;
            if (endingChar[i-1] != firstChar) {
                lastSwaps[i] = (lastSwaps[i] + 1) % MOD;
            }

            /*
            Extend all right-ending points to the right
            ---      ---OOO
             --  TO   --OOO (plus the old one for the bottom half of triangle)
              -        -OOO
            */
            totalRightSwaps[i] = (totalRightSwaps[i-1] * 2 + lastSwaps[i-1] * strLength[i-1]) % MOD;
            if (endingChar[i-1] != firstChar) {
                totalRightSwaps[i] = (totalRightSwaps[i] + endingLoc[i-1]+1) % MOD;
            }

            /*
            Extend all left-ending points to the left
            ---      OOO---
            --   TO  OOO--  (plus the old one for the bottom half of triangle)
            -        OOO-
            */
            totalLeftSwaps[i] = (totalLeftSwaps[i-1] * 2 + lastSwaps[i-1] * strLength[i-1]) % MOD;
            if (endingChar[i-1] != firstChar) {
                totalLeftSwaps[i] = (totalLeftSwaps[i] + (strLength[i-1]-firstLoc)) % MOD;
                if (totalLeftSwaps[i] < 0) totalLeftSwaps[i] += MOD;
            }

            // Update totalSwaps
            ll newWays = 0;
            // Starting index inside, ending index inside
            newWays += totalSwaps[i-1];
            // Starting index on left, ending index inside
            newWays += strLength[i-1] * totalLeftSwaps[i-1] % MOD;
            newWays += strLength[i-1] * totalRightSwaps[i-1] % MOD;
            // Combine the two
            if (endingChar[i-1] != firstChar) {
                newWays += (endingLoc[i-1]+1) * (strLength[i-1]-firstLoc) % MOD;
            }
            newWays %= MOD;
            if (newWays < 0) newWays += MOD;
            totalSwaps[i] = (totalSwaps[i-1] + newWays) % MOD;
        }

        int x;
        x = firstLoc;
        assert(x >= -1 && x < MOD);
        x = endingLoc[i];
        assert(x >= -1 && x < MOD);
        x = totalLeftSwaps[i];
        assert(x >= 0 && x < MOD);
        x = totalRightSwaps[i];
        assert(x >= 0 && x < MOD);
        x = totalSwaps[i];
        assert(x >= 0 && x < MOD);
        x = lastSwaps[i];
        assert(x >= 0 && x < MOD);
        x = strLength[i];
        assert(x >= 0 && x < MOD);
    }
    
    /*
    cerr << "first: " << firstChar << " " << firstLoc << "\n";
    cerr << "endingChar:\n";
    rep(i, 0, K+1) cerr << endingChar[i] << "\t\n"[i==K];
    cerr << "endingLoc:\n";
    rep(i, 0, K+1) cerr << endingLoc[i] << "\t\n"[i==K];
    cerr << "totalLeftSwaps:\n";
    rep(i, 0, K+1) cerr << totalLeftSwaps[i] << "\t\n"[i==K];
    cerr << "totalRightSwaps:\n";
    rep(i, 0, K+1) cerr << totalRightSwaps[i] << "\t\n"[i==K];
    cerr << "totalSwaps:\n";
    rep(i, 0, K+1) cerr << totalSwaps[i] << "\t\n"[i==K];
    cerr << "lastSwaps:\n";
    rep(i, 0, K+1) cerr << lastSwaps[i] << "\t\n"[i==K];
    cerr << "strLength:\n";
    rep(i, 0, K+1) cerr << strLength[i] << "\t\n"[i==K];
    */

    cout << totalSwaps[K] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}