#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 200;

int N;
struct Point {
    int x, y;
    bool operator<(const Point& o) const {
        return x < o.x;
    }
};
Point P[MAXN];

vector<int> yCoords;

void yInsert(int y) {
    yCoords.push_back(y);
    for (int i = yCoords.size()-1; i > 0; i--) {
        if (yCoords[i] < yCoords[i-1]) swap(yCoords[i], yCoords[i-1]);
    }
}

int countSquares(bool overcount) {
    int totalCnt = 0;
    rep(i, 0, N) {
        yCoords.clear();
        yCoords.push_back(P[i].y);
        rep(j, i+1, N) {
            int cnt = 0;
            yInsert(P[j].y);
            // Slide square from bottom to top
            int squareSize = abs(P[j].x - P[i].x);
            bool inI = false, inJ = false;
            int bl = 0, tl = -1, bs = -1-squareSize, ts = -1;
            while (bl != yCoords.size()-1 || tl != yCoords.size()-1) {
                int botDist = yCoords[bl]-bs+1;
                int topDist = (tl == yCoords.size()-1 ? INT32_MAX : yCoords[tl+1]-ts);
                if (botDist == topDist) {
                    // Both slide at once
                    if (yCoords[bl] == P[i].y) inI = false;
                    if (yCoords[bl] == P[j].y) inJ = false;
                    bl++;
                    if (yCoords[tl+1] == P[i].y) inI = true;
                    if (yCoords[tl+1] == P[j].y) inJ = true;
                    tl++;
                    bs += botDist;
                    ts += topDist;
                } else if (botDist < topDist) {
                    // Slide bottom
                    if (yCoords[bl] == P[i].y) inI = false;
                    if (yCoords[bl] == P[j].y) inJ = false;
                    bl++;
                    bs += botDist;
                    ts += botDist;
                } else {
                    // Slide top
                    if (yCoords[tl+1] == P[i].y) inI = true;
                    if (yCoords[tl+1] == P[j].y) inJ = true;
                    tl++;
                    bs += topDist;
                    ts += topDist;
                }
                // cout << bl << " " << tl << " " << bs << " " << ts << endl;

                if (inI && inJ) {
                    if (yCoords[bl] == bs && yCoords[tl] == ts) {
                        // Both borders
                        if (overcount) continue;
                    }
                    cnt++;
                }
            }
            totalCnt += cnt;
            // cout << i << " " << j << " = " << cnt << endl;
        }
    }
    return totalCnt;
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> P[i].x >> P[i].y;
    sort(P, P+N);
    int answer = N+1;
    answer += countSquares(false);
    rep(i, 0, N) swap(P[i].x, P[i].y);
    sort(P, P+N);
    answer += countSquares(true);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}