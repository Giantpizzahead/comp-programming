#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 1000005;

int N;
ll arr[MAXN], normalCost[MAXN], bestPre[MAXN];
ll r1, r2, r3, d, baseCost, answer;

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> r1 >> r2 >> r3 >> d;
    for (int i = 0; i < N; i++) cin >> arr[i];

    baseCost = 0;
    for (int i = 0; i < N; i++) {
        ll costPistol = min(r1, r3) * arr[i] + min(min(r1, r2) * 2 + d * 2, r3) + d;
        ll costLaser = r2 + d * 3 + min(r1, min(r2, r3));
        normalCost[i] = min(costPistol, costLaser);
        baseCost += normalCost[i];
        bestPre[i] = baseCost;
    }
    normalCost[N-1] -= d;
    bestPre[N-1] -= d;
    answer = bestPre[N-1];
    for (int i = 0; i < N; i++) {
        cout << normalCost[i] << ' ';
    }
    cout << endl;

    // Replace pistol with laser gun if optimal
    ll currCost = normalCost[N-1] + d;
    for (int i = N-2; i >= 0; i--) {
        ll replaceCost = r2 + d + min(r1, min(r2, r3));
        currCost += min(normalCost[i], replaceCost);
        answer = min((i == 0 ? 0 : bestPre[i-1]) + currCost, answer);
        cout << (i == 0 ? 0 : bestPre[i-1]) << ' ' << currCost << endl;
        currCost += d;
    }
    cout << answer << endl;
}