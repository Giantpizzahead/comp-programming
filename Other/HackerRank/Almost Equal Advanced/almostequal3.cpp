#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;

const int MAXN = 1e5+5, MAXSQRTN = 330;

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

struct SegmentTree {
    struct Node {
        int v, lb, ub;
        Node* left;
        Node* right;
        Node(int v, int lb, int ub) : v(v), lb(lb), ub(ub), left(nullptr), right(nullptr) {}
        Node(Node* n) : v(n->v), lb(n->lb), ub(n->ub), left(n->left), right(n->right) {}

        void merge() {
            int lv = left ? left->v : 0;
            int rv = right ? right->v : 0;
            v = lv + rv;
        }
    };

    int currVersion = -1;
    Node* root[MAXN*2];

    Node* init(int lb = 0, int ub = N-1) {
        Node* n = new Node(0, lb, ub);
        if (lb != ub) {
            n->left = init(lb, (lb+ub)/2);
            n->right = init((lb+ub)/2+1, ub);
        }
        return n;
    }

    Node* update(int i, int v, Node* n) {
        n = new Node(n);
        if (n->lb == n->ub) {
            n->v += v;
            return n;
        }
        if ((n->lb + n->ub) / 2 < i) {
            n->right = update(i, v, n->right);
        } else {
            n->left = update(i, v, n->left);
        }
        n->merge();
        return n;
    }

    void update(int i, int v) {
        Node* n = update(i, v, root[currVersion]);
        root[++currVersion] = n;
    }

    int queryLeft(int r, Node* n) {
        int result = 0;
        while (n->lb != n->ub) {
            if (r <= n->left->ub) n = n->left;
            else {
                result += n->left->v;
                n = n->right;
            }
        }
        result += n->v;
        return result;
    }

    int queryRight(int l, Node* n) {
        int result = 0;
        while (n->lb != n->ub) {
            if (l >= n->right->lb) n = n->right;
            else {
                result += n->right->v;
                n = n->left;
            }
        }
        result += n->v;
        return result;
    }

    int query(int l, int r, int v) {
        Node* n = root[v];
        while (true) {
            if (n->lb == l && n->ub == r) return n->v;
            int cut = (n->lb + n->ub) / 2 + 1;
            if ((l < cut) == (r < cut)) n = (l < cut) ? n->left : n->right;
            else return queryRight(l, n->left) + queryLeft(r, n->right);
        }
        // return queryLeft(r, root[v]) - (l == 0 ? 0 : queryLeft(l-1, root[v]));
    }

    /*
    int query(int l, int r, Node* n) {
        if (l > n->ub || r < n->lb) return 0;
        else if (n->lb >= l && n->ub <= r) return n->v;
        return query(l, r, n->left) + query(l, r, n->right);
    }

    int query(int l, int r, int v) {
        return query(l, r, root[v]);
    }
    */

    void print(Node* n, int indent = 0) {
        if (n->left) print(n->left, indent + 1);
        for (int i = 0; i < indent; i++) cout << "  ";
        cout << "(" << n->v << ", " << n->lb << ", " << n->ub << ")" << endl;
        if (n->right) print(n->right, indent + 1);
    }
};

SegmentTree segt;

void evalQueries(int group) {
    int startI = groupSize * group;
    int qi = 0;
    ll numPairs = 0;
    vector<Query>& currGroup = queries[group];
    for (int i = startI; i < N; i++) {
        // Add current element
        numPairs += segt.query(startI, i, version[i]) - 1;
        while (currGroup[qi].r == i) {
            // Answer this query
            Query& q = currGroup[qi++];
            ll extraPairs = 0;
            for (int j = startI; j < q.l; j++) {
                extraPairs += segt.query(j, i, version[j]) - 1;
            }
            answers[q.id] = numPairs - extraPairs;
        }
    }
}

int main() {
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

    for (int i = 0; i < Q; i++) cout << answers[i] << '\n';
    return 0;
}