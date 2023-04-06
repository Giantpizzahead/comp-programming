/**
 * Problem link:
 * https://leetcode.com/contest/weekly-contest-327/problems/maximum-count-of-positive-integer-and-negative-integer/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumCount(vector<int>& nums) {
        int numNeg = lower_bound(begin(nums), end(nums), 0) - begin(nums);
        int numPos = end(nums) - upper_bound(begin(nums), end(nums), 0);
        // cout << numNeg << " " << numPos << endl;
        return max(numNeg, numPos);
    }
};

// For debugging; leave this part out when submitting
int main() {
    vector<int> nums = {-3,-2,-1,0,0,1,2};
    cout << Solution().maximumCount(nums) << endl;
    return 0;
}
