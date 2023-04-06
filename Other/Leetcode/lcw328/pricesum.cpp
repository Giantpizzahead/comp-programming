/**
 * Problem link:
 * https://leetcode.com/contest/weekly-contest-328/problems/difference-between-maximum-and-minimum-price-sum/
 * 
 * Solution: Problem reduces to "find sum of longest path while leaving out exactly 1 leaf node."
 * Solve this using tree DP.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int N, R;
    long long ans;
    vector<vector<int>> adj;
    vector<int> P;
    vector<long long> ansNoLeaf, ansWithLeaf;

    void doDP(int n, int p) {
        if (adj[n].size() == 1) {
            // Leaf node
            ansNoLeaf[n] = 0;
            ansWithLeaf[n] = P[n];
            return;
        }
        // Non-leaf node
        for (int e : adj[n]) {
            if (e == p) continue;
            doDP(e, n);
        }
        // Update answer with paths that use this as topmost node
        for (int e : adj[n]) {
            long long path1 = ansNoLeaf[n] + ansWithLeaf[e];
            long long path2 = ansWithLeaf[n] + ansNoLeaf[e];
            ans = max(max(path1, path2), ans);
            ansNoLeaf[n] = max(ansNoLeaf[e] + P[n], ansNoLeaf[n]);
            ansWithLeaf[n] = max(ansWithLeaf[e] + P[n], ansWithLeaf[n]);
        }
    }

public:
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
        if (n == 1) return 0;
        else if (n == 2) return max(price[0], price[1]);
        // Root the tree at any non-leaf
        N = n;
        P = price;
        adj = vector<vector<int>>(N);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        R = -1;
        for (int i = 0; i < N; i++) if (adj[i].size() > 1) R = i;
        assert(R != -1);
        // Solve with tree DP
        ansNoLeaf = vector<long long>(N);
        ansWithLeaf = vector<long long>(N);
        ans = 0;
        doDP(R, R);
        return ans;
    }
};

int main() {
    int N = 6;
    vector<vector<int>> edges = {
        {0, 1}, {1, 2}, {1, 3}, {3, 4}, {3, 5}
    };
    vector<int> price = {9, 8, 7, 6, 10, 5};
    cout << Solution().maxOutput(N, edges, price) << endl;
    return 0;
}
