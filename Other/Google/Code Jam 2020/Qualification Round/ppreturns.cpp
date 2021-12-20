#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Segment {
    int l, r, i;

    /**
    Sort by rightmost endpoint, breaking ties by leftmost endpoint.
    **/
    bool operator<(const Segment& o) const {
        if (r == o.r) return l < o.l;
        else return r < o.r;
    }
};

void solve(int tn) {
    cout << "Case #" << tn << ": ";
    int N;
    scanf("%d", &N);
    Segment segments[N];

    int l, r;
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &l, &r);
        segments[i] = {l, r-1, i};
    }

    sort(segments, segments+N);

    // for (int i = 0; i < N; i++) printf("%d %d\n", segments[i].l, segments[i].r);

    int cLoc = -1, jLoc = -1;
    bool cValid, jValid;
    string out(N, ' ');

    // cout << out.max_size() << endl;

    for (Segment s : segments) {
        cValid = cLoc < s.l;
        jValid = jLoc < s.l;
        if (cValid && jValid) {
            if (cLoc < jLoc) {
                // Use jLoc since it ends later
                jLoc = s.r;
                out[s.i] = 'J';
            } else {
                // Use cLoc since it ends later
                cLoc = s.r;
                out[s.i] = 'C';
            }
        } else if (cValid) {
            cLoc = s.r;
            out[s.i] = 'C';
        } else if (jValid) {
            jLoc = s.r;
            out[s.i] = 'J';
        } else {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    }

    cout << out << endl;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) solve(i);
    return EXIT_SUCCESS;
}
