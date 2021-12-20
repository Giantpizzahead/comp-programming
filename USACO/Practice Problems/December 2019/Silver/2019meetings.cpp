/**
 * Solution:
 * Two clever observations lead to the solution:
 * 1) If weights are not considered, swapping velocities between two cows is the same thing as just letting them pass
 * through each other. (In the end, there will be one cow going right and one cow going left.)
 * 2) No matter how many meetings there are, the sorted order of the cows will not change. That is, if the cows are
 * sorted by initial x position, this order will never change throughout the simulation (they'd bounce off each other).
 * This also means that the sorted order of the weights stays the same.
 * 
 * With the first observation, you can figure out the exact times when cows reach the left or right barn. With the
 * second observation, you know what the weight of that cow would be. You can combine these to figure out the time
 * when the simulation stops. Then, use the first observation to count the # of pairs of cows that cross; this will
 * be equal to the # of meetings. (Do it efficiently with 2 pointers)
 *
 * Runtime: O(N * log(N))
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 50000;

int N, L, totalWeight;
struct Cow {
    int w, x, d;
};
Cow C[MAXN];

void solve() {
    cin >> N >> L;
    totalWeight = 0;
    rep(i, 0, N) {
        cin >> C[i].w >> C[i].x >> C[i].d;
        totalWeight += C[i].w;
    }
    // Sort cows in order of increasing position
    sort(C, C+N, [](const Cow& a, const Cow& b) {
        return a.x < b.x;
    });

    // Find time at which cows stop moving
    vector<pair<int, bool>> events;
    rep(i, 0, N) {
        bool onRight = (C[i].d == 1);
        int timeToBarn = (onRight ? L - C[i].x : C[i].x);
        events.emplace_back(timeToBarn, onRight);
    }
    sort(all(events));
    int currWeight = 0, currT = 0, currI = 0;
    int currL = 0, currR = N-1;
    while (currWeight < (totalWeight+1)/2) {
        currT = events[currI].first;
        while (currI != N && events[currI].first == currT) {
            if (events[currI].second) currWeight += C[currR--].w;
            else currWeight += C[currL++].w;
            currI++;
        }
    }

    // Count the number of pairs that cross before this time
    ll answer = 0;
    queue<int> rightPos;
    rep(i, 0, N) {
        if (C[i].d == 1) {
            rightPos.push(C[i].x);
        } else {
            // Remove positions that are too far away
            int furthest = C[i].x - currT * 2;
            while (!rightPos.empty() && rightPos.front() < furthest) {
                rightPos.pop();
            }
            answer += sz(rightPos);
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);
    solve();
    return 0;
}