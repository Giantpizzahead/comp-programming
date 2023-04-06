/*
(bcabd)
Remove a: (bc, bd)
To find out if bcabd wins, need to check all options for removal, and see if any of them win

Instead of winning/losing, think of each state as two things: forceEven, forceOdd
forceEven means the current player can force the game to end in an even # of moves (ex: "", "ab", "aaba")
forceOdd means the current player can force the game to end in an odd # of moves (ex: "a", "aaba")
The above assumes both players always play optimally

Does one of these two always need to be true? We saw that they could both be true... what about neither?
If neither, that means no matter what move is done, the next state is also... actually, no

How about this: canEven, canOdd
canEven means there is a config in which the game *could* end in an even # of moves (ex: "", "ab", "aaba")
canOdd means there is a config in which the game *could* end in an odd # of moves (ex: "", "ab", "aaba") 
Ok, but this ends up being true for basically everything...

First player can force the outcome, no matter what the second player does:
firstEven - "" (0 moves no matter what), "aaba" (can be forced into 2 moves)
firstOdd - "a" (1 move no matter what), "aaba" (can be forced into 3 moves)
Second player can force the outcome, no matter what the first player does:
secondEven - "ab" (2 moves no matter what), "abacdc" (can be forced into 4 or 6 moves)
secondOdd - "bbb" (1 move no matter what), "abaca" (can be forced into 3 or 5 moves)

Assume the above are defined for each substring
For each string, iterate through each possible move choice, and check the resulting substrings S_i:
For the first player forcing the outcome, at least one move choice has to exist that satisfies the condition.
For the second player forcing the outcome, all move choices must satisfy the condition.

Instead of trying to literally split the substring, we could just change the characters in each individual substring.
Effectively, this would create the same thing, just that it would still be one big string.
Once we get to a base case (after removing all adjacent same chars, all chars are unique) then the answer is predetermined.
Now, we can backtrack for a given string S:
firstEven - If any move on S leads to a state that is secondOdd
firstOdd - If any move on S leads to a state that is secondEven
secondEven - If all moves on S lead to a state that is firstOdd
secondOdd - If all moves on S lead to a state that is firstEven

All base states are either firstOdd/secondEven or firstEven/secondOdd. So:
Actually there are no guarantees. But at least with this model, we can always determine the answer...?
Let's try it. It's proven to be correct so idk.

Based on heuristics, one of the following 3 things are true:
1. First player can force odd AND second player can force even
2. First player can force both odd and even
3. First player can force even AND second player can force odd

So, consider a starting string S. It splits into T substrings that each have 1 of the 3 stats.
Split into 2 cases: Splits with a substring of type 2 and otherwise.
If no type 2 exists, then:
If sum of parities of the resulting strings is odd, then second player can force a win.
Else, the first player can just copy the moves of the second player to win.
In other words, if no type 2 exists in the split, then the person who wins is uniquely determined.

If a type 2 exists, then:

Grundy numbers:
Empty string = 0
"a", "b" = 1
"ab" = 0
Independent games: XOR of all grundy numbers (if 0, second player wins; else, first player wins)

To calc grundy of a state S, try all moves, and set ans = min number that cannot be reached by any move
This gives O(KN^2) solution directly (about)
How to calculate these efficiently?

Idea: Try extending by 1 (say we know grundies of [L, R-1], go to [L, R])
...

*/

// ============================== BEGIN TEMPLATE ==============================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#ifdef LOCAL
    #include "pprint.hpp"
#else
    #define debug(...) 42
    #define dumpVars(...) 42
#endif

void solve();

int runTests(bool multiple_tests) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (multiple_tests) {
        int T; cin >> T;
        rep(i, 0, T) solve();
    } else solve();
    return 0;
}
// =============================== END TEMPLATE ===============================

int currVal = 30;
map<vector<int>, bool> firstEven, firstOdd, secondEven, secondOdd;

bool naiveSolve(vector<int>& A) {
    // debug("naiveSolve(" << A << ")\n");
    unordered_set<int> seen;
    bool allUnique = true;
    for (int x : A) {
        if (!seen.count(x)) seen.insert(x);
        else {
            allUnique = false;
            break;
        }
    }
    // Base case
    if (allUnique) {
        if (sz(A) % 2 == 0) {
            firstEven[A] = true;
            secondOdd[A] = true;
        } else {
            firstOdd[A] = true;
            secondEven[A] = true;
        }
        return firstOdd[A];
    }
    // Try all moves
    secondOdd[A] = true;
    secondEven[A] = true;
    for (int d : seen) {
        // Try this move
        vector<int> newA;
        unordered_map<int, int> valToNewVal;
        for (int x : A) {
            if (x == d) {
                valToNewVal.clear();
            } else {
                auto ptr = valToNewVal.find(x);
                if (ptr == valToNewVal.end()) ptr = valToNewVal.emplace(x, currVal++).first;
                newA.push_back(ptr->second);
            }
        }
        naiveSolve(newA);
        // Generate solution
        if (secondOdd[newA]) firstEven[A] = true;
        if (secondEven[newA]) firstOdd[A] = true;
        if (!firstOdd[newA]) secondEven[A] = false;
        if (!firstEven[newA]) secondOdd[A] = false;
    }

    return firstOdd[A];
}

void solve() {
    string S; // cin >> S;
    S = "adbaabdbcbab";
    vector<int> A(sz(S));
    rep(i, 0, sz(S)) A[i] = S[i] - 'a';
    naiveSolve(A);
    for (auto& p : firstOdd) {
        auto& a = p.first;
        debug(firstOdd[a] << " " << firstEven[a] << " " << secondOdd[a] << " " << secondEven[a] << "\n");
    }
    cout << "ans: " << firstOdd[A] << " " << firstEven[A] << " " << secondOdd[A] << " " << secondEven[A] << "\n";

    // int M; cin >> M;
    // rep(i, 0, M) {
    //     int L, R; cin >> L >> R;
    //     L--, R--;
    // }
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
