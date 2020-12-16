#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using ll = long long;

const int MAXN = 3e5+5;

const ll BASE_POW = 79;
const ll MOD = 1e9+7;

ll basePow[MAXN];

struct Treap {
    int v, p, s = 1;
    ll preH, suffH;
    Treap* l = nullptr;
    Treap* r = nullptr;

    Treap(int v, int p = rand() * rand()) : v(v), p(p), preH(v), suffH(v) {}
};

void recalc(Treap* t) {
    int ls = 0, rs = 0;
    ll lph = 0, lsh = 0, rph = 0, rsh = 0;
    if (t->l) ls = t->l->s, lph = t->l->preH, lsh = t->l->suffH;
    if (t->r) rs = t->r->s, rph = t->r->preH, rsh = t->r->suffH;
    t->s = ls + rs + 1;
    t->preH = (lph * basePow[rs+1] + t->v * basePow[rs] + rph) % MOD;
    t->suffH = (rsh * basePow[ls+1] + t->v * basePow[ls] + lsh) % MOD;
}

pair<Treap*, Treap*> split(Treap* t, int numLeft) {
    if (!t) return {nullptr, nullptr};
    int ls = t->l ? t->l->s : 0;
    if (ls >= numLeft) {
        // Split will occur on left
        auto p = split(t->l, numLeft);
        t->l = p.second;
        recalc(t);
        return {p.first, t};
    } else {
        // Split will occur on right
        auto p = split(t->r, numLeft - ls - 1);
        t->r = p.first;
        recalc(t);
        return {t, p.second};
    }
}

Treap* join(Treap* t1, Treap* t2) {
    if (!t1) return t2;
    else if (!t2) return t1;
    else if (t1->p > t2->p) {
        // t1 is new root
        t1->r = join(t1->r, t2);
        recalc(t1);
        return t1;
    } else {
        // t2 is new root
        t2->l = join(t1, t2->l);
        recalc(t2);
        return t2;
    }
}

void print(Treap* t, int indent = 0) {
    if (!t) return;
    if (t->l) print(t->l, indent + 1);
    for (int i = 0; i < indent; i++) cout << "  ";
    cout << "(" << (char) t->v << ", " << t->preH - t->suffH << ")" << endl;
    if (t->r) print(t->r, indent + 1);
    if (indent == 0) cout << endl;
}

int N, Q;
Treap* treap;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    srand(chrono::system_clock::now().time_since_epoch().count());

    basePow[0] = 1;
    for (int i = 1; i < MAXN; i++) basePow[i] = basePow[i-1] * BASE_POW % MOD;
    cin >> N >> Q;
    string str;
    int t, l, r;
    char c;
    cin >> str;
    for (int i = 0; i < N; i++) treap = join(treap, new Treap(str[i]));
    // print(treap);
    for (int i = 0; i < Q; i++) {
        cin >> t;
        if (t == 1) {
            cin >> l >> r;
            // Delete characters
            auto p = split(treap, r);
            auto p2 = split(p.first, l-1);
            // Forget about the middle part (essentially deleting it)
            treap = join(p2.first, p.second);
        } else if (t == 2) {
            cin >> c >> l;
            // Insert character
            auto p = split(treap, l-1);
            treap = join(join(p.first, new Treap(c)), p.second);
        } else {
            cin >> l >> r;
            // Query palindrome
            auto p = split(treap, r);
            auto p2 = split(p.first, l-1);
            if (p2.second->preH == p2.second->suffH) cout << "yes\n";
            else cout << "no\n";
            treap = join(join(p2.first, p2.second), p.second);
        }
        // print(treap);
    }
    return 0;
}