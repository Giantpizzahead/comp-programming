#include <iostream>
#include <random>
#include <ctime>
using namespace std;
using ll = long long;
const ll INF = 1e18;

struct Treap {
    ll h, max1, max2, sum, lazyA = -1, lazyB = -1;
    int p, s = 1, cmax1 = 0;
    Treap* l = nullptr;
    Treap* r = nullptr;

    Treap(ll h, int p = rand() * rand()) : h(h), max1(-INF), max2(-INF), sum(h), p(p) {}

    void recalc() {
        ll lm1 = -INF, lm2 = -INF, lcm1 = 0, lsum = 0, rm1 = -INF, rm2 = -INF, rcm1 = 0, rsum = 0;
        int ls = 0, rs = 0;
        if (l) {
            if (l->h > l->max1) {
                lm1 = l->h;
                lcm1 = 1;
                lm2 = l->max1;
            } else if (l->h == l->max1) {
                lm1 = l->h;
                lcm1 = l->cmax1 + 1;
                lm2 = l->max2;
            } else {
                lm1 = l->max1;
                lcm1 = l->cmax1;
                lm2 = max(l->max2, l->h);
            }
            lsum = l->sum;
            ls = l->s;
        }
        if (r) {
            if (r->h > r->max1) {
                rm1 = r->h;
                rcm1 = 1;
                rm2 = r->max1;
            } else if (r->h == r->max1) {
                rm1 = r->h;
                rcm1 = r->cmax1 + 1;
                rm2 = r->max2;
            } else {
                rm1 = r->max1;
                rcm1 = r->cmax1;
                rm2 = max(r->max2, r->h);
            }
            rsum = r->sum;
            rs = r->s;
        }

        s = ls + rs + 1;
        sum = lsum + rsum + h;
        if (lm1 == rm1) {
            max1 = lm1;
            cmax1 = lcm1 + rcm1;
            max2 = max(lm2, rm2);
        } else if (lm1 > rm1) {
            max1 = lm1;
            cmax1 = lcm1;
            max2 = max(lm2, rm1);
        } else {
            max1 = rm1;
            cmax1 = rcm1;
            max2 = max(lm1, rm2);
        }
    }

    void putLazy(ll a, ll b) {
        // Evaluate at this node
        sum -= h;
        h = min(h + a, b);
        sum += h;
        ll cutoff = b - a;
        if (cutoff <= max2) {
            // cout << "going down" << endl;
            // Cannot put lazy here; must go down
            prop();
            if (l) l->putLazy(a, b);
            if (r) r->putLazy(a, b);
            recalc();
            return;
        } else if (cutoff < max1) {
            // cout << "stop max1" << endl;
            // Changes only max1 (relative to rest)
            sum += a * (s-1);
            max1 += a;
            max2 += a;
            ll delta = max1 - b;
            sum -= cmax1 * delta;
            max1 = b;
        } else {
            // cout << "stop same" << endl;
            // Changes everything the same
            sum += a * (s-1);
            max1 += a;
            max2 += a;
        }

        if (lazyA == -1) {
            // New lazy
            lazyA = a;
            lazyB = b;
        } else {
            // Combine lazy
            lazyA += a;
            lazyB = min(lazyB + a, b);
        }
    }

    void prop() {
        if (lazyA != -1) {
            if (l) l->putLazy(lazyA, lazyB);
            if (r) r->putLazy(lazyA, lazyB);
            lazyA = -1;
            lazyB = -1;
        }
    }
};

pair<Treap*, Treap*> split(Treap* t, int numLeft) {
    if (!t) return {nullptr, nullptr};
    t->prop();
    int ls = t->l ? t->l->s : 0;
    if (ls >= numLeft) {
        // Split in left
        auto p = split(t->l, numLeft);
        t->l = p.second;
        t->recalc();
        return {p.first, t};
    } else {
        // Split in right
        auto p = split(t->r, numLeft - ls - 1);
        t->r = p.first;
        t->recalc();
        return {t, p.second};
    }
}

Treap* join(Treap* t1, Treap* t2) {
    if (!t1) return t2;
    else if (!t2) return t1;
    else if (t1->p > t2->p) {
        // t1 is new root
        t1->prop();
        t1->r = join(t1->r, t2);
        t1->recalc();
        return t1;
    } else {
        // t2 is new root
        t2->prop();
        t2->l = join(t1, t2->l);
        t2->recalc();
        return t2;
    }
}

void print(Treap* t, int indent = 0) {
    if (!t) return;
    print(t->l, indent + 1);
    for (int i = 0; i < indent; i++) cout << "  ";
    cout << "(" << t->h << ", " << t->sum << ", " << t->max1 << ", " << t->max2 << ", " << t->lazyA << ", " << t->lazyB << ")" << endl;
    print(t->r, indent + 1);
}

void slice(Treap* t, ll h) {
    t->putLazy(0, h);
    // t->h = min(t->h, h);
    // if (t->l) slice(t->l, h);
    // if (t->r) slice(t->r, h);
    // t->recalc();
}

void grow(Treap* t, ll x) {
    t->putLazy(x, INF);
    // t->h += x;
    // if (t->l) grow(t->l, x);
    // if (t->r) grow(t->r, x);
    // t->recalc();
}

int N, Q;
Treap* treap;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // srand(time(NULL));
    cin >> N >> Q;
    int t, l, r, h;
    for (int i = 0; i < N; i++) {
        cin >> h;
        treap = join(treap, new Treap(h));
    }
    // print(treap);
    for (int i = 0; i < Q; i++) {
        cin >> t >> l >> r;
        auto p = split(treap, r);
        auto p2 = split(p.first, l-1);
        Treap* lt = p2.first;
        Treap* mt = p2.second;
        Treap* rt = p.second;
        if (t == 1) {
            // Slice
            cin >> h;
            slice(mt, h);
        } else if (t == 2) {
            // Transplant
            swap(mt, rt);
        } else {
            // Grow
            cin >> h;
            grow(mt, h);
        }
        treap = join(join(lt, mt), rt);
        cout << treap->sum << endl;
        // print(treap);
    }
    return 0;
}