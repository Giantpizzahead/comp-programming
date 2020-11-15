#include <iostream>
#include <map>
#include <set>

using namespace std;
using ll = long long;
using ld = long double;

const int MAXN = 1005;
const ld EPSILON = 0.0000000001;

int N;
ld X[MAXN], Y[MAXN];
ll numLines;
map<ld, set<ld>*> lines;

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
    }

    numLines = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            ld slope = (X[j] - X[i] == 0 ? 9999999 : (Y[j] - Y[i]) / (X[j] - X[i]));
            auto x = lines.lower_bound(slope - EPSILON);
            set<ld>* yints;
            if (x != lines.end() && x->first - EPSILON < slope) {
                // Same slope
                yints = x->second;
                slope = x->first;
            } else {
                // Doesn't exist yet
                yints = new set<ld>();
                lines[slope] = yints;
            }

            ld yint = (slope > 9999998 ? X[i] : Y[i] - slope * X[i]);
            auto t = yints->lower_bound(yint - EPSILON);
            if (t != yints->end() && *t - EPSILON < yint) {
                // Same yint; same line
                continue;
            } else {
                // Add new line
                yints->insert(yint);
                numLines++;
            }
        }
    }

    // Count intersections
    ll answer = numLines * (numLines - 1) / 2;
    for (auto x : lines) {
        answer -= x.second->size() * (x.second->size() - 1) / 2;
        // cout << x.second->size() << " slope " << x.first << endl;
    }
    cout << answer << endl;
    return 0;
}