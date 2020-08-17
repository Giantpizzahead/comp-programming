#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <string>
#include <set>

using namespace std;

string str;
int N;

struct Loc {
    int i, w;

    bool operator<(const Loc& o) const {
        return i < o.i;
    }
};

set<Loc> locs, tempLocs;

int main() {
    ios::sync_with_stdio(false);
    cin >> str;
    N = str.size();
    str += str;
    for (int i = 0; i < N; i++) locs.insert({i, 0});

    while (locs.size() > 1) {
        char bestNext = 'z';
        for (const Loc& l : locs) {
            // Include next character
            if (str[l.i + l.w] < bestNext) {
                // This one is lexigraphically minimal; delete all previous
                tempLocs.clear();
                bestNext = str[l.i + l.w];
            }
            if (str[l.i + l.w] == bestNext) {
                // Keep this one
                tempLocs.insert({l.i, l.w + 1});
            }
        }
        // Clear current locs
        locs.clear();
        // Merge substrings that overlap
        locs.insert(*tempLocs.rbegin());
        bool keepLast = true;
        Loc keepLastLoc;
        Loc last = *locs.rbegin();
        int longestWidth = -1;
        for (auto x = ++tempLocs.rbegin(); x != tempLocs.rend(); x++) {
            if (x->i + x->w == last.i) {
                // Overlap; merge the 2
                Loc newLoc = {x->i, x->w + last.w};
                locs.erase(last);
                locs.insert(newLoc);
                last = newLoc;
            } else {
                // If last one did not match longest width, remove it
                if (last.w < longestWidth) locs.erase(last);
                else if (last.w > longestWidth) {
                    // Erase everything but the last one
                    locs.clear();
                    locs.insert(last);
                    longestWidth = last.w;
                    // Save last loc
                    if (keepLast) {
                        keepLast = false;
                        keepLastLoc = last;
                    }
                }
                // Add new loc separately
                locs.insert(*x);
                last = *x;
            }
        }
        // Off by one
        if (last.w < longestWidth) locs.erase(last);
        else if (last.w > longestWidth) {
            locs.clear();
            locs.insert(last);
            longestWidth = last.w;
            if (keepLast) {
                keepLast = false;
                keepLastLoc = last;
            }
        }
        /*
        cout << "Locs: ";
        for (const Loc& l : locs) cout << "(" << l.i << ", " << l.w << ") ";
        cout << endl;
        cout << "Keep: " << keepLastLoc.i << " " << keepLastLoc.w << endl;
        */
        // Check looparound
        if (!keepLast) {
            Loc first = *locs.begin();
            if ((keepLastLoc.i + keepLastLoc.w) % N == first.i) {
                // Last one loops around to first, so must be longer
                locs.clear();
                locs.insert({keepLastLoc.i, keepLastLoc.w + first.w});
                longestWidth = keepLastLoc.w + first.w;
            }
        }
        tempLocs.clear();
        /*
        cout << "Locs: ";
        for (const Loc& l : locs) cout << "(" << l.i << ", " << l.w << ") ";
        cout << endl;
        */
    }

    int finalLoc = locs.begin()->i;
    cout << str.substr(finalLoc, N) << endl;
    return 0;
}