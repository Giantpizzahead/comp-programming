/**
 * Problem link:
 * https://leetcode.com/contest/weekly-contest-328/problems/count-the-number-of-good-subarrays/
 * 
 * Solution: Sliding window
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        int n = nums.size();
        int ri = -1;
        map<int, int> currCnt;
        long long currVal = 0, ans = 0;
        for (int li = 0; li < n; li++) {
            while (currVal < k) {
                // Add more on the right end
                if (++ri == n) return ans;
                currVal += currCnt[nums[ri]];
                currCnt[nums[ri]]++;
            }
            ans += (n-ri);
            // Remove current on the left end
            currVal -= (currCnt[nums[li]]-1);
            currCnt[nums[li]]--;
        }
        return ans;
    }
};

int main() {
    vector<int> nums = {3, 1, 4, 3, 2, 2, 4};
    Solution sol = Solution();
    cout << sol.countGood(nums, 2) << endl;
    nums = {1, 1, 1, 1, 1};
    cout << sol.countGood(nums, 10) << endl;
    return 0;
}
