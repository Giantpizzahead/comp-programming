#include <iostream>
using namespace std;
const int MAXN = 300005;

int N, K, L;
int S[MAXN], E[MAXN];

bool canWait(int a, int b, int i) {
    if (a <= b) return (E[i] < a || S[i] > b);
    else {
        // Loops around
        if (S[i] >= a || S[i] <= b) return false;
        else return true;
    }
}

void solve() {
    cin >> N >> K >> L;
    bool possible = true;
    for (int i = 0; i < N; i++) {
        int d;
        cin >> d;
        int time = L - d + 1;
        if (time > K) {
            // Not blocked
            S[i] = -1;
            E[i] = -1;
        } else {
            // Blocked; record block time
            S[i] = time;
            if (S[i] <= 0) possible = false;
            E[i] = 2 * K - time;
        }
        // cout << "block " << S[i] << " " << E[i] << endl;
    }
    if (!possible) {
        cout << "No\n";
        return;
    }
    int bestTime = -1;
    for (int i = 0; i < N; i++) {
        // cout << bestTime << endl;
        // Find earliest time Koa can move forward (to give most time to prepare for next one)
        if (S[i] == -1) {
            bestTime = -1;
            continue;
        }
        if (bestTime == -1) {
            // Any time works
            bestTime = (E[i] + 1) % (2 * K);
            continue;
        }
        // Try to go right after tide drops
        int nextTime = E[i];
        if (canWait(bestTime, nextTime, i-1)) {
            bestTime = (nextTime + 1) % (2 * K);
            continue;
        }
        // If in tide and can't wait until tide drops, cannot get past this
        if (bestTime >= S[i]-1 && bestTime < E[i]) {
            cout << "No\n";
            return;
        }
        // Not in tide; just go
        bestTime = (bestTime + 1) % (2 * K);
    }
    cout << "Yes\n";
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}