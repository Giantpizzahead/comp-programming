/**
 * Problem link:
 * https://leetcode.com/contest/weekly-contest-328/problems/difference-between-element-sum-and-digit-sum-of-an-array/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int differenceOfSum(vector<int>& nums) {
        int elementSum = 0;
        int digitSum = 0;
        for_each(nums.begin(), nums.end(), [&](int x){
            elementSum += x;
            while (x > 0) {
                digitSum += x % 10;
                x /= 10;
            }
        });
        return abs(elementSum - digitSum);
    }
};

int main() {
    vector<int> nums = {1, 15, 6, 3};
    cout << Solution().differenceOfSum(nums) << endl;
    return 0;
}
