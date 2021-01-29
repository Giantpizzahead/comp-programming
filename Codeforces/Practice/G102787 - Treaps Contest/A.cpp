#include <iostream>
#include <random>
#include <chrono>
using namespace std;

struct Treap {
    int v, p, s = 1;
    Treap* l = nullptr;
    Treap* r = nullptr;

    Treap(int v, int p = rand() * rand()) : v(v), p(p) {}

    void recalc() {
        s = (l ? l->s : 0) + (r ? r->s : 0) + 1;
    }
};

pair<Treap*, Treap*> split(Treap* t, int numLeft) {
    if (!t) return {nullptr, nullptr};
    int ls = t->l ? t->l->s : 0;
    if (ls >= numLeft) {
        // Split will be on left
        auto p = split(t->l, numLeft);
        t->l = p.second;
        t->recalc();
        return {p.first, t};
    } else {
        // Split will be on right
        auto p = split(t->r, numLeft - ls - 1);
        t->r = p.first;
        t->recalc();
        return {t, p.second};
    }
}

Treap* join(Treap* a, Treap* b) {
    if (!a) return b;
    else if (!b) return a;
    else if (a->p > b->p) {
        // a is new root
        a->r = join(a->r, b);
        a->recalc();
        return a;
    } else {
        // b is new root
        b->l = join(a, b->l);
        b->recalc();
        return b;
    }
}

Treap* insert(Treap* t, int x) {
    Treap* t2 = new Treap(x);
    return join(t, t2);
}

void print(Treap* t, int indent = 0) {
    if (!t) return;
    print(t->l, indent + 1);
    for (int i = 0; i < indent; i++) cout << "  ";
    cout << "(" << t->v << ", " << t->s << ", " << t->p << ")" << endl;
    print(t->r, indent + 1);
}

int N;
Treap* treap;

int main() {
    srand(chrono::system_clock::now().time_since_epoch().count());
    cin >> N;
    for (int i = 1; i <= N; i++) treap = insert(treap, i);
    // print(treap);
    int a, b, l;
    Treap *t1, *t2, *t3, *t4, *t5;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        if (b <= a) continue;
        l = min(b-a, N-b+1);
        // cout << a << " " << l << " " << b << " " << l << endl;
        // Swap [a, a+l] with [b, b+l]
        auto p = split(treap, b-1);
        auto p2 = split(p.second, l);
        t3 = p.first;
        t4 = p2.first;
        t5 = p2.second;
        p = split(t3, a-1);
        p2 = split(p.second, l);
        t1 = p.first;
        t2 = p2.first;
        t3 = p2.second;
        /*
        cout << "t1\n";
        print(t1);
        cout << endl;
        cout << "t2\n";
        print(t2);
        cout << endl;
        cout << "t3\n";
        print(t3);
        cout << endl;
        cout << "t4\n";
        print(t4);
        cout << endl;
        cout << "t5\n";
        print(t5);
        cout << endl;
        */
        treap = join(join(join(join(t1, t4), t3), t2), t5);
        // print(treap);
    }
    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ' ';
        auto p = split(treap, 1);
        treap = p.second;
        cout << p.first->v;
    }
    cout << endl;
    return 0;
}