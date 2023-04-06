/**
 * Problem link:
 * https://leetcode.com/contest/weekly-contest-327/problems/make-number-of-distinct-characters-equal/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    const int NUM_L = 26;
    const char FIRST_L = 'a';

    void genCount(const string& word, vector<int>& cnt, int& distinct) {
        for (char c : word) cnt[c-FIRST_L]++;
        for (int i = 0; i < NUM_L; i++) if (cnt[i]) distinct++;
    }

    int distinctDelta(vector<int>& cnt, int a, int b) {
        int delta = 0;
        if (a != b && cnt[a] == 1) delta--;
        if (a != b && cnt[b] == 0) delta++;
        return delta;
    }
public:
    bool isItPossible(string word1, string word2) {
        vector<int> cnt1(NUM_L), cnt2(NUM_L);
        int distinct1 = 0, distinct2 = 0;
        genCount(word1, cnt1, distinct1);
        genCount(word2, cnt2, distinct2);
        // Try each pair of letters
        for (int a = 0; a < NUM_L; a++) {
            for (int b = 0; b < NUM_L; b++) {
                if (!cnt1[a] || !cnt2[b]) continue;
                int newDistinct1 = distinct1 + distinctDelta(cnt1, a, b);
                int newDistinct2 = distinct2 + distinctDelta(cnt2, b, a);
                if (newDistinct1 == newDistinct2) return true;
            }
        }
        return false;
    }
};

// For debugging; leave this part out when submitting
int main() {
    Solution sol;
    cout << sol.isItPossible("ac", "b") << endl;
    cout << sol.isItPossible("abcc", "aab") << endl;
    cout << sol.isItPossible("abcde", "fghij") << endl;
    return 0;
}
