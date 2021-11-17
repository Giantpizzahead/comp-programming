#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 3e5+5;

int N;
ll initAns, answer;
int A[MAXN];
struct Segment {
    int a, b;
    bool operator<(const Segment& o) const {
        if (a == o.a) return b > o.b;
        else return a < o.a;
    }
};
vector<Segment> upSegs, downSegs;

void tryMiddle(vector<Segment>& S) {
    int maxR = -1;
    rep(i, 0, sz(S)) {
        Segment& s = S[i];
        if (s.a <= maxR) {
            // Intersects with biggest segment
            ll curr = initAns - 2 * (min(s.b, maxR) - s.a);
            answer = min(curr, answer);
            /*
            if (s.b <= maxR) {
                // Contained
                ll curr = initAns - 2 * (s.b - s.a);
                answer = min(curr, answer);
            } else {
                // Not contained (monotonic)
                ll curr = initAns - 2 * (maxR - s.a);
                answer = min(curr, answer);
            }
            */
        }
        maxR = max(s.b, maxR);
    }
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    initAns = 0;
    rep(i, 1, N) initAns += abs(A[i] - A[i-1]);
    answer = initAns;

    // Try all prefixes
    rep(i, 1, N) {
        ll curr = initAns - abs(A[i]-A[i-1]) + abs(A[i]-A[0]);
        answer = min(curr, answer);
    }
    // Try all suffixes
    rep(i, 0, N-1) {
        ll curr = initAns - abs(A[i]-A[i+1]) + abs(A[i]-A[N-1]);
        answer = min(curr, answer);
    }

    // Try all in between
    rep(i, 0, N-1) {
        if (A[i] < A[i+1]) {
            upSegs.push_back({A[i], A[i+1]});
        } else if (A[i] > A[i+1]) {
            downSegs.push_back({A[i+1], A[i]});
        }
    }
    sort(all(upSegs));
    sort(all(downSegs));
    tryMiddle(upSegs);
    tryMiddle(downSegs);

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}