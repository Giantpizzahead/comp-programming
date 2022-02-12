/*
Solution: 
Runtime: 
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 5e5+5;

int N;
int M[MAXN];

int leftS[MAXN], rightS[MAXN];
struct Point {
    int x;
    bool isS;
    ll v;
    bool operator<(const Point& o) const {
        if (x == o.x) return v < o.v;
        else return x < o.x;
    }
};
vector<Point> points;

void addRange(int l, int r, ll v) {
    // debug << "add " << l << " " << r << " " << v << endl;
    points.push_back({l, true, v});
    points.push_back({r+1, false, -v});
}

void findAdjSmaller() {
    stack<int> s;
    s.push(-1);
    rep(i, 0, N) {
        while (s.top() != -1 && M[s.top()] > M[i]) s.pop();
        leftS[i] = s.top();
        s.push(i);
    }
    s.empty();
    s.push(N);
    for (int i = N-1; i >= 0; i--) {
        while (s.top() != N && M[s.top()] >= M[i]) s.pop();
        rightS[i] = s.top();
        s.push(i);
    }

    // debug << "leftS ";
    // rep(i, 0, N) debug << leftS[i] << " \n"[i==N-1];
    // debug << "rightS ";
    // rep(i, 0, N) debug << rightS[i] << " \n"[i==N-1];
}

int A[MAXN];

void genAnswer(int I) {
    A[I] = M[I];
    for (int i = I-1; i >= 0; i--) A[i] = min(A[i+1], M[i]);
    for (int i = I+1; i < N; i++) A[i] = min(A[i-1], M[i]);
    rep(i, 0, N) cout << A[i] << " \n"[i==N-1];
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> M[i];
    // Prefix and suffix for # floors
    findAdjSmaller();
    rep(i, 0, N) {
        int l = leftS[i] + 1;
        int r = rightS[i] - 1;
        addRange(l, i, (ll) (r-i+1) * M[i]);
        addRange(i, r, (ll) (i-l+1) * M[i]);
    }
    // Overcount
    rep(i, 0, N) addRange(i, i, -M[i]);

    // Sweep to find answer
    sort(all(points));
    ll bestI = 0, bestAns = -1, curr = 0;
    for (Point& p : points) {
        curr += p.v;
        if (curr > bestAns) {
            bestAns = curr;
            bestI = p.x;
        }
    }

    // Generate answer
    genAnswer(bestI);

    // debug << bestI << " " << bestAns << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}