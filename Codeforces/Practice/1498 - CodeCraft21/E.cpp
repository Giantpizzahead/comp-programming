#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

// Total # edges = N(N-1)/2
// Average # in/out edges = (N-1)/2
// One less than average, one more than average:
// Assuming more can reach less
// K inedges = N-1-K outedges (technically N-K reachable)
// < (N-1)/2 inedges means > (N-1)/2 

// A, B, A <= B -> A+1 can reach node 1, B+1 can reach node 2
// N-1-A, B -> N-A reachable by node 1, B+1 can reach node 2, A not reachable

const int MAXN = 500;

int N;
int A[MAXN];
struct Query {
    int x, i, j;
    
    bool operator<(const Query& o) const {
        return x > o.x;
    }
};
vector<Query> Q;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) {
        rep(j, i+1, N) {
            if (A[i] <= A[j]) {
                Q.push_back({A[j]-A[i], i, j});
            } else {
                Q.push_back({A[i]-A[j], j, i});
            }
        }
    }
    sort(all(Q));
    string res;
    for (Query& q : Q) {
        cout << "? " << q.j+1 << ' ' << q.i+1 << endl;
        cin >> res;
        if (res == "Yes") {
            cout << "! " << q.i+1 << ' ' << q.j+1 << endl;
            return;
        }
    }
    cout << "! 0 0" << endl;
}

int main() {
    solve();
    return 0;
}