#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;

const int MAXN = 1e5+5, MAXSEG = 4e6, MAXSQRTN = 330;

int N, K, Q, groupSize, numGroups;
int H[MAXN], version[MAXN];
ll answers[MAXN];
struct Query {
    int l, r, id;
    bool operator<(const Query& o) const {
        return r < o.r;
    }
};
vector<Query> queries[MAXSQRTN];

ll segOps = 0, rootOps = 0;

struct SegmentTree {
    int currNode = 1;
    int V[MAXSEG], L[MAXSEG], R[MAXSEG];
    int currVersion = -1;
    int root[MAXN*2];

    void merge(int n) {
        int lv = L[n] ? V[L[n]] : 0;
        int rv = R[n] ? V[R[n]] : 0;
        V[n] = lv + rv;
    }

    int newNode(int v) {
        V[currNode] = v;
        L[currNode] = 0;
        R[currNode] = 0;
        return currNode++;
    }

    int copyNode(int n) {
        V[currNode] = V[n];
        L[currNode] = L[n];
        R[currNode] = R[n];
        return currNode++;
    }

    int init(int lb = 0, int ub = N-1) {
        int n = newNode(0);
        if (lb != ub) {
            L[n] = init(lb, ((lb+ub)>>1));
            R[n] = init(((lb+ub)>>1)+1, ub);
        }
        return n;
    }

    int update(int i, int v, int lb, int ub, int n) {
        n = copyNode(n);
        if (lb == ub) {
            V[n] += v;
            return n;
        }
        int cut = (lb+ub)>>1;
        if (cut < i) {
            R[n] = update(i, v, cut+1, ub, R[n]);
        } else {
            L[n] = update(i, v, lb, cut, L[n]);
        }
        merge(n);
        return n;
    }

    void update(int i, int v) {
        int n = update(i, v, 0, N-1, root[currVersion]);
        root[++currVersion] = n;
    }

    int queryLeft(int r, int lb, int ub, int n) {
        int result = 0, cut;
        while (lb != ub) {
            //segOps++;
            cut = (lb+ub)>>1;
            if (r > cut) {
                result += V[L[n]];
                n = R[n];
                lb = cut+1;
            } else {
                n = L[n];
                ub = cut;
            }
        }
        result += V[n];
        return result;
    }

    int queryRight(int l, int lb, int ub, int n) {
        int result = 0, cut;
        while (lb != ub) {
            //segOps++;
            cut = (lb+ub)>>1;
            if (l > cut) {
                n = R[n];
                lb = cut+1;
            } else {
                result += V[R[n]];
                n = L[n];
                ub = cut;
            }
        }
        result += V[n];
        return result;
    }

    int query(int l, int r, int v, int lb = 0, int ub = N-1) {
        int n = root[v], cut;
        bool cut1, cut2;
        while (true) {
            //segOps++;
            if (lb == l && ub == r) return V[n];
            cut = (lb+ub)>>1;
            cut1 = l <= cut;
            cut2 = r <= cut;
            if (cut1 && cut2) {
                n = L[n];
                ub = cut;
            } else if (!cut1 && !cut2) {
                n = R[n];
                lb = cut + 1;
            } else return queryRight(l, lb, cut, L[n]) + queryLeft(r, cut+1, ub, R[n]);
        }
    }

    void print(int n, int indent = 0) {
        if (L[n]) print(L[n], indent + 1);
        for (int i = 0; i < indent; i++) cout << "  ";
        cout << "(" << V[n] << ")" << endl;
        if (R[n]) print(R[n], indent + 1);
    }
};

SegmentTree segt;

void evalQueries(int group) {
    int startI = groupSize * group;
    int qi = 0;
    ll numPairs = 0, extraPairs;
    vector<Query>& currGroup = queries[group];
    for (int i = startI; i < N; i++) {
        //rootOps++;
        // Add current element
        numPairs += segt.query(startI, i, version[i]) - 1;
        while (currGroup[qi].r == i) {
            // Answer this query
            Query& q = currGroup[qi++];
            extraPairs = 0;
            for (int j = startI; j < q.l; j++) {
                //rootOps++;
                extraPairs += segt.query(j, i, version[j]) - 1;
            }
            answers[q.id] = numPairs - extraPairs;
            
        }
    }
}

int main() {
    // cerr << "start" << endl;
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> H[i];

    // Generate persistent segment tree
    segt.root[++segt.currVersion] = segt.init();
    vector<pair<int, int>> sh;
    for (int i = 0; i < N; i++) sh.emplace_back(H[i], i);
    sort(sh.begin(), sh.end());

    int li = 0, ri = 0;
    for (int mi = 0; mi < N; mi++) {
        while (sh[li].first < sh[mi].first - K) {
            segt.update(sh[li].second, -1);
            li++;
        }
        while (ri != N && sh[ri].first <= sh[mi].first + K) {
            segt.update(sh[ri].second, 1);
            ri++;
        }
        version[sh[mi].second] = segt.currVersion;
        // cout << "Version " << mi << endl;
        // for (int j = 0; j < N; j++) cout << segt.query(j, j, segt.currVersion);
        // cout << endl;
    }
    // cerr << "segtree done" << endl;

    // Generate query groups
    groupSize = round(sqrt(N));
    numGroups = (N-1) / groupSize + 1;
    cin >> Q;
    int l, r;
    for (int i = 0; i < Q; i++) {
        cin >> l >> r;
        int group = l / groupSize;
        queries[group].push_back({l, r, i});
    }
    for (int i = 0; i < numGroups; i++) {
        queries[i].push_back({-1, MAXN, -1});
        sort(queries[i].begin(), queries[i].end());
        evalQueries(i);
    }
    // cerr << "rootOps " << rootOps << endl;
    // cerr << "segOps " << segOps << endl;
    // cerr << "segNodes " << segt.currNode << endl;
    // cerr << "segVersions " << segt.currVersion+1 << endl;

    for (int i = 0; i < Q; i++) cout << answers[i] << '\n';
    return 0;
}