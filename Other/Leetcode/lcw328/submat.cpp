/**
 * Problem link:
 * https://leetcode.com/contest/weekly-contest-328/problems/increment-submatrices-by-one/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> ans(n, vector<int>(n));
        for (auto& q : queries) {
            int r1 = q[0], c1 = q[1], r2 = q[2], c2 = q[3];
            ans[r1][c1]++;
            if (r2 != n-1) ans[r2+1][c1]--;
            if (c2 != n-1) ans[r1][c2+1]--;
            if (r2 != n-1 && c2 != n-1) ans[r2+1][c2+1]++;
        }
        for (int i = 0; i < ans.size(); i++) {
            for (int j = 0; j < ans[0].size(); j++) {
                if (i != 0) ans[i][j] += ans[i-1][j];
                if (j != 0) ans[i][j] += ans[i][j-1];
                if (i != 0 && j != 0) ans[i][j] -= ans[i-1][j-1];
            }
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> queries = {{1,1,2,2},{0,0,1,1}};
    int n = 3;
    vector<vector<int>> mat = Solution().rangeAddQueries(n, queries);
    for (auto& r : mat) {
        for (int x : r) cout << x << " ";
        cout << endl;
    }
    return 0;
}
