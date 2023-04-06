/**
 * Problem link:
 * https://leetcode.com/contest/biweekly-contest-95/problems/categorize-box-according-to-criteria/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string categorizeBox(int length, int width, int height, int mass) {
        bool bulky = (length >= 10000 || width >= 10000 || height >= 10000) ||
            (((long) length) * width * height >= 1000000000);
        bool heavy = (mass >= 100);
        if (bulky && heavy) return "Both";
        else if (bulky) return "Bulky";
        else if (heavy) return "Heavy";
        else return "Neither";
    }
};

// For debugging; leave this part out when submitting
int main() {
    Solution sol;
    cout << sol.categorizeBox(1000, 35, 700, 300) << endl;
    return 0;
}
