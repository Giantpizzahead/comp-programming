/**
 * Problem link:
 * https://leetcode.com/contest/weekly-contest-327/problems/time-to-cross-a-bridge/
 * 
 * Solution: Simulation with two priority queues (one on the left, one on the right).
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    struct Worker {
        int leftToRight, pickOld, rightToLeft, putNew, id;

        bool operator<(const Worker& o) const {
            int c1 = leftToRight + rightToLeft, c2 = o.leftToRight + o.rightToLeft;
            if (c1 == c2) return id < o.id;
            else return c1 < c2;
        }
    };
    typedef priority_queue<pair<int, Worker>, vector<pair<int, Worker>>, greater<pair<int, Worker>>> wait_pq;

    void addWorker(priority_queue<Worker>& pq, Worker& w) {
        // cout << "adding " << w.id << "\n";
        pq.emplace(w);
    }

    void addWorkerWait(wait_pq& pq, Worker& w, int freeT) {
        // cout << "adding wait " << w.id << " at time " << freeT << "\n";
        pq.emplace(freeT, w);
    }

public:
    int findCrossingTime(int n, int k, vector<vector<int>>& time) {
        int ans = 0;
        priority_queue<Worker> pqLeft, pqRight;
        wait_pq pqWaitLeft, pqWaitRight;
        // To keep pqs from becoming empty
        int INF = 1e9;
        Worker w = {-1, -1, -1, -1, -1};
        addWorkerWait(pqWaitLeft, w, INF);
        addWorkerWait(pqWaitRight, w, INF);
        // Add initial workers
        int currID = 0;
        for (auto& d : time) pqLeft.push({d[0], d[1], d[2], d[3], currID++});
        int currTime = 0, numOld = n, numNew = 0;
        while (true) {
            // cout << "Current time: " << currTime << "\n";
            // Next worker to cross?
            if (!pqRight.empty()) {
                // Right side crosses
                w = pqRight.top(); pqRight.pop();
                // cout << "crossing right " << w.id << "\n";
                currTime += w.rightToLeft;
                ans = max(currTime, ans);
                int freeT = currTime + w.putNew;
                addWorkerWait(pqWaitLeft, w, freeT);
                numNew++;
                if (numNew == n) break;
            } else if (!pqLeft.empty() && numOld > 0) {
                // Left side crosses
                w = pqLeft.top(); pqLeft.pop();
                // cout << "crossing left " << w.id << "\n";
                currTime += w.leftToRight;
                int freeT = currTime + w.pickOld;
                addWorkerWait(pqWaitRight, w, freeT);
                numOld--;
            }
            // Make workers available
            while (true) {
                int nextTime = min(pqWaitLeft.top().first, pqWaitRight.top().first);
                // Can a worker cross right now?
                if (nextTime > currTime &&
                    ((!pqLeft.empty() && numOld > 0) || !pqRight.empty())) break;
                // Add a new worker
                currTime = max(nextTime, currTime);
                if (pqWaitRight.top().first <= pqWaitLeft.top().first) {
                    // Right one goes first
                    w = pqWaitRight.top().second; pqWaitRight.pop();
                    addWorker(pqRight, w);
                } else {
                    // Left one goes first
                    w = pqWaitLeft.top().second; pqWaitLeft.pop();
                    addWorker(pqLeft, w);
                }
            }
        }
        return ans;
    }
};

// For debugging; leave this part out when submitting
int main() {
    vector<vector<int>> time = {
        {1,1,2,1},
        {1,1,3,1},
        {1,1,4,1}
    };
    cout << Solution().findCrossingTime(1, 3, time) << endl;
    time = {
        {1,9,1,8},
        {10,10,10,10}
    };
    cout << Solution().findCrossingTime(3, 2, time) << endl;
    return 0;
}
