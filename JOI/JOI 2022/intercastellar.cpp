/*
JOI 2022 Problem 1

Solution: Sweep from left to right, sorting the queries and processing them in order.
The operations in the statement can be done using some basic math.
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

void solve() {
    int N; cin >> N;
    vi A(N);
    rep(i, 0, N) cin >> A[i];
    int Q; cin >> Q;
    vector<ll> X(Q);
    rep(i, 0, Q) cin >> X[i];

    ll piecesSoFar = 0;
    int currQ = 0;
    rep(i, 0, N) {
        ll currSize = A[i];
        ll currPieces = 1;
        while (currSize % 2 == 0) {
            currSize /= 2;
            currPieces *= 2;
        }
        // Answer all queries in this range
        piecesSoFar += currPieces;
        while (currQ != Q && X[currQ] <= piecesSoFar) {
            cout << currSize << '\n';
            currQ++;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}