#include <iostream>
#include <algorithm>
#include <math.h>
#include <unordered_set>

using namespace std;
using ll = long long;
using ld = long double;

const int MAXN = 1000;
const int INF = 987654321;
const ld EPSILON = 0.000000001;

int gcf(int a, int b) {
    if (a == 0) return b;
    else return gcf(b % a, a);
}

struct Segment {
    ll x1, y1, x2, y2;
    ll slopeTop, slopeBot;
    ld slope;
    bool isVertical;

    void init(int x1, int y1, int x2, int y2) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        // Segments go from left to right, bottom to top if vertical
        if (x1 > x2 || (x1 == x2 && y1 > y2)) {
            swap(this->x1, this->x2);
            swap(this->y1, this->y2);
        }
        slopeTop = this->y2-this->y1;
        slopeBot = this->x2-this->x1;
        if (slopeBot == 0) isVertical = true;
        else {
            int slopeGCF = gcf(abs(slopeTop), abs(slopeBot));
            slopeTop /= slopeGCF;
            slopeBot /= slopeGCF;
            slope = (ld) slopeTop / slopeBot;
        }
    }
};

pair<int, int> getIntersect(Segment a, Segment b) {
    if (a.isVertical && b.isVertical) return {-INF, -INF};
    if (b.isVertical) {
        swap(a, b);
    }
    if (a.isVertical) {
        // One vertical and one non-vertical
        if (b.x1 > a.x1 || b.x2 < a.x1) return {-INF, -INF};
        if ((a.x1 - b.x1) % b.slopeBot != 0) return {-INF, -INF};
        ll intersectY = b.y1 + (a.x1 - b.x1) / b.slopeBot * b.slopeTop;
        if (intersectY > a.y2 || intersectY < a.y1) return {-INF, -INF};
        return {a.x1, intersectY};
    }

    // Both non-vertical
    ld intersectX = (b.y1 - a.y1 + a.slope * a.x1 - b.slope * b.x1) / (a.slope - b.slope);
    ll intersectXRounded = round(intersectX);
    if (abs(intersectXRounded - intersectX) > EPSILON) return {-INF, -INF};
    if (intersectXRounded > b.x2 || intersectXRounded < b.x1 || intersectXRounded > a.x2 || intersectXRounded < a.x1) return {-INF, -INF};

    ld intersectY = a.slope * (intersectXRounded - a.x1) + a.y1;
    ll intersectYRounded = round(intersectY);
    if (abs(intersectYRounded - intersectY) > EPSILON) return {-INF, -INF};

    return {intersectXRounded, intersectYRounded};
}

int N;
Segment segments[MAXN];
unordered_set<ll> usedPoints, alreadySubtracted;

int main() {
    cin >> N;
    int x1, y1, x2, y2;
    for (int i = 0; i < N; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        segments[i].init(x1, y1, x2, y2);
        // cout << segments[i].x1 << ' ' << segments[i].y1 << ' ' << segments[i].slopeTop << '/' << segments[i].slopeBot << ' ' << segments[i].isVertical << endl;
    }

    // Calculate # of points, assuming no segments overlap
    ll answer = 0;
    for (int i = 0; i < N; i++) {
        int xLength = abs(segments[i].x2 - segments[i].x1);
        int yLength = abs(segments[i].y2 - segments[i].y1);
        if (xLength == 0 || yLength == 0) {
            // All points are on line
            answer += xLength + yLength + 1;
        } else {
            // # of integer points
            answer += xLength / abs(segments[i].slopeBot) + 1;
        }
    }

    // Handle overcounting
    for (int i = 0; i < N; i++) {
        alreadySubtracted.clear();
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            // Check intersection point of these two (if they intersect)
            pair<int, int> intersect = getIntersect(segments[i], segments[j]);
            // cout << i << ' ' << j << ": " << intersect.first << ' ' << intersect.second << endl;
            if (intersect.first == -INF) continue;

            // Add to set
            ll hash = (ll) intersect.first * 2000005 + intersect.second;
            if (usedPoints.count(hash) != 0) {
                // Already exists; subtract answer
                if (alreadySubtracted.count(hash) == 0) {
                    answer--;
                    alreadySubtracted.insert(hash);
                }
            } else {
                usedPoints.insert(hash);
                alreadySubtracted.insert(hash);
            }
        }
        // cout << answer << endl;
    }

    cout << answer << endl;
    return 0;
}