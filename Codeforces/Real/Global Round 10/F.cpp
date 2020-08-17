#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 1000005;

struct Height {
    ll l, h;
};

int N;
ll arr[MAXN];
vector<Height> heights;

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        arr[i] -= i;
    }

    // Handle each mountain
    heights.push_back({1, arr[0]});
    for (int i = 1; i < N; i++) {
        // Merge heights while possible
        Height newHeight = {1, arr[i]};
        while (heights.size() >= 2) {
            Height& topH = heights[heights.size()-1];
            if (topH.h == newHeight.h) {
                // Simple merge
                newHeight.l += topH.l;
                heights.pop_back();
            } else if (newHeight.h > topH.h) {
                // Transfer some to next
                if (newHeight.h - topH.l + 1 >= topH.h) {
                    // Promote next!
                    topH.h++;
                    newHeight.h -= topH.l;
                    // Merge if needed
                    Height& nextNextH = heights[heights.size()-2];
                    if (nextNextH.h == topH.h) {
                        nextNextH.l += topH.l;
                        heights.pop_back();
                    }
                } else {
                    // Transfer some to next
                    int numTransfer = newHeight.h - topH.h + 1;
                    Height tempHeight = {topH.l - numTransfer, topH.h};
                    topH.h++;
                    topH.l = numTransfer;
                    // Merge if needed
                    Height& nextNextH = heights[heights.size()-2];
                    if (nextNextH.h == topH.h) {
                        nextNextH.l += topH.l;
                        heights.pop_back();
                    }
                    heights.push_back(tempHeight);
                    break;
                }
            } else break;  // Nothing else to do
        }
        // Merge two remaining heights
        Height& topH = heights[heights.size()-1];
        if (newHeight.h - topH.l + 1 >= topH.h) {
            
        }
        for (auto x : heights) {
            cout << x.l << ' ' << x.h << endl;
        }
    }

    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ' ';
        cout << arr[i];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    solve();
    return 0;
}