#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
using ll = long long;
using namespace std;

const int MAXN = 1e5+5, MAXSQRTN = 330, MAXH = 1e9+1;

int N, groupSize, numGroups, K, Q;
struct Query {
    int l, r, id;
};
vector<Query> queries[MAXSQRTN];
int H[MAXN];
ll answers[MAXN];

struct BIT {
    unordered_map<int, int> V;

    void reset() {
        V.clear();
    }

    void update(int i, int v) {
        i++;
        while (i <= MAXH) {
            V[i] += v;
            i += i & -i;
        }
    }

    int query(int i) {
        i++;
        int r = 0;
        while (i > 0) {
            r += V[i];
            i -= i & -i;
        }
        return r;
    }

    int query(int l, int r) {
        return query(r) - query(l-1);
    }
};

BIT bit;

void evalQueries(int group) {
    bit.reset();
    int startI = groupSize * group;
    int qi = 0;
    ll currPairs = 0;
    for (int i = startI; i < N; i++) {
        // Add current element
        currPairs += bit.query(H[i] - K, H[i] + K);
        bit.update(H[i], 1);
        // Evaluate queries ending here
        ll oldPairs = currPairs;
        while (qi != queries[group].size() && queries[group][qi].r == i) {
            // Move left pointer to correct location
            for (int j = startI; j < queries[group][qi].l; j++) {
                // Remove this element
                bit.update(H[j], -1);
                currPairs -= bit.query(H[j] - K, H[j] + K);
            }
            // Record query answer
            answers[queries[group][qi].id] = currPairs;
            // Backtrack
            currPairs = oldPairs;
            for (int j = queries[group][qi].l - 1; j >= startI; j--) {
                // Add this element
                bit.update(H[j], 1);
            }
            qi++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;
    groupSize = round(sqrt(N));
    numGroups = (N-1) / groupSize + 1;
    // cout << "info " << groupSize << " " << numGroups << endl;
    for (int i = 0; i < N; i++) cin >> H[i];
    cin >> Q;
    int l, r;
    for (int i = 0; i < Q; i++) {
        cin >> l >> r;
        int group = l / groupSize;
        queries[group].push_back({l, r, i});
    }
    for (int i = 0; i < numGroups; i++) {
        sort(queries[i].begin(), queries[i].end(), [](const Query& a, const Query& b) {
            return a.r < b.r;
        });
    }

    // Evaluate queries
    for (int g = 0; g < numGroups; g++) {
        evalQueries(g);
    }

    for (int i = 0; i < Q; i++) {
        cout << answers[i] << '\n';
    }
    return 0;
}
