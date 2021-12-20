#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;
using ll = long long;

ifstream fin("input.txt");
ofstream fout("output.txt");

const ll MOD = 1000000007;
const ll INF = 1000000007;
const int MAXN = 1000005;

int N;

struct Room {
    ll l, w, h;
};

struct Point {
    ll x, h, lh;

    // Sort in increasing order of x point
    bool operator<(const Point& o) const {
        return x < o.x;
    }
};

Room rooms[MAXN];
set<Point> points;

void solve(int tn) {
    ll currP = 0, answer = 1;
    points.clear();
    points.insert({-1, 0, 0});

    Room room;
    Point newPoint;
    for (int i = 0; i < N; i++) {
        room = rooms[i];
        newPoint = {room.l, room.h, -1};

        // Find current height
        auto currPoint = points.lower_bound(newPoint);
        currPoint--;
        newPoint.lh = currPoint->h;
        // Add going up part to perimeter
        currP += newPoint.h - currPoint->h;

        // Update heights within this room
        int lastZero = newPoint.x, currHeight = currPoint->h;
        bool isZero = (currPoint->h == 0);
        while (true) {
            auto rightPoint = points.lower_bound(newPoint);
            if (rightPoint == points.end() || rightPoint->x >= room.l + room.w) break;
            // Current height must be >= this one, so remove it
            currP -= abs(rightPoint->h - rightPoint->lh);
            // Handle zero
            if (rightPoint->h == 0 && !isZero) {
                isZero = true;
                lastZero = rightPoint->x;
            }
            if (rightPoint->h != 0 && isZero) {
                // Add horizontal perimeter
                isZero = false;
                currP += (rightPoint->x - lastZero) * 2;
            }
            currHeight = rightPoint->h;
            points.erase(rightPoint);
        }
        // Handle ending with zero
        if (isZero) {
            isZero = false;
            currP += (room.l + room.w - lastZero) * 2;
        }

        // Add ending height (if not existent already)
        auto endPoint = points.lower_bound(newPoint);
        if (endPoint != points.end() && endPoint->x == room.l + room.w) {
            // Already exists; update perimeter
            currP -= abs(endPoint->h - endPoint->lh);
            currP += abs(endPoint->h - room.h);
            Point tempPoint = {endPoint->x, endPoint->h, room.h};
            points.erase(endPoint);
            points.insert(tempPoint);
        } else {
            // Add new point / update perimeter
            currP += abs(room.h - currHeight);
            points.insert({room.l + room.w, currHeight, room.h});
        }

        // Update last height for next point
        endPoint = points.lower_bound(newPoint);
        auto nextPoint = points.upper_bound(*endPoint);
        if (nextPoint != points.end()) {
            Point tempPoint = {nextPoint->x, nextPoint->h, endPoint->h};
            points.erase(nextPoint);
            points.insert(tempPoint);
        }

        // Add start point
        points.insert(newPoint);

        postAdd:
        currP %= MOD;
        if (currP < 0) currP += MOD;
        answer = answer * currP % MOD;
        /*
        cout << currP << endl;
        for (auto x : points) {
            cout << x.x << ' ' << x.h << ' ' << x.lh << endl;
        }
        */
    }

    fout << "Case #" << tn << ": " << answer << endl;
}

void parseInput(int tn) {
    int K;
    ll Al, Bl, Cl, Dl, Aw, Bw, Cw, Dw, Ah, Bh, Ch, Dh;
    fin >> N >> K;
    for (int i = 0; i < K; i++) {
        fin >> rooms[i].l;
    }
    fin >> Al >> Bl >> Cl >> Dl;
    for (int i = 0; i < K; i++) {
        fin >> rooms[i].w;
    }
    fin >> Aw >> Bw >> Cw >> Dw;
    for (int i = 0; i < K; i++) {
        fin >> rooms[i].h;
    }
    fin >> Ah >> Bh >> Ch >> Dh;
    for (int i = K; i < N; i++) {
        rooms[i].l = (Al * rooms[i-2].l + Bl * rooms[i-1].l + Cl) % Dl + 1;
        rooms[i].w = (Aw * rooms[i-2].w + Bw * rooms[i-1].w + Cw) % Dw + 1;
        rooms[i].h = (Ah * rooms[i-2].h + Bh * rooms[i-1].h + Ch) % Dh + 1;
    }
    /*
    for (int i = 0; i < N; i++) {
        cout << rooms[i].l << " " << rooms[i].w << " " << rooms[i].h << endl;
    }
    cout << "----" << endl;
    */
    solve(tn);
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) parseInput(i);
    return 0;
}