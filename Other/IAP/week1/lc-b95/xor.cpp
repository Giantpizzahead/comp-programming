/**
 * Problem link:
 * https://leetcode.com/contest/biweekly-contest-95/problems/find-xor-beauty-of-array/
 * 
 * Solution: By iterating through each kth index and focusing on the value of one specific bit index
 * (say the LSB), you can prove that after XORing all (i, j), the value ends up just being the value of
 * that bit in the kth integer. Therefore, the XOR beauty is just the XOR sum of the array.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int xorBeauty(vector<int>& nums) {
        int res = 0;
        for (int n : nums) res ^= n;
        return res;
    }
};

// For debugging; leave this part out when submitting
int main() {
    vector<int> nums = {1, 4};
    Solution sol;
    cout << sol.xorBeauty(nums) << '\n';
    vector<int> nums2 = {15,45,20,2,34,35,5,44,32,30};
    cout << sol.xorBeauty(nums2) << '\n';
    return 0;
}
