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

struct Segment {
    ll lx, rx, ly, ry;

    // Sort segments in order of increasing left x point
    bool operator<(const Segment& o) const {
        return lx < o.lx;
    }
};

Room rooms[MAXN];
// Dynamically track where rooms start and end using segments
set<Segment> segments;

void solve(int tn) {
    ll currP = 0, answer = 1;
    segments.clear();

    Room room;
    Segment currSeg;
    for (int i = 0; i < N; i++) {
        room = rooms[i];
        currSeg = {room.l, room.l + room.w, room.h, room.h};
        currP += room.w * 2 + room.h * 2;

        // Merge segments if needed
        if (!segments.empty()) {
            // Get segment with same x point
            auto segSame = segments.lower_bound(currSeg);
            if (segSame != segments.end() && segSame->lx == currSeg.lx) {
                // Same x coordinate; which encloses which?
                if (segSame->rx >= currSeg.rx) {
                    // cout << "this enc same" << endl;
                    // This segment is completely enclosed; no need to add it anymore
                    currP -= room.w * 2 + room.h * 2;
                    goto postAdd;
                } else {
                    // cout << "other enc same" << endl;
                    // Other segment is completely enclosed; delete it
                    currP -= (segSame->rx - segSame->lx) * 2;
                    currP -= room.h * 2;
                    segments.erase(segSame);
                }
            }
            // Get first segment with lower x point (if there is one)
            auto segLeft = segments.lower_bound(currSeg);
            if (segLeft != segments.begin()) {
                segLeft--;
                if (segLeft->rx >= currSeg.lx) {
                    // Overlap; merge the segments / update currP
                    if (segLeft->rx >= currSeg.rx) {
                        // cout << "enc left" << endl;
                        // This segment is completely enclosed; no need to add it anymore
                        currP -= room.w * 2 + room.h * 2;
                        goto postAdd;
                    } else {
                        // cout << "merge left" << endl;
                        // Merge segments (delete old one)
                        currP -= (segLeft->rx - currSeg.lx) * 2;
                        currP -= room.h * 2;
                        currSeg.lx = segLeft->lx;
                        currSeg.ly = segLeft->ly;
                        segments.erase(segLeft);
                    }
                }
            }
            // Get segments with higher x point
            while (true) {
                auto segRight = segments.lower_bound(currSeg);
                if (segRight == segments.end() || segRight->lx > currSeg.rx) break;
                // Overlap; merge the segments / update currP
                if (segRight->rx < currSeg.rx) {
                    // cout << "enc right" << endl;
                    // Other segment is completely enclosed; delete it entirely
                    currP -= (segRight->rx - segRight->lx) * 2;
                    currP -= room.h * 2;
                    segments.erase(segRight);
                } else {
                    // Merge segments (delete old one)
                    // cout << "merge right" << endl;
                    currP -= (currSeg.rx - segRight->lx) * 2;
                    currP -= room.h * 2;
                    currSeg.rx = segRight->rx;
                    currSeg.ry = segRight->ry;
                    segments.erase(segRight);
                }
            }
        }

        // Add the segment
        segments.insert(currSeg);

        postAdd:
        currP %= MOD;
        if (currP < 0) currP += MOD;
        answer = answer * currP % MOD;
        /*
        cout << currP << endl;
        for (auto x : segments) {
            cout << x.lx << ' ' << x.ly << ' ' << x.rx << ' ' << x.ry << endl;
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