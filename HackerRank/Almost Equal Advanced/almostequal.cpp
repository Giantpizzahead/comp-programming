#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <ctime>
using ll = long long;
using namespace std;

const int MAXN = 1e5+5, MAXSQRTN = 330, MAXH = 1e9;

int N, groupSize, numGroups, K, Q;
struct Query {
    int l, r, id;
};
vector<Query> queries[MAXSQRTN];
int H[MAXN];
ll answers[MAXN];

/*
struct SegmentTree {
    unordered_map<int, int> V;

    void reset() {
        V.clear();
    }

    void update(int i, int v, int n = 1, int lb = 0, int ub = MAXH) {
        if (lb == ub) {
            V[n] += v;
            return;
        } else if (i > (lb+ub)/2) {
            update(i, v, n*2+1, (lb+ub)/2+1, ub);
        } else {
            update(i, v, n*2, lb, (lb+ub)/2);
        }
        V[n] = V[n*2] + V[n*2+1];
    }

    int query(int l, int r, int n = 1, int lb = 0, int ub = MAXH) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return V[n];
        return query(l, r, n*2, lb, (lb+ub)/2) + query(l, r, n*2+1, (lb+ub)/2+1, ub);
    }
};

SegmentTree segt;
*/

struct Treap {
    int v, p, s, c;
    Treap* l = nullptr;
    Treap* r = nullptr;

    Treap(int v, int p = rand()) : v(v), p(p), s(1), c(1) {}

    void update() {
        int ls = l ? l->s : 0;
        int rs = r ? r->s : 0;
        s = ls + rs + c;
    }
    
    void reset() {
        if (l) l->reset();
        if (r) r->reset();
        delete this;
    }
};

Treap* join(Treap* t1, Treap* t2) {
    if (!t1) return t2;
    else if (!t2) return t1;
    else if (t1->p > t2->p) {
        t1->r = join(t1->r, t2);
        t1->update();
        return t1;
    } else {
        t2->l = join(t1, t2->l);
        t2->update();
        return t2;
    }
}

pair<Treap*, Treap*> split(Treap* t, int maxLeft) {
    if (!t) return {nullptr, nullptr};
    if (t->v > maxLeft) {
        // Split occurs in left ST
        auto p = split(t->l, maxLeft);
        t->l = p.second;
        t->update();
        return {p.first, t};
    } else {
        // Split occurs in right ST
        auto p = split(t->r, maxLeft);
        t->r = p.first;
        t->update();
        return {t, p.second};
    }
}

void printTreap(Treap* t, int indent = 0) {
    if (!t) return;
    if (t->l) printTreap(t->l, indent+1);
    for (int i = 0; i < indent; i++) cout << "  ";
    cout << t->v << ", " << t->c << ", " << t->s << endl;
    if (t->r) printTreap(t->r, indent+1);
}

Treap* treap = nullptr;
ll currPairs;

void treapInsert(int x) {
    auto p1 = split(treap, x - K - 1);
    Treap* tl = p1.first;
    auto p2 = split(p1.second, x + K);
    Treap* tr = p2.second;
    currPairs += p2.first ? p2.first->s : 0;
    auto p3 = split(p2.first, x - 1);
    auto p4 = split(p3.second, x);
    Treap* tm1 = p3.first;
    Treap* tm2 = p4.first;
    Treap* tm3 = p4.second;
    if (tm2) {
        tm2->c++;
        tm2->s++;
    } else tm2 = new Treap(x);
    treap = join(join(join(join(tl, tm1), tm2), tm3), tr);
    // cout << "insert " << x << endl;
}

void treapDelete(int x) {
    auto p1 = split(treap, x - K - 1);
    Treap* tl = p1.first;
    auto p2 = split(p1.second, x + K);
    Treap* tr = p2.second;
    currPairs -= p2.first->s - 1;
    auto p3 = split(p2.first, x - 1);
    auto p4 = split(p3.second, x);
    Treap* tm1 = p3.first;
    Treap* tm2 = p4.first;
    Treap* tm3 = p4.second;
    if (tm2->c == 1) {
        tm2->reset();
        tm2 = nullptr;
    } else {
        tm2->c--;
        tm2->s--;
    }
    treap = join(join(join(join(tl, tm1), tm2), tm3), tr);
    // cout << "delete " << x << endl;
}

void evalQueries(int group) {
    if (treap) {
        treap->reset();
        treap = nullptr;
    }
    int startI = groupSize * group;
    int qi = 0;
    currPairs = 0;
    for (int i = startI; i < N; i++) {
        // Add current element
        treapInsert(H[i]);
        // printTreap(treap);
        // Evaluate queries ending here
        while (qi != queries[group].size() && queries[group][qi].r == i) {
            // Move left pointer to correct location
            for (int j = startI; j < queries[group][qi].l; j++) {
                // Remove this element
                treapDelete(H[j]);
                // printTreap(treap);
            }
            // Record query answer
            answers[queries[group][qi].id] = currPairs;
            // Backtrack
            for (int j = queries[group][qi].l - 1; j >= startI; j--) {
                // Add this element
                treapInsert(H[j]);
                // printTreap(treap);
            }
            qi++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(NULL));
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