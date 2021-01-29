#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 1024;

int N;
vector<int> adj[MAXN], revAdj[MAXN], golorp, topoOrdering;
set<int> currValid;
int inEdges[MAXN], nums[MAXN];

int main() {
    N = 1;
    int jawLengthToI[MAXN];
    for (int i = 0; i < MAXN; i++) jawLengthToI[i] = -1;

    // Parse expression
    int currLength = 0;
    bool mustBeZero = false;
    cin.get();
    char c = cin.get();
    while (true) {
        if (c == ')') break;
        mustBeZero = (c == '/');
        currLength = 0;
        while (true) {
            c = cin.get();
            if (c != '_') break;
            else currLength++;
        }
        if (jawLengthToI[currLength] == -1) {
            jawLengthToI[currLength] = N++;
        }
        if (mustBeZero) {
            adj[0].push_back(jawLengthToI[currLength]);
            revAdj[jawLengthToI[currLength]].push_back(0);
        }
        golorp.push_back(jawLengthToI[currLength]);
    }

    // Parse constraints
    cin.get();
    c = cin.get();
    while (true) {
        if (c == '.') break;
        int length1 = 0, length2 = 0;
        while (true) {
            c = cin.get();
            if (c != '_') break;
            length1++;
        }
        bool isGreater = (c == '>');
        while (true) {
            c = cin.get();
            if (c != '_') break;
            length2++;
        }
        length1 = jawLengthToI[length1];
        length2 = jawLengthToI[length2];
        if (isGreater) {
            adj[length2].push_back(length1);
            revAdj[length1].push_back(length2);
        } else {
            adj[length1].push_back(length2);
            revAdj[length2].push_back(length1);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int e : adj[i]) {
            inEdges[e]++;
        }
    }

    for (int i = 0; i < N; i++) {
        if (inEdges[i] == 0) currValid.insert(i);
    }

    while (!currValid.empty()) {
        // Go in increasing order
        int n = *currValid.begin();
        currValid.erase(currValid.begin());
        topoOrdering.push_back(n);
        for (int e : adj[n]) {
            inEdges[e]--;
            if (inEdges[e] == 0) currValid.insert(e);
        }
    }

    if (topoOrdering.size() != N) {
        // No topological ordering
        cout << "false\n";
        return 0;
    }

    // Assign numbers based on topological ordering
    nums[0] = 0;
    for (int i : topoOrdering) {
        nums[i] = 0;
        for (int e : revAdj[i]) {
            nums[i] = max(nums[e] + 1, nums[i]);
        }
        if (nums[i] > 9) {
            // Invalid
            cout << "false\n";
            return 0;
        }
    }

    // Output golorp values
    for (int x : golorp) cout << nums[x];
    cout << '\n';
    return 0;
}