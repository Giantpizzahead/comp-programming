/**
 * Problem link:
 * https://leetcode.com/contest/biweekly-contest-95/problems/maximize-the-minimum-powered-city/
 * 
 * Solution: Binary search on the answer. Check guesses with a simple greedy.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    bool checkMinPower(long long p, vector<int>& stations, int r, long long k) {
        int n = stations.size() + 2*r;
        vector<long long> newStations(n, 0);
        copy(begin(stations), end(stations), begin(newStations)+r);
        long long currPower = 0;
        for (int i = 0; i < n; i++) {
            currPower += newStations[i];
            if (i >= 2*r) {
                if (currPower < p) {
                    // Must add power stations here
                    long long numToAdd = p - currPower;
                    if (numToAdd > k) return false;
                    k -= numToAdd;
                    newStations[i] += numToAdd;
                    currPower += numToAdd;
                }
                // Out of range of these power stations
                currPower -= newStations[i-2*r];
            }
        }
        // for (int i = 0; i < n; i++) cout << newStations[i] << " \n"[i==n-1];
        // Made it to the end; this works
        return true;
    }

public:
    long long maxPower(vector<int>& stations, int r, int k) {
        long long low = 0, high = 1e11;
        while (low < high) {
            long long mid = (low + high + 1) / 2;
            if (checkMinPower(mid, stations, r, k)) low = mid;
            else high = mid - 1;
        }
        return low;
    }
};

// For debugging; leave this part out when submitting
int main() {
    // Input: stations = [1,2,4,5,0], r = 1, k = 2
    // Output: 5
    vector<int> stations = {1,2,4,5,0};
    int r = 1, k = 2;
    Solution sol;
    cout << sol.maxPower(stations, r, k) << '\n';

    // Input: stations = [4,4,4,4], r = 0, k = 3
    // Output: 4
    vector<int> stations2 = {4,4,4,4};
    int r2 = 0, k2 = 3;
    cout << sol.maxPower(stations2, r2, k2) << '\n';

    return 0;
}
