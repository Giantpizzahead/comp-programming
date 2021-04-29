/**
 * Fix the rightmost leader, and sweep from cow 1 to cow N.
 * For every location, the left leader must be to the right of the 1st cow with the same breed ID as the sweeped one.
 * For all left leaders in this range, answer += # of middle cows that could be used with the left leader.
 * Each cow's "middle" range is just (Index of last seen cow with same breed ID, Current cow index).
 * 
 * Use a treap to simulate the above description efficiently. Each treap node stores the # of possible triples with that
 * left leader.
 * 
 * When adding a cow:
 * Subtract 1 from every left leader in the treap that's in its middle range.
 * Delete the old treap node with the same breed ID if it exists (cannot be left leader anymore).
 * Add the sum of the allowed left leader range to the answer.
 * Add a new treap node at the end (for this cow as the left leader).
 * Add 1 to every left leader in the treap that's in the new cow's middle range.
 * 
 * Runtime: O(N * log(N)) with high constant factor
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 2e5+5;

int N;
int B[MAXN];

struct Treap {
    int origI, p;
    int v = 0, sum = 0, delta = 0;
    int s = 1;
    Treap* l = nullptr;
    Treap* r = nullptr;
    
    Treap(int i) {
        origI = i;
        p = rand();
    }

    void merge() {
        s = 1;
        sum = v;
        if (l) {
            s += l->s;
            sum += l->sum;
        }
        if (r) {
            s += r->s;
            sum += r->sum;
        }
    }

    void prop() {
        if (l) {
            l->v += delta;
            l->sum += l->s * delta;
            l->delta += delta;
        }
        if (r) {
            r->v += delta;
            r->sum += r->s * delta;
            r->delta += delta;
        }
        delta = 0;
    }

    void print(int indent=0) {
        // prop();
        if (l) l->print(indent+1);
        rep(i, 0, indent) debug << "  ";
        debug << "(" << origI << ", " << s << ", " << sum << ")" << endl;
        if (r) r->print(indent+1);
    }

    void free() {
        if (l) l->free();
        if (r) r->free();
        delete this;
    }
};

// Nodes <= i on left, others on right
pair<Treap*, Treap*> split(Treap* t, int leftI) {
    if (!t) return {NULL, NULL};
    t->prop();
    if (t->origI > leftI) {
        auto p = split(t->l, leftI);
        t->l = p.second;
        t->merge();
        return {p.first, t};
    } else {
        auto p = split(t->r, leftI);
        t->r = p.first;
        t->merge();
        return {t, p.second};
    }
}

Treap* join(Treap* t1, Treap* t2) {
    if (!t1 && !t2) return NULL;
    else if (!t1) return t2;
    else if (!t2) return t1;
    t1->prop();
    t2->prop();
    if (t1->p > t2->p) {
        t1->r = join(t1->r, t2);
        t1->merge();
        return t1;
    } else {
        t2->l = join(t1, t2->l);
        t2->merge();
        return t2;
    }
}

void treapAdd(Treap* t, int x) {
    if (!t) return;
    debug << "adding " << x << " to" << endl;
    // t->print();
    t->v += x;
    t->sum += t->s * x;
    t->delta += x;
}

int treapQuery(Treap* t) {
    if (!t) return 0;
    debug << "querying" << endl;
    // t->print();
    debug << "result: " << t->sum << endl;
    return t->sum;
}

int seen1[MAXN], seen2[MAXN];
Treap* t = nullptr;

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> B[i];
        B[i]--;
        seen1[i] = -1;
        seen2[i] = -1;
    }
    
    ll answer = 0;
    Treap *t1, *t2, *t3;
    pair<Treap*, Treap*> p, p2;
    rep(i, 0, N) {
        debug << "\non " << i << endl;
        // if (t) t->print();
        int b = B[i];
        if (seen1[b] != -1) {
            // -= # active in middle
            p = split(t, seen2[b]);
            p2 = split(p.second, seen1[b]-1);
            t1 = p.first, t2 = p2.first, t3 = p2.second;
            treapAdd(t2, -1);
            t = join(join(t1, t2), t3);
            // Delete old treap node (t2)
            p = split(t, seen1[b]-1);
            p2 = split(p.second, seen1[b]);
            t1 = p.first, t2 = p2.first, t3 = p2.second;
            t2->free();
            t = join(t1, t3);
        }
        // Answer += Sum of allowed range
        p = split(t, seen1[b]);
        t1 = p.first, t2 = p.second;
        answer += treapQuery(t2);
        t = join(t1, t2);
        // Add new treap node at end
        t1 = new Treap(i);
        t = join(t, t1);
        // += # active in middle
        p = split(t, seen1[b]);
        p2 = split(p.second, i-1);
        t1 = p.first, t2 = p2.first, t3 = p2.second;
        treapAdd(t2, 1);
        t = join(join(t1, t2), t3);
        // Update seen
        seen2[b] = seen1[b];
        seen1[b] = i;
    }
    cout << answer << '\n';
    if (t) t->free();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(1337);
    solve();
    return 0;
}