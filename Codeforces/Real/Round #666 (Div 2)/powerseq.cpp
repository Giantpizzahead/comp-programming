#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 100005;

int N;
ll arr[MAXN];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];
    sort(arr, arr+N);

    ll currPow = 1, minCost = 1e18;
    while (true) {
        ll currMult = 1, currCost = 0;
        for (int i = 0; i < N; i++) {
            currCost += abs(arr[i] - currMult);
            currMult *= currPow;
            if (currMult >= 1e18 || currMult < 0) {
                // Done
                cout << minCost << endl;
                return 0;
            }
        }
        minCost = min(currCost, minCost);
        currPow++;
    }
}