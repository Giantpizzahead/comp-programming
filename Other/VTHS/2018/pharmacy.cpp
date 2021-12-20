#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;
const ll INF = 1e18;

int N, T, numO, numR;

struct Point {
    int d, k;
    bool inStore;
};

Point P[MAXN];
ll finishTime[10];
queue<Point> remote;

void solve() {
    cin >> N >> T;
    for (int i = 0; i < N; i++) {
        char c;
        cin >> P[i].d >> c >> P[i].k;
        P[i].inStore = c == 'S';
        if (P[i].inStore) numO++;
        else numR++;
    }
    sort(P, P+N, [](const Point& a, const Point& b) {
        if (a.inStore != b.inStore) return a.inStore > b.inStore;
        if (a.d != b.d) return a.d < b.d;
        return a.k < b.k;
    });
    for (int i = numO; i < N; i++) remote.push(P[i]);

    int pi = 0, ti = 0;
    ll time = 0;
    double timeDiffO = 0, timeDiffR = 0;
    while (!remote.empty() || pi != numO) {
        time = INF;
        for (int i = 0; i < T; i++) {
            if (finishTime[i] < time) {
                time = finishTime[i];
                ti = i;
            }
        }
        // Eval next prescription
        ll oTime = (pi == numO) ? INF : P[pi].d, rTime = (remote.empty()) ? INF : remote.front().d;
        if (oTime <= time || oTime <= rTime) {
            // Must do this one
            time = max(oTime, time);
            timeDiffO += time + P[pi].k - P[pi].d;
            finishTime[ti] = time + P[pi].k;
            pi++;
        } else {
            // Work on remote
            time = max(rTime, time);
            Point& nextRemote = remote.front();
            timeDiffR += time + nextRemote.k - nextRemote.d;
            finishTime[ti] = time + nextRemote.k;
            remote.pop();
        }
        // cout << time << endl;
    }

    if (numO != 0) timeDiffO /= numO;
    if (numR != 0) timeDiffR /= numR;
    cout << fixed << timeDiffO << ' ' << timeDiffR << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}