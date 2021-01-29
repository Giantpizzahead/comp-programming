#include <iostream>
#include <random>
#include <ctime>
using namespace std;
using ll = long long;
const int MAXN = 5e5+5;

struct Treap {
    int pr, s = 1;
    ll v, sum;
    Treap* l = nullptr;
    Treap* r = nullptr;
    Treap* p = nullptr;

    Treap(int v, int pr = rand() * rand()) : v(v), pr(pr), sum(v) {}

    void recalc() {
        sum = (l ? l->sum : 0) + (r ? r->sum : 0) + v;
        s = (l ? l->s : 0) + (r ? r->s : 0) + 1;
    }
};

pair<Treap*, Treap*> split(Treap* t, int numLeft) {
    if (!t) return {nullptr, nullptr};
    int ls = (t->l ? t->l->s : 0);
    if (ls >= numLeft) {
        // Split in left
        auto p = split(t->l, numLeft);
        t->l = p.second;
        if (t->l) t->l->p = t;
        if (p.first) p.first->p = nullptr;
        t->recalc();
        return {p.first, t};
    } else {
        // Split in right
        auto p = split(t->r, numLeft - ls - 1);
        t->r = p.first;
        if (t->r) t->r->p = t;
        if (p.second) p.second->p = nullptr;
        t->recalc();
        return {t, p.second};
    }
}

Treap* join(Treap* t1, Treap* t2) {
    if (!t1) return t2;
    else if (!t2) return t1;
    else if (t1->pr > t2->pr) {
        // t1 is new root
        t1->r = join(t1->r, t2);
        if (t1->r) t1->r->p = t1;
        t1->recalc();
        return t1;
    } else {
        // t2 is new root
        t2->l = join(t1, t2->l);
        if (t2->l) t2->l->p = t2;
        t2->recalc();
        return t2;
    }
}

Treap* getRoot(Treap* t) {
    while (t->p != nullptr) t = t->p;
    return t;
}

void print(Treap* t, int indent = 0) {
    if (!t) return;
    print(t->l, indent + 1);
    for (int i = 0; i < indent; i++) cout << "  ";
    cout << "(" << t->v << ", " << t->sum << ")" << endl;
    print(t->r, indent + 1);
}

int Q;
Treap* treaps[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(NULL));
    cin >> Q;
    int t, y, z;
    for (int i = 1; i <= Q; i++) {
        cin >> t >> y;
        if (t == 1) {
            // New node
            treaps[i] = new Treap(y);
        } else if (t == 2) {
            cin >> z;
            // Merge groups if not same (y on left, z on right)
            Treap* t1 = getRoot(treaps[y]);
            Treap* t2 = getRoot(treaps[z]);
            if (t1 != t2) {
                // Merge groups
                treaps[i] = join(t1, t2);
            }
        } else if (t == 3) {
            cin >> z;
            // Split with z nodes on left
            Treap* t1 = getRoot(treaps[y]);
            if (t1->s > z) {
                auto p = split(t1, z);
                treaps[i] = p.first;
            }
        } else {
            // Query sum of values in group of y
            Treap* t1 = getRoot(treaps[y]);
            cout << t1->sum << endl;
        }
        // print(treaps[y]);
    }
    return 0;
}