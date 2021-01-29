#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

const int MAXM = 2e5+5;

int N, M, Q;
int C[MAXM], preC[MAXM];
struct Point {
    int x, y;
};
Point queries[MAXM];

void answerQuery(int i) {
    int a = 1, b = 1, c = queries[i].x, d = queries[i].y;
    int c1 = C[b], c2 = C[b+1];
    ll answer = 0;

    while (b != d) {
        c1 = C[b];
        c2 = preC[b+1];
        double best = (double) (c2 - c1) / (2 * (d - b));
        cout << "best: " << best << endl;
        ll bestT = round(best);
        bestT = min(bestT, (ll) c);
        bestT = max(bestT, (ll) a);
        answer += (bestT-a) * c1 + bestT * bestT; // + (c-bestT) * c2;

        a = bestT;
        b++;
    }

    answer += (ll) (c-a) * c1;
    cout << answer << '\n';
}

void solve() {
    cin >> N >> M;
    rep(i, 1, M+1) cin >> C[i];
    preC[M] = C[M];
    for (int i = M-1; i >= 1; i--) preC[i] = min(preC[i+1], C[i]);
    cin >> Q;
    rep(i, 0, Q) {
        cin >> queries[i].x >> queries[i].y;
        answerQuery(i);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}