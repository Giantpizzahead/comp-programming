#include <iostream>
#include <queue>

using namespace std;
using ll = long long;

const int MAXN = 100005;

int N;
ll E[MAXN], R[MAXN], enjoymentSum;
priority_queue<pair<ll, int>> toys;

void solve(int tn) {
    cin >> N;
    enjoymentSum = 0;
    while (!toys.empty()) toys.pop();
    for (int i = 0; i < N; i++) {
        cin >> E[i] >> R[i];
        enjoymentSum += E[i];
    }

    int toysRemoved = 0, answerRemoved = 0;
    ll currTime = enjoymentSum, answer = enjoymentSum;
    for (int i = 0; i < N; i++) {
        if (enjoymentSum < R[i] + E[i]) {
            // Must remove this toy
            if (currTime > answer) {
                answer = currTime;
                answerRemoved = toysRemoved;
            }
            toysRemoved++;
            currTime -= E[i];
            enjoymentSum -= E[i];

            while (!toys.empty()) {
                const pair<ll, int>& topToy = toys.top();
                // cout << topToy.first << ' ' << topToy.second << endl;
                if (enjoymentSum < topToy.first) {
                    // cout << "remove " << currTime << " " << topToy.first << endl;
                    // Must remove top toy
                    toysRemoved++;
                    currTime -= E[topToy.second] * 2;
                    enjoymentSum -= E[topToy.second];
                    toys.pop();
                } else break;
            }
        } else {
            // Keep this toy
            currTime += E[i];
            toys.push({R[i] + E[i], i});
        }
    }
    
    if (toysRemoved != N) {
        // Indefinite answer found!
        cout << "Case #" << tn << ": " << toysRemoved << " INDEFINITELY" << endl;
    } else {
        cout << "Case #" << tn << ": " << answerRemoved << " " << answer << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}