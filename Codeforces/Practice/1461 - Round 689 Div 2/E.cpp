#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e6;

ll K, L, R, T, Y;
int X;
bool visited[MAXN];
int nextNode[MAXN];
ll nextTime[MAXN];

void solve() {
    cin >> K >> L >> R >> T >> X >> Y;
    if (X > R-L) {
        cout << "No" << endl;
        return;
    }
    R -= L;
    K -= L;
    L = 0;
    if (X > Y) {
        // Special case; push up as much as possible
        ll change, currTime = 0;
        if (R-Y < 0) {
            // Just watch... maybe it'll work
            change = X;
        } else {
            change = X-Y;
            if (R-K < Y) {
                // Go one day normally
                K -= X;
                currTime++;
            }
        }
        // cout << "skip " << change << " " << currTime << " " << K << endl;
        currTime += K / change + 1;
        // cout << "time " << currTime << endl;
        if (currTime > T) cout << "Yes" << endl;
        else cout << "No" << endl;
        return;
    }
    for (int i = 0; i < X; i++) {
        // Refill here
        ll currLevel = i + Y;
        if (currLevel > R) {
            nextNode[i] = -1;
            nextTime[i] = 1;
            continue;
        }
        // See where this ends up
        currLevel = max(currLevel - X, -1LL);
        ll daysToSkip = currLevel / X;
        currLevel -= X * daysToSkip;
        nextNode[i] = currLevel;
        nextTime[i] = daysToSkip + 1;
    }
    // for (int i = 0; i < X; i++) {
    //     cout << i << ": (" << nextNode[i] << ", " << nextTime[i] << ")" << endl;
    // }

    // Traverse the graph to find answer
    ll currTime = 0;
    ll daysToSkip = K / X;
    K -= X * daysToSkip;
    currTime += daysToSkip;
    while (currTime < T) {
        // cout << "time " << currTime << ": " << K << endl;
        // Refill
        if (visited[K]) {
            // Cycle
            cout << "Yes" << endl;
            return;
        }
        visited[K] = true;
        currTime += nextTime[K];
        K = nextNode[K];
        if (K == -1) {
            cout << "No" << endl;
            return;
        }
    }
    // cout << "time " << currTime << ": " << K << endl;
    cout << "Yes" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}                                                                                                                   