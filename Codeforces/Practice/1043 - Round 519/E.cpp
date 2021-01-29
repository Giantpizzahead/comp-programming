#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 300000;

int N, M;

struct Pair {
    int x, y, i;

    // Sort by increasing y-x
    bool operator<(const Pair& o) const {
        return (y-x) < (o.y - o.x);
    }
};

ll scoreSum[MAXN];
Pair people[MAXN], rawPeople[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> M;
    ll leftSum = 0, rightSum = 0;
    int x, y;
    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        people[i] = {x, y, i};
        rawPeople[i] = {x, y, i};
        rightSum += x;
    }
    sort(people, people+N);

    for (int i = 0; i < N; i++) {
        rightSum -= people[i].x;
        // Calculate current score sum
        scoreSum[people[i].i] = leftSum + ((ll) i * people[i].x) + rightSum + ((ll) (N-1-i) * people[i].y);
        leftSum += people[i].y;
    }

    // Ignore pairs
    int u, v;
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        u--;
        v--;
        ll pairScore;
        if (rawPeople[u] < rawPeople[v]) pairScore = rawPeople[u].y + rawPeople[v].x;
        else pairScore = rawPeople[u].x + rawPeople[v].y;
        scoreSum[u] -= pairScore;
        scoreSum[v] -= pairScore;
    }

    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ' ';
        cout << scoreSum[i];
    }
    cout << endl;
    return 0;
}