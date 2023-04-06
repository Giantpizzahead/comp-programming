/**
 * Problem link:
 * https://leetcode.com/contest/weekly-contest-327/problems/maximal-score-after-applying-k-operations/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        long long ans = 0;
        priority_queue<int> vals;
        for_each(begin(nums), end(nums), [&](const int& v){ vals.push(v); });
        for (int i = 0; i < k; i++) {
            int v = vals.top();
            ans += v;
            vals.pop();
            vals.push((v+2) / 3);
        }
        return ans;
    }
};

// For debugging; leave this part out when submitting
int main() {
    vector<int> nums = {1, 10, 3, 3, 3};
    cout << Solution().maxKelements(nums, 3) << endl;
    return 0;
}
