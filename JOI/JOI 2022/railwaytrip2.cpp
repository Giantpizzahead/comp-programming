/*
JOI 2022 Problem 4

Solution / Notes:

WLOG, Let K = 3 (so only the first 3 stations can be used) for thinking.
Ex:
     123456789
...............
    654321
       J
Consider only trains going right. If J is at station X, he can take trains starting
at stations [X-2, X] and ending at [X+1, N]. For any of these trains, only the one
that reaches the furthest to the right matters in terms of reach (can disregard others).
The same argument applies for going left.

In general, we're doing something like Dijkstra here. But how to handle queries?

Let's say we've calculated the furthest right and left stations one can reach at every
station X. Call these R and L. What would these look like?

For sample input 2:
K = 3
  1 2 3 4 5 6
  . . . . . .
  5 4 3 2 1
L - - 1 1 1 6
R 6 6 6 - - -

There are no guarantees on whether L or R are sorted, they can be arbitrary.
The key thing here is that the reachable set of stations is always a contiguous range.

At every step, given a range [X, Y], the next pair after taking a train is:
(X, Y) -> (min of L in [X, Y], max of R in [X, Y])

Say all trains go right for now. If we have an efficient algorithm for this,
we can run it twice to get both directions.

So (X, Y) -> (X, max of R in [X, Y])
Let's start with the trains that have the greatest R (go the furthest to the right).
Sort them by this standard.

BINARY LIFTING SHEESH
So basically, use binary lifting to figure out the maximum possible R after some
train rides. :)
But wait, not exactly...

So consider this.
R[0][i] = Max possible R using 1 train for each station, computed directly
R[1][i] = Max possible R using 2 trains for each station, computed with:
    max(R[0][j]) for j in [i, R[0][i]]
R[2][i] = Max possible R using 4 trains, computed with:
    max(R[1][j]) for j in [i, R[1][i]]
And so on...!

This definitely works for one dimension, though runtime is smth like O(Nlog^2(N)).

What about two dimensions?
L[0] and R[0] are computed directly.
R[1][i] = max(R[0][j]) for j in [L[0][i], R[0][i]]
R[2][i] = max(R[1][j]) for j in [L[1][i], R[1][i]]
Easy! Right? Yeah, totally! ::

Runtime: O(Nlog^2(N)) - You'll need to be a bit careful
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

void sweepInit(int N, int K, int M, vi& A, vi& B, vi& result) {
    // Start is on the actual start, end is one station after the actual end
    struct Point {
        int x, v;
        bool start;
    };
    vector<Point> points;
    multiset<int> trains;
    rep(i, 0, M) {
        if (A[i] > B[i]) continue;
        points.push_back({A[i], B[i], true});
        points.push_back({min(B[i]+1, A[i]+K), B[i], false});
    }
    sort(all(points), [](const Point& p1, const Point& p2) {
        return p1.x < p2.x;
    });
    int cp = 0;
    rep(i, 0, N) {
        while (cp != sz(points) && points[cp].x == i) {
            Point& p = points[cp++];
            // cout << "point " << p.x << " " << p.v << " " << p.start << endl;
            if (p.start) trains.insert(p.v);
            else trains.erase(trains.find(p.v));
        }
        if (trains.empty()) result[i] = i;
        else result[i] = *trains.rbegin();
    }
}

void genInit(int N, int K, int M, vi& A, vi& B, vi& L, vi& R) {
    // Sweep right
    sweepInit(N, K, M, A, B, R);
    // Sweep left
    vi revA(M), revB(M);
    rep(i, 0, M) {
        revA[i] = (N-1) - A[i];
        revB[i] = (N-1) - B[i];
    }
    // cout << "revs\n";
    // rep(i, 0, M) cout << revA[i] << " \n"[i==M-1];
    // rep(i, 0, M) cout << revB[i] << " \n"[i==M-1];
    sweepInit(N, K, M, revA, revB, L);
    reverse(all(L));
    rep(i, 0, N) L[i] = (N-1) - L[i];
}

void solve() {
    int N, K; cin >> N >> K;
    int M; cin >> M;

    // Generate initial L and R arrays using sweepline greedy
    vi A(M), B(M);
    rep(i, 0, M) {
        cin >> A[i] >> B[i];
        A[i]--, B[i]--;
    }

    vi initL(N), initR(N);
    genInit(N, K, M, A, B, initL, initR);

    cout << "initial arrays:\n";
    rep(i, 0, N) cout << initL[i] << " \n"[i==N-1];
    rep(i, 0, N) cout << initR[i] << " \n"[i==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}