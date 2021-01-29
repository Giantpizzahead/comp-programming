#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2001;

int N, M, K;
pair<int, int> tasks[MAXN];

int calcOverlap(int l1, int r1, int l2, int r2) {
    return max(min(r1, r2) - max(l1, l2) + 1, 0);
}

struct Point {
    int x, c;
    Point(int x, int c) : x(x), c(c) {}
    bool operator<(Point& o) const {
        return x < o.x;
    }
};

vector<Point> points;

int fixFirst(int firstL) {
    int firstR = firstL + K - 1;
    int result = 0;
    points.clear();
    rep(i, 0, M) {
        pair<int, int>& p = tasks[i];
        result += calcOverlap(p.first, p.second, firstL, firstR);
        if (p.second > firstR) {
            // Find update points (update will be applied on the same turn)
            int p1 = p.first - K + 1;
            int p2 = min(p.first + 1, p.second - K + 2);
            int p3 = p.second + 2 - min(p2-p1, p.second-p.first+1);
            int p4 = p.second + 2;
            // cout << p1 << " " << p2 << " " << p3 << " " << p4 << endl;
            assert((p2-p1) - (p4-p3) == 0);
            // Might be partially covered by previous
            int cutout = calcOverlap(p.first, p.second, firstL, firstR);
            p1 += cutout;
            p4 -= cutout;
            
            if (p1 >= p2) continue;  // Never better
            points.emplace_back(p1, 1);
            points.emplace_back(p2, -1);
            points.emplace_back(p3, -1);
            points.emplace_back(p4, 1);
        }
    }
    //cout << "result " << result << endl;
    if (points.empty()) return result;
    sort(all(points));

    int bestVal = 0, currVal = 0, currDelta = 0, pi = 0;
    rep(i, points[0].x, points[points.size()-1].x+1) {
        while (pi != points.size() && points[pi].x == i) {
            currDelta += points[pi].c;
            pi++;
        }
        currVal += currDelta;
        bestVal = max(currVal, bestVal);
    }
    //cout << "bestVal " << bestVal << endl;
    return result + bestVal;
}

void solve() {
    cin >> N >> M >> K;
    rep(i, 0, M) cin >> tasks[i].first >> tasks[i].second;
    int answer = 0;
    rep(i, 1, N-K+2) {
        // Fix first problem author
        //cout << "fixing " << i << endl;
        answer = max(fixFirst(i), answer);
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}