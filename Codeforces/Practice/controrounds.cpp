#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAXN = 1000005;

int N;
int sets[MAXN], start[MAXN];
string str;

struct Group {
    char t;
    int i, n;
};

vector<Group> groups;

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> str;

    // Remove prefix of ?
    if (str[0] == '?') {
        bool changed = false;
        for (int i = 1; i < N; i++) {
            if (str[i] != '?') {
                changed = true;
                for (int j = 0; j < i; j++) str[j] = str[i];
                break;
            }
        }
        if (!changed) {
            // Whole string is ?
            for (int i = 0; i < N; i++) str[i] = '1';
        }
    }

    int lastI = 0;
    bool lastWasQ = true;
    for (int i = 1; i < N; i++) {
        if (str[lastI] != str[i]) {
            // Check if groups can be combined
            if (str[lastI] == '?' && groups[groups.size()-1].t == str[i]) {
                // This ? group is not needed
                lastI = groups[groups.size()-1].i;
                groups.pop_back();
            } else if (!lastWasQ && str[lastI] != '?') {
                // Add dummy ? group for easier implementation
                groups.push_back({'?', -1, 0});
                groups.push_back({str[lastI], lastI, i-lastI});
                lastI = i;
            } else {
                groups.push_back({str[lastI], lastI, i-lastI});
                lastI = i;
            }
            lastWasQ = (groups.empty() || groups[groups.size()-1].t == '?');
        }
    }
    if (str[lastI] == '?') {
        // This ? group is not needed (it's a suffix)
        lastI = groups[groups.size()-1].i;
        groups.pop_back();
    } else if (!lastWasQ) {
        groups.push_back({'?', -1, 0});
    }
    groups.push_back({str[lastI], lastI, N-lastI});

    int lastMaxUpdate = 0, lastLength = 0, lastQLength = 0;
    for (int i = 0; i < groups.size(); i++) {
        Group& g = groups[i];
        if (g.t == '?') {
            // Update everything
            int maxToUpdate = lastQLength + lastLength + g.n;
            for (int j = 1; j <= maxToUpdate; j++) {
                if (j > lastMaxUpdate) {
                    // Not updated; assume default value
                    start[j] = lastQLength;
                }
                // Figure out # of question marks to use on next batch
                int optimalCount = start[j] + lastLength + g.n;
                start[j] = min(g.n, optimalCount % j);
                optimalCount -= start[j];
                sets[j] += optimalCount / j;
            }
            lastQLength = g.n;
            lastMaxUpdate = maxToUpdate;
        } else {
            lastLength = g.n;
        }
    }
    // Update last part as well
    int maxToUpdate = lastQLength + lastLength;
    for (int i = 1; i <= maxToUpdate; i++) {
        if (i > lastMaxUpdate) start[i] = lastQLength;
        sets[i] += (start[i] + lastLength) / i;
    }

    for (int i = 1; i <= N; i++) {
        if (i != 1) cout << ' ';
        cout << sets[i];
    }
    cout << endl;

    /*
    for (Group& g : groups) {
        cout << g.i << ' ' << g.t << ' ' << g.n << endl;
    }
    */
}