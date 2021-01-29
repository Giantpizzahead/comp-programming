#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;

struct Treap {
    int v, c, p, s = 1;
    int num0 = 0, num1 = 0, left0 = 0, left1 = 0, right0 = 0, right1 = 0, answer;
    bool lazyXOR = false, lazyRev = false;
    Treap* l = nullptr;
    Treap* r = nullptr;

    Treap(int v, int c, int p = rand() * rand()) : v(v), c(c), p(p), s(c) {
        answer = c;
        if (v == 0) {
            num0 = c;
            left0 = c;
            right0 = c;
        } else {
            num1 = c;
            left1 = c;
            right1 = c;
        }
    }

    void doXOR() {
        swap(num0, num1);
        swap(left0, left1);
        swap(right0, right1);
        v = 1 - v;
        lazyXOR ^= true;
    }

    void doReverse() {
        swap(left0, right0);
        swap(left1, right1);
        swap(l, r);
        lazyRev ^= true;
    }

    void prop() {
        if (lazyXOR) {
            if (l) l->doXOR();
            if (r) r->doXOR();
        }
        if (lazyRev) {
            // Reverse
            if (l) l->doReverse();
            if (r) r->doReverse();
        }
        lazyXOR = false;
        lazyRev = false;
    }

    void recalc() {
        int ls = 0, ln0 = 0, ln1 = 0, ll0 = 0, ll1 = 0, lr0 = 0, lr1 = 0, la = 0;
        int rs = 0, rn0 = 0, rn1 = 0, rl0 = 0, rl1 = 0, rr0 = 0, rr1 = 0, ra = 0;
        if (l) {
            ls = l->s;
            ln0 = l->num0;
            ln1 = l->num1;
            ll0 = l->left0;
            ll1 = l->left1;
            lr0 = l->right0;
            lr1 = l->right1;
            la = l->answer;
        }
        if (r) {
            rs = r->s;
            rn0 = r->num0;
            rn1 = r->num1;
            rl0 = r->left0;
            rl1 = r->left1;
            rr0 = r->right0;
            rr1 = r->right1;
            ra = r->answer;
        }
        
        s = ls + rs + c;
        num0 = ln0 + rn0 + (v == 0 ? c : 0);
        num1 = ln1 + rn1 + (v == 1 ? c : 0);
        left0 = ll0;
        if (ll0 == ls && v == 0) {
            left0 = ll0 + c + rl0;
        }
        left1 = ll1;
        if (ll1 == ls && v == 1) {
            left1 = ll1 + c + rl1;
        }
        right0 = rr0;
        if (rr0 == rs && v == 0) {
            right0 = rr0 + c + lr0;
        }
        right1 = rr1;
        if (rr1 == rs && v == 1) {
            right1 = rr1 + c + lr1;
        }
        answer = max(la, ra);
        if (v == 0) answer = max(lr0 + rl0 + c, answer);
        else answer = max(lr1 + rl1 + c, answer);
    }
};

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

pair<Treap*, Treap*> split(Treap* t, int numLeft) {
    if (!t) return {nullptr, nullptr};
    t->prop();
    int ls = t->l ? t->l->s : 0;
    if (ls >= numLeft) {
        // Split on left
        auto p = split(t->l, numLeft);
        t->l = p.second;
        t->recalc();
        return {p.first, t};
    } else if (ls + t->c > numLeft) {
        // Split in middle (split node into two)
        Treap* lt = new Treap(t->v, numLeft - ls);
        Treap* rt = new Treap(t->v, t->c - (numLeft - ls));
        lt->l = t->l;
        rt->r = t->r;
        lt->recalc();
        rt->recalc();
        return split(join(lt, rt), numLeft);
    } else {
        // Split on right
        auto p = split(t->r, numLeft - ls - t->c);
        t->r = p.first;
        t->recalc();
        return {t, p.second};
    }
}

void print(Treap* t, int indent = 0) {
    if (!t) return;
    print(t->l, indent + 1);
    for (int i = 0; i < indent; i++) cout << "  ";
    cout << "(" << t->v << ", " << t->c << ", " << t->answer << ", " << t->lazyXOR << t->lazyRev << ")" << endl;
    print(t->r, indent + 1);
    if (indent == 0) cout << endl;
}

void doProp(Treap* t) {
    if (!t) return;
    t->prop();
    doProp(t->l);
    doProp(t->r);
    t->recalc();
}

int N, Q;
Treap* treap;

int main() {
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    // cout << seed << endl;
    srand(seed);
    cin >> N >> Q;
    string str;
    cin >> str;
    for (int i = 0; i < N; i++) {
        treap = join(treap, new Treap(str[i] == '1' ? 1 : 0, 1));
    }
    // doProp(treap);
    // print(treap);
    int t, l, r;
    for (int i = 0; i < Q; i++) {
        cin >> t >> l >> r;
        auto p = split(treap, r);
        auto p2 = split(p.first, l-1);
        Treap* lt = p2.first;
        Treap* mt = p2.second;
        Treap* rt = p.second;
        if (t == 1) {
            // XOR
            mt->doXOR();
        } else if (t == 2) {
            // Reverse
            mt->doReverse();
        } else {
            // Sort
            Treap* mt1 = (mt->num0 == 0) ? nullptr : new Treap(0, mt->num0);
            Treap* mt2 = (mt->num1 == 0) ? nullptr : new Treap(1, mt->num1);
            mt = join(mt1, mt2);
        }
        // print(lt);
        // print(mt);
        // print(rt);
        treap = join(join(lt, mt), rt);
        // doProp(treap);
        cout << treap->answer << '\n';
        // print(treap);
    }
    return 0;
}